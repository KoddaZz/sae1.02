#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>
using namespace std;
// procédure de décompte des votes
void decompte(const vector<vector<int>>& votes, const vector<string>& candidats) {
    // Création un vecteur de compteurs pour chaque candidat
    vector<int> compte(candidats.size(), 0);

    // Parcourir le vecteur votes et compter les premières préférences
    for (unsigned i = 0; i < votes.size(); ++i) {
        int premierVote = votes[i][0];
        compte[premierVote]++;
    }

    // Afficher les résultats des comptes pour chaque candidat
    cout << "Les premiers votes sont : " << endl;
    for (unsigned i = 0; i < candidats.size(); ++i) {
        cout << candidats[i] << " a obtenu " << compte[i] << " premier(s) vote(s)." << endl;
    }
}
//Procédure afin d'afficher les votes et candidats
void afficherVotes(const vector<string>& candidats, const vector<vector<int>>& votes) {
    cout << "Liste des candidats :"<<endl;
    //Parcours du vecteur candidats et affichage de chaque candidats
    for (unsigned i = 0; i < candidats.size(); ++i) {
        cout << i + 1 << ": " << candidats[i] << "\n";
    }

    cout << "Liste des votes :"<<endl;
    //Parcours du vecteur de vecteur votes et affichage de chaque votes
    for (unsigned i = 0; i < votes.size(); ++i) {
        cout << "Vote " << i + 1 << ": ";
        for (unsigned j = 0; j < votes[i].size(); ++j) {
            cout << votes[i][j] + 1 << " ";
        }
        cout << "\n";
    }
}
//Fonction d'entrée des candidats
vector<string> candidats(){
    vector <string> candidats;
    unsigned numCandidats;
    //Entrée du nombre de candiats
    cout << "Entrez le nombre de candidats: ";
    cin >> numCandidats;
    candidats.resize(numCandidats);
    //Entrée de chaque candidats
    for (unsigned i=0;i<numCandidats;++i){
        cout << "Candidats " << i+1 <<": ";
        cin >> candidats[i];
    }
    return candidats;
}
//Fonction d'netrée des votes
vector<vector<int>> vote_alternatif_test(const vector<string>& candidats)
{
    unsigned numCandidats;
    numCandidats=candidats.size();
    //Création du vecteur de votes et entrée du nombre de votant
    vector <vector<int>> votes;
    unsigned votant;
    cout << "Veuillez saisir le nombre de votant: ";
    cin >> votant;
    votes.resize(votant, vector<int>(numCandidats));
    //Entrée des votes
    cout << "Entrez les votes (par exemple 1 2 3 pour preferer le candidat 1 puis le 2 puis le 3 dans un vote à trois candidats"<<endl;
    for (unsigned i=0;i<votant;++i)
    {
        cout << "Vote " << i+1<< ": ";
        for(unsigned j=0;j<numCandidats; ++j)
        {
            int preference;
            cin >> preference;
            votes[i][j]=preference-1;
        }
    }
    return votes;

}

/*Lors du dépouillement, on classe d'abord les bulletins
en fonction des premières préférences : si un candidat réunit une majorité absolue
 de ces premières préférences, il est élu. Sinon le candidat arrivé dernier est
éliminé et ses bulletins sont répartis entre les autres candidats suivant les
 secondes préférences desdits bulletins.
*/
//Fonction afin de voir si il y a majorité
bool majorite(const vector<int>& compte, const int& numVotes) {
    for (unsigned i = 0; i < compte.size(); ++i) {
        if (compte[i] > numVotes / 2) {
            return true;
        }
    }
    return false;
}
//Fontion afin de trouver quel candidats a le moins de votes
int trouverDernier(const vector<int>& compte) {
    int minVotes = INT_MAX;
    int dernier = -1;
    for (unsigned i = 0; i < compte.size(); ++i) {
        if (compte[i] < minVotes && compte[i] != -1) {
            minVotes = compte[i];
            dernier = i;
        }
    }
    //renvoie l'indice du dernier candidat
    return dernier;
}
//Procédure afin d'éliminer le candidats avec le moins de votes
void eliminerCandidat(vector<vector<int>>& votes, int candidatElimine) {
    for (unsigned i = 0; i < votes.size(); ++i) {
        for (unsigned j = 0; j < votes[i].size(); ++j) {
            if (votes[i][j] == candidatElimine) {
                votes[i][j] = -1;
            }
        }
        votes[i].erase(remove(votes[i].begin(), votes[i].end(), -1), votes[i].end());
    }
}

int main() {
    vector<string> candidat;
    vector<vector<int>> votes;
    candidat = candidats();
    votes = vote_alternatif_test(candidat);
    afficherVotes(candidat, votes);
    vector<int> compte;
    // Nombre total de votes
    int numVotes = votes.size(); 
    // Décompte initial
    decompte(votes, candidat);
    // Initialiser compte pour stocker les votes
    compte.resize(candidat.size(), 0); 
    //boucle tant qu'il n'y a pas de majorité absolue
    while (!majorite(compte, numVotes)) {
        compte.clear();
        // Réinitialiser compte
        compte.resize(candidat.size(), 0); 

        // Compte les votes après avoir éliminé un candidat
        decompte(votes, candidat);
        
        // Remplir le vecteur compte avec les premiers votes
        for (unsigned i = 0; i < votes.size(); ++i) {
            // Vérifier que le vote n'est pas vide
            if (!votes[i].empty()) { 
                // Compter le premier vote
                compte[votes[i][0]]++; 
            }
        }
        //Appel de la fonction trouverDernier afin de trouver le dernier candidat et de l'éliminer
        int candidatElimine = trouverDernier(compte);
        cout << "Le candidat " << candidat[candidatElimine] << " est éliminé." << endl;
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
