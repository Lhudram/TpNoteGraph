
#include <vector>
#include <iostream>
//Structures de données :

struct _Sommet{
    int h, i ,j;
};
typedef struct _Sommet Sommet;

struct _Pair{
    double dist;
    Sommet * pred;
};
typedef struct _Pair Pair;

struct _Graph{
    int nbligne;
    int nbcolonne;
    std::vector<Sommet *> sommets;
    std::vector<Sommet *> sites;
};
typedef struct _Graph Graph;

//Fonctions
void initialisation(Graph * g);
void initialisation(Graph * g, int nbligne, int nbcolonne);

Sommet * initSommet(int h, int i, int j);
void ajouterSommet(Graph * g, int h, int i, int j);

void ajouterSite(Graph * g, int i, int j);

Sommet * returnSommet(Graph g, int i, int j);

void modifHauteur(Graph * g, int newh, int i, int j);
int returnHauteur(Graph g, int i, int j);

Sommet * voisinNord(Graph g, int i, int j);
Sommet * voisinSud(Graph g, int i, int j);
Sommet * voisinEst(Graph g, int i, int j);
Sommet * voisinOuest(Graph g, int i, int j);

void affichageGraph(Graph g);

void parcoursProfondeur(Graph g, Sommet * s, bool postfixe);
void visite(Graph g, std::vector<Sommet *> * sgris, std::vector<Sommet *> * snoir, Sommet * u);

void distanceSommet(Graph g, Sommet * s,std::vector<Pair> * PCD,std::vector<Sommet *> * sgris);
std::vector<Pair> parcoursDijkstra(Graph g, Sommet * s);


void voronoi(Graph g);
