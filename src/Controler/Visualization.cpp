#include "Visualization.hpp"

#include <ctime>
#include <iostream>
#include <cmath>

using namespace std;

Visualization::Visualization(double span, double totalTime, SpanType type)
    : _type(type),
    _span(span),
    _totalTime(totalTime){
    time_vector();
    creer_scenes();
}

Visualization::~Visualization(){

}

void Visualization::creer_scenes(){
    /*for (unsigned int i=0 ; i<moves.size() ; i++){
        scenes.push_back();
    }*/
}

void Visualization::time_vector(){
    if (_type == TIME_SPAN){
        int nbMoves = (int) (_totalTime/_span);
        double mod = fmod(_span,_totalTime);
        vector<double> timeVector(nbMoves);
        for(int i=0 ; i<nbMoves ; i++){
            timeVector[i] = i*_span;
        }
        if (mod)
            timeVector.push_back(_totalTime);
    }
    else{ // SPAN_LENGTH
        int nbMoves = (int) (_totalTime/_span);
        double mod = fmod(_span,_span);
        vector<double> timeVector(nbMoves);
        for(int i=0 ; i<nbMoves ; i++){
            timeVector[i] = 1;
        }
        if (mod)
            timeVector.push_back(_totalTime);
    }
    // appeler les macros pour avoir les déplacements correspondants
}
