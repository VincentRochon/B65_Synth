#include "MedianFilter.h"

MedianFilter::MedianFilter(int windowSize)
	:mWindowSize(windowSize)
{

}

QImage MedianFilter::ProcessImage(QImage const& image)
{
	QImage im(image);

	int* curPix{ reinterpret_cast<int*>(im.bits()) };
	int* endPix{ curPix + im.width() * im.height() };

	while (curPix < endPix) {


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
