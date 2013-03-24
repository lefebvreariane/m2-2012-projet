#ifndef STEP_H
#define STEP_H

#include <QObject>
#include <iostream>
#include <vector>
#include <limits>
using std::make_pair;
using std::pair;
using std::vector;

class Step : public QObject{
    Q_OBJECT
    vector<pair<double, double> > _punch;
    vector<pair<double, double> > _sheetGeom;
    vector<pair<double, double> > _sheetNeut;
public:
    explicit Step(vector<pair<double, double> > punch, pair<vector<pair<double, double> >,vector<pair<double, double> > > sheet, QObject *parent=0);
    explicit Step(const Step &step);
    const vector<pair<double, double> > punch() const {return _punch;}
    const vector<pair<double, double> > sheetGeom() const {return _sheetGeom;}
    const vector<pair<double, double> > sheetNeut() const {return _sheetNeut;}
    const pair<pair<double, double>, pair<double, double> > min_max() const;
    void setSheetNeut(int id, pair<double, double> p){
        _sheetNeut[id] = p;
    }
    void setSheetGeom(int id, pair<double, double> p){
        _sheetGeom[id] = p;
    }
    void replaceSheet(vector<pair<double, double> > neut, vector<pair<double, double> > geom){
        _sheetGeom = geom;
        _sheetNeut = neut;
    }
};

#endif // STEP_H
