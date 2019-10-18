#ifndef INPROCESS_H
#define INPROCESS_H


#include "qimage.h"
#include "UnaryProcess.h"
#include "MaximumFilter.h"
#include "MedianFilter.h"

class InProcess 
{
public:
	InProcess(QImage const& image);
	~InProcess() = default;


public:
	void Process();
	QImage getProcessedImage() const;


private:
	std::vector<UnaryProcess *> mProcess;
	QImage mImageToProcess;
	QImage mProcessedImage;

};

#endif