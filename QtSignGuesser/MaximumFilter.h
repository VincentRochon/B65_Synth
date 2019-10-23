#ifndef MAXIMUMFILTER_H
#define MAXIMUMFILTER_H

#include "UnaryProcess.h"
#include <algorithm>


class MaximumFilter : public UnaryProcess
{
public :
	MaximumFilter() = delete;
	MaximumFilter(int windowSize);
	~MaximumFilter() = default;


	QImage ProcessImage(QImage const& image ) override;

	void setWindowSize(int newWindowSize);
	size_t windowSize()const;

private:
	int mWindowSize = 1;

};

#endif // MAXIMUMFILTER