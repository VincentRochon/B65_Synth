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
	size_t posTracker{ 0 };
	size_t compteur{ 0 };
	int median{0};
	int windowWidth{ mWindowSize * 2 + 1 };
	std::vector<int> listOfPix(windowWidth * windowWidth);

	const int* curViewPix{ reinterpret_cast<const int*>(image.bits()) };
	int* curPix{ reinterpret_cast<int*>(im.bits()) };
	int* endPix{ curPix + imgWidth * imgHeight };
	int* vecPos{ listOfPix.data() };
	//int* nextVecPos{ listOfPix.data() };


	curViewPix += imgWidth * mWindowSize;
	curPix += imgWidth * mWindowSize; // skip lines to prevent overflow
	endPix -= imgWidth * mWindowSize; // remove last line prevent overflow for treatment

	while (curPix < endPix) {

		if (posTracker > mWindowSize&& posTracker < (imgWidth - mWindowSize))
		{

			const int* startPix{ curViewPix - imgWidth * mWindowSize + mWindowSize }; // start of the window of pixels
			//int* prevPix{ curPix - imgWidth * mWindowSize + mWindowSize };
			
			for (size_t i = 0; i < windowWidth*windowWidth; ++i)
			{
				if (compteur == windowWidth)
				{
					compteur = 0;
					startPix += imgWidth - windowWidth;// skip 1 line

				}

				
				*vecPos = *startPix;
				
				++vecPos;
				++compteur;
				++startPix;
				
			}

			vecPos -= windowWidth * windowWidth;

			std::sort(std::begin(listOfPix), std::end(listOfPix));
			// grosse perte de performance a cause du sort de algo

			/*
			for (size_t i = 0; i < listOfPix.size(); i++)
			{
				++nextVecPos;
							   
				if (*nextVecPos > * vecPos)
				{
					int tempValue{*vecPos };
					*vecPos = *nextVecPos;
					*nextVecPos = tempValue;
				}

				++vecPos;
			}
			

			vecPos -= windowWidth * windowWidth;
			*/

			int nombreTest = static_cast<int>(windowWidth * windowWidth - 1) * 0.5;
			vecPos += nombreTest;
			*curPix = *vecPos;
			vecPos -= nombreTest;


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

void MedianFilter::setWindowSize(int newWindowSize)
{
	mWindowSize = newWindowSize;
}

size_t MedianFilter::windowSize() const
{
	return mWindowSize;
}
