#include <iostream>
#include <vector>

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
};

Manifold::Manifold(int xNum, int tNum) {
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

        void rearrangement();
        void sampleUniverse(int);

        CDTUniverse(int, int);
};

CDTUniverse::CDTUniverse(int xNum, int tNum) : manifold(xNum, tNum){

}

void CDTUniverse::rearrangement(){

}

void CDTUniverse::sampleUniverse(int rearrangements) {
    for (int i = 0; i < rearrangements; i++){
        rearrangement();
    }
}

int main() {
    CDTUniverse universe(10,10);


}