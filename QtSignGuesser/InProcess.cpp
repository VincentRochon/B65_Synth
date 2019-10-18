#include "InProcess.h"

InProcess::InProcess(QImage const& image)
	:mImageToProcess(image)
{
	// A REFAIRE
	mProcess.push_back(new MaximumFilter());
}


void InProcess::Process()
{
	mProcessedImage = mProcess[0]->ProcessImage(mImageToProcess);
	
}

QImage InProcess::getProcessedImage() const
{
	return mProcessedImage;
}
