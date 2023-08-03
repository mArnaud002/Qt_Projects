#ifndef TODOAPPLICATION_H
#define TODOAPPLICATION_H

#include <QMainWindow>
#include "ui_task.h"

QT_BEGIN_NAMESPACE
namespace Ui { class toDoApplication; }
QT_END_NAMESPACE

class toDoApplication : public QMainWindow
{
    Q_OBJECT

public:
    toDoApplication(QWidget *parent = nullptr);
    ~toDoApplication();
    QString display;    //Message qui sera afficher

protected:
    void makeConnection();

private slots :
    void newTask();
    //void createTask();  // créé l'expression définissant les taches
    //void on_pushButton_2Clicked();


private:
    Ui::toDoApplication *ui;
    Ui ::Task *U;   //to access the elements contain in the form

};
#endif // TODOAPPLICATION_H
