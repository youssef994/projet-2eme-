#include "dialog.h"
#include "ui_dialog.h"
#include<QMessageBox>
#include<QSqlQueryModel>
#include<QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QTextDocument>
#include<QPrinter>
#include<QPrintDialog>
#include<QFileDialog>
#include"employe.h"
#include"conges.h"
#include<QDateTime>
#include<QTimer>
#include<statistique.h>




Dialog::Dialog(QWidget *parent) :
   QMainWindow(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
   QTimer *timer=new QTimer(this);
   connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
    timer->start();
Client c;
    ui->tableView->setModel(c.afficherperso());

    player = new QMediaPlayer(this);





}



Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    QSqlQuery qry;


   QString id,nom,prenom,budget,numero,date_mariage ;
     QString categorie ;
   id=ui->lineEdit_id->text();
    nom=ui->lineEdit_nom->text();
    prenom=ui->lineEdit_prenom->text();
    budget=ui->lineEdit_budget->text();
    numero=ui->lineEdit_num->text();
    date_mariage=ui->lineEdit_date->text();
   categorie=ui->comboBox_categorie->currentText();
   Client c(id,nom,prenom,budget,numero,date_mariage,categorie);
   if(c.verif_id(id)==false){

       QMessageBox::critical(nullptr,QObject::tr("Ajouter un Client"),
                                        QObject::tr("ID Doit contenir 6 chifres.\n"
                                                    "Click Cancel to exit ."),QMessageBox::Cancel);
            }else if((nom=="") ||(c.verif_nom(nom)==false )){
       QMessageBox::critical(nullptr,QObject::tr("Ajouter un Client"),
                                        QObject::tr("Veuillez remplir tous les cases.\n"
                                                    "Click Cancel to exit ."),QMessageBox::Cancel);

            }else if((prenom=="") || (c.verif_prenom(prenom)==false) ){
       QMessageBox::critical(nullptr,QObject::tr("Ajouter un Client"),
                                        QObject::tr("Veuillez remplir tous les cases.\n"
                                                    "Click Cancel to exit ."),QMessageBox::Cancel);

           }else if((numero=="") || (c.verif_numero(numero)==false) ){
       QMessageBox::critical(nullptr,QObject::tr("Ajouter un Client"),
                                        QObject::tr("Veuillez saisir correctement le numero.\n"
                                                    "Click Cancel to exit ."),QMessageBox::Cancel);
            }
         else if(budget==""){
       QMessageBox::critical(nullptr,QObject::tr("Ajouter un Client"),
                                        QObject::tr("Veuillez remplir tous les cases.\n"
                                                    "Click Cancel to exit ."),QMessageBox::Cancel);
               }
       else if((date_mariage=="") ||(c.verif_date_mariage(date_mariage)==false ))
   {
       QMessageBox::critical(nullptr,QObject::tr("Ajouter un Client"),
                                        QObject::tr("Veuillez saisir la date sous forme jj/mm/aaaa.\n"
                                                    "Click Cancel to exit ."),QMessageBox::Cancel);
               }
   else if((categorie=="") )
{
   QMessageBox::critical(nullptr,QObject::tr("Ajouter un Client"),
                                    QObject::tr("Veuillez saisir la categorie.\n"
                                                "Click Cancel to exit ."),QMessageBox::Cancel);
           }
            else{
   bool test=c.ajouterperso() ;
if (test)
    {
    ui->tableView->setModel(c.afficherperso());
    QMessageBox::information(nullptr,QObject::tr("Ajouter un Client"),
                                     QObject::tr("Client ajouté .\n"
                                                 "Click Cancel to exit ."),QMessageBox::Cancel);
     }
else
{
    QMessageBox::critical(nullptr,QObject::tr("Ajouter un Client"),
                                     QObject::tr("Erreur.\n"
                                                 "Click Cancel to exit ."),QMessageBox::Cancel);
}

   }

}

void Dialog::on_tabWidget_2_currentChanged(int index)
{

    QSqlQueryModel * modal=new QSqlQueryModel();


    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("select * from CLIENT");
    qry->exec();

    modal->setQuery(*qry);
    ui->tableView->setModel(modal);


    qDebug() <<(modal->rowCount());
    index=0;
    index++;

}



void Dialog::on_pushButton_delete_clicked()
{
    QSqlQuery qry;
    Client c;


    bool test =c.supprimer(ui);
    if(test)
       {
        QMessageBox::information(nullptr,QObject::tr("Supprimer un Client"),
                                         QObject::tr("Client sumprié .\n"
                                                     "Click Cancel to exit ."),QMessageBox::Cancel);

       }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Supprimer un Client"),
                                         QObject::tr("Erreur.\n"
                                                     "Click Cancel to exit ."),QMessageBox::Cancel);
       }



}

