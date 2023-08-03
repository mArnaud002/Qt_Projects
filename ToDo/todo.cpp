#include "todo.h"
#include "ui_todo.h"
#include "task.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDate>

ToDo::ToDo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ToDo)
{
    ui->setupUi(this);

    makeConnection();

    loadTask();

    getTasks();
}

ToDo::~ToDo()
{
    delete ui;
}

void ToDo :: makeConnection()
{
    connect (ui->actionNew_Task, SIGNAL(triggered()), this, SLOT(newTask()));
    connect( ui->actionDelete_Task, SIGNAL(triggered()),this,SLOT(deleteTask()));
}

void ToDo :: newTask()
{

    Task *T = new Task;
    T->setModal(true);
    T->exec();

    addTask();
    getTasks();

}

void ToDo :: deleteTask()
{
    qDeleteAll(ui->listWidget->selectedItems());
    qDeleteAll(ui->listWidget_2->selectedItems());
    qDeleteAll(ui->listWidget_3->selectedItems());
}

void ToDo :: loadTask()
{
    QFile fileToday("C:\\Users\\hp\\Desktop\\QT\\ToDo\\Storage\\task.txt");
    fileToday.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream task(&fileToday);
    while (!task.atEnd())
    {
         ui->listWidget->addItem(task.readLine());
    }

    QFile filePending("C:\\Users\\hp\\Desktop\\QT\\ToDo\\Storage\\PendingTask.txt");
    filePending.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream taskPending(&filePending);
    while (!taskPending.atEnd())
    {
        ui->listWidget_2->addItem(taskPending.readLine());
    }

    QFile fileFinished("C:\\Users\\hp\\Desktop\\QT\\ToDo\\Storage\\FinishedTask.txt");
    fileFinished.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream taskfinished(&fileFinished);
    while (!taskfinished.atEnd())
    {
         ui->listWidget_3->addItem(taskfinished.readLine());
    }
}

void ToDo :: addTask()
{
    QFile fileToday("C:\\Users\\hp\\Desktop\\QT\\ToDo\\Storage\\task.txt");
    fileToday.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream task(&fileToday);
    QString lineT;

    while(!task.atEnd())
    {
        lineT = task.readLine();
        numT++;
    }
    if(numT>numToday)
    {
        ui->listWidget->addItem(lineT);
    }


    QFile filePending("C:\\Users\\hp\\Desktop\\QT\\ToDo\\Storage\\PendingTask.txt");
    filePending.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream taskPending(&filePending);
    QString lineP;
    while(!taskPending.atEnd())
    {
        lineP = taskPending.readLine();
        numP++;
    }
    if(numP>numPending)
    {
        ui->listWidget_2->addItem(lineP);
    }


    QFile fileFinished("C:\\Users\\hp\\Desktop\\QT\\ToDo\\Storage\\FinishedTask.txt");
    fileFinished.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream taskfinished(&fileFinished);
    QString lineF;

    while(!taskfinished.atEnd())
    {
        numF++;
        lineF = taskfinished.readLine();

    }

    if(numF>numFinished)
    {
        ui->listWidget_3->addItem(lineF);
    }

}

void ToDo ::getTasks()
{
    QFile fileToday("C:\\Users\\hp\\Desktop\\QT\\ToDo\\Storage\\task.txt");
    fileToday.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream task(&fileToday);
    QString lineT;
    while (!task.atEnd())
    {
        lineT = task.readLine();
        numToday++;
    }

    QFile filePending("C:\\Users\\hp\\Desktop\\QT\\ToDo\\Storage\\PendingTask.txt");
    filePending.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream taskPending(&filePending);
    QString lineP;
    while (!taskPending.atEnd())
    {
        lineP = taskPending.readLine();
        numPending++;
    }

    QFile fileFinished("C:\\Users\\hp\\Desktop\\QT\\ToDo\\Storage\\FinishedTask.txt");
    fileFinished.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream taskfinished(&fileFinished);
    QString lineF;
    while (!taskfinished.atEnd())
    {
        lineF = taskfinished.readLine();
        numFinished++;
    }
}
