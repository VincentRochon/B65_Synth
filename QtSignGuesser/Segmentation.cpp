#include "Segmentation.h"



Segmentation::Segmentation(size_t Rmin, size_t Rmax, size_t Gmin, size_t Gmax, size_t Bmin, size_t Bmax)
	:mRmin{ Rmin }, mRmax{ Rmax }, mGmin{ Gmin }, mGmax{ Gmax }, mBmin{ Bmin },mBmax{Bmax}
{
}

bool Segmentation::ProcessImage(std::vector<QImage> const&imageIn, std::vector<QImage>& imageOut)
{

	if (imageIn.size() != imageOut.size()) {
		return 0; // invalid format of either vectors
	}

	//auto imgIn{ imageIn.data() };
	auto imgOut{ imageOut.data() };

	for (size_t i = 0; i < imageOut.size(); i++) {

		//QImage im(*img);

		int imgWidth{ imgOut->width() };
		int imgHeight{ imgOut->height() };
		int* curPix{ reinterpret_cast<int*>(imgOut->bits()) };
		int* endPix{ curPix + imgWidth * imgHeight };

		while (curPix < endPix) {


			int c{ *curPix };

			unsigned char r{ static_cast<unsigned char>((c & 0x00'FF'00'00) >> 16) };
			unsigned char g{ static_cast<unsigned char>((c & 0x00'00'FF'00) >> 8) };
			unsigned char b{ static_cast<unsigned char>((c & 0x00'00'00'FF) >> 0) };

			if (r <= mRmax && r >= mRmin && g <= mGmax && g >= mGmin && b <= mBmax && b >= mBmin) {

				*curPix = 0xFF'FF'FF'FF;
			}
			else {
				*curPix = 0xFF'00'00'00;
			}

			++curPix;
		}

		//*img = im;
		//++imgIn;
		++imgOut;
	}

	return 1; //succes


}
