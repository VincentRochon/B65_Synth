#include "Distribution_Gauss.h"

Distribution_Gauss::Distribution_Gauss(int windowSize)
	:mWindowSize(windowSize)
{

}

std::vector<int> Distribution_Gauss::fillKernel()
{
	std::vector<int> ConvolutionArray(mWindowSize*2+1);


	int* curData { ConvolutionArray.data() };


	return ConvolutionArray;
}

QImage Distribution_Gauss::ProcessImage(QImage const& image)
{
	QImage im(image);


	int imgWidth{ im.width() };
	int imgHeight{ im.height() };
	int posTracker{ 0 };

	std::vector<int> ConvolutionArray{ fillKernel() };

	int* curPix{ reinterpret_cast<int*>(im.bits()) };
	int* endPix{ curPix + imgWidth * imgHeight };
	const int* curViewPix{ reinterpret_cast<const int*>(image.bits()) };

	curViewPix += imgWidth * mWindowSize;
	// endViewPix -= imageWidth * mWindowSize;
	curPix += imgWidth * mWindowSize; // skip lines to prevent overflow
	endPix -= imgWidth * mWindowSize; // remove last lines prevent overflow for treatment

	while (curPix < endPix) {

		if (posTracker > mWindowSize&& posTracker < (imgWidth - mWindowSize))
		{

			const int* startPix{ curViewPix - imgWidth * mWindowSize + mWindowSize }; // start of the window of pixels






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
