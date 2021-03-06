
#include "PDF/MuPDF.h"
#include <boost/thread.hpp>
#include "Base/Error.h"
#include "Master/MasterMemoryFileStatus.h"
#include "Master/MasterLocalFileStatus.h"

extern "C"
{
#include <mupdf/fitz.h>
}
#include "Buffer/ArrayMemoryFileBuffer.h"
#include "Buffer/JpegTurboMemoryFileBuffer.h"

// Dans le as d'une DLL fz_identity n'est pas connue, sous linux le logiciel est compiler avec des libs statics
#ifdef _WIN32
const fz_matrix fz_identity = { 1, 0, 0, 1, 0, 0 };
#endif

std::mutex Docapost::IA::MuPDF::MuPDF::mStaticContextMutex;
std::mutex Docapost::IA::MuPDF::MuPDF::mMutexes[FZ_LOCK_MAX];

Docapost::IA::MuPDF::MuPDF::MuPDF()
{
	mDrawLocks.lock = &MuPDF::s_lock;

	mDrawLocks.unlock = &MuPDF::s_unlock;

	mDrawLocks.user = this;

	initLocks();
	mContext = fz_new_context(NULL, &mDrawLocks, FZ_STORE_UNLIMITED);

	if (!mContext)
	{
		throw std::runtime_error("cannot create mupdf context");
	}

	/* Register the default file types to handle. */
	fz_try(mContext)
		fz_register_document_handlers(mContext);
	fz_catch(mContext)
	{
		auto msg = fz_caught_message(mContext);
		fz_drop_context(mContext);
		mContext = nullptr;
		throw std::runtime_error(std::string("cannot register document handlers: ") + msg);
	}
}

Docapost::IA::MuPDF::MuPDF::~MuPDF()
{
	if(mContext != nullptr)
		fz_drop_context(mContext);
}

int Docapost::IA::MuPDF::MuPDF::GetNbPage(std::string path)
{
	//std::lock_guard<std::mutex> lock(mContextMutex);
	fz_document *doc = nullptr;
	/* Open the document. */
	fz_try(mContext)
		doc = fz_open_document(mContext, path.c_str());
	fz_catch(mContext)
	{
		auto msg = fz_caught_message(mContext);
		fz_drop_context(mContext);
		mContext = nullptr;
		throw std::runtime_error(std::string("cannot open document: ") + msg);
	}

	int pageCount = 0;
	/* Count the number of pages. */
	fz_try(mContext)
		pageCount = fz_count_pages(mContext, doc);
	fz_catch(mContext)
	{
		auto msg = fz_caught_message(mContext);
		fz_drop_document(mContext, doc);
		throw std::runtime_error(std::string("cannot count number of pages: ") + msg);
	}
	fz_drop_document(mContext, doc);
	return pageCount;
}

int Docapost::IA::MuPDF::MuPDF::GetNbPage(char* pdf, int len)
{
	//std::lock_guard<std::mutex> lock(mContextMutex);
	fz_stream *stream = nullptr;
	fz_document *doc = nullptr;
	/* Open the document. */
	fz_try(mContext)
	{
		stream = fz_open_memory(mContext, (unsigned char*)pdf, len);
		doc = fz_open_document_with_stream(mContext, ".pdf", stream);
	}
	fz_catch(mContext)
	{
		auto msg = fz_caught_message(mContext);
		if (stream != nullptr)
			fz_drop_stream(mContext, stream);
		fz_drop_context(mContext);
		mContext = nullptr;
		throw std::runtime_error(std::string("cannot open document: ") + msg);
	}

	int pageCount = 0;
	/* Count the number of pages. */
	fz_try(mContext)
		pageCount = fz_count_pages(mContext, doc);
	fz_catch(mContext)
	{
		auto msg = fz_caught_message(mContext);
		fz_drop_document(mContext, doc);
		fz_drop_stream(mContext, stream);
		throw std::runtime_error(std::string("cannot count number of pages: ") + msg);
	}
	fz_drop_document(mContext, doc);
	fz_drop_stream(mContext, stream);
	return pageCount;
}

