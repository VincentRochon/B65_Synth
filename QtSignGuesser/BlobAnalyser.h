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
	static bool hCheck(QImageUtilities::BlobInfo const& blob0,
		QImageUtilities::BlobInfo const& blob1,
		QImageUtilities::BlobInfo const& blob2,
		QImageUtilities::BlobInfo const& blob3,
		QImageUtilities::BlobInfo const& blob4);



};

#endif BLOBANALYSER_H 