#include "graph.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <limits>

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
    return g.sommets[i*g.nbcolonne+j];
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
    if(i!=0)
        return g.sommets[(i-1)*g.nbcolonne+j];
}
Sommet * voisinSud(Graph g, int i, int j){
    if(i+1<g.nbligne)
        return g.sommets[(i+1)*g.nbcolonne+j];
}
Sommet * voisinEst(Graph g, int i, int j){
    if(j+1<g.nbcolonne)
        return g.sommets[i*g.nbcolonne+(j+1)];
}
Sommet * voisinOuest(Graph g, int i, int j){
    if(j!=0)
        return g.sommets[i*g.nbcolonne+(j-1)];;
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

void distanceSommet(Graph g, Sommet * s,std::vector<Pair *> * PCD,std::vector<Sommet *> * visite){
    std::vector<Sommet*> successeur;
    successeur.push_back(voisinNord(g,u->i,u->j));
    successeur.push_back(voisinOuest(g,u->i,u->j));
    successeur.push_back(voisinEst(g,u->i,u->j));
    successeur.push_back(voisinSud(g,u->i,u->j));


    for(Sommet * v : successeur){
        if(std::find(visite->begin(), visite->end(), v)==visite->end() && v!=NULL){
            PCD[v->i*g->nbcolonne+v->j].dist=sqrt(1+sqrt(s->h-v->h))+PCD[s->i*g->nbcolonne+s->j].dist;
            PCD[v->i*g->nbcolonne+v->j].pred=s;
            visite->push_back(v);
            distanceSommet(g, v, PCD, visite);
        }
    }
}

void parcoursDijkstra(Graph g, Sommet * s){

    std::vector<Sommet *> sgris;
    std::vector<Sommet *> snoir;

    std::vector<Pair *> PCD;
    PCD.resize(g.nbligne*g.nbcolonne);
    for(unsigned int i = 0; i<PCD.size();i++)
       PCD[i]=NULL;
    std::vector<Sommet *> visite;

    sgris.push_back(s);
    PCD[s->i*g->nbcolonne+s->j].dist=0;
    PCD[s->i*g->nbcolonne+s->j].pred=0;

    distanceSommet(g, s, PCD, visite);
    for(Sommet * v : g.sommets){
        if(std::find(visite->begin(), visite->end(), v)==visite->end() && v!=NULL){
            PCD[v->i*g->nbcolonne+v->j].dist=std::numeric_limits<double>::infinity();
            PCD[v->i*g->nbcolonne+v->j].pred=0;
        }
    }

    /*
    for(Sommet * u : sgris){
        if(std::find(snoir.begin(), snoir.end(), u)!=snoir.end()){
            std::vector<Sommet*> successeur;
            successeur.push_back(voisinNord(g,u->i,u->j));
            successeur.push_back(voisinOuest(g,u->i,u->j));
            successeur.push_back(voisinEst(g,u->i,u->j));
            successeur.push_back(voisinSud(g,u->i,u->j));

            for(Sommet * v : successeur){
                if(v != NULL && std::find(snoir.begin(), snoir.end(), v)==snoir.end()){
                    int dist = sqrt(1+sqrt(s->h-v->h)) + ;
                    if(std::find(sgris.begin(), sgris.end(), v)==sgris.end()){
                        Pair p;
                        p.dist=dist;
                        p.sommet=v;
                        p.pred=s;
                        PCD.push_back(&p);
                        sgris.push_back(v);
                    }
                    else{
                        for(unsigned int i=0;i<PCD.size();i++){
                            if(PCD[i]->sommet==v && PCD[i]->dist>dist)
                                PCD[i]->dist=dist;
                                PCD[i]->pred=s;
                        }
                    }
                }
            }
            snoir.push_back(u);
        }
    }



    for(unsigned int i=0;i<g.sommets.size();i++ ){
        Sommet * v = g.sommets[i];
        if(v != NULL){
            PCD[i]->dist=
            if(PCD[i]->dist==std::numeric_limits<double>::infinity()){
                PCD[i]->pred=0;
                sblanc.push_back(v);
            }
            else{
                PCD[i]->pred=s;
                sgris.push_back(v);
            }
        }
     }
     snoir.push_back(s);

    while(sgris.size()!=0){
        double minimum = std::numeric_limits<double>::infinity();
        Sommet * sminimum;
        for(Sommet * v : sgris){
            if(PCD[v].dist<minimum){
                minimum=PCD[v].dist;
                sminimum=v;
            }
        }
        for(Sommet * s : g.sommets){
            if(s!=NULL){
                if(std::find(sgris->begin(), sgris->end(), s)==sgris->end() && std::find(snoir->begin(), snoir->end(), s)==snoir->end()){
                    sgris.push_back(s);

                }
            }
        }
    }*/

}