void Docapost::IA::MuPDF::MuPDF::Extract(MasterFileStatus* file, Docapost::IA::Tesseract::ImageFormatEnum format, ImageQuality quality)
{
	//BOOST_LOG_WITH_LINE(Log::CommonLogger, boost::log::trivial::trace) << "Begin extract PDF file";
	//std::lock_guard<std::mutex> lock(mContextMutex);
	fz_stream * stream = nullptr;
	fz_document *doc = nullptr;
	/* Open the document. */
	fz_try(mContext)
	{
		if (MasterLocalFileStatus* _file = dynamic_cast<MasterLocalFileStatus*>(file))
		{
			doc = fz_open_document(mContext, _file->name.c_str());
		}
		if (MasterMemoryFileStatus* _file = dynamic_cast<MasterMemoryFileStatus*>(file))
		{
			stream = fz_open_memory(mContext, (unsigned char*)_file->OriginalFile(), _file->Length());
			doc = fz_open_document_with_stream(mContext, ".pdf", stream);
		}
	}
	fz_catch(mContext)
	{
		auto msg = fz_caught_message(mContext);
		if (stream != nullptr)
			fz_drop_stream(mContext,stream);
		fz_drop_context(mContext);
		mContext = nullptr;
		throw std::runtime_error(std::string("cannot open document: ") + msg);
	}

	int pageCount = 0;
	/* Count the number of pages. */
	fz_try(mContext)
		pageCount = fz_count_pages(mContext, doc);
	fz_catch(mContext)
	{
		auto msg = fz_caught_message(mContext);
		fz_drop_document(mContext, doc);
		if (stream != nullptr)
			fz_drop_stream(mContext, stream);
		fz_drop_context(mContext);
		mContext = nullptr;
		throw std::runtime_error(std::string("cannot count number of pages: ") + msg);
	}
	//BOOST_LOG_WITH_LINE(Log::CommonLogger, boost::log::trivial::trace) << "Count page: " << pageCount;

	boost::thread_group worker_threads;
	for (int pageNumber = 0; pageNumber < pageCount; pageNumber++)
	{
		//BOOST_LOG_WITH_LINE(Log::CommonLogger, boost::log::trivial::trace) << "Page: " << pageNumber;
		if ((*file->siblings)[pageNumber] == nullptr)
			continue;

		fz_rect rect;
		fz_irect irect;

		fz_matrix ctm = fz_identity;


		//BOOST_LOG_WITH_LINE(Log::CommonLogger, boost::log::trivial::trace) << "LoadPage";
		auto* page = fz_load_page(mContext, doc, pageNumber);
		fz_bound_page(mContext, page, &rect);

		float ratioX = mMaxResolution / (rect.x1 - rect.x0);
		float ratioY = mMaxResolution / (rect.y1 - rect.y0);
		float ratio = std::min(ratioX, ratioY);
		ratio = std::min(ratio, 4.0f);

		fz_pre_scale(&ctm, ratio, ratio);


		fz_transform_rect(&rect, &ctm);
		fz_round_rect(&irect, &rect);

		fz_display_list *list = fz_new_display_list(mContext, &rect);
		
		fz_device *dev = nullptr;
		fz_try(mContext)
		{
			dev = fz_new_list_device(mContext, list);
			fz_run_page(mContext, page, dev, &ctm, NULL);
			fz_close_device(mContext, dev);
		}
		fz_always(mContext)
		{
			fz_drop_device(mContext, dev);
			fz_drop_page(mContext, page);
		}
		fz_catch(mContext)
		{
			auto msg = fz_caught_message(mContext);
			BOOST_LOG_WITH_LINE(Log::CommonLogger, boost::log::trivial::error) << "cannot create device for page " << pageNumber << ": " << msg;
			(*file->siblings)[pageNumber]->abandoned = true;
			(*file->siblings)[pageNumber]->isCompleted = true;
			continue;
		}
		
		fz_pixmap *pix = nullptr;
		fz_try(mContext)
		{
			pix = fz_new_pixmap_with_bbox(mContext, fz_device_rgb(mContext), &irect, 0, 0);
			fz_clear_pixmap_with_value(mContext, pix, 0xFF);
		}
		fz_catch(mContext)
		{
			auto msg = fz_caught_message(mContext);
			BOOST_LOG_WITH_LINE(Log::CommonLogger, boost::log::trivial::error) << "cannot allocate " << pageNumber << ": " << msg;
			(*file->siblings)[pageNumber]->abandoned = true;
			(*file->siblings)[pageNumber]->isCompleted = true;
			continue;
		}


		WorkerParam wp;
		wp.pixmap = pix;
		wp.displayList = list;
		wp.pageNumber = pageNumber;
		wp.format = format;
		wp.quality = quality;
		fz_rect_from_irect(&wp.area, &irect);

		//worker_threads.create_thread(boost::bind(&MuPDF::Worker, this, wp, (*file->siblings)[pageNumber]));
		Worker(wp, (*file->siblings)[pageNumber]);

	}
	fz_drop_document(mContext, doc);
	if (stream != nullptr)
		fz_drop_stream(mContext, stream);
	//lock.~lock_guard();
	//worker_threads.join_all();


}

