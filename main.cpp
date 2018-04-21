#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>
struct Vertice {
    //a structure to hold each vertice on the manifold and pointers to the vertices it is connected to.

    //we hold these seperatedly to avoid needing to differentiate between pointers to vertices in the future in past geometrically.
    std::vector<Vertice*> pastVertices;
    std::vector<Vertice*> futureVertices;
    std::vector<Vertice*> currentVertices;

    unsigned long numPast() {
        return pastVertices.size();
    }
    unsigned long numFuture() {
        return futureVertices.size();
    }
};

class Manifold {
    public:
        std::vector<Vertice> manifold;
        Manifold(int xNum, int tNum);
        unsigned long numVertices(){
            return manifold.size();
        }
};
b
Manifold::Manifold(int xNum, int tNum){
    //populate the manifold with a base torus
    for (int t=0; t<tNum; t++){
        //each timelike layer

        for (int x=0; x<xNum; x++){
            manifold.push_back(*new Vertice());
            if (x>0) {
                //link to adjacent vertices in same time layer
                manifold[t*xNum+x].currentVertices.push_back(&manifold[t*xNum+x-1]);
                manifold[t*xNum+x-1].currentVertices.push_back(&manifold[t*xNum+x]);
            }
            if(t>0 and x>0) {
                //link to past vertices
                manifold[(t-1)*xNum+x-1].futureVertices.push_back(&manifold[t*xNum+x]);
                manifold[(t-1)*xNum+x].futureVertices.push_back(&manifold[t*xNum+x]);
                manifold[t*xNum+x].pastVertices.push_back(&manifold[(t-1)*xNum+x-1]);
                manifold[t*xNum+x].pastVertices.push_back(&manifold[(t-1)*xNum+x]);
            }
        }
    }
}

class CDTUniverse{

    public:
        Manifold manifold;
        double scaledCosmologicalConstant = 1;
        void rearrangement();
        void sampleUniverse(int);
        double probMove(int);
        double probInverseMove(int);
        double probAddVertice(int);
        double probRemoveVertice(int);
        CDTUniverse(int, int);
};

CDTUniverse::CDTUniverse(int xNum, int tNum) : manifold(xNum, tNum){
    srand(time(NULL));
}

void CDTUniverse::rearrangement(){
    int randomVertice = rand() % manifold.numVertices();
    double probAddVertice;
    double probRemoveVertice;
}

void CDTUniverse::sampleUniverse(int rearrangements){
    for (int i = 0; i < rearrangements; i++){
        rearrangement();
    }
}

double CDTUniverse::probMove(int randVert){
    //equation 37
    return manifold.numVertices()/(manifold.numVertices()+1) * (manifold.manifold[randVert].numPast() * manifold.manifold[randVert].numFuture())/2 * exp(-scaledCosmologicalConstant);
}

double CDTUniverse::probInverseMove(int randVert){
    //equation 38
    return exp(scaledCosmologicalConstant)/(manifold.manifold[randVert].numPast()+manifold.manifold[randVert].numFuture());
}

double CDTUniverse::probAddVertice(int randVert){
    //equation 34
    return probMove(randVert) * 1/(manifold.numVertices()*manifold.manifold[randVert].numPast() * manifold.manifold[randVert].numFuture());
}

double CDTUniverse::probRemoveVertice(int randVert){
    //equation 35
    return probInverseMove(randVert);
}

int main() {

    CDTUniverse universe(10,10);

}