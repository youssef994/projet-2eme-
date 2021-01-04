#include "connexion.h"

connexion::connexion()
{

}

bool connexion::createconnect()
{
    bool test =false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("test");
    db.setUserName("youssef");
    db.setPassword("0000");
    if(db.open())
    {
        test=true;
    }
    return test;
}
