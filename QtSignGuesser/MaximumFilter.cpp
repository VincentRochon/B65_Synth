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
	int posTracker{ 0 };

	int* curPix{ reinterpret_cast<int*>(im.bits()) };
	int* endPix{ curPix + imgWidth * imgHeight };

	curPix += imgWidth * mWindowSize; // skip lines to prevent overflow
	endPix -= imgWidth * mWindowSize; // remove last line prevent overflow for treatment
	
	while (curPix < endPix) {

		if ((posTracker % imgWidth) > mWindowSize && posTracker < (imgWidth - mWindowSize))
		{
			//int pix{ *curPix };

			*curPix = 0xFF'00'00'00;



		}

		if (posTracker == imgWidth) {
			posTracker = 0;
		}

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
