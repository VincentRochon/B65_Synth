#ifndef BLOBEXTRACTOR_H
#define	BLOBEXTRACTOR_H

#include "qimage.h"
#pragma inline_recursion(on)
#pragma inline_depth(255)


class BlobExtractor {



private:

	struct pixel
	{
		int x, y;
	};


	BlobExtractor() = delete;
	//BlobExtractor(QImage const& image);
	~BlobExtractor() = delete;

	void Remplissage(QImage &Data, int x, int y, int vc, int vr);


	static inline void floodFilling4(QImage& Data, int x, int y, int vc,int vr);


public:
	static void Etiquetage(QImage& img);
	static void borderFilling(QImage& img, int color,int borderSize); 

	QRgb qBlack;
	QRgb qWhite;
	QRgb qRemVal;

};

inline int offSet(int x, int y, int lineSize) {

	return x + lineSize * y;
}

inline int* position(int* imagePtr, int x, int y, int lineSize) {

	return imagePtr + offSet(x, y, lineSize);
}

inline unsigned char value(int* imagePtr, int x, int y, int lineSize) {


	return *(imagePtr + x + (lineSize * y));
}

inline void fillArea(int* imagePtr, int x, int y, int curVal, int remVal, int lineSize, int* imageEnd) {
	
	int* p{ position(imagePtr,x,y,lineSize) };

	if (p < imagePtr || p >= imageEnd || *p != curVal) {
		return;
	}

	*p = remVal;

	fillArea(imagePtr, x - 1, y, curVal, remVal, lineSize, imageEnd);
	fillArea(imagePtr, x + 1, y, curVal, remVal, lineSize, imageEnd);
	fillArea(imagePtr, x, y-1, curVal, remVal, lineSize, imageEnd);
	fillArea(imagePtr, x,  y+1, curVal, remVal, lineSize, imageEnd);
}


#endif // BLOBEXTRACTOR_H
