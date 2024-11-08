#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

unsigned nombreregions ;
cout << "entrer le nombre de régions participantes à l'élection" ;
cin >> nombreregions;
while( nombreregions < 2 )
    {
        cout << "entrer un nombre supérieur à deux" ;
        cin >> nombreregions ;
    }

// definition du nombre d'élécteurs par région
vector <int> nombreDeElecteurs ;
for (unsigned i = 0; i< nombreregions, i++ )
{
    cout << "entrer le nombre d'électeurs dans la region" << i ;
    cin >> nombreDeElecteurs[i] ;
}


// definition du nombre de délégués par région
vector <int> nombreDeDelegues ;
for (unsigned i = 0; i< nombreregions, i++ )
{
    cout << "entrer le nombre de délégués dans la region" << i ;
    cin >> nombreDeDelegues[i] ;
}


// Saisie des candidats par région
    vector<map<string, int>> votes(nombreregions);
    for (unsigned i = 0; i < nombreregions; i++)
    {
        cout << "Entrer le nom du candidat " << i ;
        string nombreDeDelegues;
        cin >> nomDelegue;
        votes[i][nomDelegue] = 0;  // Initialiser le nombre de votes à 0

    }


// Collecte des votes
    for (unsigned i = 0; i < nombreregions; i++)
    {
        cout << "Région "<< i <<", entrez les votes des électeurs :";
        for (int j = 0; j < nombreDeElecteurs[i]; j++)
        {
            cout << "Vote de l'électeur " << j + 1 ;
            string vote;
            cin >> vote;
            // Compter le vote si le candidat existe
            if (votes[i].find(vote) != votes[i].end())
            {
                votes[i][vote]++;
            } else
            {
                cout << "Candidat non valide, vote non compté.";
            }
        }
    }

//vote des délégués

for (unsigned i = 0; i < nombreregions; i++) {
        cout << "Région ", i ;
        // Trier les candidats par nombre de votes
        vector<pair<string, int>> candidatsVotes(votes[i].begin(), votes[i].end());
        sort(candidatsVotes.begin(), candidatsVotes.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second; // Tri par nombre de votes décroissant
        });

        cout << "Délégués élus : \n";
        for (int j = 0; j < nombreDeDelegues[i] && j < candidatsVotes.size(); j++) {
            cout << "- " << candidatsVotes[j].first << " avec " << candidatsVotes[j].second << " votes";
        }
    }