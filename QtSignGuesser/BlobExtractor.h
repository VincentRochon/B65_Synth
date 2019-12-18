#ifndef BLOBEXTRACTOR_H
#define	BLOBEXTRACTOR_H

#include "qimage.h"


class BlobExtractor {



private:



	BlobExtractor() = delete;
	BlobExtractor(BlobExtractor const&) = delete;
	BlobExtractor(BlobExtractor&&) = delete;
	BlobExtractor& operator=(BlobExtractor const&) = delete;
	BlobExtractor& operator=(BlobExtractor&&) = delete;
	~BlobExtractor() = delete;

	// void Remplissage(QImage &Data, int x, int y, int vc, int vr);


	// static inline void floodFilling4(QImage& Data, int x, int y, int vc,int vr);


public:

	struct pixel
	{
		int x, y;
	};

	// static void Etiquetage(QImage& img);
	// static void borderFilling(QImage& img, int color,int borderSize); 

	QRgb qBlack;
	QRgb qWhite;
	QRgb qRemVal;


	
};

#pragma inline_recursion(on)
#pragma inline_depth(255)

inline bool operator==(const BlobExtractor::pixel& lhs, const BlobExtractor::pixel& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; };
inline bool operator!=(const BlobExtractor::pixel& lhs, const BlobExtractor::pixel& rhs) { return !operator==(lhs, rhs); }


#endif // BLOBEXTRACTOR_H


//
//  _       _ _              _                 _                           _        _   _             
// (_)_ __ | (_)_ __   ___  (_)_ __ ___  _ __ | | ___ _ __ ___   ___ _ __ | |_ __ _| |_(_) ___  _ __  
// | | '_ \| | | '_ \ / _ \ | | '_ ` _ \| '_ \| |/ _ \ '_ ` _ \ / _ \ '_ \| __/ _` | __| |/ _ \| '_ \ 
// | | | | | | | | | |  __/ | | | | | | | |_) | |  __/ | | | | |  __/ | | | || (_| | |_| | (_) | | | |
// |_|_| |_|_|_|_| |_|\___| |_|_| |_| |_| .__/|_|\___|_| |_| |_|\___|_| |_|\__\__,_|\__|_|\___/|_| |_|
//                                      |_|                                                           
//



/*
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

	if (p < imagePtr || p >= imageEnd || *p != curVal || *p == 0xFF'FF'00'00) {
		return;
	}

	*p = remVal;

	fillArea(imagePtr, x - 1, y, curVal, remVal, lineSize, imageEnd);
	fillArea(imagePtr, x + 1, y, curVal, remVal, lineSize, imageEnd);
	fillArea(imagePtr, x, y - 1, curVal, remVal, lineSize, imageEnd);
	fillArea(imagePtr, x, y + 1, curVal, remVal, lineSize, imageEnd);
}*/