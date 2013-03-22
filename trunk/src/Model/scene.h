#ifndef REALSCENE_H
#define REALSCENE_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomNode>
#include <iostream>
#include <cmath>
#include <vector>
using std::vector;
using std::pair;
using std::make_pair;
using std::cout;
using std::endl;

class Scene : public QObject {
    Q_OBJECT
    vector<pair<double, double> >                                                _matrix;
    vector<pair<vector<pair<double, double> >, vector<pair<double, double> > > > _strippers;
    pair<vector<pair<double, double> >, vector<pair<double, double> > >          _punch;
    pair<vector<pair<double, double> >, vector<pair<double, double> > >          _sheet;
    double                                                                       _thickness;

    vector<vector<pair<double, double> > > _sheetNeutralFibers;
    vector<vector<pair<double, double> > > _sheetBorders;
    vector<pair<double, double> > _sheetArea;
public:
    // Constructeurs & destructeur
    Scene(const Scene &scene);
    explicit Scene(QString xmlFilePath, QObject *parent=0);
    virtual ~Scene(){}
    // Getters
    vector<pair<double, double> >                                                matrix()    const {return _matrix;}
    vector<pair<vector<pair<double, double> >, vector<pair<double, double> > > > strippers() const {return _strippers;}
    pair<vector<pair<double, double> >, vector<pair<double, double> > >          punch()     const {return _punch;}
    pair<vector<pair<double, double> >, vector<pair<double, double> > >          sheet()     const {return _sheet;}
    double                                                                       thickness() const {return _thickness;}
    pair<pair<double, double>, pair<double, double> >                            min_max();

    vector<vector<pair<double, double> > > triangleMatrix();
private:
    void fillUnits       (QDomElement);
    void fillMatrice     (QDomElement);
    void fillStrippers   (QDomElement);
    void fillStripper    (QDomElement, int);
    void fillStripperUtil(QDomElement, int , bool);
    void fillPunch       (QDomElement);
    void fillPunchUtil   (QDomElement, bool);
    void fillSheet       (QDomElement);
    void fillSheetUtil   (QDomElement, bool);

    static pair<double, double> intersection(pair<pair<double, double>, pair<double, double> > a, pair<pair<double, double>, pair<double, double> > b);
};

#endif // REALSCENE_H
