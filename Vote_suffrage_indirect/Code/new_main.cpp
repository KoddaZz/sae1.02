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
#include <cstdlib>
#include <ctime>

using namespace std;

map<int, map<string, int>> DeleguesRegion;

int NombreVotesBlanc = 0;

// Initialisation des map des Candidats Regionaux / Nationaux
void initialiserCandidats(map<string, int> repertoireCandidats) {

    int nombreDeCandidats = 0;
    string saisieNomCandidat;

    cout << "Combien de candidats y a t-il ? ";
    cin >> nombreDeCandidats;

    cin.ignore();

    for (unsigned int candidat = 0; candidat < nombreDeCandidats; ++candidat) {

        cout << "Initalisez le nom du candidat : ";
        getline(cin, saisieNomCandidat);

        repertoireCandidats[saisieNomCandidat] = 0;

    }

}


string saisieVoteDuVotant() {
    string saisieVote = "";

    cout << "Pour quel candidat souhaitez-vous voter ? ";
    getline(cin, saisieVote);

    return saisieVote;  /
}

// FONCTION : Sert à vérifier si le nom du candidat existe, si non cela sera considéré comme un vote blanc
void VerificationVoteBlanc(string NomCandidat, map<string, int>& NomCandidatMap) {
    if (NomCandidatMap.find(NomCandidat) != NomCandidatMap.end()) {
        ++NomCandidatMap[NomCandidat];
    } else {
        ++NombreVotesBlanc;
    }
}

int main() {
    initialiserCandidats(DeleguesRegion[1]);

    string SaisieVote = saisieVoteDuVotant();  /
    VerificationVoteBlanc(SaisieVote, DeleguesRegion[1]);

    cout << "Nombre de votes blancs : " << NombreVotesBlanc << endl;

    return 0;
}
