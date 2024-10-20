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
using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0))); // Correction pour adapter à type sécurisé
    // Mise en place du dictionnaire répertoriant les candidats
    vector<string> prenoms = {
        "James", "Emily", "Michael", "Sarah", "William", "Jessica", "Robert", "Ashley", "John", "Jennifer",
        "David", "Amanda", "Richard", "Brittany", "Joseph", "Samantha", "Charles", "Lauren", "Thomas", "Megan",
        "Christopher", "Hannah", "Daniel", "Victoria", "Matthew", "Kayla", "Anthony", "Alexis", "Donald", "Rachel",
        "Mark", "Madison", "Paul", "Natalie", "Steven", "Alyssa", "Andrew", "Grace", "Joshua", "Olivia",
        "Brian", "Sophia", "Kevin", "Chloe", "George", "Isabella", "Edward", "Emma", "Ronald", "Ava",
        "Timothy", "Mia", "Kenneth", "Abigail", "Jason", "Emily", "Eric", "Ella", "Jeffrey", "Madeline",
        "Ryan", "Addison", "Jacob", "Hailey", "Nicholas", "Charlotte", "Stephen", "Harper", "Frank", "Lily",
        "Patrick", "Brooklyn", "Scott", "Layla", "Justin", "Zoe", "Larry", "Penelope", "Brandon", "Scarlett",
        "Benjamin", "Stella", "Samuel", "Nora", "Gregory", "Eleanor", "Alexander", "Violet", "Henry", "Ellie",
        "Jonathan", "Sophie", "Ethan", "Mila", "Jack", "Aria", "Peter", "Lillian", "Aaron", "Avery",
        "Adam", "Audrey", "Sean", "Savannah", "Austin", "Lucy", "Kyle", "Paisley", "Jesse", "Evelyn",
        "Raymond", "Bella", "Philip", "Hazel", "Carl", "Claire", "Arthur", "Skylar", "Dennis", "Caroline",
        "Walter", "Anna", "Jerry", "Samantha", "Bruce", "Autumn", "Lawrence", "Kennedy", "Wayne", "Madelyn",
        "Alan", "Ariana", "Roger", "Elliana", "Terry", "Genesis", "Harold", "Gianna", "Gerald", "Serenity",
        "Henry", "Ruby", "Louis", "Cora", "Joe", "Emilia", "Howard", "Peyton", "Billy", "Rylee"
    };


    cout << "Bienvenue sur une simulation d'un vote !" << endl;
    unsigned nombreDeVotants = 0; // Initialisation de nombreDeVotants
    unsigned Compteur = 0;
    unsigned nombreRegion = 0;
    unsigned nombreDeleguesRegion = 0;
    unsigned nombreCandidatsNationaux;
    unsigned nomAuHasard = 0;
    string saisiNomCandidat = " ";
    cout << "Combien d'Etats / region voulez vous simuler ? ";
    cin >> nombreRegion;
    cout << "Combien de candidat Delegues voulez vous par région ? ";
    cin >> nombreDeleguesRegion;
    unsigned compteur2 = 0;
    unsigned nombreVoteBlancNational;

    map<int, string> dicoDeleguesParRegions;

    map<int,int> nombreVotesBlancParRegions;

    for (unsigned i = 0; i < nombreRegion; i++) {
        Compteur = 0;
        map<int,int> nombreVotantsRegionaux;
        nombreDeVotants = rand()%15;
        nombreVotantsRegionaux[i] = nombreDeVotants;

        map<int, map<string, int>> candidatsEtats;
        // Générer les délégués de manière unique
        for (unsigned j = 0; j < nombreDeleguesRegion; j++) {
            nomAuHasard = rand() % prenoms.size();
            auto prenom = prenoms[nomAuHasard];
            if (candidatsEtats[i].find(prenom) == candidatsEtats[i].end()) {
                candidatsEtats[i][prenom] = 0;
            }
        }
        while (Compteur < nombreVotantsRegionaux[i]) {
            cout << "La liste des candidats est : " << endl;
            for (const auto& votant : candidatsEtats) {
                int idx = 1;  // Correction d'affichage manquée.
                for (const auto& pair : votant.second) {
                    cout << idx << ". " << pair.first << endl;
                    idx++;
                }
            }
            cout << "Entrez le nom du candidat : ";
            cin >> saisiNomCandidat;
            cout << endl;
            Compteur++;
            if (candidatsEtats[i].find(saisiNomCandidat) != candidatsEtats[i].end()) {
                candidatsEtats[i][saisiNomCandidat] += 1;
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

    map<string, int> candidatsNationaux;
    // Générer les délégués de manière unique
    for (unsigned j = 0; j < nombreCandidatsNationaux; j++) {
        nomAuHasard = rand() % prenoms.size();
        auto prenom = prenoms[nomAuHasard];
        if (candidatsNationaux.find(prenom) == candidatsNationaux.end()) {
            candidatsNationaux[prenom] = 0;
        }
    }

    cout << " " << endl << " ===================== [ NATIONAL ] ===================== " << endl << "      VOTE CANDIDAT NATIONAL     " << endl << " ===================== [ NATIONAL ] ===================== " << endl << " " << endl;

    while (compteur2 < nombreRegion) {
        // ANNONCE DES CANDIDATS NATIONAUX

        cout << "La liste des candidats est : " << endl;
        for (const auto& votant : candidatsNationaux) {
            int idx = 1;  // Correction d'affichage manquée.
            for (const auto& pair : votant.second) {
                cout << idx << ". " << pair.first << endl;
                idx++;
            }
        }
        cout << "Entrez le nom du candidat : ";
        cin >> saisiNomCandidat;
        cout << endl;
        compteur2++;

        if (candidatsNationaux.find(saisiNomCandidat) != candidatsNationaux.end()) {
            candidatsNationaux[saisiNomCandidat] += 1;
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