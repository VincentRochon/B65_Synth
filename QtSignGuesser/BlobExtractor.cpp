#include "BlobExtractor.h"
#include <queue>


void Remplissage(Data, x, y, vc, vr) {


	std::queue<int> ListeARemplacer();

	// S’assure que la valeur d’entrée soit à remplacer et amorce le remplissage
	if (Data[x][y] != vc) {
		return;
	}
	else {
		ListeARemplacer.Add(x, y);
	}

	// Parcours la liste des données à remplacer
	for (size_t i = 0; i < ListeARemplacer.size(); ++i) {
		
		x, y = ListeARemplacer[i];

		if (Data[x][y] == vc) {

			// voisin a gauche
			int G = x;

			while (G >= 0 && Data[G][y] == vc) {

				Data[G][y] = vr;
				if (y > 0 && Data[G][y] == vc) {

					ListeARemplacer.Add(G, y - 1); // Insère le voisin du haut

				}
				if (y < Data.height() - 1 && Data[G][y + 1] == vc) {
					ListeARemplacer.Add(G, y + 1); // Insère le voisin du bas
				}
				G--;
			}
			if (G >= 0) { // Recherche les voisins diagonau

				if (y > 0 && Data[G][y - 1] == vc) {
					ListeARemplacer.Add(G, y - 1); // Insère le voisin du haut
				}
				if (y < Data.Height() - 1 && Data[G][y + 1] == vc) {

					ListeARemplacer.Add(G, y + 1); // Insère le voisin du bas
				}
			}
			// voisin a droite
			int	D = x + 1;
			while (D < Data.Width() && Data[D][y] == vc) {

				Data[D][y] = vr;

				if (y > 0 && Data[G][y - 1] == vc) {

					ListeARemplacer.Add(D, y - 1); // Insère le voisin du haut

				}
				if (y < Data.Height() - 1 && Data[G][y + 1] == vc) {

					ListeARemplacer.Add(D, y + 1); // Insère le voisin du bas
				} 
				D++;
			}
			if (D < Data.Width()) { // Recherche les voisins diagonaux

				if (y > 0 && Data[G][y - 1] == vc) {
					ListeARemplacer.Add(D, y - 1); // Insère le voisin du haut
				}
				if (y < Data.Height() - 1 && Data[G][y + 1] == vc) {
					ListeARemplacer.Add(D, y + 1); // Insère le voisin du bas
				}
			}
		}
		
	}
}
