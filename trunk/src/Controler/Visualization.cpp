#include "Visualization.hpp"

#include <ctime>
#include <iostream>
#include <cmath>

using namespace std;

Visualization::Visualization(double span, double totalTime):
    _scene("../src/scenes/Document1.xml"),
    //_scene("../src/scenes/simpleScene.xml"),
    _span(span),
    _totalTime(totalTime){
    time_vector();
    creer_scene();
}

Visualization::~Visualization(){}

void Visualization::creer_scene(){
    // Passage à OpenFEM
    // .........
    // .........
    // remplissage des étapes
    //_scene.remplir_etapes();
}

void Visualization::time_vector(){
    int nbMoves = _totalTime/_span;
    double mod = fmod(_totalTime,_span);
    _timeVector.resize(nbMoves);
    for(int i=0 ; i<nbMoves ; i++){
        _timeVector[i] = i*_span;
    }
    if (mod)
        _timeVector.push_back(_totalTime);
}
