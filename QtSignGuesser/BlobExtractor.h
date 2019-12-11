#ifndef BLOBEXTRACTOR_H
#define	BLOBEXTRACTOR_H

#include "qimage.h"

class BlobExtractor {

public:

	struct pixel
	{
		int x, y;
	};

	BlobExtractor() = delete;
	//BlobExtractor(QImage const& image);
	~BlobExtractor() = delete;


private:

	std::vector<int> mData;


};

#endif // BLOBEXTRACTOR_H
