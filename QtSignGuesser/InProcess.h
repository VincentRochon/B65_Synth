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
#include "btree.h" // to remove
#include "MoyenneImage.h"

class InProcess 
{
public:
	InProcess(QImage const&);
	~InProcess();


public:
	void Process();
	QImage getProcessedImage() const;
	std::vector<QImage> getProcessedImages() const;
	void addMaximumFilter(int neighborhoodSize);
	void addMedianFilter(int neighborhoodSize);
	void addGaussianConvolution(int neighborhoodSize);
	void addUniformeConvolution(int neighborhoodSize);
	void addSegmentation(size_t Rmin, size_t Rmax, size_t Gmin, size_t Gmax, size_t Bmin, size_t Bmax);
	void addMoyenneImage();


private:
	std::list<UnaryProcess *> mProcess;
	QImage mProcessedImage;
	std::vector<QImage> mImageIn;
	std::vector<QImage> mImageOut;

};

#endif