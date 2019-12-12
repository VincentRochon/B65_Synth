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

	void Remplissage(QImage &Data, int x, int y, int vc, int vr);
	void Etiquetage(QImage& img);

#pragma inline_recursion(on)
#pragma inline_depth(255)

	inline void floodFilling(QImage &Data,int x,int y,int vc,int vr);

private:

	std::vector<int> mData;


};

#endif // BLOBEXTRACTOR_H
