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
			// in the range
			int c{ *curPix };

			c = 0xFF'00'00'00;

		}
		else {

			int c{ *curPix };

			unsigned char r{ static_cast<unsigned char>((c & 0x00'FF'00'00) >> 16) };
			unsigned char g{ static_cast<unsigned char>((c & 0x00'00'FF'00) >> 8) };
			unsigned char b{ static_cast<unsigned char>((c & 0x00'00'00'FF) >> 0) };

			int average{ static_cast<int>((float)r * 0.25f + (float)g * 0.67f + (float)b * 0.08f) };
			*curPix = (average << 16) |
				(average << 8) |
				(average << 0) |
				0xFF'00'00'00;
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
