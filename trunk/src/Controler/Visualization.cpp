#include "Visualization.hpp"

#include <ctime>
#include <iostream>
#include <cmath>
#include "../Model/fakesimu.h"
using namespace std;

Visualization::Visualization(int span, int totalTime):
    //scene("../scenes/Document21.xml"),
    //_scene("../scenes/simpleScene.xml"),
    _span(span),
    _totalTime(totalTime){
    fakeSimu *f = new fakeSimu(&scene);
    delete f;
    time_vector();
    //creer_scene();
}

Visualization::~Visualization(){}

void Visualization::creer_scene(){
    // Passage à OpenFEM
    // .........
    // .........
    // remplissage des étapes
    //_scene.remplir_etapes();
    //_scene.calculer_aire();
}

void Visualization::time_vector(){
    int nbMoves = _totalTime/_span;
    _timeVector.resize(nbMoves);
    for(int i=0 ; i<nbMoves ; i++){
        _timeVector[i] = i*_span;
    }
}

void Visualization::updateVisu(int span, int totalTime){
    _span = span;
    _totalTime = totalTime;
    time_vector();
    creer_scene();
}