void Dialog::on_pushButton_edit_clicked()
{  QSqlQuery qry ;

    QString id,nom,prenom,budget,numero,date_mariage ;
     QString categorie;
    id=ui->lineEdit_id->text();
     nom=ui->lineEdit_nom->text();
     prenom=ui->lineEdit_prenom->text();
     budget=ui->lineEdit_budget->text();
     numero=ui->lineEdit_num->text();
     date_mariage=ui->lineEdit_date->text();
   categorie=ui->comboBox_categorie->currentText();
    Client c(id,nom,prenom,budget,numero,date_mariage,categorie);
         bool test=c.modifierperso();
         if (test)
         {
             QMessageBox::information(nullptr,QObject::tr("Modifier un Client"),
                                              QObject::tr("Client Modifié .\n"
                                                          "Click Cancel to exit ."),QMessageBox::Cancel);

          }
     else
     {
             QMessageBox::critical(nullptr,QObject::tr("Modifier un Client"),
                                              QObject::tr("Erreur.\n"
                                                          "Click Cancel to exit ."),QMessageBox::Cancel);
        }


}



void Dialog::on_pushButton_2_clicked()
{

    QString str;
       str.append("<html><head></head><body><center>"+QString("GESTION RESERVATION"));
       str.append("<table border=1><tr>") ;
       str.append("<td>"+QString("ID")+"</td>") ;
       str.append("<td>"+QString("GP_MUSIC")+"</td>") ;
       str.append("<td>"+QString("GP_SERVEUR")+"</td>") ;
       str.append("<td>"+QString("GP_DECO")+"</td>") ;
       str.append("<td>"+QString("GP_PATISERIE")+"</td>") ;
       str.append("<td>"+QString("GP_PHOTOGRAPHIE")+"</td>") ;



       QSqlQuery* query=new QSqlQuery();
       query->exec("SELECT ID,GP_MUSIC,GP_SERVEUR,GP_DECO,GP_PATISERIE,GP_PHOTOGRAPHIE FROM RESERVATION");

       while(query->next())
       {
       str.append("<tr><td>");
       str.append(query->value(0).toString()) ;
       str.append("</td><td>") ;
       str.append(query->value(1).toString());
       str.append("</td><td>") ;
       str.append(query->value(2).toString());
       str.append("</td><td>") ;
       str.append(query->value(3).toString());
       str.append("</td><td>") ;
       str.append(query->value(4).toString());
       str.append("</td><td>") ;
       str.append(query->value(5).toString());
       str.append("</td></td>");
       str.append(query->value(6).toString());
       str.append("</td></tr>");


       }
    str.append("</table></center></body></html>") ;

    QPrinter printer ;
    printer.setOrientation(QPrinter::Portrait);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4) ;

    QString path=QFileDialog::getSaveFileName(NULL,"Convertir a PDF","..","PDF(*.pdf)");

    if (path.isEmpty()) return ;
    printer.setOutputFileName(path) ;

    QTextDocument doc;
    doc.setHtml(str) ;
    doc.print(&printer);


}

void Dialog::on_pushButton_recherche_clicked()
{  Client c;
    c.recherche(ui);
}

void Dialog::on_tableView_activated(const QModelIndex &index)
{
    QSqlQuery* query=new QSqlQuery();
QString val=ui->tableView->model()->data(index).toString() ;
           query->prepare("SELECT * FROM CLIENT  where ID='"+val+"' or NOM='"+val+"' or PRENOM='"+val+"' or BUDGET_MAX='"+val+"' or NUMERO='"+val+"'or D_MARAIGE='"+val+"'  ");
    if(query->exec())
{ while (query->next())
        {            ui->lineEdit_id->setText(query->value(0).toString());
            ui->lineEdit_nom->setText(query->value(1).toString());
            ui->lineEdit_prenom->setText(query->value(2).toString());
            ui->lineEdit_budget->setText(query->value(3).toString());
            ui->lineEdit_num->setText(query->value(4).toString());
            ui->lineEdit_date->setText(query->value(5).toString());





        }

    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Sélectionner un Client"),
                                         QObject::tr("Erreur .\n"
                                                     "Click Cancel to exit ."),QMessageBox::Cancel);
       }


}



void Dialog::on_radioButton_clicked()
{
    Client c ;
    c.TRI1(ui);
}



void Dialog::on_radioButton_2_clicked()
{
    Client c;
    c.TRI2(ui);
}

void Dialog::on_pushButton_actualiser_clicked()
{
    QSqlQueryModel * modal=new QSqlQueryModel();


    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("select * from CLIENT");
    qry->exec();

    modal->setQuery(*qry);
    ui->tableView->setModel(modal);

     // ui->tableView->setModel(c.afficher());
     // qDebug()<<ui->tabclient->model()->rowCount();




}

