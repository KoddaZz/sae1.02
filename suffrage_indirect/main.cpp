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
#include <algorithm>
using namespace std;

map<int, map<string, int>> DeleguesRegion;

int NombreVotesBlanc = 0;
unsigned int nombreDeRegions = 0;
int compteurDelegues = 0;

// Initialisation des map des Candidats Regionaux / Nationaux

string litUneString (){
    string uneChaine;
    while (true){
        getline (cin, uneChaine);
        if ((!cin) || (uneChaine.substr(0,2) != "//") || uneChaine.size() == 0) break;
    }
    return uneChaine;
}

int litUnEntier (){
    string uneChaine;
    while (true){
        getline (cin, uneChaine);
        if ((!cin) || (uneChaine.substr(0,2) != "//") || uneChaine.size() == 0) break;
    }
    // cout << "La chaine: " << uneChaine << endl; // DEBUG
    return stoi(uneChaine);
}

int saisieNombreDeCandidats() {

    unsigned int nombreDeCandidats = 0;

    nombreDeCandidats = litUnEntier();

    return nombreDeCandidats;
}

void repertoireCandidats(map<string , int> & repertoireCandidats, unsigned int nbrCandidats){

    string saisieNomCandidat;

    for (unsigned int candidat = 0; candidat < nbrCandidats; ++candidat) {

        saisieNomCandidat = litUneString();

        repertoireCandidats[saisieNomCandidat] = 0;

    }

}


string saisieVoteDuVotant() {
    string saisieVote = "";

    saisieVote = litUneString();

    return saisieVote;
}


// FONCTION : Sert à vérifier si le nom du candidat existe, si non cela sera considéré comme un vote blanc
void DepouillageVote(string NomCandidat, map<string, int>& NomCandidatMap) {
    if (NomCandidatMap.find(NomCandidat) != NomCandidatMap.end()) {
        ++NomCandidatMap[NomCandidat];
    } else {
        ++NombreVotesBlanc;
    }
}

void rechercheGagnant(map<string, int>& NomCandidatMap){

    string nomDuVainqueur;
    int scoreMax = 0;

    for (const auto & pair : NomCandidatMap) {
        if (pair.second > scoreMax) {
            scoreMax = pair.second;
            nomDuVainqueur = pair.first;
        }
    }

    cout << "Le Vainqueur de cette élection est : " << nomDuVainqueur << endl;

}



int main() {

    int compteurDelegues = 0;
    int nombreDeVotantsRegional = 0;

    nombreDeRegions = litUnEntier();

    for (unsigned i = 0; i < nombreDeRegions; ++i) {

        nombreDeVotantsRegional = litUnEntier();

        unsigned int nombreDeCandidatsVoteRegional = saisieNombreDeCandidats();
        repertoireCandidats(DeleguesRegion[i], nombreDeCandidatsVoteRegional);

        while (compteurDelegues < nombreDeVotantsRegional) {

            string SaisieVote = saisieVoteDuVotant();
            DepouillageVote(SaisieVote, DeleguesRegion[i]);

            ++compteurDelegues;
        }

        compteurDelegues = 0;
        rechercheGagnant(DeleguesRegion[i]);

    }

    map<string, int> candidatsNationaux;

    unsigned int nombreDeCandidatsVoteNational = saisieNombreDeCandidats();
    repertoireCandidats(candidatsNationaux, nombreDeCandidatsVoteNational);

    unsigned int compteurNational = 0;

    while (compteurNational < nombreDeRegions) {

        string SaisieVote = saisieVoteDuVotant();
        DepouillageVote(SaisieVote, candidatsNationaux);

        ++compteurNational;

    }

    rechercheGagnant(candidatsNationaux);

}
