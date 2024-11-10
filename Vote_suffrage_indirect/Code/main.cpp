/*
Authors : GHEUX Théo
          FABRE Alexis
          FUSELIER Jules
          ACEMYAN DE OLIVEIRA Ewan
          UYSUN Ali
*/
// Importation des bibliothèques nécessaires
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>  // afin d'utiliser quoted()
using namespace std;

int main() {
    unsigned nombreDeVotants = 0; // Initialisation de nombreDeVotants
    unsigned compteur = 0; // -> boucle while pour les candidats régionaux
    unsigned nombreRegion = 0; // nombre de regions au total dans la simulation de vote
    unsigned nombreDeleguesRegion = 0; // Nombre de candidats delegues ( à définir spécialement pour chaque région )
    unsigned nombreCandidatsNationaux; // Nombre de candidats qui se présentent à la nationale
    string enregistrementNomCandidat = " "; // => servira pour enregistrer les noms des candidats à chaque fois ( delegues / national )
    string saisieNomCandidatVote = " "; // Ce que le vote va rentrer ( Pour qui il va voter )
    cout << "Combien de region(s) voulez vous simuler ( Le nombre ( entier ) de regions dans leqsquelles vous voulez simuler un vote ) ? ";
    cin >> nombreRegion;
    unsigned compteur2 = 0;
    unsigned nombreVoteBlancNational = 0;

    map<int, string> dicoDeleguesParRegions;

    map<int,int> nombreVotesBlancParRegions;

    for (unsigned i = 0; i < nombreRegion; ++i) {
        compteur = 0;
        map<int,int> nombreVotantsRegionaux;
        cout << "Entrez le nombre de votants :";
        cin >> nombreDeVotants; // Entrée d'un entier
        nombreVotantsRegionaux[i] = nombreDeVotants;

        map<int, map<string, int>> DeleguesRegion;

        cout << "Combien de candidat Delegues voulez vous dans la region numero " << i << " : ";
        cin >> nombreDeleguesRegion; // Saisie du nombre (entier) de Délégués
        for (unsigned j = 0; j < nombreDeleguesRegion; ++j) {
            cout << "Enregistrez les noms des candidats afin de debuter le vote des regionaux : ";
            cin >> quoted(enregistrementNomCandidat);
            DeleguesRegion[i][enregistrementNomCandidat] = 0;
        }
        while (compteur < nombreVotantsRegionaux[i]) {


            // //getline(cin, var);
            cout << "Entrez le nom du candidat : ";
            cin >> quoted(saisieNomCandidatVote);
            cout << endl;
            ++compteur;
            if (DeleguesRegion[i].find(saisieNomCandidatVote) != DeleguesRegion[i].end()) {
                ++DeleguesRegion[i][saisieNomCandidatVote ];
            }
            else {
                ++nombreVotesBlancParRegions[i];
            }
        }
// AFFICHAGE à MODIFIER D'EMPLACEMENT
    }

    cout << "Combien il y a de candidats Nationaux ? " << endl;
    cin >> nombreCandidatsNationaux; // Saisir un entier
    map<string, int> candidatsNationaux = map<string, int>();

    for (unsigned j = 0; j < nombreCandidatsNationaux; ++j) {
        cout << "Enregistrez les noms des candidats afin de débuter le vote des nationaux : " << endl;
        cin >> quoted(enregistrementNomCandidat);
        candidatsNationaux[enregistrementNomCandidat] = 0; // Initialise son nombre de voix à 0
    }


    while (compteur2 < nombreRegion) {
        cout << "Entrez le nom du candidat : ";
        cin >> quoted(saisieNomCandidatVote);
        cout << endl;
        ++compteur2;

        if (candidatsNationaux.find(saisieNomCandidatVote) != candidatsNationaux.end()) {
            candidatsNationaux[saisieNomCandidatVote] += 1;
        } else {
            ++nombreVoteBlancNational;
        }
    }


    return 0;
}

// CREATION DICO => Resultat des votes FAIT
// PATCH ERREUR => Nombre de votes blancs s'accumule pour des régions diff ! FAIT
// IMPORTANT : OPTIMISER LE CODE EN LE TRANSFORMANT AVEC DES PROCEDURES
