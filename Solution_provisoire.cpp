#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>
using namespace std;

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

// Fonction d'entrée des candidats
vector<string> entrerCandidats() {
    vector<string> candidats;
    unsigned numCandidats;
    cout << "Entrez le nombre de candidats: ";
    cin >> numCandidats;
    candidats.resize(numCandidats);
    for (unsigned i = 0; i < numCandidats; ++i) {
        cout << "Candidat " << i + 1 << ": ";
        cin >> candidats[i];
    }
    return candidats;
}

// Fonction d'entrée des votes
vector<vector<int>> entrerVotes(const vector<string>& candidats) {
    unsigned numCandidats = candidats.size();
    vector<vector<int>> votes;
    unsigned votant;
    cout << "Veuillez saisir le nombre de votants: ";
    cin >> votant;
    votes.resize(votant, vector<int>(numCandidats));
    cout << "Entrez les votes (par exemple 1 2 3 pour préférer le candidat 1 puis le 2 puis le 3 dans un vote à trois candidats)" << endl;
    for (unsigned i = 0; i < votant; ++i) {
        cout << "Vote " << i + 1 << ": ";
        for (unsigned j = 0; j < numCandidats; ++j) {
            int preference;
            cin >> preference;
            votes[i][j] = preference - 1;
        }
    }
    return votes;
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
    vector<string> candidat = entrerCandidats();
    vector<vector<int>> votes = entrerVotes(candidat);
    afficherVotes(candidat, votes);

    // Nombre total de votes
    int numVotes = votes.size();

    // Initialiser le vecteur compte pour stocker les votes
    vector<int> compte(candidat.size(), 0);
    vector<bool> elimines(candidat.size(), false);

    // Boucle tant qu'il n'y a pas de majorité absolue
    while (true) {
        // Décompte initial ou après chaque élimination
        decompte(votes, compte);

        // Afficher les résultats des comptes pour chaque candidat
        cout << "Les premiers votes sont : " << endl;
        for (unsigned i = 0; i < candidat.size(); ++i) {
            if (!elimines[i]) {
                cout << candidat[i] << " a obtenu " << compte[i] << " premier(s) vote(s)." << endl;
            }
        }

        if (majorite(compte, numVotes)) {
            break;
        }

        // Trouver le dernier candidat et l'éliminer
        int candidatElimine = trouverDernier(compte, elimines);
        cout << "Le candidat " << candidat[candidatElimine] << " est éliminé." << endl;
        elimines[candidatElimine] = true;
        eliminerCandidat(votes, candidatElimine);
    }

    for (unsigned i = 0; i < compte.size(); ++i) {
        if (compte[i] > numVotes / 2) {
            cout << "Le gagnant est " << candidat[i] << " avec " << compte[i] << " votes." << endl;
            break;
        }
    }

    return 0;
}
