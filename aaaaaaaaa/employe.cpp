#include "employe.h"
#include<QMessageBox>





Client::Client()
{
    id="";
    nom="";
    prenom="";
    budget="";
    numero="";
    date_mariage="";
    categorie="";
}

Client::Client(QString id,QString nom,QString prenom,QString budget,QString numero,QString date_mariage,QString categorie)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->budget=budget;
    this->numero=numero;
    this->date_mariage=date_mariage;
    this->categorie=categorie;
}

bool Client::ajouterperso()
{

    QSqlQuery qry ;
    qry.prepare("insert into CLIENT (ID,NOM,PRENOM,BUDGET_MAX,NUMERO,D_MARAIGE,CATEGORIE) values ('"+id+"','"+nom+"','"+prenom+"','"+budget+"','"+numero+"','"+date_mariage+"','"+categorie+"')") ;
qry.bindValue(":ID",id);
qry.bindValue(":NOM",nom);
qry.bindValue(":PRENOM",prenom);
qry.bindValue(":BUDGET_MAX",budget);
qry.bindValue(":NUMERO",numero);
qry.bindValue(":D_MARAIGE",date_mariage);
qry.bindValue(":CATEGORIE",categorie);

    return qry.exec();

}

QSqlQueryModel * Client::afficherperso()
{
    QSqlQueryModel * modal=new QSqlQueryModel();
    modal->setQuery("select * from CLIENT");
    modal->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    modal->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    modal->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    modal->setHeaderData(3, Qt::Horizontal, QObject::tr("BUDGET_MAX"));
    modal->setHeaderData(4, Qt::Horizontal, QObject::tr("NUMERO"));
    modal->setHeaderData(5, Qt::Horizontal, QObject::tr("D_MARAIGE"));
    modal->setHeaderData(6, Qt::Horizontal, QObject::tr("CATEGORIE"));
    return modal;

}

bool Client::modifierperso()
{
    QSqlQuery query ;
//////////
       query.prepare("update CLIENT set ID='"+id+"',NOM='"+nom+"',PRENOM='"+prenom+"',BUDGET_MAX='"+budget+"',NUMERO='"+numero+"',D_MARAIGE='"+date_mariage+"',CATEGORIE='"+categorie+"' where ID='"+id+"' ");
       query.bindValue(":ID",id);
       query.bindValue(":NOM",nom);
       query.bindValue(":Prenom", prenom);
       query.bindValue(":BUDGET_MAX",budget);
       query.bindValue(":NUMERO",numero);
       query.bindValue(":D_MARAIGE",date_mariage);
       query.bindValue(":CATEGORIE",categorie);

       return query.exec();
}

bool Client::supprimer(Ui::Dialog *ui)
{
    QString id;
    id=ui->lineEdit_id->text();
  QSqlQuery query ;
  query.prepare("DELETE FROM CLIENT WHERE ID='"+id+"'");
  if(query.exec())
  {
              return query.exec();
  }
  else return false;


}

void Client::recherche(Ui::Dialog *ui)
{
    QSqlQuery q;
        QSqlQueryModel *modal=new QSqlQueryModel();
        QString mot =ui->lineEdit_rechercher->text();
        q.prepare("select * from CLIENT where (ID LIKE '%"+mot+"%' or NOM LIKE '%"+mot+"%' or PRENOM LIKE '%"+mot+"%' )");

        q.exec() ;
        modal->setQuery(q);
        ui->tableView->setModel(modal);
}

void Client::TRI1(Ui::Dialog *ui)
{
    QSqlQuery q;
       QSqlQueryModel *model=new QSqlQueryModel();
       q.prepare("select * from CLIENT order by NOM");
       q.exec();
       model->setQuery(q);
       ui->tableView->setModel(model);
}

void Client::TRI2(Ui::Dialog *ui)
{
    QSqlQuery q;
       QSqlQueryModel *model=new QSqlQueryModel();
       q.prepare("select * from CLIENT order by ID");
       q.exec();
       model->setQuery(q);
       ui->tableView->setModel(model);
}

bool Client::verif_id(QString ch_id){
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

bool Client::verif_nom(QString ch_nom){
    bool test=true;
    int i;
    if(true)
    {
        for(i=0;i<ch_nom.length();i++){
            if(!(((ch_nom[i]>='A')&&(prenom[i]<='Z'))||((prenom[i]>='a')&&(prenom[i]<='z')))){
                test=false;
                return  test;
        }
    }
  }
    return  test;
}

bool Client::verif_prenom(QString ch_prenom){
    bool test=true;
    int i;
    if(true)
    {
        for(i=0;i<ch_prenom.length();i++){
            if(!(((ch_prenom[i]>='A')&&(nom[i]<='Z'))||((nom[i]>='a')&&(nom[i]<='z')))){
                test=false;
                return  test;
        }
    }
  }
    return  test;
}

bool Client::verif_date_mariage(QString date_mariage)
{

    bool test=true;
    int i;
    if(date_mariage.length()!=10){
       test=false;
       return  test;
    }

         else{
       for(i=0;i<date_mariage.length();i++){
            if(!((date_mariage[1]>='0')&&(date_mariage[1]<='9'))&&(!((date_mariage[2]>='0')&&(date_mariage[2]<='9'))) && (!((date_mariage[4]>='0')&&(date_mariage[4]<='9'))) && (!((date_mariage[5]>='0')&&(date_mariage[5]<='9'))) && (!((date_mariage[7]>='0')&&(date_mariage[7]<='9'))) && (!((date_mariage[8]>='0')&&(date_mariage[8]<='9'))) && (!((date_mariage[9]>='0')&&(date_mariage[9]<='9'))) && (!((date_mariage[10]>='0')&&(date_mariage[10]<='9')))){
                test=false;
               return  test;
        }
        }
   }

 return test;}

//
bool Client::verif_numero(QString numero)
{

    bool test=true;
    int i;
    if(numero.length()!=8){
       test=false;
       return  test;
    }else{
        for(i=0;i<numero.length();i++){
            if(!((numero[i]>='0')&&(numero[i]<='9'))){
                test=false;
                return  test;
        }
        }
    }
 return test;}







