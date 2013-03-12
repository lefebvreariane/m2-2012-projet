#ifndef SCENE_H
#define SCENE_H

#include <QWidget>
#include <QString>
#include <QFile>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomNode>

class XmlScene : public QWidget
{
    Q_OBJECT
public:
    XmlScene(QString filePath, QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // SCENE_H
