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
    vector<pair<float, float> >             _matrice;
    vector<vector<pair<float, float> > >    _devetisseur;
    vector<pair<float, float> >             _poincon;
    vector<pair<float, float> >             _tole;
    QString uniteTemps;
    QString uniteDistance;
    double duree;
    double axeX;
    double axeY;
    double epaisseurTole;
    double xTranslation;
    double yTranslation;
    double xRotation;
    double yRotation;
    double angle;
public:
    // Constructeurs & destructeur
    explicit Scene(
            vector<pair<float, float> > matrice,
            vector<vector<pair<float, float> > > devetisseur,
            vector<pair<float, float> > poincon,
            vector<pair<float, float> > tole,
            QObject *parent = 0) : QObject(parent), _matrice(matrice), _devetisseur(devetisseur), _poincon(poincon), _tole(tole){}
    explicit Scene(QString xmlFilePath, QObject *parent=0);
    virtual ~Scene(){}
    // Modifieurs
    virtual void addMatrice(pair<float, float> p)               {_matrice.push_back(p);}
    virtual void addDevetisseur(int i, pair<float, float> p)    {_devetisseur[i].push_back(p);}
    virtual void addPoicon(pair<float, float> p)                {_poincon.push_back(p);}
    virtual void addTole(pair<float, float> p)                  {_tole.push_back(p);}
    // Accesseurs
    virtual const vector<pair<float, float> > matrice()                 const {return _matrice;}
    virtual const vector<vector<pair<float, float> > > devetisseur()    const {return _devetisseur;}
    virtual const vector<pair<float, float> > poincon()                 const {return _poincon;}
    virtual const vector<pair<float, float> > tole()                    const {return _tole;}
    virtual void resetTole() {_tole.clear();}
    virtual void save() const;
private:
    void fillUnits       (QDomElement);
    void fillMatrice     (QDomElement);
    void fillDevetisseur (QDomElement);
    void fillPoincon     (QDomElement);
    void fillTole        (QDomElement);
};

#endif // REALSCENE_H
