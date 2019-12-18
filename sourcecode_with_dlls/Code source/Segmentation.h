#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include "UnaryProcess.h"


class Segmentation : public UnaryProcess
{
public:
	Segmentation() = delete;
	Segmentation(size_t Rmin, size_t Rmax, size_t Gmin, size_t Gmax, size_t Bmin, size_t Bmax);
	~Segmentation() = default;


	bool ProcessImage(std::vector<QImage> const &imageIn, std::vector<QImage>& imageOut) override;


private:
	size_t mRmin;
	size_t mGmin;
	size_t mBmin;
	size_t mRmax;
	size_t mGmax;
	size_t mBmax;


};

#endif // SEGMENTATION