#include "InProcess.h"

InProcess::InProcess(QImage const& image)
	:mImageReference{ image }, mImageToProcess{image}
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
		(*itBegin)->ProcessImage(mImageReference, mImageToProcess);
		
		mImageReference = mImageToProcess;

		itBegin++;

	}
	
}
/*
QImage InProcess::getProcessedImage() const
{
	return mProcessedImage;
}*/

std::vector<QImage> const & InProcess::getImageToProcess() const
{
	return mImageToProcess;
}

std::vector<QImage> const& InProcess::getImageOfReference() const
{
	return mImageReference;
}

void InProcess::setImageOfReference(QImage const& image)
{
	mImageReference.clear();
	mImageReference.push_back(image);

}

void InProcess::setImageOfReference(QImage const& image1, QImage const& image2)
{
	mImageReference.clear();
	mImageReference.push_back(image1);
	mImageReference.push_back(image2);
}

void InProcess::setImageOfReference(QImage const& image1, QImage const& image2, QImage const& image3)
{
	mImageReference.clear();
	mImageReference.push_back(image1);
	mImageReference.push_back(image2);
	mImageReference.push_back(image3);
}

void InProcess::setImageOfReference(QImage const& image1, QImage const& image2, QImage const& image3, QImage const& image4)
{
	mImageReference.clear();
	mImageReference.push_back(image1);
	mImageReference.push_back(image2);
	mImageReference.push_back(image3);
	mImageReference.push_back(image4);
}

void InProcess::setImageOfReference(QImage const& image1, QImage const& image2, QImage const& image3, QImage const& image4, QImage const& image5)
{
	mImageReference.clear();
	mImageReference.push_back(image1);
	mImageReference.push_back(image2);
	mImageReference.push_back(image3);
	mImageReference.push_back(image4);
	mImageReference.push_back(image5);
}

void InProcess::setImageOfReference(std::vector<QImage> const& image)
{
	mImageReference = image;
}

void InProcess::setImageToProcess(QImage& image)
{
	mImageToProcess.clear();
	mImageToProcess.push_back(image);
}

void InProcess::setImageToProcess(QImage& image1, QImage& image2)
{
	mImageToProcess.clear();
	mImageToProcess.push_back(image1);
	mImageToProcess.push_back(image2);
}

void InProcess::setImageToProcess(QImage& image1, QImage& image2, QImage& image3)
{
	mImageToProcess.clear();
	mImageToProcess.push_back(image1);
	mImageToProcess.push_back(image2);
	mImageToProcess.push_back(image3);
}

void InProcess::setImageToProcess(QImage& image1, QImage& image2, QImage& image3, QImage& image4)
{
	mImageToProcess.clear();
	mImageToProcess.push_back(image1);
	mImageToProcess.push_back(image2);
	mImageToProcess.push_back(image3);
	mImageToProcess.push_back(image4);
}

void InProcess::setImageToProcess(QImage& image1, QImage& image2, QImage& image3, QImage& image4, QImage& image5)
{
	mImageToProcess.clear();
	mImageToProcess.push_back(image1);
	mImageToProcess.push_back(image2);
	mImageToProcess.push_back(image3);
	mImageToProcess.push_back(image4);
	mImageToProcess.push_back(image5);
}

void InProcess::setImageToProcess(std::vector<QImage>& image)
{
	mImageToProcess = image;
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


