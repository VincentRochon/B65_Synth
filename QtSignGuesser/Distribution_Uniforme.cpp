#include "Distribution_Uniforme.h"

Distribution_Uniforme::Distribution_Uniforme(int windowSize)
	:mWindowSize(windowSize)
{
}

std::vector<float> Distribution_Uniforme::getKernel()
{
	size_t windowWidth = (mWindowSize * 2 + 1);
	size_t window = (windowWidth * windowWidth);
	
	std::vector<float> ConvolutionArray(window, (1.0f / window));

	/*
	float* curData{reinterpret_cast<float*>(ConvolutionArray.data()) };

	float value{ 1.0f / window };

	for (size_t i = 0; i < window; ++i)
	{
	
		ConvolutionArray[i] = value;
	}
	*/
	return ConvolutionArray;
}

QImage Distribution_Uniforme::ProcessImage(QImage const& image)
{
	QImage im(image);


	int imgWidth{ im.width() };
	int imgHeight{ im.height() };
	size_t windowWidth = (mWindowSize * 2 + 1);
	size_t window = (windowWidth * windowWidth);
	int posTracker{ 0 };

	//std::vector<float > ConvolutionArray{ getKernel() };

	float uniformeValue{ 1.0f / window };

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
			int sum{0};

			for (size_t i = 0; i < windowWidth; ++i)
			{
				for (size_t j = 0; j < windowWidth; ++j)
				{
					sum += (*startPix * uniformeValue);
					++startPix;
				}
				startPix += imgWidth - windowWidth;// skip 1 line
			}

			*curPix = sum;
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