void Dialog::on_pushButton_sauvgarderreservatio_clicked()
{   QSqlQuery qry ;
    QString id_reservation,gp_music,gp_serveur,gp_deco,gp_patiserie,gp_photographie ;
       id_reservation=ui->lineEdit_id_reservation->text();
           gp_music=ui->lineEdit_nomGP_music->text();
           gp_serveur=ui->lineEdit_nomGP_serveur->text();
        gp_deco=ui->lineEdit_nomGP_deco->text();
        gp_patiserie=ui->lineEdit_nomGP_patisserie->text();
        gp_photographie=ui->lineEdit_nomGP_photographie->text();

  Reservation R(id_reservation,gp_music,gp_serveur,gp_deco,gp_patiserie,gp_photographie);
  if(R.verif_id(id_reservation)==false){

      QMessageBox::critical(nullptr,QObject::tr("Ajouter Réservation"),
                                       QObject::tr("ID Doit contenir 6 chifres.\n"
                                                   "Click Cancel to exit ."),QMessageBox::Cancel);
           }else if((gp_music=="")){
      QMessageBox::critical(nullptr,QObject::tr("Ajouter Réservation"),
                                       QObject::tr("Veuillez remplir tous les cases.\n"
                                                   "Click Cancel to exit ."),QMessageBox::Cancel);

           }
  else if((gp_serveur=="") )
{
  QMessageBox::critical(nullptr,QObject::tr("Ajouter Réservation"),
                                   QObject::tr("Veuillez saisir la date sous forme jj/mm/aaaa.\n"
                                               "Click Cancel to exit ."),QMessageBox::Cancel);
          }else if((  gp_deco=="") ){
      QMessageBox::critical(nullptr,QObject::tr("Ajouter Réservation"),
                                       QObject::tr("Veuillez remplir tous les cases.\n"
                                                   "Click Cancel to exit ."),QMessageBox::Cancel);

          }else if((gp_patiserie=="") ){
      QMessageBox::critical(nullptr,QObject::tr("Ajouter Réservation"),
                                       QObject::tr("Veuillez saisir correctement le numero.\n"
                                                   "Click Cancel to exit ."),QMessageBox::Cancel);
           }
        else if(gp_photographie==""){
      QMessageBox::critical(nullptr,QObject::tr("Ajouter Réservation"),
                                       QObject::tr("Veuillez remplir tous les cases.\n"
                                                   "Click Cancel to exit ."),QMessageBox::Cancel);
              }


else {
bool test=R.ajouterreservation();
if(test)
{
    QMessageBox::information(nullptr,QObject::tr("Ajouter Réservation"),
                                         QObject::tr("Réservation ajoutée .\n"
                                                     "Click Cancel to exit ."),QMessageBox::Cancel);
         }
    else
    {
    QMessageBox::critical(nullptr,QObject::tr("Ajouter Réservation"),
                                     QObject::tr("ERooR .\n"
                                                 "Click Cancel to exit ."),QMessageBox::Cancel);
    }
}
}












void Dialog::on_tabWidget_3_currentChanged(int index)
{
    Reservation r;
    r.afficherreservation(ui);

}

void Dialog::on_tableView_2_activated(const QModelIndex &index)
{
   Reservation r ;
   r.selectionnerreservation(ui,index);
}

void Dialog::on_pushButton_modifierreservation_clicked()
{
    QSqlQuery qry ;

      QString id_reservation,gp_music,gp_serveur,gp_deco,gp_patiserie,gp_photographie ;
      id_reservation=ui->lineEdit_id_reservation->text();
          gp_music=ui->lineEdit_nomGP_music->text();
          gp_serveur=ui->lineEdit_nomGP_serveur->text();
       gp_deco=ui->lineEdit_nomGP_deco->text();
       gp_patiserie=ui->lineEdit_nomGP_patisserie->text();
       gp_photographie=ui->lineEdit_nomGP_photographie->text();

       Reservation r(id_reservation,gp_music,gp_serveur,gp_deco,gp_patiserie,gp_photographie);

 bool test=r.modifierreservation();
     if (test)
             {
         QMessageBox::information(nullptr,QObject::tr("Modifier Réservation"),
                                          QObject::tr("Réservation Modifié .\n"
                                                      "Click Cancel to exit ."),QMessageBox::Cancel);

              }
         else
         {
         QMessageBox::critical(nullptr,QObject::tr("Modifier Réservation"),
                                          QObject::tr("Réservation Modifié .\n"
                                                      "Click Cancel to exit ."),QMessageBox::Cancel);
            }


}

