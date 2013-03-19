#ifndef REALSCENE_H
#define REALSCENE_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomNode>
#include <iostream>
#include <cmath>
#include <vector>
using std::vector;
using std::pair;
using std::make_pair;
using std::cout;
using std::endl;

#define PI atan(1)*4
#define distanceTemps     (temps, tempsMax, distanceMax)        -distanceMax/2*cos(2*PI*temps/tempsMax)+distanceMax/2
#define vitesseTemps      (temps, tempsMax, distanceMax)        PI*distanceMax/tempsMax*sin(2*PI*temps/tempsMax)
#define accelerationTemps (temps, tempsMax, distanceMax)        2*pow(PI,2)*distanceMax/pow(tempsMax,2)*cos(2*PI*temps/tempsMax)
#define tempsDistance     (distance,     tempsMax, distanceMax) acos((distance-(distanceMax/2))/(-distanceMax/2))/(2*PI/tempsMax)
#define tempsVitesse      (vitesse,      tempsMax, distanceMax) asin(vitesse*tempsMax/(PI*distanceMax))*tempsMax/(2*PI)
#define tempsAcceleration (acceleration, tempsMax, distanceMax) acos((acceleration*pow(tempsMax,2))/(2*pow(PI,2)*distanceMax))*tempsMax/(2*PI)

class Scene : public QObject {
    Q_OBJECT
    vector<pair<double, double> >                                                _matrix;
    vector<pair<vector<pair<double, double> >, vector<pair<double, double> > > > _strippers;
    pair<vector<pair<double, double> >, vector<pair<double, double> > >          _punch;
    pair<vector<pair<double, double> >, vector<pair<double, double> > >          _sheet;
    double                                                                       _thickness;
public:
    // Constructeurs & destructeur
    Scene(const Scene &scene);
    explicit Scene(QString xmlFilePath, QObject *parent=0);
    virtual ~Scene(){}
    // Getters
    const vector<pair<double, double> >                                                matrix()    const {return _matrix;}
    const vector<pair<vector<pair<double, double> >, vector<pair<double, double> > > > strippers() const {return _strippers;}
    const pair<vector<pair<double, double> >, vector<pair<double, double> > >          punch()     const {return _punch;}
    const pair<vector<pair<double, double> >, vector<pair<double, double> > >          sheet()     const {return _sheet;}
    const double                                                                       thickness() const {return _thickness;}
    const pair<pair<double, double>, pair<double, double> >                                                  min_max();
private:
    void fillUnits       (QDomElement);
    void fillMatrice     (QDomElement);
    void fillStrippers   (QDomElement);
    void fillStripper    (QDomElement, int);
    void fillStripperUtil(QDomElement, int , bool);
    void fillPunch       (QDomElement);
    void fillPunchUtil   (QDomElement, bool);
    void fillSheet       (QDomElement);
    void fillSheetUtil   (QDomElement, bool);
};

#endif // REALSCENE_H
