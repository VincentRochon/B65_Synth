#include "MaximumFilter.h"

MaximumFilter::MaximumFilter(int windowSize)
	:mWindowSize(windowSize)
{
	
}

bool  MaximumFilter::ProcessImage(std::vector<QImage> const &imageIn, std::vector<QImage>& imageOut)
{
	if (imageIn.size() != imageOut.size()) {
		return false; // invalid format of either vectors
	}

	int posTracker{ 0 };
	int windowWidth{ mWindowSize * 2 + 1 };
	unsigned char maxRed{};
	unsigned char maxBlue{};
	unsigned char maxGreen{};
	unsigned char r{};
	unsigned char g{};
	unsigned char b{};
	int c{};

	auto imgIn{ imageIn.data() };
	auto imgOut{ imageOut.data() };

	for (size_t i = 0; i < imageIn.size(); ++i)
	{

		int imgWidth{ imgOut->width() };
		int imgHeight{ imgOut->height() };

		int* curPix{ reinterpret_cast<int*>(imgOut->bits()) };
		int* endPix{ curPix + imgWidth * imgHeight };
		const int* curViewPix{ reinterpret_cast<const int*>(imgIn->bits()) };

		curViewPix += imgWidth * mWindowSize;
		// endViewPix -= imageWidth * mWindowSize;
		curPix += imgWidth * mWindowSize; // skip lines to prevent overflow
		endPix -= imgWidth * mWindowSize; // remove last lines prevent overflow for treatment

		while (curPix < endPix) {

			if (posTracker > mWindowSize&& posTracker < (imgWidth - mWindowSize))
			{

				const int* startPix{ curViewPix - imgWidth * mWindowSize + mWindowSize }; // start of the window of pixels
				const int* prevPix{ startPix };

				c = *startPix;

				maxRed = static_cast<unsigned char>((c & 0x00'FF'00'00) >> 16);
				maxGreen = static_cast<unsigned char>((c & 0x00'00'FF'00) >> 8);
				maxBlue = static_cast<unsigned char>((c & 0x00'00'00'FF) >> 0);


				for (size_t i = 0; i < windowWidth; ++i)
				{
					for (size_t j = 0; j < windowWidth; ++j)
					{
						++startPix;

						c = *startPix;

						r = static_cast<unsigned char>((c & 0x00'FF'00'00) >> 16);
						g = static_cast<unsigned char>((c & 0x00'00'FF'00) >> 8);
						b = static_cast<unsigned char>((c & 0x00'00'00'FF) >> 0);


						if (r > maxRed)
						{
							maxRed = r;
						}

						if (g > maxGreen)
						{
							maxGreen = g;
						}

						if (b > maxBlue)
						{
							maxBlue = b;
						}

					}
					startPix += imgWidth - windowWidth - 1;// skip 1 line

				}
				*curPix = (maxRed << 16) | (maxGreen << 8) | (maxBlue << 0) | 0xFF'00'00'00;
			}

			if (posTracker == imgWidth) {
				posTracker = 0;
			}

			++curViewPix;
			++posTracker;
			++curPix;
		}

		++imgIn;
		++imgOut;

	}
	return true; //succes
}

void MaximumFilter::setWindowSize(int newWindowSize)
{
	mWindowSize = newWindowSize;
}

size_t MaximumFilter::windowSize() const
{
	return mWindowSize;
}
