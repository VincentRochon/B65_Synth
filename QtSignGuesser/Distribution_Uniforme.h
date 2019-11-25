#ifndef DISTRIBUTION_UNIFORME_H
#define DISTRIBUTION_UNIFORME_H

#include "Kernel.h"

class Distribution_Uniforme : public Kernel
{
public:
	Distribution_Uniforme() = delete;
	Distribution_Uniforme(int windowSize);
	~Distribution_Uniforme() = default;

	void ProcessImage(std::vector<QImage> &image) override;



private:
	std::vector<float> getKernel() override;
	int mWindowSize = 1;
};


#endif // DISTRIBUTION_UNIFORME
