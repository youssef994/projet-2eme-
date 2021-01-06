#ifndef DIALOG_H
#define DIALOG_H

#include <QMainWindow>
#include <QDialog>
#include <QMediaPlayer>
#include <QDebug>
#include<QPropertyAnimation>



QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QMainWindow
{
    Q_OBJECT
private slots:
    void showTime();
    void on_pushButton_clicked();

    void on_tabWidget_2_currentChanged(int index);

    void on_pushButton_delete_clicked();

    void on_pushButton_edit_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_recherche_clicked();

    void on_tableView_activated(const QModelIndex &index);



    void on_radioButton_clicked();

    void on_radioButton_destroyed();

    void on_radioButton_2_clicked();

    void on_pushButton_actualiser_clicked();

    void on_pushButton_sauvgarderreservatio_clicked();

    void on_tabWidget_3_currentChanged(int index);

    void on_tableView_2_activated(const QModelIndex &index);

    void on_pushButton_modifierreservation_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_slider_progress_sliderMoved(int position);

    void on_slider_volume_sliderMoved(int position);

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_positionChanged(qint64 position);

     void on_durationChanged(qint64 position);


     void on_lineEdit_rechercher_cursorPositionChanged(int arg1, int arg2);

     void on_pushButton_8_clicked();

     void on_pushButton_9_clicked();

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QMediaPlayer* player;
    QPropertyAnimation *animation;






};
#endif // DIALOG_H

