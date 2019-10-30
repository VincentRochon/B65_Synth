#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include "UnaryProcess.h"


class Segmentation : public UnaryProcess
{
public:
	Segmentation() = delete;
	Segmentation(size_t Rmin, size_t Rmax, size_t Bmin, size_t Bmax, size_t Gmin, size_t Gmax);
	~Segmentation() = default;


	QImage ProcessImage(QImage const& image) override;


private:
	

};

#endif // SEGMENTATION