#ifndef MAXIMUMFILTER_H
#define MAXIMUMFILTER_H

#include "RankFilter.h"


class MaximumFilter : public RankFilter
{
public :
	MaximumFilter() = delete;
	~MaximumFilter() = delete;


	QImage ProcessImage(QImage const& image, size_t NeighborSize );


};

#endif // MAXIMUMFILTER