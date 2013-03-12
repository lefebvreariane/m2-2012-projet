#include "xmlscene.h"
#include <iostream>
using namespace std;

XmlScene::XmlScene(QString filePath, QWidget *parent) : QWidget(parent){
    QDomDocument doc(filePath);
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
        return;
    if (!doc.setContent(&file)) {
        file.close();
        return;
    }
    file.close();
    QDomElement docElem = doc.documentElement();

     QDomNode n = docElem.firstChild();
     while(!n.isNull()) {
         QDomElement e = n.toElement();
         if(!e.isNull()) {
             cout << qPrintable(e.tagName()) << endl;
         }
         n = n.nextSibling();
     }
}
