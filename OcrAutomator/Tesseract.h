#pragma once
#include <string>
#include "BaseOcr.h"

using std::string;
#include <tesseract/baseapi.h>

#include <iostream>
#include <boost/format.hpp>
#include "BaseFileStatus.h"
#include "MasterFileStatus.h"
#include "ImageFormatEnum.h"
#include "MemoryFileBuffer.h"


namespace Docapost {
	namespace IA {
		namespace Tesseract {
			class Tesseract : public BaseOcr
			{
				tesseract::PageSegMode mPsm;
				tesseract::OcrEngineMode mOem;
				std::string mLang;
				tesseract::TessBaseAPI mTessBaseAPI;

				MemoryFileBuffer* ExtractPdfFromImageMagick(MasterFileStatus* file, const std::function<void(MasterFileStatus*)>& AddFile);
				MemoryFileBuffer* ExtractPdfFromMuPdf(MasterFileStatus* file, const std::function<void(MasterFileStatus*)>& AddFile);
			public:
				Tesseract(tesseract::PageSegMode psm, tesseract::OcrEngineMode oem, std::string lang, ImageFormatEnum format);

				MemoryFileBuffer* LoadFile(MasterFileStatus* file, const std::function<void(MasterFileStatus*)>& AddFile) override;
				bool ProcessThroughOcr(MemoryFileBuffer* imgData, std::string& text) override;

				~Tesseract();
			};
		}
	}
}