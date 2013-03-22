#ifndef VISUALIZATION_HPP
#define VISUALIZATION_HPP
#include "Model/scene.h"
#include <vector>

#define PI atan(1)*4
#define distanceTemps     (temps, tempsMax, distanceMax)        -distanceMax/2*cos(2*PI*temps/tempsMax)+distanceMax/2
#define vitesseTemps      (temps, tempsMax, distanceMax)        PI*distanceMax/tempsMax*sin(2*PI*temps/tempsMax)
#define accelerationTemps (temps, tempsMax, distanceMax)        2*pow(PI,2)*distanceMax/pow(tempsMax,2)*cos(2*PI*temps/tempsMax)
#define tempsDistance     (distance,     tempsMax, distanceMax) acos((distance-(distanceMax/2))/(-distanceMax/2))/(2*PI/tempsMax)
#define tempsVitesse      (vitesse,      tempsMax, distanceMax) asin(vitesse*tempsMax/(PI*distanceMax))*tempsMax/(2*PI)
#define tempsAcceleration (acceleration, tempsMax, distanceMax) acos((acceleration*pow(tempsMax,2))/(2*pow(PI,2)*distanceMax))*tempsMax/(2*PI)


class Visualization {

public:
    Scene scene;

    Visualization(int span, int totalTime);
    ~Visualization();

    int span() const {return _span;}
    int totalTime() const {return _totalTime;}
    std::vector<int> timeVector() const {return _timeVector;}
    void updateVisu(int span, int totalTime);
    void creer_scene();

private:
    std::vector<int> _timeVector;
    int _span;
    int _totalTime;

    void time_vector();
//private slots:

};

#endif // VISUALIZATION_HPP
