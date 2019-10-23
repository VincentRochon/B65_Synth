#include "InProcess.h"

InProcess::InProcess(QImage const& image)
	:mImageToProcess(image),mProcessedImage(image)
{

}


void InProcess::Process()
{
	auto itBegin{ mProcess.begin() };
	auto itEnd{ mProcess.end() };

	while (itBegin != itEnd)
	{
		mProcessedImage = (*itBegin)->ProcessImage(mImageToProcess);
		
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


