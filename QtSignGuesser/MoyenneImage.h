#ifndef MOYENNEIMAGE_H
#define MOYENNEIMAGE_H

#include "UnaryProcess.h"

class MoyenneImage : public UnaryProcess
{

public :

	MoyenneImage() = default;
	~MoyenneImage() = default;

	bool ProcessImage(std::vector<QImage> const& imageIn, std::vector<QImage>& imageOut) override;


};

#endif // !MOYENNEIMAGE_H
