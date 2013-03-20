#include "scene.h"
#include <limits>
Scene::Scene(const Scene &scene) : QObject(scene.parent()){
    this->_matrix = scene.matrix();
    this->_strippers = scene.strippers();
    this->_punch = scene.punch();
    this->_sheet = scene.sheet();
    this->_thickness = scene.thickness();
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
