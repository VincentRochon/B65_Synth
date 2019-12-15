#include "BlobAnalyser.h"


void BlobAnalyser::sortList(QImageUtilities::BlobList& listToSort)
{

	std::sort(listToSort.begin(), listToSort.end(), my_compare);

	
}

void BlobAnalyser::trimList(QImageUtilities::BlobList& listToTrim, int amountToKeep, bool Reverse)
{
	if (listToTrim.size() < amountToKeep) return; // keep all

	int amountToTrim{ listToTrim.size() - amountToKeep };

	if (Reverse) {

		for (size_t i = 0; i < amountToTrim; ++i)
		{
			listToTrim.removeFirst();
		}
	}
	else {

		for (size_t i = 0; i < amountToTrim; i++)
		{
			listToTrim.removeLast();
		}
	}
}

QString BlobAnalyser::analysePosition(QImageUtilities::BlobList const& listOfBlobs)
{
	if (listOfBlobs.size() != 5) return QString("invalide Size");

	auto curPos{ listOfBlobs.begin() };

	QImageUtilities::BlobInfo blob1{ *curPos };
	++curPos;
	QImageUtilities::BlobInfo blob2{ *curPos };
	++curPos;
	QImageUtilities::BlobInfo blob3{ *curPos };
	++curPos;
	QImageUtilities::BlobInfo blob4{ *curPos };
	++curPos;
	QImageUtilities::BlobInfo blob5{ *curPos };

	



	return QString("bb");
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
