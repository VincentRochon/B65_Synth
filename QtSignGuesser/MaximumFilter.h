#ifndef MAXIMUMFILTER_H
#define MAXIMUMFILTER_H

#include "UnaryProcess.h"


class MaximumFilter : public UnaryProcess
{
public :
	MaximumFilter() = default;
	MaximumFilter(int windowSize);
	~MaximumFilter() = default;


	QImage ProcessImage(QImage const& image ) override;

	void setWindowSize(int newWindowSize);
	size_t windowSize()const;

private:
	int mWindowSize = 0;

};

#endif // MAXIMUMFILTER