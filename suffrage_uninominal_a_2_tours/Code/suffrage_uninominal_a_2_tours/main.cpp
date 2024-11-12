#include <iostream>
#include <vector>
#include <string>

using namespace std;

string litUneString (){
    string uneChaine;
    while (true){
        getline (cin, uneChaine);
        if ((!cin) || (uneChaine.substr(0,2) != "//")) break;
    }
    return uneChaine;
}

int litUnEntier (){
    string uneChaine;
    while (true){
        getline (cin, uneChaine);
        if ((!cin) || (uneChaine.substr(0,2) != "//")) break;
    }
    return stoi(uneChaine);
}

void saisirCandidats(vector<string> & tableau_des_candidats)
/* Cette procédure prend en paramètre un vecteur de string vide et demande à l'utilisateur de le remplir avec le nom des candidats */
{
    // On vide le tableau au cas où le vecteur n'est pas vide
    tableau_des_candidats.clear();
    size_t nb_candidats;
    string nom ;
    string chaine ;
    nb_candidats = litUnEntier();
    for(size_t i = 1 ; i <= nb_candidats ; i = i + 1)
    {
        if (i == 1)
        {
            nom = litUneString();
            tableau_des_candidats.push_back(nom);
        }
        else
        {
            nom = litUneString();
            tableau_des_candidats.push_back(nom);
        }
    }
}

void saisirVotes(const vector<string> & tableau_candidats, vector <size_t> & votes )
/* Cette procédure prend en paramètre le vecteur de string des noms des candidats et un vecteur d'entiers naturels vide et demande à l'utilisateur
de remplir le vecteur vide avec le nombre de voix qu'a obtenu chaque candidat */
{
    // On vide le tableau au cas où le vecteur n'est pas vide :
    votes.clear();
    
    // L'utilisateur saisit les votes qu'ont obtenu les candidats :
    size_t vote_tmp ;
    for (size_t i = 0 ; i < tableau_candidats.size() ; i = i + 1)
    {
        vote_tmp = litUnEntier();
        votes.push_back(vote_tmp);
        
    }
    
    // On affiche les votes :
}

int main()
{
    // Premier tour :
    vector <string> tableau_des_candidats ;
    saisirCandidats(tableau_des_candidats);
    
    vector <size_t> votes ;
    saisirVotes(tableau_des_candidats,votes);
    
    // On teste s'il y'a une majorité absolue
    
    size_t somme_des_votes = 0 ;
    for ( unsigned i = 0 ; i < votes.size() ; i = i + 1)
    {
        somme_des_votes = somme_des_votes + votes[i] ;
    }
    
    unsigned i = 0 ;
    unsigned x = 0 ;
    
    while(i < votes.size())
    {
        // Si un candidat a obtenu la majorité absolue :
        if (votes[i] > somme_des_votes / 2)
        {
            cout << tableau_des_candidats[i]
                 << " a obtenue une majorité absolue avec "
                 << votes[i]
                 << " voix et remporte donc le vote."
                 << endl ;
            
            // Si il y'a une majorité absolue, une variable x de type "unsigned" vaut 1, sinon elle vaut 0
            x = x + 1 ;
            break ;
        }
        i = i + 1;
    }
    // Si x vaut 0 ( c'est-à-dire qu'il n'y a pas de majorité absolue ) on procède au second tour :
    if (x == 0)
    {
        // cout << "Il n'y a pas de majorité absolue. Nous allons donc effectuer un second tour." << endl << endl ;
        
        // Second tour :
        
        string premier_candidat ;
        string second_candidat ;
        size_t premier_vote = 0 ;
        size_t second_vote = 0 ;
        size_t indice = 0 ;
        size_t indice2 = 0 ;
        
        /* On définit les deux candidats qui passe au second tour :
          premier_candidat est le candidat qui a obtenu le plus de votes au premier tour et
          second_candidat est le deuxième candidat qui a obtenu le plus de votes au premier tour */
        
        for(size_t i = 0 ; i < votes.size() ; i = i + 1)
        {
            if (votes[i] > premier_vote)
            {
                premier_vote = votes[i];
                indice = i ;
            }
        }
        
        premier_candidat = tableau_des_candidats[indice] ;
        
        for(size_t i = 0 ; i < votes.size() ; i = i + 1)
        {
            if ( i != indice)
            {
                if (votes[i] > second_vote)
                {
                    second_vote = votes[i];
                    indice2 = i ;
                }
            }
            
        }
        
        second_candidat = tableau_des_candidats[indice2] ;
        
        vector <string> tableau_des_candidats2 ;
        tableau_des_candidats2.push_back(premier_candidat);
        tableau_des_candidats2.push_back(second_candidat);
        // On saisit le nombre de votes qu'on obtenu les candidats au second tour avec la procédure saisirVotes() :
        vector <size_t> votes_second_tour ;
        saisirVotes(tableau_des_candidats2,votes_second_tour);
        
        
        // Si le premier candidat a plus de votes que le second, il gagne :
        if (votes_second_tour[0] > votes_second_tour[1])
        {
            cout << tableau_des_candidats2[0]
                 << " a obtenu "
                 << votes_second_tour[0]
                 << " votes tandis que "
                 << tableau_des_candidats2[1]
                 << " a obtenu "
                 << votes_second_tour[1]
                 << " votes."
                 << endl
                 << " C'est donc "
                 << tableau_des_candidats2[0]
                 << " qui a obtenu la majorité et remporte ainsi le vote.";
            
        }
        // Sinon, si le second candidat a plus de votes que le premier, il gagne :
        else if (votes_second_tour[1] > votes_second_tour[0])
        {
            cout << tableau_des_candidats2[1]
                 << " a obtenu "
                 << votes_second_tour[1]
                 << " votes tandis que "
                 << tableau_des_candidats2[0]
                 << " a obtenu "
                 << votes_second_tour[0]
                 << " votes."
                 << endl
                 << "C'est donc "
                 << tableau_des_candidats2[1]
                 << " qui a obtenu la majorité et remporte ainsi le vote."
                 << endl ;
        }
        // Sinon, il y'a égalité au second tour :
        else
        {
            /* Si les deux candidats n'ont pas obtenu le même nombre de voix au premier tour,
              c'est le candidat premier_candidat qui gagne */
            if (votes[indice]!=votes[indice2])
            {
                cout << "IL y'a égalité entre les deux candidats du second tour car ils ont tous les deux obtenu "
                     << votes_second_tour[0]
                     << " votes."
                     << endl
                     << "Le gagnant est donc le candidat qui a obtenu le plus de voix au premier tour."
                     << endl
                     << "Au premier tour, "
                     << tableau_des_candidats2[0]
                     << " a obtenu "
                     << votes[indice]
                     << " voix tandis que "
                     << tableau_des_candidats2[1]
                     << " a obtenu "
                     << votes[indice2]
                     << " voix."
                     << endl
                     << "C'est donc "
                     << tableau_des_candidats2[0]
                     << " qui a obtenu la majorité et remporte ainsi le vote."
                     << endl ;
                
            }
            // Sinon, il y'a égalité au premier tour (en plus du deuxième tour) : Pas de chance !
            else
            {
                cout << "Pas de chance ! Les deux candidats ont tous les deux obtenu le même nombre de voix au premier et au second tour ;-;";
                
            }
            
            
        }
    }
}



