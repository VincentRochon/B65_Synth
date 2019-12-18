#ifndef UNARYPROCESS_H
#define UNARYPROCESS_H

#include <QImage>



class UnaryProcess {
public:
	UnaryProcess() = default;
	virtual ~UnaryProcess() = default;

	virtual bool ProcessImage(std::vector<QImage> const &imageIn,std::vector<QImage> &imageOut ) =0;

};

#endif // UNARYPROCESS_H