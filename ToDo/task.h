#ifndef TASK_H
#define TASK_H

#include <QDialog>


namespace Ui {
class Task;
}

class Task : public QDialog
{
    Q_OBJECT

public:
    explicit Task(QWidget *parent = nullptr);
    ~Task();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Task *ui;

};

#endif // TASK_H