void Dialog::on_pushButton_3_clicked()
{
    QSqlQuery qry;
   Reservation r;


    bool test =r.supprimerreservation(ui);
    if(test)
       {
        QMessageBox::information(nullptr,QObject::tr("Supprimer Réservation"),
                                         QObject::tr("Réservation supprimé .\n"
                                                     "Click Cancel to exit ."),QMessageBox::Cancel);

       }
    else
    {
        QMessageBox::information(nullptr,QObject::tr("Supprimer Réservation"),
                                         QObject::tr("Erreur .\n"
                                                     "Click Cancel to exit ."),QMessageBox::Cancel);
       }

}

void Dialog::on_pushButton_4_clicked()
{
    Reservation r ;
    r.afficherreservation(ui);

}

void Dialog::on_pushButton_5_clicked()
{/*
    QString id_reservation,gp_music,gp_serveur,gp_deco,gp_patiserie,gp_photographie ;
   // Reservation r(id_reservation,gp_music,gp_serveur,gp_deco,gp_patiserie,gp_photographie);

    QPrinter printer;
     printer.setOutputFormat(QPrinter::PdfFormat);
     printer.setOutputFileName("‪C:/Users/moeta/OneDrive/Bureau/a.pdf");


       QPainter painter;
       painter.begin(&printer);
       QFont font;
        id_reservation= ui->lineEdit_id_reservation->text();
        gp_music = ui->lineEdit_nomGP_music->text();
         gp_serveur = ui->lineEdit_nomGP_serveur->text();
          gp_deco = ui->lineEdit_nomGP_deco->text();
           gp_patiserie = ui->lineEdit_nomGP_patisserie->text();
            gp_photographie = ui->lineEdit_nomGP_photographie->text();



       font.setPixelSize(35);
       painter.setFont(font);
       painter.setPen(Qt::blue);

       painter.drawText(100,300,"ID :");

       painter.drawText(100,400,"GP_MUSIC :");

       painter.drawText(100,500,"GP_SERVEUR :");

       painter.drawText(100,600,"GP_DECO:");

       painter.drawText(100,700,"GP_PATISERIE :");
       painter.drawText(100,700,"GP_PHOTOGRAPHIE :");

       font.setPixelSize(22);
       painter.setFont(font);
       painter.setPen(Qt::green);

       painter.drawText(500,300,id_reservation);
       painter.drawText(500,400,gp_music);
       painter.drawText(500,500,gp_serveur);
       painter.drawText(500,600,gp_deco);
       painter.drawText(500,700,gp_patiserie);
       painter.drawText(500,700,gp_photographie);
       painter.end();< md->columnCount();
           column++) {

    Reservation r ;
    r.creationpdf();


    QPrinter printer;
        QPrintDialog printDialog( &printer, 0);
        if( QDialog::Accepted == printDialog.exec() ) {

            if( QPrinter::Landscape != printer.orientation() ) {
                printer.setOrientation(QPrinter::Landscape);
            }

            QPoint startPoint = QPoint(20, 20);
            QRegion printRegion = QRegion( 20, 20, printer.paperRect().width(),printer.paperRect().height() );

               ui->tableView->render( &printer, startPoint, printRegion, QWidget::DrawChildren );

        }
        */
    const QString format("<td>%1</td>");
           QString html;
           QAbstractItemModel *md = ui->tableView_2->model();
           html = "<html><body><table border=\"0\">";

           html += "<td></td>";
           for(int column = 0; column < md->columnCount();
               column++) {
               QString data = md->headerData(column, Qt::Horizontal, Qt::DisplayRole).toString();
               html += format.arg(data);
           }
           for(int row = 0; row < md->rowCount() ; row++) {
               html += "<tr>";
               QString data = md->headerData(row, Qt::Vertical, Qt::DisplayRole).toString();
               html += format.arg(data);
               for(int column = 0; column < md->columnCount();
                   column++) {
                   QString data = md->index(row, column).data(Qt::DisplayRole).toString();
                   html += format.arg(data);
               }
               html += "</tr>";
           }
           html += "</table></body></html>";

           QPrinter printer;
           QPrintDialog *dialog = new QPrintDialog(&printer);
           if(dialog->exec() == QDialog::Accepted) {
               QTextDocument document;
               document.setHtml(html);
               document.print(&printer);
           }
    }


void Dialog::on_slider_progress_sliderMoved(int position)
{
player->setPosition(position);}

void Dialog::on_slider_volume_sliderMoved(int position)
{
 player->setVolume(position);
}

void Dialog::on_pushButton_6_clicked()
{
// import file
    player->setMedia(QUrl("qrc:/song/ressources/elissa-aa-baly-habibi_uCClgMns.mp3")) ;
       player->play();
       qDebug() << player->errorString();
}

void Dialog::on_pushButton_7_clicked()
{
player->stop();
}











