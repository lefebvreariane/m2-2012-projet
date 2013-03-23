#include "fakesimu.h"

fakeSimu::fakeSimu(QObject *parent) : QObject(parent){
    _matrix.push_back(make_pair(7.45  ,  0.00));
    _matrix.push_back(make_pair(-10.00,  0.00));
    _matrix.push_back(make_pair(-10.00,  -10.00));
    _matrix.push_back(make_pair(8.45  ,  -10.00));
    _matrix.push_back(make_pair(8.45  ,  -1.00));
    _matrix.push_back(make_pair(8.45  ,  -0.92));
    _matrix.push_back(make_pair(8.44  ,  -0.84));
    _matrix.push_back(make_pair(8.43  ,  -0.77));
    _matrix.push_back(make_pair(8.40  ,  -0.69));
    _matrix.push_back(make_pair(8.38  ,  -0.62));
    _matrix.push_back(make_pair(8.34  ,  -0.55));
    _matrix.push_back(make_pair(8.31  ,  -0.48));
    _matrix.push_back(make_pair(8.26  ,  -0.41));
    _matrix.push_back(make_pair(8.21  ,  -0.35));
    _matrix.push_back(make_pair(8.16  ,  -0.29));
    _matrix.push_back(make_pair(8.10  ,  -0.24));
    _matrix.push_back(make_pair(8.04  ,  -0.19));
    _matrix.push_back(make_pair(7.98  ,  -0.15));
    _matrix.push_back(make_pair(7.91  ,  -0.11));
    _matrix.push_back(make_pair(7.84  ,  -0.08));
    _matrix.push_back(make_pair(7.76  ,  -0.05));
    _matrix.push_back(make_pair(7.69  ,  -0.03));
    _matrix.push_back(make_pair(7.61  ,  -0.01));
    _matrix.push_back(make_pair(7.53  ,  -0.00));

    _stripper.push_back(make_pair(9.45  ,  6.0));
    _stripper.push_back(make_pair(-10.00,  6.0));
    _stripper.push_back(make_pair(-10.00,  1.0));
    _stripper.push_back(make_pair(9.45  ,  1.0));

    _punch.push_back(make_pair(19.45,  1.50));
    _punch.push_back(make_pair(19.45,  16.50));
    _punch.push_back(make_pair(9.45,  16.50));
    _punch.push_back(make_pair(9.45,  2.50));
    _punch.push_back(make_pair(9.46,  2.42));
    _punch.push_back(make_pair(9.47,  2.34));
    _punch.push_back(make_pair(9.48,  2.27));
    _punch.push_back(make_pair(9.50,  2.19));
    _punch.push_back(make_pair(9.53,  2.12));
    _punch.push_back(make_pair(9.56,  2.05));
    _punch.push_back(make_pair(9.60,  1.98));
    _punch.push_back(make_pair(9.64,  1.91));
    _punch.push_back(make_pair(9.69,  1.85));
    _punch.push_back(make_pair(9.75,  1.79));
    _punch.push_back(make_pair(9.80,  1.74));
    _punch.push_back(make_pair(9.87,  1.69));
    _punch.push_back(make_pair(9.93,  1.65));
    _punch.push_back(make_pair(10.00,  1.61));
    _punch.push_back(make_pair(10.07,  1.58));
    _punch.push_back(make_pair(10.14,  1.55));
    _punch.push_back(make_pair(10.22,  1.53));
    _punch.push_back(make_pair(10.30,  1.51));
    _punch.push_back(make_pair(10.37,  1.50));
    _punch.push_back(make_pair(10.45,  1.50));

    _sheetGeom.push_back(make_pair(-17.55, 1.00));
    _sheetGeom.push_back(make_pair(-17.55, 0.00));
    _sheetGeom.push_back(make_pair(17.50, 0.00));
    _sheetGeom.push_back(make_pair(17.50, 1.00));

    _sheetNeut.push_back(make_pair(-17.55, 0.50));
    _sheetNeut.push_back(make_pair(17.50, 0.50));

    _thickness = 1;
    _time = 5;
    _fps = 25;
    _punchDistance = 10;

    _scene = new Scene(_matrix, _punch, _stripper, _sheetGeom, _sheetNeut, _thickness);
    for (int i=0; i<_time*_fps; i++)
        _scene->addStep(generateStep(i));
}

fakeSimu::fakeSimu(vector<pair<double, double> > matrix, vector<pair<double, double> > punch, vector<pair<double, double> > stripper, vector<pair<double, double> > geom, vector<pair<double, double> > neut, QObject *parent):
    QObject(parent), _matrix(matrix), _punch(punch), _stripper(stripper), _sheetGeom(geom), _sheetNeut(neut){}

static double distanceTemps(double temps, double tempsMax, double distanceMax){
    return -distanceMax/2*cos(2*PI*temps/tempsMax)+distanceMax/2;
}

Step* fakeSimu::generateStep(int id){
    int frames = _time*_fps;
    assert(id>=0 && id<=frames);

    vector<pair<double, double> > punch;
    double punchMove = distanceTemps(id, _time, _punchDistance);
    for (unsigned int i=0; i<_punch.size(); i++)
        punch.push_back(make_pair(_punch[i].first, _punch[i].second+punchMove));

    Step *step = new Step(punch);
    return step;
}
