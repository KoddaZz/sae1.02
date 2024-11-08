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
#include <iomanip>  // afin d'utiliser quoted()
using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0)));
    // Mise en place du dictionnaire répertoriant les candidats
    string nomExempleAEntrer = "'Roberto De Zerbi'";

    cout << "Bienvenue sur une simulation d'un vote d'un suffrage indirect !" << endl << " "<< endl;
    cout << "===================== [ INSTRUCTIONS ] =====================" << endl
         << "Pour le bon fonctionnement de ce programme, vous devrez à CHAQUE entrée dite string ou texte, faire comme le modèle ci dessous : " << endl
         << "Exemple au moment de saisir un candidat : " << nomExempleAEntrer << endl
         << "[ ! ] - Mais mettre des des doubles guillemets a la place ! "
         << " " << endl
         << "Votez bien !" << endl;
    unsigned nombreDeVotants = 0; // Initialisation de nombreDeVotants
    unsigned compteur = 0; // -> boucle while pour les candidats régionaux
    unsigned nombreRegion = 0; // nombre de regions au total dans la simulation de vote
    unsigned nombreDeleguesRegion = 0; // Nombre de candidats delegues ( à définir spécialement pour chaque région )
    unsigned nombreCandidatsNationaux; // Nombre de candidats qui se présentent à la nationale
    string enregistrementNomCandidat = " "; // => servira pour enregistrer les noms des candidats à chaque fois ( delegues / national )
    string saisieNomCandidatVote = " "; // Ce que le vote va rentrer ( Pour qui il va voter )
    cout << "Combien de region(s) voulez vous simuler ( Le nombre ( entier ) de regions dans leqsquelles vous voulez simuler un vote ) ? ";
    cin >> nombreRegion;
    unsigned compteur2 = 0;
    unsigned nombreVoteBlancNational;

    map<int, string> dicoDeleguesParRegions;

    map<int,int> nombreVotesBlancParRegions;

    for (unsigned i = 0; i < nombreRegion; i++) {
        compteur = 0;
        map<int,int> nombreVotantsRegionaux; // Creation d'un dictionnaire pour enregistrer le nombre de votants par région
        cout << "Entrez le nombre de votants :";
        cin >> nombreDeVotants; // Entrée d'un entier
        nombreVotantsRegionaux[i] = nombreDeVotants; // Pour chaque région on aura le nombre de votants

        map<int, map<string, int>> DeleguesRegion;
        // Création d'un dictionnaire de dictonnaire pour enregistrer :
        //  - le nom des délégués selon la région
        //  - le nombre de voix qu'ils ont reçu

        /*for (unsigned j = 0; j < nombreDeleguesRegion; j++) {
            // AJOUT D'UN MODE ADMIN ?
            // Si admin = True
            cout << "Enregistrez les noms des candidats afin de debuter le vote des regionaux : ";
            cin >> quoted(enregistrementNomCandidat);
            DeleguesRegion[i][enregistrementNomCandidat] = 0;
        }
        */
        cout << "Combien de candidat Delegues voulez vous dans la region numero " << i << " : ";
        cin >> nombreDeleguesRegion; // Saisie du nombre (entier) de Délégués
        while (compteur < nombreVotantsRegionaux[i]) { // Simulation du vote pour chaque région

            cout << "Combien de candidat Delegues voulez vous dans la region numero " << i << " : ";
            cin >> nombreDeleguesRegion; // Saisie du nombre (entier) de Délégués
            for (unsigned j = 0; j < nombreDeleguesRegion; j++) { // BOUCLE => Enregistrer les noms de tout les candidats pour chaque régions
                // AJOUT D'UN MODE ADMIN ?
                // Si admin = True
                cout << "Enregistrez les noms des candidats afin de debuter le vote des regionaux : ";
                cin >> quoted(enregistrementNomCandidat); // Saisir le nom du candidat afin de l'inscrire sur les listes ( EX ENTREE : "FUSELIER Jules" )
                DeleguesRegion[i][enregistrementNomCandidat] = 0; // Initialiser le nombre de voix à 0 selon le nom du candidat
            } // TO DO : FAIRE QUE L'ON NE PEUT PAS ENREGISTRER 2 FOIS LA MÊME PERSONNE ( rajouter un if ? )
            cout << "La liste des candidats est : " << endl;
            for (const auto& votant : DeleguesRegion) { // BOUCLE SERVANT A AFFICHER LES CANDIDATS POUR LESQUELS ON PEUT VOTER
                int idx = 1;
                for (const auto& pair : votant.second) {
                    cout << idx << ". " << pair.first << endl;
                    idx++;
                }
            }
            cout << "Entrez le nom du candidat : "; // Saisie du nom du candidat par le votant
            cin >> quoted(saisieNomCandidatVote); // EX ENTREE = "Théo Gheux
            cout << endl;
            compteur++; // Incrémentation du compteur afin de pas créer une boucle infinie ( while ) [ A MIEUX EXPLIQUER ]
            if (DeleguesRegion[i].find(saisieNomCandidatVote) != DeleguesRegion[i].end()) { // VERIF si le candidat pour lequel on a voté existe
                DeleguesRegion[i][saisieNomCandidatVote ] += 1; // SI OUI, Cela augmente le nombre de voix qu'a obtenu le candidat de 1
            } else {
                nombreVotesBlancParRegions[i]++; // SI NON, cela augmente le nombre de vote blancs selon la région ( un compteur / région )
            }
        }
        // Creation d'un tableau afin de créer une liste triée des candidats
        vector<pair<string, int>> liste_candidats(DeleguesRegion[i].begin(), DeleguesRegion[i].end());
        // Trier les candidats par nombre de votes (ordre décroissant)
        sort(liste_candidats.begin(), liste_candidats.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
        });
        // AFFICHAGE D'UN PODIUM ( modif à faire [i] ajouter un %
        cout << "Podium des candidats de la region " << i << " : " << endl;
        for (unsigned int k = 0; k < 3 && k < liste_candidats.size(); k++) {
            cout << k+1 << ". " << liste_candidats[k].first << " avec " << liste_candidats[k].second << " vote(s)." << endl;
        }
        cout << "Nombre de votes blancs : " << nombreVotesBlancParRegions[i] << endl << " " << endl << " ===================== [ REGIONAL ] ===================== " << endl << "      NOUVEAU VOTE / NOUVELLE REGION      " << endl << " ===================== [ REGIONAL ] ===================== " << endl << " " << endl;
