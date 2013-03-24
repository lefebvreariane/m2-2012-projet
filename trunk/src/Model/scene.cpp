#include "scene.h"
#include <limits>
#include <cmath>
#include <cstdlib>
#include <cassert>
#define PI atan(1)*4
Scene::Scene(const Scene &scene) : QObject(scene.parent()){
    this->_matrix = scene.matrix();
    this->_strippers = scene.strippers();
    this->_punch = scene.punch();
    this->_sheet = scene.sheet();
    this->_thickness = scene.thickness();
}

Scene::Scene(vector<pair<double, double> > matrix, vector<pair<double, double> > punch, vector<pair<double, double> > stripper, vector<pair<double, double> > geom, vector<pair<double, double> > neut, int thickness)
    : _matrix(matrix), _thickness(thickness){

    _punch.first = punch;
    _punch.second = punch;

    _strippers.resize(1);
    _strippers[0].first = stripper;
    _strippers[0].second = stripper;

    _sheet.first = geom;
    _sheet.second = neut;
}

Scene::Scene(QString xmlFilePath, QObject *parent) : QObject(parent){
    QDomDocument domDocument;
    QFile file(xmlFilePath);
    if (!file.open(QIODevice::ReadOnly))
        return;
    if (!domDocument.setContent(&file))
    {
        file.close();
        return;
    }
    QDomElement racine(domDocument.documentElement());
    QDomNode node = racine.firstChild();
    while (!node.isNull()){
        QDomElement elt = node.toElement();
        if (elt.tagName() == "matrix") this->fillMatrice(elt);
        else if (elt.tagName() == "strippers"){
            _strippers.resize(node.childNodes().size());
            this->fillStrippers(elt);
        }
        else if (elt.tagName() == "punch") this->fillPunch(elt);
        else if (elt.tagName() == "sheet") this->fillSheet(elt);
        node = node.nextSibling();
    }
    vector<vector<pair<double, double> > > test = triangleMatrix();
}

void Scene::fillAll(vector<pair<double, double> > matrix, vector<pair<double, double> > punch, vector<pair<double, double> > stripper, vector<pair<double, double> > geom, vector<pair<double, double> > neut, int thickness){
    _matrix = matrix;

    _punch.first = punch;
    _punch.second = punch;

    _strippers.resize(1);
    _strippers[0].first = stripper;
    _strippers[0].second = stripper;

    _sheet.second = geom;
    _sheet.first = neut;

    _thickness = thickness;
}

void Scene::fillMatrice(QDomElement e){
    QDomNode node = e.firstChild();
    while (!node.isNull()){
        QDomElement elt = node.toElement();
        _matrix.push_back(make_pair(elt.attribute("x").toDouble(), elt.attribute("y").toDouble()));
        node = node.nextSibling();
    }
}

void Scene::fillStrippers(QDomElement e){
    QDomNode node = e.firstChild();
    int i=0;
    while (!node.isNull()){
        QDomElement elt = node.toElement();
        fillStripper(elt, i);
        node = node.nextSibling();
    }
}
void Scene::fillStripper(QDomElement e, int i){
    QDomNode node = e.firstChild();
    while (!node.isNull()){
        QDomElement elt = node.toElement();
        if (elt.tagName() == "up") fillStripperUtil(elt, i, true);
        else fillStripperUtil(elt, i, false);
        node = node.nextSibling();
    }
}
void Scene::fillStripperUtil(QDomElement e, int i, bool up){
    QDomNode node = e.firstChild();
    while (!node.isNull()){
        QDomElement elt = node.toElement();
        if (up) _strippers[i].first.push_back(make_pair(elt.attribute("x").toDouble(), elt.attribute("y").toDouble()));
        else _strippers[i].second.push_back(make_pair(elt.attribute("x").toDouble(), elt.attribute("y").toDouble()));
        node = node.nextSibling();
    }
}

void Scene::fillPunch(QDomElement e){
    QDomNode node = e.firstChild();
    while (!node.isNull()){
        QDomElement elt = node.toElement();
        if (elt.tagName() == "up") fillPunchUtil(elt, false);
        else fillPunchUtil(elt, true);
        node = node.nextSibling();
    }
}
void Scene::fillPunchUtil(QDomElement e, bool up){
    QDomNode node = e.firstChild();
    while (!node.isNull()){
        QDomElement elt = node.toElement();
        if (up) _punch.first.push_back(make_pair(elt.attribute("x").toDouble(), elt.attribute("y").toDouble()));
        else _punch.second.push_back(make_pair(elt.attribute("x").toDouble(), elt.attribute("y").toDouble()));
        node = node.nextSibling();
    }
}

