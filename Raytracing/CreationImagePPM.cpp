// CreationImagePPM.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void createPPMImage(vector<int> dimensions, vector<vector<vector<int>>> pixels, const char* filename) {

	int i, j;
	ofstream file;
	file.open(filename);
	string content = "P3\n" + to_string(dimensions[0]) + " " + to_string(dimensions[1]) + "\n255\n";

	
	for (i = 0; i < dimensions[1]; i++) {
		for (j = 0; j < dimensions[0]; j++) {
			content += to_string(pixels[i][j][0]) + "\t\t" + to_string(pixels[i][j][1]) + "\t\t" + to_string(pixels[i][j][2]) + "\t\t";
		}
		content += "\n";
	}

	file << content;
	file.close();

}

/*int main()
{
	vector<int> dimensions = { 3,2 };
	vector<vector<vector<int>>> pixels = { {{255,0,0},{0,255,0},{0,0,255}},
										{{255,255,0},{255,255,255},{0,0,0}} };
	const char* filename = "image.ppm";

	createPPMImage(dimensions, pixels, filename);

}*/

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
