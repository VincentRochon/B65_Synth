#include "Distribution_Gauss.h"

Distribution_Gauss::Distribution_Gauss(int windowSize)
	:mWindowSize(windowSize)
{

}

std::vector<float> Distribution_Gauss::getKernel()
{
	int longueur{ mWindowSize * 2 + 1 };
	float moyenneX{ 1 + (longueur - 1) * 0.5f };
	float moyenneY{ moyenneX };
	float ecartypeX{ (longueur - 1) * 0.25f };
	float ecartypeY{ ecartypeX };

	const double e{ 2.71828182845904523536 };
	const double pi{ 3.14159265358979323846 };

	std::vector<float> ConvolutionArray(longueur * longueur);

	float* curData{ reinterpret_cast<float*>(ConvolutionArray.data()) };

	//(pow(i-moyenneX,2)/(2*ecartypeX) + pow(j-moyenneY)/(2*ecartypeX))*-1

	//(1/(pow(2*pi,0.5))* ecartypeX* ecartypeY)* pow(e, (pow(i - moyenneX, 2) / (2 * ecartypeX) + pow(j - moyenneY) / (2 * ecartypeX)) * -1)
		
	for (size_t i = 1; i <= longueur; ++i)
	{
		for (size_t j = 1; j <= longueur; ++j)
		{
			*curData = (1 / (pow(2 * pi, 0.5f)) * ecartypeX * ecartypeY) * pow(e, (pow(i - moyenneX, 2) / (2 * ecartypeX) + pow(j - moyenneY,2) / (2 * ecartypeY)) * -1);
			++curData;
		}
	}
	
	return ConvolutionArray;
}

QImage Distribution_Gauss::ProcessImage(QImage const& image)
{
	QImage im(image);


	int imgWidth{ im.width() };
	int imgHeight{ im.height() };
	int posTracker{ 0 };
	size_t windowWidth = (mWindowSize * 2 + 1);

	std::vector<float> ConvolutionArray{ getKernel() };

	int* curPix{ reinterpret_cast<int*>(im.bits()) };
	int* endPix{ curPix + imgWidth * imgHeight };
	const int* curViewPix{ reinterpret_cast<const int*>(image.bits()) };
	float* vectStart{ ConvolutionArray.data() };
	float* curPosVect{ ConvolutionArray.data() };

	curViewPix += imgWidth * mWindowSize;
	// endViewPix -= imageWidth * mWindowSize;
	curPix += imgWidth * mWindowSize; // skip lines to prevent overflow
	endPix -= imgWidth * mWindowSize; // remove last lines prevent overflow for treatment

	while (curPix < endPix) {

		if (posTracker > mWindowSize&& posTracker < (imgWidth - mWindowSize))
		{

			const int* startPix{ curViewPix - imgWidth * mWindowSize + mWindowSize }; // start of the window of pixels

			int sum{ 0 };

			for (size_t i = 0; i < windowWidth; ++i)
			{
				for (size_t j = 0; j < windowWidth; ++j)
				{
					sum += (*startPix) * (*curPosVect);


					++curPosVect;
					++startPix;
				}
				startPix += imgWidth - windowWidth;// skip 1 line
			}

			curPosVect = vectStart;

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
