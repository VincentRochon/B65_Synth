#include "ImageMerger.h"

QImage ImageMerger::merge(QImage const& Image1, QImage const& Image2)
{
	QImage ImageMerged{ Image1.size(),Image1.format() };

	//if (Image1.size() != Image2.size()) {
	//	return ImageMerged; // failure, image doesn't match
	//}

	int imgWidth{ Image1.width() };
	int imgHeight{ Image1.height() };
	auto ImageMergedStart{ reinterpret_cast<int*>(ImageMerged.bits()) };
	auto ImageMergedCurrentPix{ ImageMergedStart };
	auto ImageMergedEnd{ ImageMergedStart + imgWidth * imgHeight };

	auto Image1curPix{ reinterpret_cast<const int*>(Image1.bits()) };
	auto Image1End{ Image1curPix + imgWidth * imgHeight };

	auto Image2curPix{ reinterpret_cast<const int*>(Image2.bits()) };
	auto Image2End{ Image2curPix + imgWidth * imgHeight };

	while (ImageMergedCurrentPix < ImageMergedEnd) // turns everything to black
	{
		*ImageMergedCurrentPix = 0xFF'00'00'00;
		ImageMergedCurrentPix++;
	}
	ImageMergedCurrentPix = ImageMergedStart; // reset position
	
	while (ImageMergedCurrentPix < ImageMergedEnd)
	{

			if (*Image1curPix != 0xFF'00'00'00) { // 1st image non zero

				*ImageMergedCurrentPix = *Image1curPix;
			}
			if (*Image1curPix == 0xFF'00'00'00 && *Image2curPix != 0xFF'00'00'00) { // 2nd image non zero
				*ImageMergedCurrentPix = *Image2curPix;
			}
			
			//if (*Image1curPix != 0xFF'00'00'00) { // 1st image non zero
			//	*ImageMergedCurrentPix = *Image1curPix;
			//}
			

	++ImageMergedCurrentPix;
	++Image1curPix;
	++Image2curPix;
	}


	return ImageMerged;
}