void Scene::fillSheet(QDomElement e){
    _thickness = e.attribute("thickness").toDouble();
    QDomNode node = e.firstChild();
    while (!node.isNull()){
        QDomElement elt = node.toElement();
        if (elt.tagName() == "geometry") fillSheetUtil(elt, false);
        else fillSheetUtil(elt, true);
        node = node.nextSibling();
    }
}
void Scene::fillSheetUtil(QDomElement e, bool geometry){
    QDomNode node = e.firstChild();
    while (!node.isNull()){
        QDomElement elt = node.toElement();
        if (geometry) _sheet.first.push_back(make_pair(elt.attribute("x").toDouble(), elt.attribute("y").toDouble()));
        else _sheet.second.push_back(make_pair(elt.attribute("x").toDouble(), elt.attribute("y").toDouble()));
        node = node.nextSibling();
    }
}

pair<pair<double, double>, pair<double, double> > Scene::min_max(){
    pair<pair<double, double>, pair<double, double> > out = make_pair(
                make_pair(std::numeric_limits<double>::max(), std::numeric_limits<double>::max()),
                make_pair(std::numeric_limits<double>::min(), std::numeric_limits<double>::min()));
    for (unsigned int i=0; i<_matrix.size(); i++){
        if (out.first.first   > _matrix[i].first)  out.first.first   = _matrix[i].first;
        if (out.first.second  > _matrix[i].second) out.first.second  = _matrix[i].second;
        if (out.second.first  < _matrix[i].first)  out.second.first  = _matrix[i].first;
        if (out.second.second < _matrix[i].second) out.second.second = _matrix[i].second;
    }
    for (unsigned int i=0; i<_strippers.size(); i++){
        pair<vector<pair<double, double> >, vector<pair<double, double> > > tmpP = _strippers[i];
        vector<pair<double, double> > v1(tmpP.first), v2(tmpP.second);
        for (unsigned int i=0; i<v1.size(); i++){
            if (out.first.first   > v1[i].first)  out.first.first   = v1[i].first;
            if (out.first.second  > v1[i].second) out.first.second  = v1[i].second;
            if (out.second.first  < v1[i].first)  out.second.first  = v1[i].first;
            if (out.second.second < v1[i].second) out.second.second = v1[i].second;
            if (out.first.first   > v2[i].first)  out.first.first   = v2[i].first;
            if (out.first.second  > v2[i].second) out.first.second  = v2[i].second;
            if (out.second.first  < v2[i].first)  out.second.first  = v2[i].first;
            if (out.second.second < v2[i].second) out.second.second = v2[i].second;
        }
    }
    for (unsigned int i=0; i<_punch.first.size(); i++){
        if (out.first.first   > _punch.first[i].first)   out.first.first   = _punch.first[i].first;
        if (out.first.second  > _punch.first[i].second)  out.first.second  = _punch.first[i].second;
        if (out.second.first  < _punch.first[i].first)   out.second.first  = _punch.first[i].first;
        if (out.second.second < _punch.first[i].second)  out.second.second = _punch.first[i].second;
        if (out.first.first   > _punch.second[i].first)  out.first.first   = _punch.second[i].first;
        if (out.first.second  > _punch.second[i].second) out.first.second  = _punch.second[i].second;
        if (out.second.first  < _punch.second[i].first)  out.second.first  = _punch.second[i].first;
        if (out.second.second < _punch.second[i].second) out.second.second = _punch.second[i].second;
    }
    for (unsigned int i=0; i<_sheet.first.size(); i++){
        if (out.first.first   > _sheet.first[i].first)   out.first.first   = _sheet.first[i].first;
        if (out.first.second  > _sheet.first[i].second)  out.first.second  = _sheet.first[i].second;
        if (out.second.first  < _sheet.first[i].first)   out.second.first  = _sheet.first[i].first;
        if (out.second.second < _sheet.first[i].second)  out.second.second = _sheet.first[i].second;
        if (out.first.first   > _sheet.second[i].first)  out.first.first   = _sheet.second[i].first;
        if (out.first.second  > _sheet.second[i].second) out.first.second  = _sheet.second[i].second;
        if (out.second.first  < _sheet.second[i].first)  out.second.first  = _sheet.second[i].first;
        if (out.second.second < _sheet.second[i].second) out.second.second = _sheet.second[i].second;
    }
    return out;
}
static pair<double, double> segmentToVecteur(pair<pair<double, double>, pair<double, double> > s){
    return make_pair(s.second.first-s.first.first, s.second.second-s.first.second);
}

static double radToDeg(double in){
    return in * 180. / PI;
}

