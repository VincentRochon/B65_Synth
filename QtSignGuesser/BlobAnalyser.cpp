#include "BlobAnalyser.h"


void BlobAnalyser::sortListLtoR(QImageUtilities::BlobList& listToSort)
{

	std::sort(listToSort.begin(), listToSort.end(), my_compare);

	
}

void BlobAnalyser::sortList(QImage const& image, QImageUtilities::BlobList & listToSort)
{
	int imgWidth{ image.width() };
	int imgHeight{ image.height() };
	int compteur{1};

	std::vector < BlobExtractor::pixel > tempVect(imgWidth * imgHeight, {0,0});
	QImageUtilities::BlobList newList{ listToSort };

	auto curPix{ listToSort.begin() };
	auto endPix{ listToSort.end() };

	while (curPix < endPix)
	{
		int x{ static_cast<int>(curPix->centroid().x()) };
		int y{ static_cast<int>(curPix->centroid().y()) };

		tempVect[x + (y * imgHeight)] = {x,y};
		++compteur;
		++curPix;
	}

	auto curPointer{ tempVect.begin() };
	auto endPointer{ tempVect.end() };
	
	compteur = 0 ;
	BlobExtractor::pixel dummyPix{0,0};

	while (curPointer < endPointer)
	{
		if (*curPointer != dummyPix) {

			int x{ curPointer->x };
			int y{ curPointer->y };

			newList[compteur] = findXnYmatch(listToSort, x, y);
			++compteur;
		}
		++curPointer;
	}

	listToSort = newList;
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
	if (listOfBlobs.size() != 5) return QString("invalide");

	auto curPos{ listOfBlobs.begin() };

	QImageUtilities::BlobInfo blob0{ *curPos };
	++curPos;
	QImageUtilities::BlobInfo blob1{ *curPos };
	++curPos;
	QImageUtilities::BlobInfo blob2{ *curPos };
	++curPos;
	QImageUtilities::BlobInfo blob3{ *curPos };
	++curPos;
	QImageUtilities::BlobInfo blob4{ *curPos };

	
	if (hCheck(blob0, blob1, blob2, blob3, blob4)) {
		return QString("H");
	}
	if (xCheck(blob0, blob1, blob2, blob3, blob4)) {
		return QString("X");
	}


	return QString("Echec");
}

bool BlobAnalyser::hCheck(QImageUtilities::BlobInfo const& blob0, QImageUtilities::BlobInfo const& blob1, QImageUtilities::BlobInfo const& blob2, QImageUtilities::BlobInfo const& blob3, QImageUtilities::BlobInfo const& blob4)
{
	int	x0{ static_cast<int>(blob0.centroid().x()) };
	int	y0{ static_cast<int>(blob0.centroid().y()) };
	int	x1{ static_cast<int>(blob1.centroid().x()) };
	int	y1{ static_cast<int>(blob1.centroid().y()) };
	int	x2{ static_cast<int>(blob2.centroid().x()) };
	int	y2{ static_cast<int>(blob2.centroid().y()) };
	int	x3{ static_cast<int>(blob3.centroid().x()) };
	int	y3{ static_cast<int>(blob3.centroid().y()) };
	int	x4{ static_cast<int>(blob4.centroid().x()) };
	int	y4{ static_cast<int>(blob4.centroid().y()) };

	int counter{};
	

	if (y0 < y1 && y0 < y2&& y0 < y4) {
		++counter; // good position 1st blob
	}

	if (y1 > y0 && y1 > y3 && y1 > y4)
	{
		++counter; // good position 2nd blob
	}

	if (y2 > y0 && y2 > y3 && y2 > y4) {
		++counter; // good position 3rd blob
	}

	
	if (y3 < y1 && y3 < y2)
	{
		++counter; // good position 3rd blob
	}
	

	if (y4 > y0 && y4 > y3)
	{
		++counter; // good position 4th blob
	}

	if (counter == 5)
	{
		return true; // success
	}

	return false; // failure
}

bool BlobAnalyser::xCheck(QImageUtilities::BlobInfo const & blob0, QImageUtilities::BlobInfo const & blob1, QImageUtilities::BlobInfo const & blob2, QImageUtilities::BlobInfo const & blob3, QImageUtilities::BlobInfo const & blob4)
{
	int	x0{ static_cast<int>(blob0.centroid().x()) };
	int	y0{ static_cast<int>(blob0.centroid().y()) };
	int	x1{ static_cast<int>(blob1.centroid().x()) };
	int	y1{ static_cast<int>(blob1.centroid().y()) };
	int	x2{ static_cast<int>(blob2.centroid().x()) };
	int	y2{ static_cast<int>(blob2.centroid().y()) };
	int	x3{ static_cast<int>(blob3.centroid().x()) };
	int	y3{ static_cast<int>(blob3.centroid().y()) };
	int	x4{ static_cast<int>(blob4.centroid().x()) };
	int	y4{ static_cast<int>(blob4.centroid().y()) };

	int counter{}; 

	if (y0 > y1 && y0 > y2 && y0 > y3 && y0 > y4) {
		++counter;
	}

	if (y1 < y0 && y1 < y2 && y1 < y4) {
		++counter;
	}

	if (y2 > y1 && y2 > y3 && y2 > y4) {
		++counter;
	}

	if (y3 < y0 && y3 < y2 && y3 < y4) {
		++counter;
	}

	if (y4 < y0 && y4 > y1 && y4 < y2 && y4 > y3) {
		++counter;
	}


	if (counter == 5)
	{
		return true; // success
	}

	return false; // failure
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

QImageUtilities::BlobInfo BlobAnalyser::findXnYmatch(QImageUtilities::BlobList& blobList, int x, int y)
{
	auto curBlob{ blobList.begin() };
	auto endBlob{ blobList.end() };


	while (curBlob < endBlob)
	{
		int curX{ static_cast<int>(curBlob->centroid().x()) };
		int curY{ static_cast<int>(curBlob->centroid().y()) };

		if (curX == x && curY == y) {

			return *curBlob;
		}

		++curBlob;
	}

	return QImageUtilities::BlobInfo();
}

