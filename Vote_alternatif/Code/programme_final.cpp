#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>
using namespace std;
//procédure afin de lire depuis les fichiers d'entrées
void lireFichierEntree(vector<string>& glaces, vector<vector<int>>& votes) {
    //Création de booléen qui servent de référence sur la ligne lue
    bool lectureGlaces = false;
    bool lectureVotes = false;
    string input;
    //Boucle pour parcours tout le fichier
    while(true){
        //Lecture de la ligne suivante
        getline(cin,input);
        //Si la ligne vaut fin alors laboucle s'arrête
        if(input.substr(0,3)=="fin"){
            break;
        }
        //Si la ligne vaut liste des glaces on sait que les noms de glaces vont suivre donc on met lectureGlaces à vrai
        if (input.substr(2, 16) == "liste des glaces") {
            lectureGlaces = true;
            lectureVotes = false;
            continue;
        }
        //Si la ligne vaut voila la liste des joueurs on sait que les votes vont suivre donc on met lectureVotes à vrai
        if (input.substr(2, 26) == "voila la liste des joueurs")
        {
            lectureGlaces = false;
            lectureVotes = true;
            continue;
        }
        //Ignorer les commentaires
        if(input.substr(0,2)=="//"){
            continue;
        }
        //Si lectureGlaces vaut vrai on met le nom de la glace dans un tableau glaces
        if (lectureGlaces==true) {
            glaces.push_back(input);
        }
        //Si lectureVotes vaut vrai on met les votes dans le tableau votes
        else if (lectureVotes==true){
            //Preférences servira d'intermédiaire
            vector<int> preferences;
            //Boucle afin de prendre chaque chiffre de ma ligne
            for (size_t i = 0; i < input.size(); ++i) {
                if (isdigit(input[i])) {
                    // convertion du caractère en entier grâce au code ASCII
                    int preference = input[i] - '0'; 
                    //On ajuste pour que l'inice du vecteur soit basé sur 0
                    preferences.push_back(preference-1); 
                }
            }
            //On met notre tableau préférences dans votes
            votes.push_back(preferences);
        }
    }
}


// Fonction pour compter les premières préférences
void decompte(const vector<vector<int>>& votes, vector<int>& compte) {
    // Réinitialiser le vecteur de compteurs pour chaque candidat
    fill(compte.begin(), compte.end(), 0);

    // Parcourir le vecteur votes et compter les premières préférences
    for (size_t i=0; i<votes.size();++i) {
        if (!votes[i].empty()) {
            int premierVote = votes[i][0];
            //Incrémentation du compteur premierVote
            compte[premierVote]++;
        }
    }
}


// Fonction pour vérifier si un candidat a une majorité absolue
bool majorite(const vector<int>& compte, const int& numVotes) {
    for (unsigned i = 0; i < compte.size(); ++i) {
        //Si le nombre de premiers votes d'un candidat est supérieur à la moitié des électerus on renvoie vrai
        if (compte[i] > numVotes / 2) {
            return true;
        }
    }
    //Sinon on renvoie faux
    return false;
}

// Fonction pour trouver le candidat avec le moins de votes
int trouverDernier(const vector<int>& compte, const vector<bool>& elimines) {
    //Variable qui sert de minimum on l'initialise avec la valeur maximum qui ne fera que baisser
    int minVotes = INT_MAX;
    //Variable d'indice du dernier candidat
    int dernier = -1;
    for (unsigned i = 0; i < compte.size(); ++i) {
        //On vérifie que le dernier candidat n'est pas déjà éliminé et que ses votes sont plus petits que notre minimum
        if (!elimines[i] && compte[i] < minVotes) {
            minVotes = compte[i];
            dernier = i;
        }
    }
    return dernier;
}

// Procédure pour éliminer le candidat avec le moins de votes
void eliminerCandidat(vector<vector<int>>& votes, int candidatElimine) {
    for (size_t i = 0; i < votes.size(); ++i) {
        //On enlève de notre tableau vote le candidat éliminé
        votes[i].erase(remove(votes[i].begin(), votes[i].end(), candidatElimine), votes[i].end());
    }
}


int main() {
    //Création des tableaux glaces et votes utilisé dans la fonction lireFichierEntree
    vector<string> glaces;
    vector<vector<int>> votes;
    lireFichierEntree(glaces, votes);

    // Nombre total de votes
    int numVotes = votes.size();

    // Création du tableau compte pour stocker les votes
    vector<int> compte(glaces.size(), 0);
    //Création d'un tableau elimines qui contient quel candidat est éliminé
    vector<bool> elimines(glaces.size(), false);

    // Boucle tant qu'il n'y a pas de majorité absolue
    while (true) {
        // Décompte initial ou après chaque élimination
        decompte(votes, compte);
        if (majorite(compte, numVotes)) {
            break;
        }

        // Trouver le dernier candidat et l'éliminer
        int candidatElimine = trouverDernier(compte, elimines);
        cout << "Le candidat " << glaces[candidatElimine] << " est éliminé." << endl;
        elimines[candidatElimine] = true;
        eliminerCandidat(votes, candidatElimine);
    }

    for (unsigned i = 0; i < compte.size(); ++i) {
        if (compte[i] > numVotes / 2) {
            cout << "Le gagnant est " << glaces[i] << " avec " << compte[i] << " votes." << endl;
            break;
        }
    }

    return 0;
}
