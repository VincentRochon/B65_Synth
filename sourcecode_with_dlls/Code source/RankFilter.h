#ifndef RANKFILTER_H
#define RANKFILTER_H

#include "UnaryProcess.h"


class RankFilter : public UnaryProcess
{

public:
	RankFilter() = delete;
	RankFilter(int neighborhoodSize);
	~RankFilter() = default;

private:
	int mNeighborhoodSize;
};

#endif // RANKFILTER_H