#ifndef MEDIAN_FILTER_H
#define MEDIAN_FILTER_H

#include "UnaryProcess.h"


class MedianFilter : public UnaryProcess
{
public:
	MedianFilter() = delete;
	MedianFilter(int windowSize);
	~MedianFilter() = default;


	bool ProcessImage(std::vector<QImage> const &imageIn, std::vector<QImage>& imageOut) override;
 
	void setWindowSize(int newWindowSize);
	size_t windowSize()const;

private:
	int mWindowSize = 1;

};
#endif // MEDIANFILTER_H