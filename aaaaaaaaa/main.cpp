#include "dialog.h"
#include"accueil.h"
#include"connexion.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

       // Dialog dialog;

   accueil w;
        connexion c;
        bool test=c.createconnect();
        if(test)
        {
             w.show();
             QMessageBox::information(nullptr,QObject::tr("Data Base is open"),QObject::tr("Connection successful. \n"
                                                                                            "Click Cancel to exit"),QMessageBox::Cancel);
        }else
        {
            QMessageBox::critical(nullptr,QObject::tr("Data Base is not open"),QObject::tr("Connection failed. \n "
                                                                                          "Click Cancel to exit"),QMessageBox::Cancel);

        }

        return a.exec();
}
