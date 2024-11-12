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


// FONCTION : Servant à gérer la saisie du nombre de candidat
int saisieNombreDeCandidats() {

    unsigned int nombreDeCandidats = 0;

    nombreDeCandidats = litUnEntier();

    return nombreDeCandidats;
}


//PROCEDURE : servant à repertorier dans une map un nombre donné de candidats et initialiser leur nombre de voix à 0
void repertoireCandidats(map<string , int> & repertoireCandidats, unsigned int nbrCandidats){

    string saisieNomCandidat;

    for (unsigned int candidat = 0; candidat < nbrCandidats; ++candidat) {

        saisieNomCandidat = litUneString();

        repertoireCandidats[saisieNomCandidat] = 0;

    }

}

// FONCTION : servant à gérer la saisie des votes des votants
string saisieVoteDuVotant() {
    string saisieVote = "";

    saisieVote = litUneString();

    return saisieVote;
}


// PROCEDURE : Sert à vérifier si le nom du candidat existe, si non cela sera considéré comme un vote blanc ou vote valide
void DepouillageVote(string NomCandidat, map<string, int>& NomCandidatMap) {
    if (NomCandidatMap.find(NomCandidat) != NomCandidatMap.end()) {
        ++NomCandidatMap[NomCandidat];
    } else {
        ++NombreVotesBlanc;
    }
}

// PROCEDURE : servant à rechercher le gagnant selon la valeur de la clé de la map -> renvoie la clé de la valeur la plus grande.
void rechercheGagnant(map<string, int>& NomCandidatMap){

    string nomDuVainqueur; // -> clé de la valeur la plus grande
    int scoreMax = 0; // -> valeur la plus grande

    for (const pair<string,int> & pair : NomCandidatMap) { // parcourt toutes les paires de clés et valeurs d'une map
        if (pair.second > scoreMax) {
            scoreMax = pair.second;
            nomDuVainqueur = pair.first;
        }
    }

    cout << "Le Vainqueur de cette élection est : " << nomDuVainqueur << endl;
    cout << " " << endl;
    cout << " Cette élection s'est terminée avec " << NombreVotesBlanc << " vote(s) blanc(s) ! " << endl;
    cout << " " << endl;

}



int main() {

    int compteurDelegues = 0;
    int nombreDeVotantsRegional = 0;

    nombreDeRegions = litUnEntier();

    // Boucle servant à la session des votes régionaux ( toutes les régions ) -> "i" fait que on fait une région par une région. Chaque itération -> nouvelle région -> nouvelle session de vote
    for (unsigned i = 0; i < nombreDeRegions; ++i) {
        NombreVotesBlanc = 0; // Réinitialisation des votes blancs pour une nouvelle session de vote

        nombreDeVotantsRegional = litUnEntier();

        unsigned int nombreDeCandidatsVoteRegional = saisieNombreDeCandidats();
        repertoireCandidats(DeleguesRegion[i], nombreDeCandidatsVoteRegional);

        while (compteurDelegues < nombreDeVotantsRegional) { // Début des votes et du dépouillage des votes ( en arrière plan )

            string SaisieVote = saisieVoteDuVotant();
            DepouillageVote(SaisieVote, DeleguesRegion[i]);

            ++compteurDelegues;
        }

        compteurDelegues = 0;
        rechercheGagnant(DeleguesRegion[i]); // renvoie le vainqueur de l'élection de la région "i"

    }

    NombreVotesBlanc = 0; // Réinitialisation des votes blancs pour une nouvelle session de vote

    map<string, int> candidatsNationaux;

    // Début de l'élection nationale
    unsigned int nombreDeCandidatsVoteNational = saisieNombreDeCandidats();
    repertoireCandidats(candidatsNationaux, nombreDeCandidatsVoteNational);

    unsigned int compteurNational = 0;

    while (compteurNational < nombreDeRegions) { // Début des votes et du dépouillage des votes ( en arrière plan )

        string SaisieVote = saisieVoteDuVotant();
        DepouillageVote(SaisieVote, candidatsNationaux);

        ++compteurNational;

    }

    rechercheGagnant(candidatsNationaux); // renvoie le vainqueur l'élection nationale

}
