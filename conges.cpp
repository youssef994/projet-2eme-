#include "conges.h"
#include<QPrinter>

Reservation::Reservation()
{
    id_reservation="";
    nom="";
    prenom="";
    debut="";
    fin="";
    nb="";

}

Reservation::Reservation(QString id_reservation,QString gp_music, QString gp_serveur , QString gp_deco , QString gp_patiserie , QString gp_photographie )
{
    this->id_reservation=id_reservation ;
    this->nom=gp_music ;
    this->prenom=gp_serveur ;
    this->debut=gp_deco;
    this->fin=gp_patiserie;
    this->nb=gp_photographie ;
}

bool Reservation::ajouterreservation()
{
    QSqlQuery qry ;
qry.prepare("insert into CONGES (ID,NOM,PRENOM,DEBUT,FIN,NB) values ('"+id_reservation+"','"+nom+"','"+prenom+"','"+debut+"','"+fin+"','"+nb+"')") ;
   qry.bindValue(":ID",id_reservation);
   qry.bindValue(":NOM",nom);
   qry.bindValue(":PRENOM",prenom);
   qry.bindValue(":DEBUT",debut);
   qry.bindValue(":FIN",fin);
   qry.bindValue(":NB",nb);

       return qry.exec();

}

void Reservation::afficherreservation(Ui::Dialog *ui)
{

        QSqlQuery q;
        QSqlQueryModel *modal=new QSqlQueryModel();
        q.prepare("select * from CONGES");
        q.exec();
        modal->setQuery(q);
        ui->tableView_2->setModel(modal);

}

void Reservation::selectionnerreservation(Ui::Dialog *ui,const QModelIndex &index)
{ QSqlQuery qry;
    QString val;
   val=ui->tableView_2->model()->data(index).toString();

   qry.prepare("SELECT * FROM CONGES  where ID='"+val+"' or NOM='"+val+"' or PRENOM='"+val+"' or DEBUT='"+val+"' or FIN='"+val+"'or NB='"+val+"' ");
       if(qry.exec())
       {
           while (qry.next())

           {

               ui->lineEdit_id_reservation->setText(qry.value(0).toString());
                ui->lineEdit_nomGP_music->setText(qry.value(1).toString());
                ui->lineEdit_nomGP_serveur->setText(qry.value(2).toString());
                ui->lineEdit_nomGP_deco->setText(qry.value(3).toString());
                ui->lineEdit_nomGP_patisserie->setText(qry.value(4).toString());
                ui->lineEdit_nomGP_photographie->setText(qry.value(5).toString());
           }

       }


}
bool Reservation::modifierreservation()
{
    QSqlQuery query ;

       query.prepare("update CONGES set ID='"+id_reservation+"',NOM='"+nom+"',PRENOM='"+prenom+"',DEBUT='"+debut+"',FIN='"+fin+"',NB='"+nb+"' where ID='"+id_reservation+"' ");
       query.bindValue(":ID",id_reservation);
       query.bindValue(":NOM",nom);
       query.bindValue(":PRENOM",prenom);
       query.bindValue(":DEBUT",debut);
       query.bindValue(":FIN",fin);
       query.bindValue(":NB",nb);

          return query.exec();
}

bool Reservation::supprimerreservation(Ui::Dialog *ui)
{
    QString id_reservation;
    id_reservation=ui->lineEdit_id_reservation->text();
  QSqlQuery query ;
  query.prepare("DELETE FROM CONGES WHERE ID='"+id_reservation+"'");
  if(query.exec())
  {
              return query.exec();
  }
  else return false;


}

void Reservation::creationpdf()
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
        if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(fileName);

        QTextDocument doc;
        QSqlQuery q;
        q.prepare("SELECT * FROM CONGES ");
        q.exec();
        QString pdf="<br> <h1  style='color:red'>LISTE DES CONGES  <br></h1>\n <br> <table>  <tr>  <th> ID  </th> <th> NOM GP MUSIC </th> <th> NOM GP SERVEUR </th> <th> NOM GP DECO </th> <th> NOM GP PATISERIE </th> <th> NOM GP PHOTOGRAPHIE </th></tr>" ;


        while ( q.next()) {

            pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toString()+" " + q.value(1).toString() +"</td>   <td>" +q.value(2).toString() +"  "" " "</td>   <td>"+q.value(3).toString()+"</td>   <td>"+q.value(4).toString()+" " "ans "  " " "</td>   <td>"+q.value(5).toString()+" </td> <td>"+q.value(5).toString()+" </td>" ;

        }
        doc.setHtml(pdf);
        doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
        doc.print(&printer);
}
bool Reservation::verif_id(QString ch_id){
   bool test=true;
   int i;
   if(ch_id.length()!=6){
      test=false;
      return  test;
   }else{
       for(i=0;i<ch_id.length();i++){
           if(!((ch_id[i]>='0')&&(ch_id[i]<='9'))){
               test=false;
               return  test;
       }
       }
   }
return test;}
