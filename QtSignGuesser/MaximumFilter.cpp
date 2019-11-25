#include "MaximumFilter.h"

MaximumFilter::MaximumFilter(int windowSize)
	:mWindowSize(windowSize)
{
	
}

void  MaximumFilter::ProcessImage(std::vector<QImage> &image)
{
	
	int posTracker{ 0 };
	int windowWidth{ mWindowSize * 2 + 1 };
	unsigned char maxRed{};
	unsigned char maxBlue{};
	unsigned char maxGreen{};
	unsigned char r{};
	unsigned char g{};
	unsigned char b{};
	int c{};

	auto img{ image.data() };

	for (size_t i = 0; i < image.size(); i++)
	{
		QImage im(*img);

		int imgWidth{ im.width() };
		int imgHeight{ im.height() };

		int* curPix{ reinterpret_cast<int*>(im.bits()) };
		int* endPix{ curPix + imgWidth * imgHeight };
		const int* curViewPix{ reinterpret_cast<const int*>((*img).bits()) };

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

		*img = im;

	}
	/*
	for each (QImage img in image)
	{
		QImage im(img);
		
		int imgWidth{ im.width() };
		int imgHeight{ im.height() };
			   
		int* curPix{ reinterpret_cast<int*>(im.bits()) };
		int* endPix{ curPix + imgWidth * imgHeight };
		const int* curViewPix{ reinterpret_cast<const int*>(img.bits()) };

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
	
		img = im;
	}*/

	// return returnImage;

	//QImage im(image);

	/*
	int imgWidth{ im.width() };
	int imgHeight{ im.height() };

	int posTracker{ 0 };
	int windowWidth{ mWindowSize * 2 + 1 };
	unsigned char maxRed{};
	unsigned char maxBlue{};
	unsigned char maxGreen{};
	unsigned char r{};
	unsigned char g{};
	unsigned char b{};
	int c{};


	int* curPix{ reinterpret_cast<int*>(im.bits()) };
	int* endPix{ curPix + imgWidth * imgHeight };
	const int* curViewPix{ reinterpret_cast<const int*>(image.bits())  };

	curViewPix += imgWidth * mWindowSize;
	// endViewPix -= imageWidth * mWindowSize;
	curPix += imgWidth * mWindowSize; // skip lines to prevent overflow
	endPix -= imgWidth * mWindowSize; // remove last lines prevent overflow for treatment
	
	while (curPix < endPix) {

		if (posTracker > mWindowSize && posTracker < (imgWidth - mWindowSize))
		{
			
			const int * startPix{ curViewPix - imgWidth * mWindowSize + mWindowSize }; // start of the window of pixels
			const int * prevPix{ startPix };

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
				startPix += imgWidth - windowWidth-1;// skip 1 line

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

	return im;*/
}

void MaximumFilter::setWindowSize(int newWindowSize)
{
	mWindowSize = newWindowSize;
}

size_t MaximumFilter::windowSize() const
{
	return mWindowSize;
}
