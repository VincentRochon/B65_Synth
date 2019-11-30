#include "InProcess.h"

InProcess::InProcess(QImage const& image)
	:mImageIn{ image }, mImageOut{image}
{

}

InProcess::~InProcess()
{
	std::list<UnaryProcess*>::iterator itBegin{ mProcess.begin() };
	std::list<UnaryProcess*>::iterator itEnd{ mProcess.end() };

	while (itBegin != itEnd)
	{
		delete *itBegin;

		++itBegin;
	}
}


void InProcess::Process()
{
	std::list<UnaryProcess *>::iterator itBegin{ mProcess.begin() };
	std::list<UnaryProcess*>::iterator itEnd{ mProcess.end() };

	while (itBegin != itEnd)
	{
		(*itBegin)->ProcessImage(mImageIn,mImageOut);
		
		mImageIn = mImageOut;

		itBegin++;

	}
	
}

QImage InProcess::getProcessedImage() const
{
	return mProcessedImage;
}

std::vector<QImage> const & InProcess::getProcessedImages() const
{
	return mImageOut;
}

std::vector<QImage> const& InProcess::getImageToProcess() const
{
	return mImageIn;
}

void InProcess::setImageToProcess(QImage const& image)
{
	mImageIn.clear();
	mImageIn.push_back(image);

}

void InProcess::setImageToProcess(QImage const& image1, QImage const& image2)
{
	mImageIn.clear();
	mImageIn.push_back(image1);
	mImageIn.push_back(image2);
}

void InProcess::setImageToProcess(QImage const& image1, QImage const& image2, QImage const& image3)
{
	mImageIn.clear();
	mImageIn.push_back(image1);
	mImageIn.push_back(image2);
	mImageIn.push_back(image3);
}

void InProcess::setImageToProcess(QImage const& image1, QImage const& image2, QImage const& image3, QImage const& image4)
{
	mImageIn.clear();
	mImageIn.push_back(image1);
	mImageIn.push_back(image2);
	mImageIn.push_back(image3);
	mImageIn.push_back(image4);
}

void InProcess::setImageToProcess(QImage const& image1, QImage const& image2, QImage const& image3, QImage const& image4, QImage const& image5)
{
	mImageIn.clear();
	mImageIn.push_back(image1);
	mImageIn.push_back(image2);
	mImageIn.push_back(image3);
	mImageIn.push_back(image4);
	mImageIn.push_back(image5);
}

void InProcess::setImageToProcess(std::vector<QImage> const& image)
{
	mImageIn.clear();
	mImageIn = image;
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

void InProcess::addUniformeConvolution(int neighborhoodSize)
{
	mProcess.push_back(new Distribution_Uniforme(neighborhoodSize));
}

void InProcess::addSegmentation(size_t Rmin, size_t Rmax, size_t Gmin, size_t Gmax, size_t Bmin, size_t Bmax)
{
	mProcess.push_back(new Segmentation(Rmin,Rmax,Gmin,Gmax,Bmin,Bmax));
}

void InProcess::addMoyenneImage()
{
	mProcess.push_back(new MoyenneImage());
}

void InProcess::addNormalisation(unsigned char normalValue)
{

	mProcess.push_back(new Normalisation(normalValue));

}

void InProcess::addUniformisation()
{
	mProcess.push_back(new Uniformisation());
}


