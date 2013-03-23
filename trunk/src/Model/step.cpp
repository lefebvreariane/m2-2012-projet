#include "step.h"
#include <limits>

Step::Step(vector<pair<double, double> > punch, QObject *parent) : QObject(parent), _punch(punch){
}
Step::Step(const Step &step) : QObject(step.parent()){
    this->_punch = step.punch();
    this->_sheet = step.sheet();
}

const pair<pair<double, double>, pair<double, double> > Step::min_max() const{
    pair<pair<double, double>, pair<double, double> > out = make_pair(
            make_pair(std::numeric_limits<double>::max(), std::numeric_limits<double>::max()),
            make_pair(std::numeric_limits<double>::min(), std::numeric_limits<double>::min()));
    for (unsigned int i=0; i<_sheet.size(); i++){
        if (out.first.first   > _sheet[i].first)  out.first.first   = _sheet[i].first;
        if (out.first.second  > _sheet[i].second) out.first.second  = _sheet[i].second;
        if (out.second.first  < _sheet[i].first)  out.second.first  = _sheet[i].first;
        if (out.second.second < _sheet[i].second) out.second.second = _sheet[i].second;
    }
    for (unsigned int i=0; i<_punch.size(); i++){
        if (out.first.first   > _punch[i].first)  out.first.first   = _punch[i].first;
        if (out.first.second  > _punch[i].second) out.first.second  = _punch[i].second;
        if (out.second.first  < _punch[i].first)  out.second.first  = _punch[i].first;
        if (out.second.second < _punch[i].second) out.second.second = _punch[i].second;
    }
    return out;
}
