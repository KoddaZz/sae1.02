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
    srand(static_cast<unsigned int>(time(0)));
    // Mise en place du dictionnaire répertoriant les candidats


    cout << "Bienvenue sur une simulation d'un vote !" << endl;
    unsigned nombreDeVotants = 0; // Initialisation de nombreDeVotants
    unsigned compteur = 0;
    unsigned nombreRegion = 0;
    unsigned nombreDeleguesRegion = 0;
    unsigned nombreCandidatsNationaux;
    string enregistrementNomCandidat = " ";
    string saisiNomCandidatVote = " ";
    cout << "Combien d'Etats / region voulez vous simuler ? ";
    cin >> nombreRegion;
    cout << "Combien de candidat Delegues voulez vous par region ? ";
    cin >> nombreDeleguesRegion;
    unsigned compteur2 = 0;
    unsigned nombreVoteBlancNational;

    map<int, string> dicoDeleguesParRegions;

    map<int,int> nombreVotesBlancParRegions;

    for (unsigned i = 0; i < nombreRegion; i++) {
        compteur = 0;
        map<int,int> nombreVotantsRegionaux;
        cout << "Entrez le nombre de votants :";
        cin >> nombreDeVotants;
        nombreVotantsRegionaux[i] = nombreDeVotants;

        map<int, map<string, int>> candidatsEtats;
        // Générer les délégués de manière unique
        for (unsigned j = 0; j < nombreDeleguesRegion; j++) {
            // AJOUT D'UN MODE ADMIN ?
            // Si admin = True
            cout << "Enregistrez les noms des candidats afin de debuter le vote des regionaux : ";
            cin >> quoted(enregistrementNomCandidat);
            candidatsEtats[i][enregistrementNomCandidat] = 0;
        }
        while (compteur < nombreVotantsRegionaux[i]) {
            cout << "La liste des candidats est : " << endl;
            for (const auto& votant : candidatsEtats) {
                int idx = 1;  // Correction d'affichage manquée.
                for (const auto& pair : votant.second) {
                    cout << idx << ". " << pair.first << endl;
                    idx++;
                }
            }
            cout << "Entrez le nom du candidat : ";
            cin >> quoted(saisiNomCandidatVote);
            cout << endl;
            compteur++;
            if (candidatsEtats[i].find(saisiNomCandidatVote) != candidatsEtats[i].end()) {
                candidatsEtats[i][saisiNomCandidatVote ] += 1;
            } else {
                nombreVotesBlancParRegions[i]++;
            }
        }
        vector<pair<string, int>> liste_candidats(candidatsEtats[i].begin(), candidatsEtats[i].end());
        // Trier les candidats par nombre de votes (ordre décroissant)
        sort(liste_candidats.begin(), liste_candidats.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
        });
        cout << "Podium des candidats de la region " << i << " : " << endl;
        for (unsigned int k = 0; k < 3 && k < liste_candidats.size(); k++) {
            cout << k+1 << ". " << liste_candidats[k].first << " avec " << liste_candidats[k].second << " vote(s)." << endl;
        }
        cout << "Nombre de votes blancs : " << nombreVotesBlancParRegions[i] << endl << " " << endl << " ===================== [ REGIONAL ] ===================== " << endl << "      NOUVEAU VOTE / NOUVELLE REGION      " << endl << " ===================== [ REGIONAL ] ===================== " << endl << " " << endl;

        dicoDeleguesParRegions[i] = liste_candidats[0].first;
    }

    cout << "Combien il y a de candidats Nationaux ? " << endl;
    cin >> nombreCandidatsNationaux;
    map<string, int> candidatsNationaux = map<string, int>();

    for (unsigned j = 0; j < nombreCandidatsNationaux; j++) {
        // AJOUT D'UN MODE ADMINISTRATEUR ?
        // if admin = True ?
        cout << "Enregistrez les noms des candidats afin de débuter le vote des nationaux : " << endl;
        cin >> quoted(enregistrementNomCandidat);
        candidatsNationaux[enregistrementNomCandidat] = 0;
    }

    cout << " " << endl << " ===================== [ NATIONAL ] ===================== " << endl << "      VOTE CANDIDAT NATIONAL     " << endl << " ===================== [ NATIONAL ] ===================== " << endl << " " << endl;

    while (compteur2 < nombreRegion) {
        // ANNONCE DES CANDIDATS NATIONAUX

        cout << "La liste des candidats est : " << candidatsNationaux.size() << endl;
        for (const auto& votantNational : candidatsNationaux) {
            cout << "La liste des candidats est : " << votantNational.first << endl ;
        }
        cout << "Entrez le nom du candidat : ";
        cin >> quoted(saisiNomCandidatVote);
        cout << endl;
        compteur2++;

        if (candidatsNationaux.find(saisiNomCandidatVote) != candidatsNationaux.end()) {
            candidatsNationaux[saisiNomCandidatVote] += 1;
        } else {
            ++nombreCandidatsNationaux;
        }
    }
    vector<pair<string, int>> liste_candidats(candidatsNationaux.begin(), candidatsNationaux.end());

    sort(liste_candidats.begin(), liste_candidats.end(), [](pair<string, int> a, pair<string, int> b) {
        return a.second > b.second;
    });
    // Afficher le podium
    cout << "Podium des candidats : " << endl;
    for (unsigned int i = 0; i < 3 && i < liste_candidats.size(); i++) {
        cout << i+1 << ". " << liste_candidats[i].first << " avec " << liste_candidats[i].second << " vote(s)." << endl;
    }
    cout << "Nombre de votes blancs : " << nombreVoteBlancNational << endl;

    return 0;
}

// CREATION DICO => Resultat des votes FAIT
// PATCH ERREUR => Nombre de votes blancs s'accumule pour des régions diff ! FAIT
// IMPORTANT : OPTIMISER LE CODE EN LE TRANSFORMANT AVEC DES PROCEDURES