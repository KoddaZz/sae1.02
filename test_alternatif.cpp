#include <iostream>
#include <vector>
#include <string>
using namespace std;



void afficherVotes(const vector<string>& candidats, const vector<vector<int>>& votes) {
    cout << "Liste des candidats :";
    for (unsigned i = 0; i < candidats.size(); ++i) {
        cout << i + 1 << ": " << candidats[i] << "\n";
    }

    cout << "Liste des votes :";
    for (unsigned i = 0; i < votes.size(); ++i) {
        cout << "Vote " << i + 1 << ": ";
        for (unsigned j = 0; j < votes[i].size(); ++j) {
            cout << votes[i][j] + 1 << " ";
        }
        cout << "\n";
    }
}
void vote_alternatif_test()
{
    vector <string> candidats;
    vector <vector<int>> votes;

    int numCandidats;
    cout << "Entrez le nombre de candidats: ";
    cin >> numCandidats;
    candidats.resize(numCandidats);

    for (unsigned i=0;int(i)<numCandidats;++i){
        cout << "Candidats " << i+1 <<": ";
        cin >> candidats[i];
    }

    int votant;
    cout << "Veuillez saisir le nombre de votant: ";
    cin >> votant;
    votes.resize(votant, vector<int>(numCandidats));

    cout << "Entrez les votes (par exemple 1 2 3 pour preferer le candidat 1 puis le 2 puis le 3 dans un vote à quatre candidats";
    for (unsigned i=0;int(i)<votant;++i)
    {
        cout << "Vote " << i+1<< ": ";
        for(unsigned j=0;int(j)<numCandidats; ++j)
        {
            int preference;
            cin >> preference;
            votes[i][j]=preference-1;
        }
    }
    cout<<"test";
    afficherVotes(candidats, votes);
}
/*Lors du dépouillement, on classe d'abord les bulletins
en fonction des premières préférences : si un candidat réunit une majorité absolue
 de ces premières préférences, il est élu. Sinon le candidat arrivé dernier est
éliminé et ses bulletins sont répartis entre les autres candidats suivant les
 secondes préférences desdits bulletins.
*/
int main()
{
    vote_alternatif_test();
    return 0;
}