void Docapost::IA::MuPDF::MuPDF::s_lock(void* user, int lock)
{
	if (user == nullptr)
		return;

	MuPDF* mupdf = static_cast<MuPDF*>(user);

	if (mupdf == nullptr)
		return;

	mupdf->lock(user, lock);
}
void Docapost::IA::MuPDF::MuPDF::s_unlock(void* user, int lock)
{
	if (user == nullptr)
		return;

	MuPDF* mupdf = static_cast<MuPDF*>(user);

	if (mupdf == nullptr)
		return;

	mupdf->unlock(user, lock);
}

void Docapost::IA::MuPDF::MuPDF::lock(void* user, int lock)
{
	mMutexes[lock].lock();
}

void Docapost::IA::MuPDF::MuPDF::unlock(void* user, int lock)
{
	mMutexes[lock].unlock();
}

void Docapost::IA::MuPDF::MuPDF::initLocks()
{
}

void Docapost::IA::MuPDF::MuPDF::Worker(WorkerParam wp, MasterFileStatus* file)
{
	CatchAllErrorSignals();
	CatchAllExceptions();
	//BOOST_LOG_WITH_LINE(Log::CommonLogger, boost::log::trivial::trace) << "clone context";
	auto local_ctx = fz_clone_context(mContext);

	fz_device *dev = nullptr;
	fz_try(local_ctx)
	{
		//BOOST_LOG_WITH_LINE(Log::CommonLogger, boost::log::trivial::trace) << "create thread device";
		dev = fz_new_draw_device(local_ctx, &fz_identity, wp.pixmap);
		fz_run_display_list(local_ctx, wp.displayList, dev, &fz_identity, &wp.area, NULL);
		//fz_run_page(ctx, page, dev, &fz_identity, NULL);
		fz_close_device(local_ctx, dev);
	}
	fz_always(local_ctx)
	{
		fz_drop_device(local_ctx, dev);
	}
	fz_catch(local_ctx)
	{
		auto msg = fz_caught_message(mContext);
		fz_drop_pixmap(local_ctx, wp.pixmap);
		BOOST_LOG_WITH_LINE(Log::CommonLogger, boost::log::trivial::error) << "cannot draw pages " <<wp.pageNumber << ": " << msg;
		fz_drop_context(local_ctx);
		fz_drop_pixmap(mContext, wp.pixmap);
		fz_drop_display_list(mContext, wp.displayList);
		file->abandoned = true;
		file->isCompleted = true;
		return;
	}

	if (wp.format == Docapost::IA::Tesseract::ImageFormatEnum::JPG)
	{
		file->buffer = WriteToJPEG(wp, wp.quality.jpegQuality);
	}
	else if (wp.format == Docapost::IA::Tesseract::ImageFormatEnum::PNG)
	{
		auto buffer = fz_new_buffer_from_pixmap_as_png(local_ctx, wp.pixmap, fz_default_color_params(local_ctx));
		file->buffer = new Tesseract::FzBufferMemoryFileBuffer(local_ctx, buffer);
	}
	else
	{
		BOOST_LOG_WITH_LINE(Log::CommonLogger, boost::log::trivial::trace) << "Cannot convert to specified format, rollback to jpg";
		file->buffer = WriteToJPEG(wp, wp.quality.jpegQuality);
	}

	fz_drop_context(local_ctx);
	//std::lock_guard<std::mutex> lock(mContextMutex);
	fz_drop_pixmap(mContext, wp.pixmap);
	fz_drop_display_list(mContext, wp.displayList);

}

// Copier de https://github.com/chris-allan/libjpeg-turbo/blob/master/turbojpeg.c ligne 421 -> tjCompress2
Docapost::IA::Tesseract::MemoryFileBuffer* Docapost::IA::MuPDF::MuPDF::WriteToJPEG(WorkerParam& wp, int quality) const
{
	long unsigned int _jpegSize = 0;
	unsigned char* _compressedImage = nullptr;
	tjhandle _jpegCompressor = tjInitCompress();
	tjCompress2(_jpegCompressor, wp.pixmap->samples, wp.area.x1, 0, wp.area.y1, TJPF_RGB,
		&_compressedImage, &_jpegSize, TJSAMP_444, quality,
		TJFLAG_FASTDCT);

	//auto res = new std::vector<unsigned char>(_compressedImage, _compressedImage + _jpegSize);

	tjDestroy(_jpegCompressor);
	//tjFree(_compressedImage);

	return new Tesseract::JpegTurboMemoryFileBuffer(_compressedImage, _jpegSize);
}
