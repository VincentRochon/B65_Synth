#include "Segmentation.h"



Segmentation::Segmentation(size_t Rmin, size_t Rmax, size_t Gmin, size_t Gmax, size_t Bmin, size_t Bmax)
	:mRmin{ Rmin }, mRmax{ Rmax }, mGmin{ Gmin }, mGmax{ Gmax }, mBmin{ Bmin },mBmax{Bmax}
{
}

QImage Segmentation::ProcessImage(QImage const& image)
{
	QImage im(image);


	int imgWidth{ im.width() };
	int imgHeight{ im.height() };

	int* curPix{ reinterpret_cast<int*>(im.bits()) };
	int* endPix{ curPix + imgWidth * imgHeight };


	while (curPix < endPix) {


		int c{ *curPix };

		unsigned char r{ static_cast<unsigned char>((c & 0x00'FF'00'00) >> 16) };
		unsigned char g{ static_cast<unsigned char>((c & 0x00'00'FF'00) >> 8) };
		unsigned char b{ static_cast<unsigned char>((c & 0x00'00'00'FF) >> 0) };

		if (r < mRmax && r > mRmin&& g < mGmax && g > mGmin&& b < mBmax && b > mBmin) {

			*curPix = 0xFF'FF'FF'FF;
		}
		else {
			*curPix = 0xFF'00'00'00;
		}

		++curPix;
	}

	return im;
}
