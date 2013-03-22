#include "Visualization.hpp"

#include <ctime>
#include <iostream>
#include <cmath>

using namespace std;

Visualization::Visualization(int span, int totalTime):
        scene("../scenes/Document2#1.xml"),
    //_scene("../scenes/simpleScene.xml"),
    _span(span),
    _totalTime(totalTime){
    time_vector();
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
    int modulo = _totalTime%_span;
    _timeVector.resize(nbMoves);
    for(int i=0 ; i<nbMoves ; i++){
        _timeVector[i] = i*_span;
    }
    if (modulo)
        _timeVector.push_back(_totalTime);
}

void Visualization::updateVisu(int span, int totalTime){
    _span = span;
    _totalTime = totalTime;
    time_vector();
    creer_scene();
}
