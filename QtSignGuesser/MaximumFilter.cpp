#include "MaximumFilter.h"

MaximumFilter::MaximumFilter(int windowSize)
	:mWindowSize(windowSize)
{
	
}

QImage MaximumFilter::ProcessImage(QImage const& image)
{
	QImage im(image);


	int imgWidth{ im.width() };
	int imgHeight{ im.height() };
	int imageWidth{ image.width() };
	int imageHeight{ image.height() };

	int posTracker{ 0 };
	int windowWidth{ mWindowSize * 2 + 1 };
	int max{};

	int* curPix{ reinterpret_cast<int*>(im.bits()) };
	int* endPix{ curPix + imgWidth * imgHeight };
	const int* curViewPix{ reinterpret_cast<const int*>(image.bits())  };
	const int* endViewPix{ curPix + imageWidth * imageHeight };

	curViewPix += imageWidth * mWindowSize;
	// endViewPix -= imageWidth * mWindowSize;
	curPix += imgWidth * mWindowSize; // skip lines to prevent overflow
	endPix -= imgWidth * mWindowSize; // remove last lines prevent overflow for treatment
	
	while (curPix < endPix) {

		if (posTracker > mWindowSize && posTracker < (imgWidth - mWindowSize))
		{
			
			const int * startPix{ curViewPix - imageWidth * mWindowSize + mWindowSize }; // start of the window of pixels
			const int * prevPix{ startPix };
			max = *startPix;
			
			for (size_t i = 0; i < windowWidth; ++i)
			{
				for (size_t j = 0; j < windowWidth; ++j)
				{
					++startPix;
					if (*startPix > * prevPix && *startPix > max)
					{
						//*prevPix = *startPix;
						max = *startPix;
					}
					if (i > 0 && j == 0){
						prevPix += imageWidth - windowWidth-1;
					}
					++prevPix;
				}
				startPix += imageWidth - windowWidth-1;// skip 1 line

			}
	
			*curPix = max;
		}

		if (posTracker == imgWidth) {
			posTracker = 0;
		}

		++curViewPix;
		++posTracker;
		++curPix;
	}

	return im;
}

void MaximumFilter::setWindowSize(int newWindowSize)
{
	mWindowSize = newWindowSize;
}

size_t MaximumFilter::windowSize() const
{
	return mWindowSize;
}
