#ifndef TASK_H
#define TASK_H

#include <QDialog>
#include <QDate>
#include "todoapplication.h"
#include "ui_todoapplication.h"

namespace Ui {
class Task;
}

class Task : public QDialog
{
    Q_OBJECT

public:
    explicit Task(QWidget *parent = nullptr);
    ~Task();
    QString display;    //Message qui sera afficher

private slots :
    void saveTaskSlot();



private:
    Ui::Task *ui;

    Ui::toDoApplication *U;




};

#endif // TASK_H
