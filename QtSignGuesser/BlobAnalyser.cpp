#include "BlobAnalyser.h"


void BlobAnalyser::sortList(QImageUtilities::BlobList& listToSort)
{

	std::sort(listToSort.begin(), listToSort.end(), my_compare);

	
}

bool BlobAnalyser::my_compare(const QImageUtilities::BlobInfo & firstBlob,const QImageUtilities::BlobInfo& secondBlob)
{
	if (firstBlob.centroid().x() < secondBlob.centroid().x())
	{
		return true;
	}
	else if (firstBlob.centroid().x() > secondBlob.centroid().x())
	{
		return false;
	}
	else
	{
		if (firstBlob.centroid().y() < secondBlob.centroid().y())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
