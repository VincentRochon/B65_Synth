#include "MedianFilter.h"

MedianFilter::MedianFilter(int windowSize)
	:mWindowSize(windowSize)
{

}

bool MedianFilter::ProcessImage(std::vector<QImage> const& imageIn, std::vector<QImage>& imageOut)
{
	if (imageIn.size() != imageOut.size()) {
		return false; // invalid format of either vectors
	}

	size_t posTracker{ 0 };
	size_t compteur{ 0 };
	int median{ 0 };
	int windowWidth{ mWindowSize * 2 + 1 };
	unsigned char r{};
	unsigned char g{};
	unsigned char b{};
	unsigned char midRed{};
	unsigned char midGreen{};
	unsigned char midBlue{};
	int c{};
	std::vector<unsigned char> listOfRed(windowWidth * windowWidth);
	std::vector<unsigned char> listOfGreen(windowWidth * windowWidth);
	std::vector<unsigned char> listOfBlue(windowWidth * windowWidth);
	unsigned char* vecPosRed{ listOfRed.data() };
	unsigned char* vecPosGreen{ listOfGreen.data() };
	unsigned char* vecPosBlue{ listOfBlue.data() };

	auto imgIn{ imageIn.data() };
	auto imgOut{ imageOut.data() };

	for (size_t i = 0; i < imageIn.size(); ++i) {

		//QImage im(*img);

		int imgWidth{ imgOut->width() };
		int imgHeight{ imgOut->height() };

		const int* curViewPix{ reinterpret_cast<const int*>(imgIn->bits()) };
		int* curPix{ reinterpret_cast<int*>(imgOut->bits()) };
		int* endPix{ curPix + imgWidth * imgHeight };

		curViewPix += imgWidth * mWindowSize;
		curPix += imgWidth * mWindowSize; // skip lines to prevent overflow
		endPix -= imgWidth * mWindowSize; // remove last line prevent overflow for treatment

		while (curPix < endPix) {

			if (posTracker > mWindowSize&& posTracker < (imgWidth - mWindowSize))
			{
				//btree* redTree = new btree();
				//btree* greenTree = new btree();
				//btree* blueTree = new btree();

				const int* startPix{ curViewPix - imgWidth * mWindowSize + mWindowSize }; // start of the window of pixels
				//int* prevPix{ curPix - imgWidth * mWindowSize + mWindowSize };

				for (size_t i = 0; i < windowWidth * windowWidth; ++i)
				{
					if (compteur == windowWidth)
					{
						compteur = 0;
						startPix += imgWidth - windowWidth;// skip 1 line
					}
					c = *startPix;

					r = static_cast<unsigned char>((c & 0x00'FF'00'00) >> 16);
					g = static_cast<unsigned char>((c & 0x00'00'FF'00) >> 8);
					b = static_cast<unsigned char>((c & 0x00'00'00'FF) >> 0);

					//redTree->insert(r);
					//greenTree->insert(g);
					//blueTree->insert(b);


					*vecPosRed = r;
					*vecPosGreen = g;
					*vecPosBlue = b;

					++vecPosRed;
					++vecPosGreen;
					++vecPosBlue;


					++compteur;
					++startPix;

				}

				vecPosRed -= windowWidth * windowWidth;
				vecPosGreen -= windowWidth * windowWidth;
				vecPosBlue -= windowWidth * windowWidth;

				//r = static_cast<unsigned char>(redTree->findMedian(redTree->getRoot()));
				//g = static_cast<unsigned char>(greenTree->findMedian(greenTree->getRoot()));
				//b = static_cast<unsigned char>(blueTree->findMedian(blueTree->getRoot()));

				std::sort(std::begin(listOfRed), std::end(listOfRed));
				std::sort(std::begin(listOfGreen), std::end(listOfGreen));
				std::sort(std::begin(listOfBlue), std::end(listOfBlue));
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
				vecPosRed += nombreTest;
				vecPosGreen += nombreTest;
				vecPosBlue += nombreTest;

				*curPix = (*vecPosRed << 16) | (*vecPosGreen << 8) | (*vecPosBlue << 0) | 0xFF'00'00'00;
				//* curPix = *vecPos;
				vecPosRed -= nombreTest;
				vecPosGreen -= nombreTest;
				vecPosBlue -= nombreTest;
			}

			if (posTracker == imgWidth) {
				posTracker = 0;
			}

			++curViewPix;
			++posTracker;
			++curPix;
		}
		++imgIn;
		++imgOut;
		//*img = im;
	}

	return true; //succesfull

}

void MedianFilter::setWindowSize(int newWindowSize)
{
	mWindowSize = newWindowSize;
}

size_t MedianFilter::windowSize() const
{
	return mWindowSize;
}
