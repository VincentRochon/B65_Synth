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


	//auto imgIn{ imageIn.data() };
	auto imgOut{ imageOut.data() };
	int c{};
	unsigned char maxRed{}, maxGreen{}, maxBlue{};
	unsigned char minRed{}, minGreen{}, minBlue{};
	unsigned char r{}, g{}, b{};

	for (size_t i = 0; i < imageOut.size(); ++i){

		int imgWidth{ imgOut->width() };
		int imgHeight{ imgOut->height() };
		maxRed = 0; // reset value
		maxGreen = 0;
		maxBlue = 0;
		minRed = 255;
		minGreen = 255;
		minBlue = 255;

		int* curPix{ reinterpret_cast<int*>(imgOut->bits()) };
		int* endPix{ curPix + imgWidth * imgHeight };
		//const int* curViewPix{ reinterpret_cast<const int*>(imgIn->bits()) };

		while (curPix < endPix) { // premiere passe pour trouver max et min de l'image

			
			c = *curPix;
			
			r = static_cast<unsigned char>((c & 0x00'FF'00'00) >> 16);
			g = static_cast<unsigned char>((c & 0x00'00'FF'00) >> 8);
			b = static_cast<unsigned char>((c & 0x00'00'00'FF) >> 0);
			
			
			if (r > maxRed) {
				maxRed = r;
			}
			if (g > maxGreen) {
				maxGreen = g;
			}
			if (b > maxBlue) {
				maxBlue = b;
			}
			if (r < maxRed) {
				minRed = r;
			}
			if (g < maxRed) {
				minGreen = g;
			}
			if (b < maxRed) {
				minBlue = b;
			}


			++curPix;
			//++curViewPix;
		}


		curPix -= imgWidth * imgHeight; // reset start pos
		//curViewPix -= imgWidth * imgHeight; // reset start pos


		float redDiff{ static_cast<float>(maxRed - minRed)};
		float greenDiff{ static_cast<float>(maxGreen - minGreen)};
		float blueDiff{ static_cast<float>(maxBlue - minBlue)};

		while (curPix < endPix) { // premiere passe pour trouver max et min de l'image


			c = *curPix;

			r = static_cast<unsigned char>((c & 0x00'FF'00'00) >> 16);
			g = static_cast<unsigned char>((c & 0x00'00'FF'00) >> 8);
			b = static_cast<unsigned char>((c & 0x00'00'00'FF) >> 0);


			r = ((r - minRed) / redDiff) * mNormalValue;
			g = ((g - minGreen) / greenDiff) * mNormalValue;
			b = ((b - minBlue) / blueDiff) * mNormalValue;

			
			(*curPix) = (r << 16) | (g << 8) | (b << 0) | 0xFF'00'00'00;;

			++curPix;

		}

		++imgOut;

	}



	return true;
}
