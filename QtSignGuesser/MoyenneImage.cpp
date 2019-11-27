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

			///

			*curPix += std::floor(*curViewPix / numberOfImage);
			++curPix;
			++curViewPix;
		}

		++imgIn;
			   
	}


	return true; // succes
}
