#include "BlobExtractor.h"
#include <queue>

void BlobExtractor::Etiquetage(QImage& img) {

	
	int* curPix{ reinterpret_cast<int *>(img.bits()) };
	int imgWidth{ img.width() };
	int imgHeight{ img.height() };
	int* endPix{ curPix + imgWidth * imgHeight };
	
	for (size_t i = 0; i < imgHeight; ++i)
	{
		for (size_t j = 0; j < imgWidth; ++j)
		{
			if (*curPix != 0xFF'00'00'00 && *curPix != 0xFF'FF'FF'FF) {

				*curPix = 0xFF'00'00'FF;

			}
			++curPix;
		}
	}
	
	borderFilling(img, 0xFF'00'00'00,5);
	//fillArea(curPix, 0, 0, 0xFF'00'00'00, 0xFF'FF'FF'FF, imgWidth, endPix);

}
void BlobExtractor::borderFilling(QImage & img, int color, int borderSize)
{
	int* curPix{ reinterpret_cast<int *>(img.bits()) };
	int imgWidth{ img.width() };
	int imgHeight{ img.height() };
	int* endPix{ curPix + imgWidth * imgHeight };
	int posTracker{ 0 };

	for (size_t i = 0; i < imgWidth * borderSize; i++)
	{
		*curPix = color;
		++curPix;
	}

	while (curPix < endPix - (imgWidth * borderSize)) {



		if (posTracker < borderSize || posTracker >= (imgWidth - borderSize))
		{
			*curPix = color;

		}

		//*curPix = color;

		if (posTracker == imgWidth) {
			posTracker = 0;
		}

		++posTracker;
		++curPix;
	}

	for (size_t i = 0; i < imgWidth * borderSize; i++)
	{
		*curPix = color;
		++curPix;
	}


}
/*
inline void BlobExtractor::floodFilling4(QImage & Data, int x, int y, int vc,int vr)
{
	auto curPix{ Data.bits() };
	auto imgWidth{ Data.width() };

	if (x < 0 || x > imgWidth || *(curPix += (x + y * imgWidth)) == vc) {
		return;
	}

	*curPix = vr;

	floodFilling4(Data, x-1, y, vc, vr);
	floodFilling4(Data, x+1, y, vc, vr);
	// floodFilling4(Data, x, y-1, vc, vr);
	// floodFilling4(Data, x, y+1, vc, vr);


}*/


void BlobExtractor::Remplissage(QImage &Data,int x,int y,int vc,int vr) {

	auto curPos{ Data.bits() };
	auto resetPos{ Data.bits() };
	int imageWidth{Data.width()};
	int imageHeight{Data.height()};
	std::deque<BlobExtractor::pixel> ListeARemplacer;

	if (x > imageWidth || y > imageHeight) {
		return; // out of bounds
	}

	// S’assure que la valeur d’entrée soit à remplacer et amorce le remplissage
	if (*(curPos += x + (y * imageWidth)) != vc) {
		return;
	}
	else {
		//BlobExtractor::pixel px = {x,y};
		ListeARemplacer.push_back({ x,y });
	}

	// Parcours la liste des données à remplacer
	/*
	auto startList {ListeARemplacer.begin() };
	auto endList{ ListeARemplacer.end() };
	while (startList < endList)
	{
		x, y = startList[0].x;


		++startList;
	}*/

	for (size_t i = 0; i < ListeARemplacer.size(); ++i) {
		
		x, y = ListeARemplacer[i].x, ListeARemplacer[i].y;
		curPos = resetPos;

		if (curPos += x + (y * imageWidth) == vc) {

			// voisin a gauche
			int G = x;
			//curPos = resetPos;
			while (G >= 0 && *curPos == vc) {
				// curPos = resetPos;
				*curPos = vr;
				if (y > 0 && *(curPos - y * imageWidth) == vc) {

					//ListeARemplacer.Add(G, y - 1); // Insère le voisin du haut
					ListeARemplacer.push_back({ G,y - 1 });
				}
				if (y < imageHeight - 1 && *(curPos + y * imageWidth) == vc) {
					//ListeARemplacer.Add(G, y + 1); // Insère le voisin du bas
					ListeARemplacer.push_back({ G,y + 1 });
				}
				--G;
				--curPos;
			}
			if (G >= 0) { // Recherche les voisins diagonaux de gauche
				/*
				if (y > 0 && Data[G][y - 1] == vc) {
					ListeARemplacer.Add(G, y - 1); // Insère le voisin du haut
				}
				if (y < Data.Height() - 1 && Data[G][y + 1] == vc) {

					ListeARemplacer.Add(G, y + 1); // Insère le voisin du bas
				}*/
				if (y > 0 && *(curPos - y * imageWidth) == vc) {

					//ListeARemplacer.Add(G, y - 1); // Insère le voisin du haut
					ListeARemplacer.push_back({ G,y - 1 });
				}
				if (y < imageHeight - 1 && *(curPos + y * imageWidth) == vc) {
					//ListeARemplacer.Add(G, y + 1); // Insère le voisin du bas
					ListeARemplacer.push_back({ G,y + 1 });
				}
			}
			// voisin a droite
			int	D = x + 1;
			curPos += 2;
			while (D < imageWidth && *curPos == vc) {

				*curPos = vr;

				if (y > 0 && *(curPos - y * imageWidth) == vc) {

					ListeARemplacer.push_back({ D, y - 1 }); // Insère le voisin du haut

				}
				if (y < imageHeight - 1 && *(curPos + y * imageWidth) == vc) {

					ListeARemplacer.push_back({ D, y + 1 }); // Insère le voisin du bas
				} 
				++D;
				++curPos;
			}
			if (D < imageWidth) { // Recherche les voisins diagonaux

				if (y > 0 && *(curPos - y * imageWidth) == vc) {
					ListeARemplacer.push_back({ D, y - 1 }); // Insère le voisin du haut
				}
				if (y < imageHeight - 1 && *(curPos + y * imageWidth) == vc) {
					ListeARemplacer.push_back({ D, y + 1 }); // Insère le voisin du bas
				}
			}
		}
		
	}
}
