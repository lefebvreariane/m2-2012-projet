#ifndef REALSCENE_H
#define REALSCENE_H

#include <QObject>
#include <iostream>
#include <vector>
using std::vector;
using std::pair;
class RealScene : public QObject {
    Q_OBJECT
    vector<pair<float, float> > _matrice;
    vector<pair<float, float> > _devetisseur;
    vector<pair<float, float> > _poincon;
    vector<pair<float, float> > _tole;
public:
    // Constructeur & destructeur
    explicit RealScene(
            vector<pair<float, float> > matrice,
            vector<pair<float, float> > devetisseur,
            vector<pair<float, float> > poincon,
            vector<pair<float, float> > tole,
            QObject *parent = 0) : QObject(parent), _matrice(matrice), _devetisseur(devetisseur), _poincon(poincon), _tole(tole){}
    virtual ~RealScene(){}
    // Modifieurs
    virtual void addMatrice(pair<float, float> p)       {_matrice.push_back(p);}
    virtual void addDevetisseur(pair<float, float> p)   {_devetisseur.push_back(p);}
    virtual void addPoicon(pair<float, float> p)        {_poincon.push_back(p);}
    virtual void addTole(pair<float, float> p)          {_tole.push_back(p);}
    // Accesseurs
    virtual const vector<pair<float, float> > matrice()     const {return _matrice;}
    virtual const vector<pair<float, float> > devetisseur() const {return _devetisseur;}
    virtual const vector<pair<float, float> > poincon()     const {return _poincon;}
    virtual const vector<pair<float, float> > tole()        const {return _tole;}
    virtual void resetTole() {_tole.clear();}
signals:
    
public slots:
    
};

#endif // REALSCENE_H
