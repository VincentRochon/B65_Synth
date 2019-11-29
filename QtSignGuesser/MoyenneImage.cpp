#include "MoyenneImage.h"

bool MoyenneImage::ProcessImage(std::vector<QImage> const& imageIn, std::vector<QImage>& imageOut)
{

	if (imageOut.size() != 1) {

		return false; // must have only 1 output
	}
	
	auto imgIn{ imageIn.data() };
	auto imgOut{ imageOut.data() };

	size_t numberOfImage{ imageIn.size() };

	int imgWidth{ imgOut->width() };
	int imgHeight{ imgOut->height() };
	int* curPix{ reinterpret_cast<int*>(imgOut->bits()) };
	int* endPix{ curPix + imgWidth * imgHeight };
	int colorIn{}, colorOut{};
	unsigned char rIn{}, gIn{}, bIn{}, rOut{}, gOut{}, bOut{};

	while (curPix < endPix) {

		*curPix = 0; // reset the value
		++curPix;
	}

	for (size_t i = 0; i < imageIn.size(); ++i)
	{
		curPix = reinterpret_cast<int*>(imgOut->bits());
		endPix = curPix + imgWidth * imgHeight;
		const int* curViewPix{ reinterpret_cast<const int*>(imgIn->bits()) };

		while (curPix < endPix) {

			colorIn = *curViewPix;
			colorOut = *curPix;

			rIn = static_cast<unsigned char>((colorIn & 0x00'FF'00'00) >> 16)/ numberOfImage;
			gIn = static_cast<unsigned char>((colorIn & 0x00'00'FF'00) >> 8) / numberOfImage;
			bIn = static_cast<unsigned char>((colorIn & 0x00'00'00'FF) >> 0) / numberOfImage;

			rOut = static_cast<unsigned char>((colorOut & 0x00'FF'00'00) >> 16);
			gOut = static_cast<unsigned char>((colorOut & 0x00'00'FF'00) >> 8);
			bOut = static_cast<unsigned char>((colorOut & 0x00'00'00'FF) >> 0);

			rOut += rIn;
			gOut += gIn;
			bOut += bIn;


			(*curPix) = (rOut << 16) | (gOut << 8) | (bOut << 0) | 0xFF'00'00'00;
			++curPix;
			++curViewPix;
		}

		++imgIn;
			   
	}


	return true; // succes
}
