#ifndef BLOBANALYSER_H
#define	BLOBANALYSER_H

#include "QImageUtilities.h"


class BlobAnalyser {

	BlobAnalyser() = delete;
	BlobAnalyser(BlobAnalyser const&) = delete;
	BlobAnalyser(BlobAnalyser&&) = delete;
	BlobAnalyser& operator=(BlobAnalyser const&) = delete;
	BlobAnalyser& operator=(BlobAnalyser&&) = delete;
	~BlobAnalyser() = delete;

public:
	static void sortList(QImageUtilities::BlobList & listToSort);
	static void trimList(QImageUtilities::BlobList& listToTrim, int AmountToKeep, bool Reverse = false);
	static QString analysePosition(QImageUtilities::BlobList const& listToTrim);
private:
	static bool my_compare(const QImageUtilities::BlobInfo &a,const QImageUtilities::BlobInfo &b);

private:


};

#endif BLOBANALYSER_H 