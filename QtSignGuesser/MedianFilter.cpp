#include "MedianFilter.h"

MedianFilter::MedianFilter(int windowSize)
	:mWindowSize(windowSize)
{

}

QImage MedianFilter::ProcessImage(QImage const& image)
{
	QImage im(image);

	int imgWidth{ im.width() };
	int imgHeight{ im.height() };
	int posTracker{ 0 };
	int windowWidth{ mWindowSize * 2 + 1 };

	int* curPix{ reinterpret_cast<int*>(im.bits()) };
	int* endPix{ curPix + imgWidth * imgHeight };

	curPix += imgWidth * mWindowSize; // skip lines to prevent overflow
	endPix -= imgWidth * mWindowSize; // remove last line prevent overflow for treatment

	while (curPix < endPix) {

		if ((posTracker % imgWidth) > mWindowSize&& posTracker < (imgWidth - mWindowSize))
		{

			int* startPix{ curPix - imgWidth * mWindowSize + mWindowSize }; // start of the window of pixels
			//int* prevPix{ curPix - imgWidth * mWindowSize + mWindowSize };

			for (size_t i = 0; i < windowWidth; ++i)
			{
				for (size_t j = 0; j < windowWidth; j++)
				{

				}

				startPix += imgWidth - windowWidth;// skip 1 line

			}

			*curPix = *startPix;

		}

		if (posTracker == imgWidth) {
			posTracker = 0;
		}

		++posTracker;
		++curPix;
		++curPix;
	}

	return im;
}

void MedianFilter::setWindowSize(int newWindowSize)
{
	mWindowSize = newWindowSize;
}

size_t MedianFilter::windowSize() const
{
	return mWindowSize;
}
