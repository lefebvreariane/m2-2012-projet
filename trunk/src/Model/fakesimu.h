#ifndef FAKESIMU_H
#define FAKESIMU_H

#include <QObject>
#include <iostream>
#include <vector>
#include <cmath>
#include "scene.h"
#include "step.h"

#define PI atan(1)*4

using std::pair;
using std::make_pair;
using std::vector;

class fakeSimu : public QObject
{
    Q_OBJECT
    vector<pair<double, double> > _matrix;
    vector<pair<double, double> > _punch;
    vector<pair<double, double> > _stripper;
    vector<pair<double, double> > _sheetGeom;
    vector<pair<double, double> > _sheetNeut;
    int      _thickness;
    int      _time;
    int      _fps;
    int      _punchDistance;
public:
    explicit fakeSimu(Scene *scene, QObject *parent = 0);
    explicit fakeSimu(vector<pair<double, double> > matrix, vector<pair<double, double> > punch, vector<pair<double, double> > stripper, vector<pair<double, double> > geom, vector<pair<double, double> > neut, QObject *parent);
    virtual ~fakeSimu(){}

    Step* generateStep(int id, Scene *scene);
    //Scene* scene() {return scene;}
};

#endif // FAKESIMU_H
