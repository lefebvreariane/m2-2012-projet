#include "scene.h"
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
//        cout << elt.tagName().toStdString() << endl;
        // Remplissage de la matrice.
        if (elt.tagName() == "matrix") this->fillMatrice(elt);
        else if (elt.tagName() == "strippers") this->fillStrippers(elt);
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
        _strippers.resize(i+1);
        fillStripper(elt, i);
        node = node.nextSibling();
    }
}
void Scene::fillStripper(QDomElement e, int i){
    QDomNode node = e.firstChild();
    while (!node.isNull()){
        QDomElement elt = node.toElement();
        if (elt.tagName() == "up")
            fillStripperUtil(elt, i, true);
        else if (elt.tagName() == "down")
            fillStripperUtil(elt, i, false);
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
        cout << elt.tagName().toStdString() << endl;
        if (elt.tagName() == "geometry") fillSheetUtil(elt, false);
        else fillSheetUtil(elt, true);
        node = node.nextSibling();
    }
}
void Scene::fillSheetUtil(QDomElement e, bool geometry){
    QDomNode node = e.firstChild();
    while (!node.isNull()){
        QDomElement elt = node.toElement();
        cout << elt.tagName().toStdString() << endl;
        if (geometry) _sheet.first.push_back(make_pair(elt.attribute("x").toDouble(), elt.attribute("y").toDouble()));
        else _sheet.second.push_back(make_pair(elt.attribute("x").toDouble(), elt.attribute("y").toDouble()));
        node = node.nextSibling();
    }
}

pair<pair<double, double> > Scene::min_max(){
    pair<pair<double, double> > out = make_pair(
                make_pair(numeric_limits<double>::max(), numeric_limits<double>::max()),
                make_pair(numeric_limits<double>::min(), numeric_limits<double>::min()));
    for (unsigned int i=0; i<_matrix.size(); i++){
        if (out.first.first   > _matrix[i].first)  out.first.first   = _matrix[i].first;
        if (out.first.second  > _matrix[i].second) out.first.second  = _matrix[i].second;
        if (out.second.first  < _matrix[i].first)  out.second.first  = _matrix[i].first;
        if (out.second.second < _matrix[i].second) out.second.second = _matrix[i].second;
    }
    return out;
}
