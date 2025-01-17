#ifndef DISTRIBUTION_GAUSS_H
#define DISTRIBUTION_GAUSS_H

#include "Kernel.h"

class Distribution_Gauss : public Kernel
{
public:
	Distribution_Gauss() = delete;
	Distribution_Gauss(int windowSize);
	~Distribution_Gauss() = default;

	bool ProcessImage(std::vector<QImage> const &imageIn, std::vector<QImage>& imageOut) override;



private:
	std::vector<float> getKernel() override;
	int mWindowSize = 1;

};

#endif // DISTRIBUTION_GAUSS