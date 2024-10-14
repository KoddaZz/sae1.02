/*
Authors : GHEUX Théo
             FABRE Alexis
             FUSELIER Jules
             ACEMYAN DE OLIVEIRA Ewan
             UYSUN Ali
*/

// Importation des blibliothèques nécessaires

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Mise en place du dictionnaire répertoriant les candidats
    map<string, int> candidats;
    candidats["John"] = 0;
    candidats["Brom"] = 0;
    candidats["Sam"] = 0;
    candidats["Sofia"] = 0;

    unsigned nombreDeVotants;
    unsigned Compteur = 0;
    unsigned nombreDeVoteBlanc = 0;
    string saisiNomCandidat = " ";
    string saisiNomDuVotant = " ";
    cout << "Entrez le nombre de votants participants : ";
    cin >> nombreDeVotants;
    while (Compteur < nombreDeVotants) {
        cout << "Qui êtes vous ? ";
        cin >> saisiNomDuVotant;
        cout << "Bonjour, " << saisiNomDuVotant << " ! " << endl << "Voici la liste des candidats est : " << endl << "1. John" << endl << "2. Brom" << endl << "3. Sam" << endl << "4. Sofia" << endl;
        cout << "Entez le nom du candidat : ";
        cin >> saisiNomCandidat;
        cout << endl;
        Compteur++;
        if (candidats.find(saisiNomCandidat) != candidats.end()) {
            candidats[saisiNomCandidat] += 1;
        }
        else {
            nombreDeVoteBlanc++;
        }
    }

    // Convertir la map en un tableau de paires afin d'établir le podium

    // PENSE BETE : candidats.begin -> pointeur qui représente le début
    //              candidats.end ->   pointeur qui représente la fin

    vector<pair<string, int>> liste_candidats(candidats.begin(), candidats.end());

    // Trier les candidats par nombre de votes (ordre décroissant)
    sort(liste_candidats.begin(), liste_candidats.end(), [](pair<string, int> a, pair<string, int> b) {
        return a.second > b.second;
    });

    // Afficher le podium
    cout << "Podium des candidats : " << endl;
    for (unsigned int i = 0; i < 3 && i < liste_candidats.size(); i++) {
        cout << i+1 << ". " << liste_candidats[i].first << " avec " << liste_candidats[i].second << " vote(s)." << endl;
    }
    cout << "Nombre de votes blancs : " << nombreDeVoteBlanc << endl;

    return 0;
}
