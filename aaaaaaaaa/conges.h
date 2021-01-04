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
QString gp_music;
QString gp_serveur;
QString gp_deco;
QString gp_patiserie;
QString gp_photographie ;
public:
    Reservation(QString,QString,QString,QString,QString,QString);
    Reservation();

      void setId(QString n){id_reservation=n;}
      void setGp_music(QString n){gp_music=n;}
      void setGp_serveur(QString n){gp_serveur=n;}
      void setGp_deco(QString n){gp_deco=n;}
      void setGp_patiserie(QString n){gp_patiserie=n;}
      void setGp_photographie(QString n){gp_photographie=n;}

      QString getId(){return id_reservation;}
      QString getGp_music(){return gp_music;}
      QString getGp_serveur(){return gp_serveur;}
      QString getGp_deco(){return gp_deco;}
      QString getGp_patiserie(){return gp_patiserie;}
      QString getGp_photographie(){return gp_photographie;}

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
