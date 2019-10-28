#ifndef INPROCESS_H
#define INPROCESS_H


#include "qimage.h"
#include "UnaryProcess.h"
#include "MaximumFilter.h"
#include "MedianFilter.h"
#include "Kernel_Convolution.h"
#include "Distribution_Gauss.h"
#include "Distribution_Normal.h"

class InProcess 
{
public:
	InProcess(QImage const& image);
	~InProcess() = default;


public:
	void Process();
	QImage getProcessedImage() const;
	void addMaximumFilter(int neighborhoodSize);
	void addMedianFilter(int neighborhoodSize);


private:
	std::list<UnaryProcess *> mProcess;
	QImage mImageToProcess;
	QImage mProcessedImage;

};

#endif