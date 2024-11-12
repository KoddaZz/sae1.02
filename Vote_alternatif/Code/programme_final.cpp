#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>
using namespace std;

void lireFichierEntree(vector<string>& glaces, vector<vector<int>>& votes) {
    string ligne;
    bool lectureGlaces = false;
    bool lectureVotes = false;
    string input;

    while(true){
        getline(cin,input);
        if(input.substr(0,3)=="fin"){
            break;
        }

        if (input.substr(2, 16) == "liste des glaces") {
            lectureGlaces = true;
            lectureVotes = false;
            continue;
        }
        if (input.substr(2, 26) == "voila la liste des joueurs")
        {
            lectureGlaces = false;
            lectureVotes = true;
            continue;
        }
        if(input.substr(0,2)=="//"){
            continue;
        }
        if (lectureGlaces==true) {
            glaces.push_back(input);
        }
        else if (lectureVotes==true){
            vector<int> preferences;
            for (size_t i = 0; i < input.size(); ++i) {
                if (isdigit(input[i])) {
                    int preference = input[i] - '0'; // Convertit le caractère en entier grâce au code ASCII
                    preferences.push_back(preference-1); // Ajuste pour un index de vecteur basé sur zéroccccccccc
                }
            }
            votes.push_back(preferences);
        }
    }
}


// Fonction pour compter les premières préférences
void decompte(const vector<vector<int>>& votes, vector<int>& compte) {
    // Réinitialiser le vecteur de compteurs pour chaque candidat
    fill(compte.begin(), compte.end(), 0);

    // Parcourir le vecteur votes et compter les premières préférences
    for (const auto& vote : votes) {
        if (!vote.empty()) {
            int premierVote = vote[0];
            compte[premierVote]++;
        }
    }
}


// Procédure pour afficher les votes et candidats
void afficherVotes(const vector<string>& candidats, const vector<vector<int>>& votes) {
    cout << "Liste des candidats :" << endl;
    for (unsigned i = 0; i < candidats.size(); ++i) {
        cout << i + 1 << ": " << candidats[i] << "\n";
    }

    cout << "Liste des votes :" << endl;
    for (unsigned i = 0; i < votes.size(); ++i) {
        cout << "Vote " << i + 1 << ": ";
        for (unsigned j = 0; j < votes[i].size(); ++j) {
            cout << votes[i][j] + 1 << " ";
        }
        cout << "\n";
    }
}


// Fonction pour vérifier si un candidat a une majorité absolue
bool majorite(const vector<int>& compte, const int& numVotes) {
    for (unsigned i = 0; i < compte.size(); ++i) {
        if (compte[i] > numVotes / 2) {
            return true;
        }
    }
    return false;
}

// Fonction pour trouver le candidat avec le moins de votes
int trouverDernier(const vector<int>& compte, const vector<bool>& elimines) {
    int minVotes = INT_MAX;
    int dernier = -1;
    for (unsigned i = 0; i < compte.size(); ++i) {
        if (!elimines[i] && compte[i] < minVotes) {
            minVotes = compte[i];
            dernier = i;
        }
    }
    return dernier;
}

// Procédure pour éliminer le candidat avec le moins de votes
void eliminerCandidat(vector<vector<int>>& votes, int candidatElimine) {
    for (auto& vote : votes) {
        vote.erase(remove(vote.begin(), vote.end(), candidatElimine), vote.end());
    }
}


int main() {
    cout << "testttt";
    vector<string> glaces;
    vector<vector<int>> votes;
    lireFichierEntree(glaces, votes);

    // Nombre total de votes
    int numVotes = votes.size();

    // Initialiser le vecteur compte pour stocker les votes
    vector<int> compte(glaces.size(), 0);
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
