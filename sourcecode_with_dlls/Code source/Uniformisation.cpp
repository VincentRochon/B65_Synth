#include "Uniformisation.h"

bool Uniformisation::ProcessImage(std::vector<QImage> const& CarteEclairage, std::vector<QImage>& imageOut)
{
	if (CarteEclairage.size() > 1) {
		return false; // invalide number of carte eclairage
	}


	auto CarteEclair{ CarteEclairage.data() };
	auto imgOut{ imageOut.data() };

	int cCe{}, cOut{};
	unsigned char rCe{}, gCe{}, bCe{}, rOut{}, gOut{}, bOut{};
		
	const int* curViewPix{ reinterpret_cast<const int*>(CarteEclair->bits()) };
	const int* startViewPix{ curViewPix };

	for (size_t i = 0; i < imageOut.size(); i++)
	{
		int imgWidth{ imgOut->width() };
		int imgHeight{ imgOut->height() };

		int* curPix{ reinterpret_cast<int*>(imgOut->bits()) };
		int* endPix{ curPix + imgWidth * imgHeight };

		while (curPix < endPix)
		{

			cOut = *curPix;
			cCe = *curViewPix;

			rCe = static_cast<unsigned char>((cCe & 0x00'FF'00'00) >> 16);
			gCe = static_cast<unsigned char>((cCe & 0x00'00'FF'00) >> 8);
			bCe = static_cast<unsigned char>((cCe & 0x00'00'00'FF) >> 0);

			rOut = static_cast<unsigned char>((cOut & 0x00'FF'00'00) >> 16);
			gOut = static_cast<unsigned char>((cOut & 0x00'00'FF'00) >> 8);
			bOut = static_cast<unsigned char>((cOut & 0x00'00'00'FF) >> 0);

			if (rCe == 0) {
				rCe = 1;
			}
			if (gCe == 0) {
				gCe = 1;
			}
			if (bCe == 0) {
				bCe = 1;
			}

			rOut = rOut / rCe;
			gOut = gOut / gCe;
			bOut = bOut / bCe;


			*curPix = (rOut << 16) | (gOut << 8) | (bOut << 0) | 0xFF'00'00'00;
			++curPix;
			++curViewPix;
		}
			   		 	  	  	 
		curViewPix = startViewPix; // restart position of carte eclairage
	}




	return true;
}
