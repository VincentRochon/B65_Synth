#ifndef UNARYPROCESS_H
#define UNARYPROCESS_H

#include <QImage>


class UnaryProcess
{
	public:
	UnaryProcess() = default;
	~UnaryProcess() = default;

	static QImage ProcessImage(QImage const& image, int NeighborSize) ;

};

#endif // UNARYPROCESS_H