#include "UnaryProcess.h"

QImage UnaryProcess::ProcessImage(QImage const& image, int NeighborSize)
{
	QImage im(image);

	int* curPix{ reinterpret_cast<int*>(im.bits()) };
	int* endPix{ curPix + im.width() * im.height() };
	while (curPix < endPix) {
		int c{ *curPix };
		
		unsigned char r{ static_cast<unsigned char>((c & 0x00'FF'00'00) >> 16) };
		unsigned char g{ static_cast<unsigned char>((c & 0x00'00'FF'00) >> 8) };
		unsigned char b{ static_cast<unsigned char>((c & 0x00'00'00'FF) >> 0) };

		int average{ static_cast<int>((float)r * 0.25f + (float)g * 0.67f + (float)b * 0.08f) };
		*curPix = (average << 16) |
			(average << 8) |
			(average << 0) |
			0xFF'00'00'00;

		++curPix;
	}

	return im;
}
