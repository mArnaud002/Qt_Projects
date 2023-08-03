#ifndef TASK_H
#define TASK_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class Task;
}

class Task : public QDialog
{
    Q_OBJECT

public:
    explicit Task(QWidget *parent = nullptr);
    ~Task();
     QSqlDatabase getData()const;   //Fonction qui retourne la base de données

protected:
    void connectDatabase(); //Fonction pour se connecter à la database


private slots:
    void on_pushButton_clicked();

private:
    Ui::Task *ui;
    QSqlDatabase db;


};

#endif // TASK_H
