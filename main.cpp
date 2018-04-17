#include <iostream>
#include <vector>

struct vertice {
    //a structure to hold each vertice on the manifold and pointers to the vertices it is connected to.
    std::vector<vertice*> pastVertices;
    std::vector<vertice*> futureVertices;
    std::vector<vertice*> currentVertices;

    unsigned long numPast() {
        return pastVertices.size();
    }
    unsigned long numFuture() {
        return futureVertices.size();
    }
};

struct Manifold {
    std::vector<vertice> manifold;

    Manifold(int xNum, int tNum){
        //populate the manifold with a base torus
        for (int t=0; t<tNum; t++){
            //each timelike layer



        }
    }
};


class CDTUniverse{

    void rearrangement();
    void sampleUniverse();

};

void CDTUniverse::rearrangement(){

}

void CDTUniverse::sampleUniverse() {

}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}