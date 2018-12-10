#include <iostream>
#include <fstream>
#include "graph.h"

using namespace std;

int main()
{
    Graph g;

    std::ifstream TestFile("graph.txt");
    if (!TestFile) return 1;
    cin.rdbuf(TestFile.rdbuf());

    int nblignes, nbcolonnes;
    std::cin >> nblignes >> nbcolonnes;
    initialisation(&g,nblignes,nbcolonnes);

    int nbnoeuds;
    std::cin >> nbnoeuds;
    for (int n = 0; n < nbnoeuds; ++n) {
        int h, i, j;
        std::cin >> h >> i >> j;
         ajouterSommet(&g,h,i,j);
    }

    int nbsites;
    std::cin >> nbsites;
    for (int n = 0; n < nbsites; ++n) {
        int i, j;
        std::cin >> i >> j;
        ajouterSite(&g,i,j);
    }
    TestFile.close();

    affichageGraph(g);
    parcoursProfondeur(g,returnSommet(g,0,3),true);
    std::cout<<std::endl;
    parcoursProfondeur(g,returnSommet(g,0,3),false);
    std::vector<Pair> PCDResult = parcoursDijkstra(g,returnSommet(g,0,0));
    for(unsigned int i = 0; i<PCDResult.size();i++){
        if(PCDResult[i].pred!=NULL){
            std::cout<<"Le sommet "<<g.sommets[i]->h<<" est a distance "<<PCDResult[i].dist<<" de "<<PCDResult[i].pred->h<<std::endl;
        }
    }

    voronoi(g);

}
