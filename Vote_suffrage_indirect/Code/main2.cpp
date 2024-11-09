// Importation des bibliothèques nécessaires



// CREATION DICO => Resultat des votes FAIT
// PATCH ERREUR => Nombre de votes blancs s'accumule pour des régions diff ! FAIT
// IMPORTANT : OPTIMISER LE CODE EN LE TRANSFORMANT AVEC DES PROCEDURES



#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0))); // Correction pour adapter à type sécurisé

    cout << "Bienvenue sur une simulation d'un vote !" << endl;
    
    unsigned nombreDeVotants = 0; // Initialisation de nombreDeVotants
    unsigned compteur = 0;
    unsigned nombreRegion = 0;
    unsigned nombreDeleguesRegion = 0;
    unsigned nombreCandidatsNationaux;
    unsigned nomAuHasard = 0;
    string saisiNomCandidat = " ";

    cout << "Combien d'Etats / région voulez-vous simuler ? ";
    cin >> nombreRegion;
    
    cout << "Combien de candidats Délégués voulez-vous par région ? ";
    cin >> nombreDeleguesRegion;

    string prenom; // retiré de la boucle for 
    vector<string> prenoms;

    // Saisie des noms de candidats par l'utilisateur
    for (unsigned i = 0; i < nombreRegion * nombreDeleguesRegion; ++i) // pas sur de ça 
    {
        cout << "Entrez le prénom du candidat " << (i + 1) << ": ";
        cin >> prenom;
        prenoms.push_back(prenom);
    }

    unsigned compteur2 = 0;
    unsigned nombreVotesBlancNational = 0;

    map<int, string> dicoDeleguesParRegions;
    map<int, int> nombreVotesBlancParRegions;

    for (unsigned i = 0; i < nombreRegion; i++) {
        compteur = 0;
        map<int, int> nombreVotantsRegionaux;
        nombreDeVotants = rand() % 15; // à changer 
        nombreVotantsRegionaux[i] = nombreDeVotants;

        map<int, map<string, int>> candidatsEtats;

        // Générer les délégués de manière unique
        for (unsigned j = 0; j < nombreDeleguesRegion; j++) {
            nomAuHasard = rand() % prenoms.size();
            auto prenom = prenoms[nomAuHasard]; // maxime conseil de mettre une string à la place de auto / il déconseille d'utiliser des auto
            if (candidatsEtats[i].find(prenom) == candidatsEtats[i].end()) {
                candidatsEtats[i][prenom] = 0;
            }
        }

        while (compteur < nombreVotantsRegionaux[i]) {
            cout << "La liste des candidats est : " << endl;
            for (const auto& votant : candidatsEtats) // pareil ici
            {  
                int idx = 1;  // Correction d'affichage manquée.
                for (const auto& pair : votant.second) {
                    cout << idx << ". " << pair.first << endl;
                    idx++;
                }
            }
            cout << "Entrez le nom du candidat : ";
            cin >> saisiNomCandidat;
            cout << endl;
            compteur++;
            if (candidatsEtats[i].find(saisiNomCandidat) != candidatsEtats[i].end()) {
                candidatsEtats[i][saisiNomCandidat] += 1;
            } else {
                nombreVotesBlancParRegions[i]++;
            }
        }

        vector<pair<string, int>> liste_candidats(candidatsEtats[i].begin(), candidatsEtats[i].end());
        sort(liste_candidats.begin(), liste_candidats.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
        });
        
        cout << "Podium des candidats de la région " << i << " : " << endl;
        for (unsigned int k = 0; k < 3 && k < liste_candidats.size(); k++) {
            cout << k + 1 << ". " << liste_candidats[k].first << " avec " << liste_candidats[k].second << " vote(s)." << endl;
        }
        cout << "Nombre de votes blancs : " << nombreVotesBlancParRegions[i] << endl << " " << endl;
        cout << " ===================== [ REGIONAL ] ===================== " << endl << "      NOUVEAU VOTE / NOUVELLE REGION      " << endl;
        cout << " ===================== [ REGIONAL ] ===================== " << endl << " " << endl;

        dicoDeleguesParRegions[i] = liste_candidats[0].first;
    }

    cout << "Combien il y a de candidats Nationaux ? " << endl;
    cin >> nombreCandidatsNationaux;
    map<string, int> candidatsNationaux;

    for (unsigned j = 0; j < nombreCandidatsNationaux; j++) {
        string prenom;
        cout << "Entrez le prénom du candidat national " << (j + 1) << ": ";
        cin >> prenom;
        candidatsNationaux[prenom] = 0;
    }

    cout << " " << endl << " ===================== [ NATIONAL ] ===================== " << endl << "      VOTE CANDIDAT NATIONAL     " << endl;
    cout << " ===================== [ NATIONAL ] ===================== " << endl << " " << endl;

    while (compteur2 < nombreRegion) {
        cout << "La liste des candidats est : " << endl;
        for (const auto& votantNational : candidatsNationaux) {
            cout << votantNational.first << endl;
        }
        cout << "Entrez le nom du candidat : ";
        cin >> saisiNomCandidat;
        cout << endl;
        compteur2++;

        if (candidatsNationaux.find(saisiNomCandidat) != candidatsNationaux.end()) {
            candidatsNationaux[saisiNomCandidat] += 1;
        } else {
            nombreVotesBlancNational++;
        }
    }

    vector<pair<string, int>> liste_candidats(candidatsNationaux.begin(), candidatsNationaux.end());
    sort(liste_candidats.begin(), liste_candidats.end(), [](pair<string, int> a, pair<string, int> b) {
        return a.second > b.second;
    });
    
    cout << "Podium des candidats : " << endl;
    for (unsigned int i = 0; i < 3 && i < liste_candidats.size(); i++) {
        cout << i + 1 << ". " << liste_candidats[i].first << " avec " << liste_candidats[i].second << " vote(s)." << endl;
    }
    cout << "Nombre de votes blancs : " << nombreVotesBlancNational << endl;

    return 0;
}


//j'ai demandé des conseils à maxime le goat il m'a recommandé de changé tout les partie aléatoire du code par des invites de commandes pour saisir les candidats... car par l'aléa marche pas sur oracle 


#include <iostream>
#include <vector>
#include <unordered_map>

int majorite (const std::vector<int>& votes){ 
    unordered_map<int, int> compteur;
    int seuil = votes.size() / 2; // calcul du seuil de majorité
}

    for (int vote : votes) {
        if (++compteur[vote] > seuil) {
            return vote; // renvoie le candidat avec le plus de voix 
    }
    cout << "aucun candidat n'a la majorité " 
}

int main() {
    vector<int> votes = {1, 2, 3, 1, 2, 1, 1}; // Exemple de votes
    int majorite = majorite(votes);
    cout << (majorite != -1 ? "Le candidat avec la majorité est : " : "Aucun candidat n'a la majorité.") 
              << (majorite != -1 ? to_string(majorite) : "") << endl;
    return 0;
}

//brouillon à re adapter et améliorer 