static pair<double, double> intersection(
        pair<pair<double, double>, pair<double, double> > a,
        pair<pair<double, double>, pair<double, double> > b){

    if (std::max(a.first.first, a.second.first) < std::min(b.first.first, b.second.first))
        return make_pair(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());

    double a1 = (a.first.second-a.second.second)/(a.first.first-a.second.first);
    double a2 = (b.first.second-b.second.second)/(b.first.first-b.second.first);
    double b1 = a.first.second - a1*a.first.first;
    double b2 = b.first.second - a2*b.first.first;

    if (a1 == a2)
        return make_pair(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());

    double xa  = (b2-b1)/(a1-a2);
    double ya1 = a1 * xa + b1;
    double ya2 = a2 * xa + b2;

    if ((xa < std::max(std::min(a.first.first, a.second.first), std::min(b.first.first, b.second.first))) ||
            (xa > std::min(std::max(a.first.first, a.second.first), std::max(b.first.first, b.second.first))))
        return make_pair(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());

    if (ya1 != ya2) return make_pair(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    else return make_pair(xa, ya1);
}

static vector<pair<pair<double, double>, pair<double, double> > > pointsToSegments(vector<pair<double, double> > in){
    vector<pair<pair<double, double>, pair<double, double> > > out;
    for (unsigned int i=0; i<in.size()-1; i++)
        out.push_back(make_pair(in[i], in[i+1]));
    out.push_back(make_pair(in[in.size()-1], in[0]));
    return out;
}

static void safeInsert(pair<pair<double, double>, pair<double, double> > s, vector<pair<pair<double, double>, pair<double, double> > > &t){
    bool b = false;
    for (unsigned int i=0; i<t.size(); i++){
        if (s.first.first == t[i].first.first && s.first.second == t[i].first.second && s.second.first == t[i].second.first && s.second.second == t[i].second.second)
            b = true;
        if (s.first.first == t[i].second.first && s.first.second == t[i].second.second && s.second.first == t[i].first.first && s.second.second == t[i].first.second)
            b = true;
        if (b) break;
    }
    if (!b) t.push_back(s);
}

static double angleVecteur(pair<double, double> v){
    double x = v.first;
    double y = v.second;
    double res = atan2(abs(y),abs(x));
    if(x<0 && y>0)
        res += PI/2;
    else if(x<0 && y<0)
        res += PI;
    else if (x>0 && y<0)
        res += 3*PI/2;
    else if (x==0 || y==0)
        res += PI;
    return res;
}

static bool isConvexe(pair<pair<double, double>, pair<double, double> > a, pair<pair<double, double>, pair<double, double> > b){
    pair<double, double> aa = segmentToVecteur(a);
    pair<double, double> bb = segmentToVecteur(b);
    double alpha = radToDeg(angleVecteur(aa));
    double beta  = radToDeg(angleVecteur(bb));
    if (beta<alpha)
        return 360 - alpha + beta <= 180;
    return beta-alpha <= 180;
}

static bool isConvexe(vector<pair<double, double> > in){
    pair<pair<double, double>, pair<double, double> > a = make_pair(in[0], in[1]);
    pair<pair<double, double>, pair<double, double> > b = make_pair(in[1], in[2]);
    return isConvexe(a,b);
}

static bool isConvexe(vector<pair<pair<double, double>, pair<double, double> > > in){
    return isConvexe(in[0], in[1]);
}

static vector<pair<pair<double, double>, pair<double, double> > > addSegments(vector<pair<pair<double, double>, pair<double, double> > > in){
    vector<pair<pair<double, double>, pair<double, double> > > out = in;
    for (unsigned int i=0; i<in.size()-1; i++){
        for (unsigned int j=i+1; j<out.size(); j++){
            if (in[i].first != out[j].second && isConvexe(in[i], out[j])){
                pair<pair<double, double>, pair<double, double> > toCreate = make_pair(in[i].first, out[j].second);
                bool intersec = false;
                for (unsigned int k=0; k<out.size(); k++){
                    if (intersection(toCreate, out[k]) != make_pair(std::numeric_limits<double>::max(), std::numeric_limits<double>::max()))
                        intersec = true;
                }
                if (!intersec){
                    safeInsert(toCreate, out);
                }
            }
        }
    }
    return out;
}

static bool connected(pair<pair<double, double>, pair<double, double> > a, pair<pair<double, double>, pair<double, double> > b){
    return (a.first == b.first || a.first == b.second || a.second == b.first || a.second == b.second) &&
            ((a.first != b.first && a.second != b.second) || (a.first != b.second && a.second == b.first));
}

static vector<vector<pair<pair<double, double>, pair<double, double> > > > segmentsToTriangles(vector<pair<pair<double, double>, pair<double, double> > > in){
    vector<vector<pair<pair<double, double>, pair<double, double> > > > out;
    for (unsigned int i=0; i<in.size(); i++){
        for (unsigned int j=0; j<in.size(); j++){
            for (unsigned int k=0; k<in.size(); k++){
                if (connected(in[i], in[j]) && connected(in[i], in[k]) && connected(in[j], in[k])){
                    vector<pair<pair<double, double>, pair<double, double> > > tmp;
                    tmp.push_back(in[i]);
                    tmp.push_back(in[j]);
                    tmp.push_back(in[k]);
                    out.push_back(tmp);
                    if (i != j && j != k && k != i){
                        if (in[i].second == in[j].first && in[j].second == in[j].first && in[k].second == in[i].first){
                            vector<pair<pair<double, double>, pair<double, double> > > tmp;
                            tmp.push_back(in[i]);
                            tmp.push_back(in[j]);
                            tmp.push_back(in[k]);
                            if (!isConvexe(tmp))
                                out.push_back(tmp);
                        } else if(in[i].second == in[k].first && in[k].second == in[j].first && in[j].second == in[i].first){
                            vector<pair<pair<double, double>, pair<double, double> > > tmp;
                            tmp.push_back(in[i]);
                            tmp.push_back(in[k]);
                            tmp.push_back(in[j]);
                            if (!isConvexe(tmp))
                                out.push_back(tmp);
                        }
                    }
                }
            }
        }
    }
    return out;
}

static vector<pair<double, double> > cleanTriangle(vector<pair<pair<double, double>, pair<double, double> > > in){
    pair<double, double> p1 = in[0].first;
    pair<double, double> p2 = in[0].second;
    pair<double, double> p3;
    if      (in[1].first != p1 && in[1].first != p2)   p3 = in[1].first;
    else if (in[2].first != p1 && in[2].first != p2)   p3 = in[2].first;
    else if (in[1].second != p1 && in[1].second != p2) p3 = in[1].second;
    else if (in[2].second != p1 && in[2].second != p2) p3 = in[2].second;
    assert(p1 != p2 && p2 != p3 && p3 != p1);
    vector<pair<double, double> > out;
    out.push_back(p1);
    out.push_back(p2);
    out.push_back(p3);
    if (!isConvexe(out)){
        out[0] = p3;
        out[2] = p1;
    }
    return out;
}

vector<vector<pair<double, double> > > Scene::triangleMatrix(){
    vector<pair<pair<double, double>, pair<double, double> > > tmp = pointsToSegments(_matrix);
    vector<pair<pair<double, double>, pair<double, double> > > tmp2 = addSegments(tmp);
    vector<vector<pair<pair<double, double>, pair<double, double> > > > tmp3 = segmentsToTriangles(tmp2);
    vector<vector<pair<double, double> > > out;
    for (unsigned int i=0; i<tmp3.size(); i++){
        out.push_back(cleanTriangle(tmp3[i]));
    }
    return out;
}

void Scene::increase_resolution_sheet(){
    vector<pair<double, double> > tmpGeom;
    vector<pair<double, double> > tmpNeut;
    float distX = _sheet.second[1].first - _sheet.second[0].first; // distX = x2 - x1

    tmpGeom.push_back(_sheet.second[1]);
    tmpNeut.push_back(_sheet.first[0]);
    float spanX = distX/125;
    pair<double,double> point;
    for (unsigned int j=1 ; j<125 ; j++){
        point.first = _sheet.second[1].first+j*spanX;
        point.second = _sheet.second[1].second;
        tmpGeom.push_back(point);
        point.first = _sheet.first[0].first+j*spanX;
        point.second = _sheet.first[0].second;
        tmpNeut.push_back(point);
    }
    _sheet.first = tmpNeut;
    tmpGeom.push_back(_sheet.second[2]);
    tmpGeom.push_back(_sheet.second[3]);
    for (unsigned int j=1 ; j<125 ; j++){
        point.first = _sheet.second[3].first-j*spanX;
        point.second = _sheet.second[3].second;
        tmpGeom.push_back(point);
    }
    tmpGeom.push_back(_sheet.second[0]);
    _sheet.second = tmpGeom;
}

int Scene::tracking(float pointOld[2], int step){
    pair<double,double> pointNew = steps()[step]->sheet()[0];
    int indice, distMin, dist;
    distMin = indice = dist = 0;
    // search the nearest point on the sheet
    distMin = sqrt(pow(pointNew.first-pointOld[0],2)+pow(pointNew.second-pointOld[1],2));
    for (unsigned int i=0 ; i<steps()[step]->sheet().size() ; i++){
        pointNew = steps()[step]->sheet()[i];
        dist = sqrt(pow(pointNew.first-pointOld[0],2)+pow(pointNew.second-pointOld[1],2));
        if (distMin > dist){
            indice = i;
            distMin = dist;
        }
    }
    return indice;
}
