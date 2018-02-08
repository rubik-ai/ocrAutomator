#include "BaseOcrWithLoader.h"
#include "Error.h"
#include "MuPDF.h"
#include "ArrayMemoryFileBuffer.h"

std::mutex Docapost::IA::Tesseract::BaseOcrWithLoader::mCreationThreadMutex{};
int Docapost::IA::Tesseract::BaseOcrWithLoader::mCurrentPdfCreationThread = 0;
#ifdef MAGICK
Docapost::IA::Tesseract::MemoryFileBuffer* Docapost::IA::Tesseract::BaseOcrWithLoader::ExtractPdfFromImageMagick(MasterFileStatus* file, const std::function<void(MasterFileStatus*)>& AddFile)
{
	try
	{
		std::lock_guard<std::mutex> lock(*file->mutex_siblings);
		if (file->fileSize > 0)
		{
			return file->data;
		}
		Magick::ReadOptions options;
		options.density(Magick::Geometry(250, 250));
		std::list<Magick::Image> images;

		Magick::readImages(&images, file->name, options);

		size_t i;
		std::list<Magick::Image>::iterator image;
		for (image = images.begin(), i = 0; image != images.end(); image++, i++)
		{
			if ((*file->siblings)[i] == nullptr)
				continue;
			Magick::Blob blobOut;
			image->colorSpace(MagickCore::RGBColorspace);
			image->quality(80);
			image->density(Magick::Geometry(300, 300));
			image->resolutionUnits(MagickCore::ResolutionType::PixelsPerInchResolution);
			image->magick("JPEG");
			image->write(&blobOut);
			auto data = (char*)blobOut.data();
			(*file->siblings)[i]->data = new std::vector<l_uint8>(data, data + blobOut.length());
			(*file->siblings)[i]->fileSize = (*file->siblings)[i]->data->size();
			if (file->filePosition != (*file->siblings)[i]->filePosition)
			{
				AddFile((*file->siblings)[i]);
			}
		}
		return file->data;
	}
	catch (Magick::ErrorDelegate &ed)
	{
		BOOST_LOG_WITH_LINE(Log::CommonLogger, boost::log::trivial::warning) << "Cannot decode file " << file->name << " | " << ed.what() << std::endl;
		return nullptr;
	}
	catch (Magick::Exception &e)
	{
		BOOST_LOG_WITH_LINE(Log::CommonLogger, boost::log::trivial::warning) << "Cannot decode file " << file->name << " | " << e.what() << std::endl;
		return nullptr;
	}
	catch (...)
	{
		auto eptr = std::current_exception();
		auto n = eptr.__cxa_exception_type()->name();
		BOOST_LOG_WITH_LINE(Log::CommonLogger, boost::log::trivial::warning) << "Cannot decode file " << file->name << " | " << n << std::endl;
		return nullptr;
	}
	return nullptr;
}

Docapost::IA::Tesseract::MemoryFileBuffer* Docapost::IA::Tesseract::BaseOcrWithLoader::ExtractPdfFromMuPdf(MasterFileStatus * file, const std::function<void(MasterFileStatus*)>& AddFile) { return nullptr; }
#endif

#ifndef MAGICK
Docapost::IA::Tesseract::MemoryFileBuffer* Docapost::IA::Tesseract::BaseOcrWithLoader::ExtractPdfFromImageMagick(MasterFileStatus* file, const std::function<void(MasterFileStatus*)>& AddFile) { return nullptr; }

Docapost::IA::Tesseract::MemoryFileBuffer* Docapost::IA::Tesseract::BaseOcrWithLoader::ExtractPdfFromMuPdf(MasterFileStatus * file, const std::function<void(MasterFileStatus*)>& AddFile)
{
	CatchAllErrorSignals();
	CatchAllExceptions();

	try
	{
		BOOST_LOG_WITH_LINE(Log::CommonLogger, boost::log::trivial::trace) << "Extract PDF file " << file->name;
		Docapost::IA::MuPDF::MuPDF pdf;
		pdf.Extract(file, mImageFormat);
	}
	catch (std::exception &e)
	{
		BOOST_LOG_WITH_LINE(Log::CommonLogger, boost::log::trivial::warning) << "Cannot extract PDF file " << file->name << " error: " << e.what();
		std::lock_guard<std::mutex> lock(mCreationThreadMutex);
		mCurrentPdfCreationThread--;
		throw std::runtime_error("Cannot extract PDF file " + file->name + " error: " + e.what());
	}
	catch (std::runtime_error &e)
	{
		BOOST_LOG_WITH_LINE(Log::CommonLogger, boost::log::trivial::warning) << "Cannot extract PDF file " << file->name << " error: " << e.what();
		std::lock_guard<std::mutex> lock(mCreationThreadMutex);
		mCurrentPdfCreationThread--;
		throw std::runtime_error("Cannot extract PDF file " + file->name + " error: " + e.what());
	}

	bool first = false;
	for (auto s : *file->siblings)
	{
		if (s == nullptr) continue;
		/*if(file->filePosition != s->filePosition)
		{*/
		AddFile(s);
		//}
	}

	std::lock_guard<std::mutex> lock(mCreationThreadMutex);
	mCurrentPdfCreationThread--;
	return file->buffer;
}
Docapost::IA::Tesseract::MemoryFileBuffer* Docapost::IA::Tesseract::BaseOcrWithLoader::GetImage(MasterFileStatus * file, const std::function<void(MasterFileStatus*)>& AddFile)
{
	std::lock_guard<std::mutex> lock(*file->mutex_siblings);
	if (file->buffer != nullptr && file->buffer->len() > 0)
	{
		return file->buffer;
	}

	std::lock_guard<std::mutex> lockThread(mCreationThreadMutex);
	//BOOST_LOG_WITH_LINE(Log::CommonLogger, boost::log::trivial::trace) << "Concurrent PDF Creation " << mCurrentPdfCreationThread;
	if (mCurrentPdfCreationThread > mMaxPdfCreationThread)
	{
		// We put back the file on the list of file to process because we will not process it in this call
		AddFile(file);
		return nullptr;
	}

	mCurrentPdfCreationThread++;

	boost::thread(boost::bind(&Tesseract::BaseOcrWithLoader::ExtractPdfFromMuPdf, this, file, AddFile)).detach();
	return nullptr;
}
#endif

Docapost::IA::Tesseract::MemoryFileBuffer* Docapost::IA::Tesseract::BaseOcrWithLoader::LoadFile(MasterFileStatus* file, const std::function<void(MasterFileStatus*)>& AddFile) {
	if (file->filePosition >= 0)
	{
#ifdef MAGICK
		return ExtractPdfFromImageMagick(file, AddFile);
#endif
#ifndef MAGICK
		return GetImage(file, AddFile);
#endif
	}
	else
	{
		FILE* f = fopen(file->name.c_str(), "r");
		if (f == nullptr)
		{
			std::cerr << "Impossible d'ouvrir le fichier " << file->name << std::endl;
			throw std::runtime_error("Impossible d'ouvrir le fichier " + file->name);
		}

		// Determine file size
		fseek(f, 0, SEEK_END);
		size_t size = ftell(f);

		file->buffer = new ArrayMemoryFileBuffer(size);

		rewind(f);
		fread(file->buffer->data(), sizeof(unsigned char), size, f);
		fclose(f);

		return file->buffer;
	}
}