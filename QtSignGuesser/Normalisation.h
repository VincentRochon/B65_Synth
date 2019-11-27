#ifndef NORMALISATION_H	
#define NORMALISATION_H


#include "UnaryProcess.h"

class Normalisation : public UnaryProcess
{
public :


	Normalisation() = delete;
	Normalisation(unsigned char mNormalValue);
	~Normalisation() = default;

	bool ProcessImage(std::vector<QImage> const& imageIn, std::vector<QImage>& imageOut) override;

private:
	unsigned char mNormalValue;


};


#endif // NORMALISATION_H