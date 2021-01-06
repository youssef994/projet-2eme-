#ifndef RESERVATION_H
#define RESERVATION_H
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
#include<QtCore>
#include<QtGui>

class Reservation
{
private :
QString id_reservation;
QString nom;
QString prenom;
QString debut;
QString fin;
QString nb ;
public:
    Reservation(QString,QString,QString,QString,QString,QString);
    Reservation();

      void setId(QString n){id_reservation=n;}
      void setGp_music(QString n){nom=n;}
      void setGp_serveur(QString n){prenom=n;}
      void setGp_deco(QString n){debut=n;}
      void setGp_patiserie(QString n){fin=n;}
      void setGp_photographie(QString n){nb=n;}

      QString getId(){return id_reservation;}
      QString getGp_music(){return nom;}
      QString getGp_serveur(){return prenom;}
      QString getGp_deco(){return debut;}
      QString getGp_patiserie(){return fin;}
      QString getGp_photographie(){return nb;}

      bool ajouterreservation();
      void afficherreservation(Ui::Dialog *ui);
      void selectionnerreservation(Ui::Dialog *ui,const QModelIndex &index);
      bool modifierreservation();
      bool supprimerreservation(Ui::Dialog *ui);
      void creationpdf();
bool verif_id(QString ch_id);
      ~Reservation(){};

};

#endif // RESERVATION_H