// AFFICHAGE à MODIFIER D'EMPLACEMENT
        dicoDeleguesParRegions[i] = liste_candidats[0].first;
    }

    cout << "Combien il y a de candidats Nationaux ? " << endl; // Saisie du nombre de candidats à mettre sur les listes électorales
    cin >> nombreCandidatsNationaux; // Saisir un entier
    map<string, int> candidatsNationaux = map<string, int>(); // Création du dictionnaire afin d'enregistrer le nombre de voix par candidat selon son nom ( clé )

    for (unsigned j = 0; j < nombreCandidatsNationaux; j++) {  // BOUCLE => Enregistrer les noms des candidats à la national
        // AJOUT D'UN MODE ADMINISTRATEUR ?
        // if admin = True ?
        cout << "Enregistrez les noms des candidats afin de débuter le vote des nationaux : " << endl;
        cin >> quoted(enregistrementNomCandidat);
        candidatsNationaux[enregistrementNomCandidat] = 0; // Initialise son nombre de voix à 0
    }

    cout << " " << endl << " ===================== [ NATIONAL ] ===================== " << endl << "      VOTE CANDIDAT NATIONAL     " << endl << " ===================== [ NATIONAL ] ===================== " << endl << " " << endl;

    while (compteur2 < nombreRegion) {
        // ANNONCE DE LA LISTE DES CANDIDATS NATIONAUX

        cout << "La liste des candidats est : " << candidatsNationaux.size() << endl;
        for (const auto& votantNational : candidatsNationaux) {
            cout << "La liste des candidats est : " << votantNational.first << endl ;
        }
        cout << "Entrez le nom du candidat : ";
        cin >> quoted(saisieNomCandidatVote); // [ Votant ] => Saisir le nom d'un candidat comme le modèle suivant : "FABRE Alexis" [ ! ] Guillemets importants !
        cout << endl;
        compteur2++;

        if (candidatsNationaux.find(saisieNomCandidatVote) != candidatsNationaux.end()) { // VERIF si le candidat pour lequel on a voté existe
            candidatsNationaux[saisieNomCandidatVote] += 1; // SI OUI, Cela augmente le nombre de voix qu'a obtenu le candidat de 1
        } else {
            ++nombreVoteBlancNational; // SI NON, cela augmente le nombre de vote blanc
        }
    }
    // Creation d'un tableau afin de créer une liste triée des candidats

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
