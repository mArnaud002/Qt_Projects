#ifndef TODO_H
#define TODO_H

#include <QMainWindow>
#include <QSqlDatabase>


QT_BEGIN_NAMESPACE
namespace Ui { class toDo; }
QT_END_NAMESPACE

class toDo : public QMainWindow
{
    Q_OBJECT

public:
    toDo(QWidget *parent = nullptr);
    ~toDo();

protected :
    void makeConnection();
    void addTask();     //Fontion qui ajoute les taches à la vue

private slots:
    void newTask();     //Fonction pour ajouter les taches à la base de données

private:
    Ui::toDo *ui;
    QSqlDatabase db;
};
#endif // TODO_H
