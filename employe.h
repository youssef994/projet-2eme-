#ifndef CLIENT_H
#define CLIENT_H
#include "ui_dialog.h"
#include"dialog.h"
#include<QString>
#include<QSqlDatabase>
#include<QSqlError>
#include<QSqlQuery>
#include<QFileInfo>
#include<QMessageBox>
#include<QSqlQueryModel>
#include<QDebug>
#include<QFileDialog>
#include<QDialog>


class Client
{
private :
QString id;
QString nom;
QString prenom;
QString cin;
QString numero;
QString date ;
QString sexe ;
public:
    Client(QString,QString,QString,QString,QString,QString,QString);
    Client();

    void setId(QString n){id=n;}
    void setNom(QString n){nom=n;}
    void setPrenom(QString n){prenom=n;}
    void setBudget(QString n){cin=n;}
    void setNumero(QString n){numero=n;}
    void setDate_mariage(QString n){date=n;}
    void setCategorie(QString n){sexe=n;}

    QString getID(){return id;}
    QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    QString getBudget(){return cin;}
    QString getNumero(){return numero;}
    QString getDate_mariage(){return date;}
    QString getCategorie(){return sexe;}

bool ajouterperso();
QSqlQueryModel *afficherperso();
bool modifierperso ();
bool supprimer(Ui::Dialog *ui);
void recherche(Ui::Dialog *ui);
void TRI1(Ui::Dialog *ui);
void TRI2(Ui::Dialog *ui);
bool verif_id(QString ch);
bool verif_nom(QString nom) ;
bool verif_prenom(QString prenom) ;
bool verif_numero(QString numero) ;
bool verif_date_mariage(QString date_mariage) ;






    ~Client(){};


};

#endif // CLIENT_H
