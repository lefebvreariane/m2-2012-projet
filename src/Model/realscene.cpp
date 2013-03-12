#include "realscene.h"

RealScene::RealScene(QString xmlFilePath, QObject *parent) : QObject(parent){
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

void RealScene::fillUnits       (QDomElement e){
    QDomNode node = e.firstChild();
    while (!node.isNull()){
        QDomElement elt = node.toElement();
        if (elt.tagName() == "time"){
            uniteTemps      = elt.attribute("timeUnit");
            duree           = elt.attribute("duration").toInt();
        } else if (elt.tagName() == "distance"){
            uniteDistance   = elt.attribute("distanceUnit");
            axeX            = elt.attribute("xAxis").toInt();
            axeY            = elt.attribute("yAxis").toInt();
        }
        node = node.nextSibling();
    }
}
void RealScene::fillMatrice     (QDomElement e){
    QDomNode node = e.firstChild();
    while (!node.isNull()){
        QDomElement elt = node.toElement();
        addMatrice(make_pair(elt.attribute("x").toInt(), elt.attribute("y").toInt()));
        node = node.nextSibling();
    }
    if (e.attribute("closedMatrix") == "False")
        addMatrice(make_pair(e.firstChild().toElement().attribute("x").toInt(), e.firstChild().toElement().attribute("y").toInt()));
}
void RealScene::fillDevetisseur (QDomElement e){
    QDomNode node = e.firstChild();
    int i(0);
    while (!node.isNull()){
        QDomElement elt = node.toElement();
        QDomNode tmpNode = elt.firstChild();
        while (!tmpNode.isNull()){
            QDomElement tmpElt = tmpNode.toElement();
            addDevetisseur(i, make_pair(tmpElt.attribute("x").toInt(), tmpElt.attribute("y").toInt()));
            tmpNode = tmpNode.nextSibling();
        }
        node = node.nextSibling();
    }
}
void RealScene::fillPoincon     (QDomElement e){
    QDomNode node = e.firstChild();
    while (!node.isNull()){
        QDomElement elt = node.toElement();
        if (elt.tagName() == "point")
            addPoicon(make_pair(elt.attribute("x").toInt(), elt.attribute("y").toInt()));
        else if (elt.tagName() == "transformation") {NULL;}
        else if (elt.tagName() == "rotation")       {NULL;}
        node = node.nextSibling();
    }
}
void RealScene::fillTole        (QDomElement e){
    QDomNode node = e.firstChild();
    while (!node.isNull()){
        QDomElement elt = node.toElement();
        addTole(make_pair(elt.attribute("x").toInt(), elt.attribute("y").toInt()));
        node = node.nextSibling();
    }
    epaisseurTole = e.attribute("thickness").toInt();
}
