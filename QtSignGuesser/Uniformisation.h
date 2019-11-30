#ifndef UNIFORMISATION_H
#define UNIFORMISATION_H

#include "UnaryProcess.h"

class Uniformisation : public UnaryProcess
{

public:

	Uniformisation() = default;
	~Uniformisation() = default;

	bool ProcessImage(std::vector<QImage> const& CarteEclairage, std::vector<QImage>& imageOut) override;


};

#endif // UNIFORMISATION_H
