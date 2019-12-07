#ifndef BLOBEXTRACTOR_H
#define	BLOBEXTRACTOR_H

#include "qimage.h"

class BlobExtractor {

public:

	BlobExtractor() = delete;
	BlobExtractor(QImage const& image);
	~BlobExtractor() = default;


private:

	std::vector<int> mData;


};

#endif // BLOBEXTRACTOR_H
