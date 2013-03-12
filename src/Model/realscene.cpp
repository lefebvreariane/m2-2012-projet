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
    QDomElement racine(domDocument.documentElement()), tmp;
    QDomNode noeud = racine.firstChild();
    while (!noeud.isNull()){
        tmp = noeud.toElement();
        cout << tmp.tagName().toStdString() << endl;
        if (tmp.tagName() == "units")
            fillUnits(tmp);
        else if (tmp.tagName() == "matrix")
            fillMatrice(tmp);
        else if (tmp.tagName() == "stripper")
            fillDevetisseur(tmp);
        else if (tmp.tagName() == "punch")
            fillPoincon(tmp);
        else if (tmp.tagName() == "sheet")
            fillTole(tmp);
        noeud = noeud.nextSibling();
    }
    file.close();
}

void RealScene::fillUnits       (QDomElement e){}
void RealScene::fillMatrice     (QDomElement e){}
void RealScene::fillDevetisseur (QDomElement e){}
void RealScene::fillPoincon     (QDomElement e){}
void RealScene::fillTole        (QDomElement e){}
