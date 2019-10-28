#ifndef DISTRIBUTION_GAUSS_H
#define DISTRIBUTION_GAUSS_H

#include "Kernel.h"

class Distribution_Gauss : public Kernel
{
public:
	Distribution_Gauss() = delete;
	Distribution_Gauss(int windowSize);
	~Distribution_Gauss() = default;


	QImage ProcessImage(QImage const& image) override;



private:
	

};

#endif // DISTRIBUTION_GAUSS