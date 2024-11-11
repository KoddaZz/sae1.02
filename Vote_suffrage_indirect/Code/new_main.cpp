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
int nombreDeRegions = 0;
int compteurDelegues = 0;

// Initialisation des map des Candidats Regionaux / Nationaux
int saisieNombreDeCandidats() {

    int nombreDeCandidats = 0;

    cout << "Combien de candidats y a t-il ? ";
    cin >> nombreDeCandidats;

    cin.ignore();

    return nombreDeCandidats;
}

void repertoireCandidats(map<string , int> & repertoireCandidats, int nbrCandidats){

    string saisieNomCandidat;

    for (unsigned int candidat = 0; candidat < nbrCandidats; ++candidat) {

        cout << "Initalisez le nom du candidat : ";
        getline(cin, saisieNomCandidat);

        repertoireCandidats[saisieNomCandidat] = 0;

    }

}


string saisieVoteDuVotant() {
    string saisieVote = "";

    cout << "Pour quel candidat souhaitez-vous voter ? ";
    getline(cin, saisieVote);

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

    cout << "Combien il y a t-il de région ? ";
    cin >> nombreDeRegions;

    cin.ignore();

    for (unsigned i = 0; i < nombreDeRegions; ++i) {

        cout << "Combien de votants y a t-il pour le vote régional ? ";
        cin >> nombreDeVotantsRegional;

        cin.ignore();

        int nombreDeCandidatsVoteRegional = saisieNombreDeCandidats();
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

    int nombreDeCandidatsVoteNational = saisieNombreDeCandidats();
    repertoireCandidats(candidatsNationaux, nombreDeCandidatsVoteNational);

    int compteurNational = 0;

    while (compteurNational < nombreDeRegions) {

        string SaisieVote = saisieVoteDuVotant();
        DepouillageVote(SaisieVote, candidatsNationaux);

        ++compteurNational;

    }

    rechercheGagnant(candidatsNationaux);

}