#include "accueil.h"
#include "ui_accueil.h"
#include"ui_dialog.h"
#include"dialog.h"
#include<QSqlQuery>

accueil::accueil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accueil)
{
    ui->setupUi(this);
}

accueil::~accueil()
{
    delete ui;
}

void accueil::on_pushButton_2_clicked()
{
 QString nom,mot_de_passe ;
 nom=ui->lineEdit_nomlogin->text();
 mot_de_passe=ui->lineEdit_mdplogin->text();

 QSqlQuery qry ;
 if (qry.exec("select * from LOGIN where nom='"+nom+"' and MOT_DE_PASSE='"+mot_de_passe+"'"))
{
     int count=0;
     while(qry.next())
     {
         count ++ ;
     }
     if(count==1)
     {
         ui->label_voir->setText("mot de passe et nom correct") ;
         dialog = new Dialog(this);
         dialog->show();
         //hide();
     }
     if(count<1)
     {
         ui->label_voir->setText("mot de passe et nom ne sont  correct") ;
     }
 }



}
