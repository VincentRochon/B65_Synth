#ifndef IMAGEMERGER_H
#define IMAGEMERGER_H

#include "qimage.h"

class ImageMerger 
{
public:
	ImageMerger() = delete;
	~ImageMerger() = delete;

	static QImage merge(QImage const& Image1, QImage const& Image2);

};


#endif // IMAGEMERGER_H