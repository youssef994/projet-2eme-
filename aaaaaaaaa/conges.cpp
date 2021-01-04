#include "conges.h"
#include<QPrinter>

Reservation::Reservation()
{
    id_reservation="";
    gp_music="";
    gp_serveur="";
    gp_deco="";
    gp_patiserie="";
    gp_photographie="";

}

Reservation::Reservation(QString id_reservation,QString gp_music, QString gp_serveur , QString gp_deco , QString gp_patiserie , QString gp_photographie )
{
    this->id_reservation=id_reservation ;
    this->gp_music=gp_music ;
    this->gp_serveur=gp_serveur ;
    this->gp_deco=gp_deco;
    this->gp_patiserie=gp_patiserie;
    this->gp_photographie=gp_photographie ;
}

bool Reservation::ajouterreservation()
{
    QSqlQuery qry ;
qry.prepare("insert into RESERVATION (ID,GP_MUSIC,GP_SERVEUR,GP_DECO,GP_PATISERIE,GP_PHOTOGRAPHIE) values ('"+id_reservation+"','"+gp_music+"','"+gp_serveur+"','"+gp_deco+"','"+gp_patiserie+"','"+gp_photographie+"')") ;
   qry.bindValue(":ID_",id_reservation);
   qry.bindValue(":GP_MUSIC",gp_music);
   qry.bindValue(":GP_SERVEUR",gp_serveur);
   qry.bindValue(":GP_DECO",gp_deco);
   qry.bindValue(":GP_PATISERIE",gp_patiserie);
   qry.bindValue(":GP_PHOTOGRAPHIE",gp_photographie);

       return qry.exec();

}

void Reservation::afficherreservation(Ui::Dialog *ui)
{

        QSqlQuery q;
        QSqlQueryModel *modal=new QSqlQueryModel();
        q.prepare("select * from RESERVATION");
        q.exec();
        modal->setQuery(q);
        ui->tableView_2->setModel(modal);

}

void Reservation::selectionnerreservation(Ui::Dialog *ui,const QModelIndex &index)
{ QSqlQuery qry;
    QString val;
   val=ui->tableView_2->model()->data(index).toString();

   qry.prepare("SELECT * FROM RESERVATION  where ID='"+val+"' or GP_MUSIC='"+val+"' or GP_SERVEUR='"+val+"' or GP_DECO='"+val+"' or GP_PATISERIE='"+val+"'or GP_PHOTOGRAPHIE='"+val+"' ");
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

       query.prepare("update RESERVATION set ID='"+id_reservation+"',GP_MUSIC='"+gp_music+"',GP_SERVEUR='"+gp_serveur+"',GP_DECO='"+gp_deco+"',GP_PATISERIE='"+gp_patiserie+"',GP_PHOTOGRAPHIE='"+gp_photographie+"' where ID='"+id_reservation+"' ");
       query.bindValue(":ID",id_reservation);
       query.bindValue(":GP_MUSIC",gp_music);
       query.bindValue(":GP_SERVEUR",gp_serveur);
       query.bindValue(":GP_DECO",gp_deco);
       query.bindValue(":GP_PATISERIE",gp_patiserie);
       query.bindValue(":GP_PHOTOGRAPHIE",gp_photographie);

          return query.exec();
}

bool Reservation::supprimerreservation(Ui::Dialog *ui)
{
    QString id_reservation;
    id_reservation=ui->lineEdit_id_reservation->text();
  QSqlQuery query ;
  query.prepare("DELETE FROM RESERVATION WHERE ID='"+id_reservation+"'");
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
        q.prepare("SELECT * FROM RESERVATION ");
        q.exec();
        QString pdf="<br> <h1  style='color:red'>LISTE DES RESERVATION  <br></h1>\n <br> <table>  <tr>  <th> ID  </th> <th> NOM GP MUSIC </th> <th> NOM GP SERVEUR </th> <th> NOM GP DECO </th> <th> NOM GP PATISERIE </th> <th> NOM GP PHOTOGRAPHIE </th></tr>" ;


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
