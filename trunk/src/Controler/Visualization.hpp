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

    Visualization(double span, double totalTime);
    ~Visualization();

    double span() const {return _span;}
    double totalTime() const {return _totalTime;}
    std::vector<double> timeVector() const {return _timeVector;}
    Scene scene() const {return _scene;}

private:
    std::vector<double> _timeVector;
    Scene _scene;
    double _span;
    double _totalTime;

    void creer_scene();
    void time_vector();
//private slots:

};

#endif // VISUALIZATION_HPP
