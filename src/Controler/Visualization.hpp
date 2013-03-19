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

enum SpanType {TIME_SPAN, SPAN_LENGTH};

class Visualization {

public:

    Visualization(double span, double totalTime);
    ~Visualization();

    double type() const {return _type;}
    double span() const {return _span;}
    double total_time() const {return _totalTime;}
    std::vector<double> time_vector() const {return _timeVector;}

private:
    std::vector<double> _timeVector;
    std::vector<Scene> _scenes;
    SpanType _type;
    double _span;
    double _totalTime;

    void creer_scenes();
    void time_vector();
//private slots:

};

#endif // VISUALIZATION_HPP