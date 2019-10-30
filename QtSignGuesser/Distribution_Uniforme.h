#ifndef DISTRIBUTION_UNIFORME_H
#define DISTRIBUTION_UNIFORME_H

#include "Kernel.h"

class Distribution_Uniforme : public Kernel
{
public:
	Distribution_Uniforme() = delete;
	Distribution_Uniforme(int windowSize);
	~Distribution_Uniforme() = default;

	QImage ProcessImage(QImage const& image) override;



private:
	std::vector<int> fillKernel() override;
	int mWindowSize = 1;
};


#endif // DISTRIBUTION_UNIFORME
