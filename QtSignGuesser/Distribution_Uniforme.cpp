#include "Distribution_Uniforme.h"

Distribution_Uniforme::Distribution_Uniforme(int windowSize)
	:mWindowSize(windowSize)
{
}

std::vector<float> Distribution_Uniforme::fillKernel()
{
	size_t windowWidth = (mWindowSize * 2 + 1);
	size_t window = (windowWidth * windowWidth);
	
	std::vector<float> ConvolutionArray(window, 0.0f);

	float* curData{reinterpret_cast<float*>(ConvolutionArray.data()) };

	for (size_t i = 0; i < window; ++i)
	{
	
		ConvolutionArray[i] =(1.0f / window);
	}

	return ConvolutionArray;
}

QImage Distribution_Uniforme::ProcessImage(QImage const& image)
{
	QImage im(image);


	int imgWidth{ im.width() };
	int imgHeight{ im.height() };
	int posTracker{ 0 };

	std::vector<float > ConvolutionArray{ fillKernel() };

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
