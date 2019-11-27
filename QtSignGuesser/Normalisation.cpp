#include "Normalisation.h"

Normalisation::Normalisation(unsigned char mNormalValue)
	:mNormalValue{ mNormalValue }
{
}

bool Normalisation::ProcessImage(std::vector<QImage> const& imageIn, std::vector<QImage>& imageOut)
{

	if (imageIn.size() != imageOut.size()) {
		return false; // invalid format of either vectors
	}


	auto imgIn{ imageIn.data() };
	auto imgOut{ imageOut.data() };
	int c{};

	

	for (size_t i = 0; i < imageIn.size(); ++i){


		int imgWidth{ imgOut->width() };
		int imgHeight{ imgOut->height() };
		unsigned char max{0};
		unsigned char min{255};

		int* curPix{ reinterpret_cast<int*>(imgOut->bits()) };
		int* endPix{ curPix + imgWidth * imgHeight };
		const int* curViewPix{ reinterpret_cast<const int*>(imgIn->bits()) };

		while (curPix < endPix) { // premiere passe pour trouver max et min de l'image

			
			c = *curViewPix;
			
			
			
			if (*curViewPix > max) {




				//max = *curViewPix;
			}
			if (*curViewPix < min) {
				
				
				
				//min = *curViewPix;
			}

			++curPix;
			++curViewPix;
		}


		curPix -= imgWidth * imgHeight; // reset start pos
		curViewPix -= imgWidth * imgHeight; // reset start pos



		while (curPix < endPix) { // premiere passe pour trouver max et min de l'image



			
			*curPix

			++curPix;
			++curViewPix;
		}



		++imgIn;
		++imgOut;

	}



	return true;
}
