#include "InProcess.h"

InProcess::InProcess(QImage const& image)
	:mProcessedImage(image)
{

}

InProcess::~InProcess()
{
	std::list<UnaryProcess*>::iterator itBegin{ mProcess.begin() };
	std::list<UnaryProcess*>::iterator itEnd{ mProcess.end() };

	while (itBegin != itEnd)
	{
		delete [] *itBegin;

		++itBegin;
	}
}


void InProcess::Process()
{
	std::list<UnaryProcess *>::iterator itBegin{ mProcess.begin() };
	std::list<UnaryProcess*>::iterator itEnd{ mProcess.end() };

	while (itBegin != itEnd)
	{
		mProcessedImage = (*itBegin)->ProcessImage(mProcessedImage);
		
		itBegin++;

	}
	
}

QImage InProcess::getProcessedImage() const
{
	return mProcessedImage;
}

void InProcess::addMaximumFilter(int neighborhoodSize)
{
	mProcess.push_back(new MaximumFilter(neighborhoodSize));
}

void InProcess::addMedianFilter(int neighborhoodSize)
{
	mProcess.push_back(new MedianFilter(neighborhoodSize));
}

void InProcess::addGaussianConvolution(int neighborhoodSize)
{
	mProcess.push_back(new Distribution_Gauss(neighborhoodSize));
}

void InProcess::addNormalConvolution(int neighborhoodSize)
{
	mProcess.push_back(new Distribution_Uniforme(neighborhoodSize));
}


