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
#include "btree.h"

class InProcess 
{
public:
	InProcess();
	~InProcess();


public:
	void Process();
	QImage getProcessedImage() const;
	void addMaximumFilter(int neighborhoodSize);
	void addMedianFilter(int neighborhoodSize);
	void addGaussianConvolution(int neighborhoodSize);
	void addUniformeConvolution(int neighborhoodSize);
	void addSegmentation(size_t Rmin, size_t Rmax, size_t Gmin, size_t Gmax, size_t Bmin, size_t Bmax);


private:
	std::list<UnaryProcess *> mProcess;
	QImage mProcessedImage;
	std::vector<QImage> mVectorOfProcessedImage;
	std::vector<QImage const&> mVectorOfImageToProcess;

};

#endif