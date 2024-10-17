//
// Created by jules on 17/10/2024.
//

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
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));
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




    map<string, int> candidatsNationaux;
    candidatsNationaux["Trump"] = 0;
    candidatsNationaux["Bieden"] = 0;
    candidatsNationaux["Clinton"] = 0;

    cout << "Bienvenue sur une simulation d'un vote !" << endl;

    unsigned nombreDeVotants;
    unsigned Compteur = 0;
    unsigned nombreDeVoteBlanc = 0;
    unsigned nombreRegion = 0;
    unsigned nombreDeleguesRegion = 0;
    unsigned nomAuHasard = 0;
    string saisiNomCandidat = " ";
<<<<<<< HEAD
    cout << "Combien d'Etats / region voulez vous simuler ? ";
    cin >> nombreRegion;
    cout << "Combien de Délégués voulez vous par région ? ";
    cin >> nombreDeleguesRegion;
=======
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
>>>>>>> 2a9c074e3ae60fd89e5a652997fdb178994940f4

    unsigned compteur2 = 0;

    for (unsigned i = 0; i < nombreRegion; i++) {
        Compteur = 0;
        map<int, map<string, int> > candidatsEtats;

        for (unsigned j = 0; j < nombreDeleguesRegion; j++) {
            nomAuHasard = rand()%prenoms.size();
            candidatsEtats[i][prenoms[nomAuHasard]] = 0;
        }

        while (Compteur < nombreDeVotants) {
            cout << "La liste des candidats est : " << endl;
                for (const auto& votant : candidatsEtats) {
                    for (const auto& pair : votant.second) {
                        cout <<  << ". " << pair.first << endl;
                    }
                }
            }
            cout << "Entrez le nom du candidat : ";
            cin >> saisiNomCandidat;
            cout << endl;
            Compteur++;
            if (candidatsEtats[i].find(saisiNomCandidat) != candidatsEtats[i].end()) {
                candidatsEtats[i][saisiNomCandidat] += 1;
            }
            else {
                nombreDeVoteBlanc++;
            }
        }

        vector<pair<string, int>> liste_candidats(candidatsEtats[i].begin(), candidatsEtats[i].end());

        // Trier les candidats par nombre de votes (ordre décroissant)
        sort(liste_candidats.begin(), liste_candidats.end(), [](pair<string, int> a, pair<string, int> b) {
            return a.second > b.second;
        });

        cout << "Podium des candidats : " << endl;
        for (unsigned int k = 0; k < 3 && k < liste_candidats.size(); k++) {
            cout << k+1 << ". " << liste_candidats[k].first << " avec " << liste_candidats[k].second << " vote(s)." << endl;
        }
        cout << "Nombre de votes blancs : " << nombreDeVoteBlanc << endl;

    }
    return 0;
}
/*
    // Convertir la map en un tableau de paires afin d'établir le podium

    // PENSE BETE : candidats.begin -> pointeur qui représente le début
    //              candidats.end ->   pointeur qui représente la fin

    vector<pair<string, int>> liste_candidats(candidatsEtats.begin(), candidatsEtats.end());

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
<<<<<<< HEAD
*/
=======
>>>>>>> 2a9c074e3ae60fd89e5a652997fdb178994940f4
