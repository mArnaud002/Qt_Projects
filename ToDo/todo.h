#ifndef TODO_H
#define TODO_H

#include <QMainWindow>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class ToDo; }
QT_END_NAMESPACE

class ToDo : public QMainWindow
{
    Q_OBJECT

public:
    ToDo(QWidget *parent = nullptr);
    ~ToDo();

private slots :
    void newTask();
    void deleteTask();

private:
    Ui::ToDo *ui;
    int numToday = 0;
    int numPending = 0;
    int numFinished = 0;
    int numT = 0;
    int numP = 0;
    int numF = 0;

protected:
    void makeConnection();
    void loadTask();
    void getTasks();
    void addTask();
    void addTodayTask();
    void addPendingTask();
    void addFinishedTask();

};
#endif // TODO_H
