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

void messageLancement() {
    string nomExempleAEntrer = "'Roberto De Zerbi'";

    cout << "Bienvenue sur une simulation d'un vote d'un suffrage indirect !" << endl << " "<< endl;
    cout << "===================== [ INSTRUCTIONS ] =====================" << endl
         << "Pour le bon fonctionnement de ce programme, vous devrez à CHAQUE entrée dite string ou texte, faire comme le modèle ci dessous : " << endl
         << "Exemple au moment de saisir un candidat : " << nomExempleAEntrer << endl
         << "[ ! ] - Mais mettre des des doubles guillemets a la place ! "
         << " " << endl
         << "Votez bien !" << endl;
}

void scrutinElection (){


}

int main() {
    messageLancement();
    return 0;
}