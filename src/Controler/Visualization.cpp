#include "Visualization.hpp"

#include <ctime>
#include <iostream>
#include <cmath>

using namespace std;

Visualization::Visualization(double span, double totalTime):
    _span(span),
    _totalTime(totalTime){
    time_vector();
    creer_scenes();
}

Visualization::~Visualization(){}

void Visualization::creer_scenes(){
    /*for (unsigned int i=0 ; i<timeVector.size() ; i++){
        scenes.push_back();
    }*/

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
