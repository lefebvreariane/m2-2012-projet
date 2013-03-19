#ifndef STEP_H
#define STEP_H

#include <QObject>
#include <iostream>
#include <vector>
using std::pair;
using std::vector;

class Step : public QObject{
    Q_OBJECT
    vector<pair<double, double> > _punch;
    vector<pair<double, double> > _sheet;
public:
    explicit Step(QObject *parent = 0);
    explicit Step(const Step &step);
    const vector<pair<double, double> > punch() const {return _punch;}
    const vector<pair<double, double> > sheet() const {return _sheet;}
};

#endif // STEP_H
