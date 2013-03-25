#include "fakesimu.h"
#include <cassert>

fakeSimu::fakeSimu(Scene *scene, QObject *parent) : QObject(parent){
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


    scene->fillAll(_matrix, _punch, _stripper, _sheetGeom, _sheetNeut, _thickness);
    // --------------------
    // increase the resolution of the metalSheet
    if (scene->sheet().second.size() == 4){
        scene->increase_resolution_sheet();
    }
    // --------------------
    for (int i=0; i<_time*_fps; i++){
        scene->addStep(generateStep(i, scene));
    }
}

fakeSimu::fakeSimu(vector<pair<double, double> > matrix, vector<pair<double, double> > punch, vector<pair<double, double> > stripper, vector<pair<double, double> > geom, vector<pair<double, double> > neut, QObject *parent):
    QObject(parent), _matrix(matrix), _punch(punch), _stripper(stripper), _sheetGeom(geom), _sheetNeut(neut){}

static double distanceTemps(double temps, double tempsMax, double distanceMax){
    return -distanceMax/2*cos(2*PI*temps/tempsMax)+distanceMax/2;
}

Step* fakeSimu::generateStep(int id, Scene *scene){
    int frames = _time*_fps;
    assert(id>=0 && id<=frames);
    double punchMove = distanceTemps((1000/_fps)*id, _time*1000, _punchDistance);

    // fill the punch
    vector<pair<double, double> > punch;
    for (unsigned int i=0; i<_punch.size(); i++)
        punch.push_back(make_pair(_punch[i].first, _punch[i].second-punchMove));

    // fill the sheet
    pair<vector<pair<double, double> >,vector<pair<double, double> > > sheet;
    for (unsigned int i=0; i<scene->sheet().second.size(); i++)
        sheet.first.push_back(make_pair(scene->sheet().second[i].first, scene->sheet().second[i].second));
    for (unsigned int i=0; i<scene->sheet().first.size(); i++)
        sheet.second.push_back(make_pair(scene->sheet().first[i].first, scene->sheet().first[i].second));

    // create the step
    Step *step = new Step(punch, sheet);
    return step;
}

pair<double, double> fakeSimu::getRotationPoint(Scene *scene){
    double x(scene->matrix()[0].first);
    for (unsigned int i=0; i<scene->matrix().size(); i++)
        if (scene->matrix()[i].first > x)
            x = scene->matrix()[i].first;
    pair<double, double> out = make_pair(x+.5, .5);
    return out;
}

void fakeSimu::applyRotation(Scene *scene){
    pair<double, double> centre = getRotationPoint(scene);
    int firstFrame(9), lastFrame(30);
    for (int i=firstFrame; i<=lastFrame+1; i++){
        double deg = -95 * (i-firstFrame)/(lastFrame-firstFrame);
        deg = PI * deg / 180;
        vector<pair<double, double> > neut = scene->steps()[i]->sheetNeut();
        for (unsigned int j=0; j<neut.size(); j++){
            if (neut[j].first > centre.first){
                double dist = sqrt(pow(centre.first-neut[j].first, 2) + pow(centre.second-neut[j].second, 2));
                scene->steps()[i]->setSheetNeut(j, make_pair(dist*cos(deg)+centre.first, dist*sin(deg)+centre.second));
            }
        }
        vector<pair<double, double> > geom = scene->steps()[i]->sheetGeom();
        for (unsigned int j=0; j<geom.size(); j++){
            if (geom[j].first > centre.first-.5 && j<=geom.size()/2){
                double dist = sqrt(pow(centre.first-.5-geom[j].first, 2) + pow(centre.second-.5-geom[j].second, 2));
                scene->steps()[i]->setSheetGeom(j, make_pair(dist*cos(deg)+centre.first-.5, dist*sin(deg)+centre.second-.5));
            }
            if(geom[j].first > centre.first+.5 && j>=geom.size()/2){
                double dist = sqrt(pow(centre.first+.5-geom[j].first, 2) + pow(centre.second+.5-geom[j].second, 2));
                scene->steps()[i]->setSheetGeom(j, make_pair(dist*cos(deg)+centre.first+.5, dist*sin(deg)+centre.second+.5));
            }
        }
    }
    vector<pair<double, double> > neut = scene->steps()[lastFrame-1]->sheetNeut();
    vector<pair<double, double> > geom = scene->steps()[lastFrame-1]->sheetGeom();
    for (unsigned int i=lastFrame; i<scene->steps().size(); i++)
        scene->steps()[i]->replaceSheet(neut, geom);
}
