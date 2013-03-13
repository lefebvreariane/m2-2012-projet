#include "scene.h"
Scene::Scene(const Scene &scene) : QObject(scene.parent()){
    _matrice       = scene.matrice();
    _devetisseur   = scene.devetisseur();
    _poincon       = scene.poincon();
    _tole          = scene.tole();
    _uniteTemps    = scene.uniteTemps();
    _uniteDistance = scene.uniteDistance();
    _duree         = scene.duree();
    _axeX          = scene.axeX();
    _axeY          = scene.axeY();
    _epaisseurTole = scene.epaisseurTole();
    _xTranslation  = scene.xTranslation();
    _yTranslation  = scene.yTranslation();
    _xRotation     = scene.xRotation();
    _yRotation     = scene.yRotation();
    _angle         = scene.angle();
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
        cout << elt.tagName().toStdString() << endl;
        if (elt.tagName() == "units")
            fillUnits(elt);
        else if (elt.tagName() == "matrix")
            fillMatrice(elt);
        else if (elt.tagName() == "stripper")
            fillDevetisseur(elt);
        else if (elt.tagName() == "punch")
            fillPoincon(elt);
        else if (elt.tagName() == "sheet")
            fillTole(elt);
        node = node.nextSibling();
    }
    file.close();
}

void Scene::fillUnits       (QDomElement e){
    QDomNode node = e.firstChild();
    while (!node.isNull()){
        QDomElement elt = node.toElement();
        if (elt.tagName() == "time"){
            _uniteTemps      = elt.attribute("timeUnit");
            _duree           = elt.attribute("duration").toDouble();
        } else if (elt.tagName() == "distance"){
            _uniteDistance   = elt.attribute("distanceUnit");
            _axeX            = elt.attribute("xAxis").toDouble();
            _axeY            = elt.attribute("yAxis").toDouble();
        }
        node = node.nextSibling();
    }
}
void Scene::fillMatrice     (QDomElement e){
    QDomNode node = e.firstChild();
    while (!node.isNull()){
        QDomElement elt = node.toElement();
        addMatrice(make_pair(elt.attribute("x").toDouble(), elt.attribute("y").toDouble()));
        node = node.nextSibling();
    }
    if (e.attribute("closedMatrix") == "False")
        addMatrice(make_pair(e.firstChild().toElement().attribute("x").toDouble(), e.firstChild().toElement().attribute("y").toDouble()));
}

void Scene::fillDevetisseur (QDomElement e){
    QDomNode node = e.firstChild();
    int i(0);
    while (!node.isNull()){
        QDomElement elt = node.toElement();
        QDomNode tmpNode = elt.firstChild();
        while (!tmpNode.isNull()){
            QDomElement tmpElt = tmpNode.toElement();
            addDevetisseur(i, make_pair(tmpElt.attribute("x").toDouble(), tmpElt.attribute("y").toDouble()));
            tmpNode = tmpNode.nextSibling();
        }
        node = node.nextSibling();
    }
}
void Scene::fillPoincon     (QDomElement e){
    QDomNode node = e.firstChild();
    while (!node.isNull()){
        QDomElement elt = node.toElement();
        if (elt.tagName() == "point")
            addPoicon(make_pair(elt.attribute("x").toDouble(), elt.attribute("y").toDouble()));
        else if (elt.tagName() == "transformation") {
            _xTranslation = elt.attribute("xTranslation").toDouble();
            _yTranslation = elt.attribute("yTranslation").toDouble();
        }
        else if (elt.tagName() == "rotation")       {
            _xRotation = elt.attribute("xRotation").toDouble();
            _yRotation = elt.attribute("yRotation").toDouble();
            _angle     = elt.attribute("angle").toDouble();
        }
        node = node.nextSibling();
    }
}
void Scene::fillTole        (QDomElement e){
    QDomNode node = e.firstChild();
    while (!node.isNull()){
        QDomElement elt = node.toElement();
        addTole(make_pair(elt.attribute("x").toDouble(), elt.attribute("y").toDouble()));
        node = node.nextSibling();
    }
    _epaisseurTole = e.attribute("thickness").toDouble();
}

void Scene::save() const{
    QDomDocument domDocument;
    QDomNode xmlNode = domDocument.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    domDocument.insertBefore(xmlNode, domDocument.firstChild());
    QDomElement scene       = domDocument.createElement("scene");
    QDomElement units       = domDocument.createElement("units");
    QDomElement matrix      = domDocument.createElement("matrix");
    QDomElement stripper    = domDocument.createElement("stripper");
    QDomElement punch       = domDocument.createElement("punch");
    QDomElement sheet       = domDocument.createElement("sheet");
    scene.appendChild(units);
    scene.appendChild(matrix);
    scene.appendChild(stripper);
    scene.appendChild(punch);
    scene.appendChild(sheet);

    QDomElement time = domDocument.createElement("time");
    time.setAttribute("timeUnits", _uniteTemps);
    time.setAttribute("duration", _duree);
    QDomElement distance = domDocument.createElement("distance");
    distance.setAttribute("distanceUnit", _uniteDistance);
    distance.setAttribute("xAxis", _axeX);
    distance.setAttribute("yAxis", _axeY);
    units.appendChild(time);
    units.appendChild(distance);

    if (_matrice[0].first == _matrice[_matrice.size()-1].first && _matrice[0].second == _matrice[_matrice.size()-1].second)
        matrix.setAttribute("closedMatrix", "True");
    else matrix.setAttribute("closedMatrix", "False");
    for (unsigned int i=0; i<_matrice.size(); i++){
        QDomElement point = domDocument.createElement("point");
        point.setAttribute("x", _matrice[i].first);
        point.setAttribute("y", _matrice[i].second);
        matrix.appendChild(point);
    }

    if (_poincon[0].first == _poincon[_poincon.size()-1].first && _poincon[0].second == _poincon[_poincon.size()-1].second)
        punch.setAttribute("slosedPunch", "True");
    else punch.setAttribute("closedPunch", "False");
    for (unsigned int i=0; i<_poincon.size(); i++){
        QDomElement point = domDocument.createElement("point");
        point.setAttribute("x", _poincon[i].first);
        point.setAttribute("y", _poincon[i].second);
        punch.appendChild(point);
    }
    // TODO: inclure les rotations/translations

    sheet.setAttribute("thickness", _epaisseurTole);
    // TODO: contenu de la tôle à spécifier
}
