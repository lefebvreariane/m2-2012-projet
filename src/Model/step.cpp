#include "step.h"
#include <limits>

Step::Step(vector<pair<double, double> > punch, pair<vector<pair<double,double> >,vector<pair<double,double> > >  sheet, QObject *parent) : QObject(parent), _punch(punch), _sheetGeom(sheet.first), _sheetNeut(sheet.second){
}
Step::Step(const Step &step) : QObject(step.parent()){
    this->_punch = step.punch();
    this->_sheetGeom = step.sheetGeom();
    this->_sheetNeut = step.sheetNeut();
}

const pair<pair<double, double>, pair<double, double> > Step::min_max() const{
    pair<pair<double, double>, pair<double, double> > out = make_pair(
            make_pair(std::numeric_limits<double>::max(), std::numeric_limits<double>::max()),
            make_pair(std::numeric_limits<double>::min(), std::numeric_limits<double>::min()));
    for (unsigned int i=0; i<_sheetGeom.size(); i++){
        if (out.first.first   > _sheetGeom[i].first)  out.first.first   = _sheetGeom[i].first;
        if (out.first.second  > _sheetGeom[i].second) out.first.second  = _sheetGeom[i].second;
        if (out.second.first  < _sheetGeom[i].first)  out.second.first  = _sheetGeom[i].first;
        if (out.second.second < _sheetGeom[i].second) out.second.second = _sheetGeom[i].second;
    }
    for (unsigned int i=0; i<_punch.size(); i++){
        if (out.first.first   > _punch[i].first)  out.first.first   = _punch[i].first;
        if (out.first.second  > _punch[i].second) out.first.second  = _punch[i].second;
        if (out.second.first  < _punch[i].first)  out.second.first  = _punch[i].first;
        if (out.second.second < _punch[i].second) out.second.second = _punch[i].second;
    }
    return out;
}
