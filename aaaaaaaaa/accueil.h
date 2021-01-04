#ifndef ACCUEIL_H
#define ACCUEIL_H

#include <QDialog>
#include<dialog.h>

namespace Ui {
class accueil;
}

class accueil : public QDialog
{
    Q_OBJECT

public:
    explicit accueil(QWidget *parent = nullptr);
    ~accueil();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::accueil *ui;
    Dialog *dialog;
};

#endif // ACCUEIL_H
