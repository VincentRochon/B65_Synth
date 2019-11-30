#ifndef INPROCESS_H
#define INPROCESS_H

#include "qimage.h"
#include "UnaryProcess.h"
#include "MaximumFilter.h"
#include "MedianFilter.h"
#include "Kernel.h"
#include "Distribution_Gauss.h"
#include "Distribution_Uniforme.h"
#include "Segmentation.h"
#include "MoyenneImage.h"
#include "Normalisation.h"
#include "Uniformisation.h"

class InProcess 
{
public:
	InProcess(QImage const&);
	~InProcess();


public:
	void Process();
	QImage getProcessedImage() const;
	std::vector<QImage> const & getProcessedImages() const;
	std::vector<QImage> const & getImageToProcess() const;
	void setImageToProcess(QImage const& image);
	void setImageToProcess(QImage const& image1, QImage const& image2);
	void setImageToProcess(QImage const& image1, QImage const& image2, QImage const& image3);
	void setImageToProcess(QImage const& image1, QImage const& image2, QImage const& image3, QImage const& image4);
	void setImageToProcess(QImage const& image1, QImage const& image2, QImage const& image3, QImage const& image4, QImage const& image5);
	void setImageToProcess(std::vector<QImage> const& image);
	void addMaximumFilter(int neighborhoodSize);
	void addMedianFilter(int neighborhoodSize);
	void addGaussianConvolution(int neighborhoodSize);
	void addUniformeConvolution(int neighborhoodSize);
	void addSegmentation(size_t Rmin, size_t Rmax, size_t Gmin, size_t Gmax, size_t Bmin, size_t Bmax);
	void addMoyenneImage();
	void addNormalisation(unsigned char normalValue);
	void addUniformisation();


private:
	std::list<UnaryProcess *> mProcess;
	QImage mProcessedImage;
	std::vector<QImage> mImageIn;
	std::vector<QImage> mImageOut;

};

#endif