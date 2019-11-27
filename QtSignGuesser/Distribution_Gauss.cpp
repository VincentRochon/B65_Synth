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
	float ecartTypeX{ (longueur - 1) * 0.20f };
	float ecartTypeY{ ecartTypeX };

	const float e{ 2.71828182845904523536f };
	const float pi{ 3.14159265358979323846f };

	std::vector<float> ConvolutionArray(longueur * longueur);

	float* curData{ reinterpret_cast<float*>(ConvolutionArray.data()) };



	// pow(i-moyenneX,2) / 2*ecartTypeX
	// pow(j-moyenneY,2) / 2*ecartTypeY
	// (pow(i-moyenneX,2) / 2*ecartTypeX)+(pow(j-moyenneY,2) / 2*ecartTypeY)

	// pow(e,-(pow(i-moyenneX,2) / 2*ecartTypeX)+(pow(j-moyenneY,2) / 2*ecartTypeY))
	/// pow(e,-((pow(i-moyenneX,2) / 2*ecartTypeX)+(pow(j-moyenneY,2) / 2*ecartTypeY)))

	// pow(2*pi,0.5)
	// pow(2*pi,0.5)*ecartTypeX*ecartTypeY
	// 1/(pow(2*pi,0.5)*ecartTypeX*ecartTypeY)

	// (1/(pow(2*pi,0.5)*ecartTypeX*ecartTypeY))*pow(e,-((pow(i-moyenneX,2) / 2*ecartTypeX)+(pow(j-moyenneY,2) / 2*ecartTypeY)))
	
	float sum{0};
			
	for (size_t i = 1; i <= longueur; ++i)
	{
		for (size_t j = 1; j <= longueur; ++j)
		{
			///*curData = (1 / (pow(2 * pi, 0.5f)) * ecartTypeX * ecartTypeY) * pow(e, (pow(i - moyenneX, 2) / (2 * ecartTypeX) + pow(j - moyenneY,2) / (2 * ecartTypeY))* -1);
			///*curData = (1 / ((pow(2 * pi, 0.5))*ecartTypeX*ecartTypeY))*(pow(e, (pow(i - moyenneX, 2) / 2 * ecartTypeX) + (pow(j - moyenneY, 2) / 2 * ecartTypeY)*-1));
			*curData = (1 / (pow(2 * pi, 0.5f)*ecartTypeX*ecartTypeY))*pow(e, -((pow(i - moyenneX, 2) / 2 * ecartTypeX) + (pow(j - moyenneY, 2) / 2 * ecartTypeY)));
			sum += *curData;
			++curData;
		}
	}

	curData = reinterpret_cast<float*>(ConvolutionArray.data());
	
	for (auto &v : ConvolutionArray) {

		v /= sum;
	}
	
	sum = 0;

	for (auto &v : ConvolutionArray) {

		sum += v;
	}

	return ConvolutionArray;
}

bool Distribution_Gauss::ProcessImage(std::vector<QImage> const &imageIn, std::vector<QImage> & imageOut)
{
	if (imageIn.size() != imageOut.size()) {
		return 0; // invalid format of either vectors
	}
	
	int posTracker{ 0 };
	unsigned char maxRed{};
	unsigned char maxBlue{};
	unsigned char maxGreen{};
	unsigned char r{};
	unsigned char g{};
	unsigned char b{};
	int c{};
	size_t windowWidth = (mWindowSize * 2 + 1);
	std::vector<float> ConvolutionArray(getKernel());
	float* vectStart{ ConvolutionArray.data() };
	float* curPosVect{ ConvolutionArray.data() };

	auto imgIn{ imageIn.data() };
	auto imgOut{ imageOut.data() };

	for (size_t i = 0; i < imageIn.size(); ++i) {

		//QImage im(*img);

		int imgWidth{ imgOut->width() };
		int imgHeight{ imgOut->height() };

		int* curPix{ reinterpret_cast<int*>(imgOut->bits()) };
		int* endPix{ curPix + imgWidth * imgHeight };
		const int* curViewPix{ reinterpret_cast<const int*>(imgIn->bits()) };

		curViewPix += imgWidth * mWindowSize;
		// endViewPix -= imageWidth * mWindowSize;
		curPix += imgWidth * mWindowSize; // skip lines to prevent overflow
		endPix -= imgWidth * mWindowSize; // remove last lines prevent overflow for treatment

		while (curPix < endPix) {

			if (posTracker > mWindowSize&& posTracker < (imgWidth - mWindowSize))
			{

				const int* startPix{ curViewPix - imgWidth * mWindowSize + mWindowSize }; // start of the window of pixels

				maxRed = 0;
				maxBlue = 0;
				maxGreen = 0;

				for (size_t i = 0; i < windowWidth; ++i)
				{
					for (size_t j = 0; j < windowWidth; ++j)
					{
						c = *startPix;

						r = static_cast<unsigned char>((c & 0x00'FF'00'00) >> 16);
						g = static_cast<unsigned char>((c & 0x00'00'FF'00) >> 8);
						b = static_cast<unsigned char>((c & 0x00'00'00'FF) >> 0);

						maxRed += (r) * (*curPosVect);
						maxGreen += (g) * (*curPosVect);
						maxBlue += (b) * (*curPosVect);


						++curPosVect;
						++startPix;
					}
					startPix += imgWidth - windowWidth;// skip 1 line
				}

				curPosVect = vectStart;

				*curPix = (maxRed << 16) | (maxGreen << 8) | (maxBlue << 0) | 0xFF'00'00'00;

			}

			if (posTracker == imgWidth) {
				posTracker = 0;
			}

			++curViewPix;
			++posTracker;
			++curPix;
		}

		//*img = im;
		++imgIn;
		++imgOut;
	}

	return 1; // succes

}
