#include <iostream>
#include <vector>
#include <string>
using namespace std;
/*void majorité(const vector<int>& compte){
    for (unsigned i = 0;i < compte.size();++i)
    {
        if compte[i]>
    }
}
*/
void decompte(const vector<vector<int>>& votes, const vector<string>& candidats) {
    // Initialiser un vecteur de compteurs pour chaque candidat
    vector<int> compte(candidats.size(), 0);

    // Parcourir les votes et compter les premières préférences
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

void afficherVotes(const vector<string>& candidats, const vector<vector<int>>& votes) {
    cout << "Liste des candidats :"<<endl;
    for (unsigned i = 0; i < candidats.size(); ++i) {
        cout << i + 1 << ": " << candidats[i] << "\n";
    }

    cout << "Liste des votes :"<<endl;
    for (unsigned i = 0; i < votes.size(); ++i) {
        cout << "Vote " << i + 1 << ": ";
        for (unsigned j = 0; j < votes[i].size(); ++j) {
            cout << votes[i][j] + 1 << " ";
        }
        cout << "\n";
    }
}
vector<string> candidats(){
    vector <string> candidats;
    unsigned numCandidats;
    cout << "Entrez le nombre de candidats: ";
    cin >> numCandidats;
    candidats.resize(numCandidats);

    for (unsigned i=0;i<numCandidats;++i){
        cout << "Candidats " << i+1 <<": ";
        cin >> candidats[i];
    }
    return candidats;
}
vector<vector<int>> vote_alternatif_test(const vector<string>& candidats)
{
    unsigned numCandidats;
    numCandidats=candidats.size();
    vector <vector<int>> votes;
    unsigned votant;
    cout << "Veuillez saisir le nombre de votant: ";
    cin >> votant;
    votes.resize(votant, vector<int>(numCandidats));

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
string main()
{
    vector<string> candidat;
    vector<vector<int>> votes;
    candidat=candidats();
    votes=vote_alternatif_test(candidat);
    afficherVotes(candidat, votes);
    vector<int> compte
    int numVotes;
    compte=decompte(votes,candidat);
    for (unsigned i = 0;i < compte.size();++i)
    {
        if compte[i]>numVotes{
            return candidat[i];
        }
    
    }
    return 0;
}
