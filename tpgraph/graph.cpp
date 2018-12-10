#include "graph.h"
#include <iostream>
#include <algorithm>

void initialisation(Graph * g){
    g->nbligne = 0;
    g->nbcolonne = 0;
}


void initialisation(Graph * g, int nbligne, int nbcolonne){
    g->nbligne=nbligne;
    g->nbcolonne=nbcolonne;
    g->sommets.resize(nbligne*nbcolonne);
    for(unsigned int i = 0; i<g->sommets.size();i++)
        g->sommets[i]=NULL;
}

Sommet * initSommet(int h, int i, int j){
    Sommet * s = new Sommet;
    s->i=i;
    s->j=j;
    s->h=h;
    return s;
}
void ajouterSommet(Graph * g, int h, int i, int j){
    if(i<g->nbligne && i>=0 && j<g->nbcolonne && j>=0)
        g->sommets[i*g->nbcolonne+j]=initSommet(h,i,j);
}

Sommet * returnSommet(Graph g, int i, int j){
    if(g.sommets[i*g.nbcolonne+j]!=NULL)
        return g.sommets[i*g.nbcolonne+j];
    return NULL;
}

void modifHauteur(Graph * g, int newh, int i, int j){
    if(g->sommets[i*g->nbcolonne+j]!=NULL)
        g->sommets[i*g->nbcolonne+j]->h=newh;
}


int returnHauteur(Graph g, int i, int j){
    if(g.sommets[i*g.nbcolonne+j]!=NULL)
        return g.sommets[i*g.nbcolonne+j]->h;
    return -1;
}


Sommet * voisinNord(Graph g, int i, int j){
    if(i!=0 && g.sommets[(i-1)*g.nbcolonne+j]!=NULL)
        return g.sommets[(i-1)*g.nbcolonne+j];
    return NULL;
}
Sommet * voisinSud(Graph g, int i, int j){
    if(i+1<g.nbligne && g.sommets[(i+1)*g.nbcolonne+j]!=NULL)
        return g.sommets[(i+1)*g.nbcolonne+j];
    return NULL;
}
Sommet * voisinEst(Graph g, int i, int j){
    if(j+1<g.nbcolonne && g.sommets[i*g.nbcolonne+(j+1)]!=NULL)
        return g.sommets[i*g.nbcolonne+(j+1)];
    return NULL;
}
Sommet * voisinOuest(Graph g, int i, int j){
    if(j!=0 && g.sommets[i*g.nbcolonne+(j-1)]!=NULL)
        return g.sommets[i*g.nbcolonne+(j-1)];
    return NULL;
}

void affichageGraph(Graph g){
    for(int i = 0;i<g.nbligne;i++){
        for(int j = 0;j<g.nbcolonne;j++){

            std::cout<<"[";
            if(std::find(g.sites.begin(), g.sites.end(), g.sommets[i*g.nbcolonne+j])!=g.sites.end())
                std::cout<<"!";
            if(g.sommets[i*g.nbcolonne+j]!=NULL)
                std::cout<<g.sommets[i*g.nbcolonne+j]->h;
            if(j!=g.nbcolonne-1)
                std::cout<<"]--";
            else
                std::cout<<"]";
        }
        std::cout<<std::endl;
    }
}

void ajouterSite(Graph * g, int i, int j){
    if(g->sommets[i*g->nbcolonne+j]!=NULL)
        g->sites.push_back(g->sommets[i*g->nbcolonne+j]);
    else
        std::cout<<"Ce sommet n'existe pas"<<std::endl;
}

void parcoursProfondeur(Graph g, Sommet * s, bool postfixe){
    std::vector<Sommet *> sgris;
    std::vector<Sommet *> snoir;

    int position = -1;

    for(unsigned int i=0;i<g.sommets.size();i++ ){
        Sommet * u = g.sommets[i];
        if(u==s)
            position = i;
    }

    if(position != -1){
        for(unsigned int j=position;j<(g.sommets.size()+position);j++ ){
            int indice=j%g.sommets.size();
            Sommet * u = g.sommets[indice];
            if(std::find(sgris.begin(), sgris.end(), u)==sgris.end() && std::find(snoir.begin(), snoir.end(), u)==snoir.end() && u != NULL){
                sgris.push_back(u);
                visite(g, &sgris, &snoir, u);
            }
        }
        if(postfixe){
            for(Sommet * v : snoir){
                std::cout<<v->h<<" ";
            }
        }
        else{
            for(Sommet * v : sgris){
                std::cout<<v->h<<" ";
            }
        }
    }

}

void visite(Graph g, std::vector<Sommet *> * sgris, std::vector<Sommet *> * snoir, Sommet * u){
    std::vector<Sommet*> successeur;
    successeur.push_back(voisinNord(g,u->i,u->j));
    successeur.push_back(voisinOuest(g,u->i,u->j));
    successeur.push_back(voisinEst(g,u->i,u->j));
    successeur.push_back(voisinSud(g,u->i,u->j));


    for(unsigned int i=0;i<successeur.size();i++ ){
        Sommet * v = successeur[i];
        if(std::find(sgris->begin(), sgris->end(), v)==sgris->end() && std::find(snoir->begin(), snoir->end(), v)==snoir->end() && v!=NULL){
            sgris->push_back(v);
            visite(g, sgris, snoir, v);
        }
    }
    snoir->push_back(u);
}

void parcoursDijkstra(Graph g, Sommet * s){
    std::vector<Pair *> PCD;
     for(unsigned int i=0;i<g.sommets.size();i++ ){
        Sommet * v = g.sommets[i];
        if(v != NULL){
            PCD[i]->dist=sqrt(1+sqrt(s->h-v->h));
        }
     }

}
