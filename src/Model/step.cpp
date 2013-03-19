#include "step.h"

Step::Step(QObject *parent) : QObject(parent){
}
Step::Step(const Step &step) : QObject(step.parent()){
    this->_punch = step.punch();
    this->_sheet = step.sheet();
}
