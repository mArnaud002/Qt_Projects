#include "todo.h"
#include "ui_todo.h"
#include "task.h"
#include "QSqlQueryModel"
#include "QSqlQuery"
#include "QSqlDatabase"

toDo::toDo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::toDo)
{
    ui->setupUi(this);

    Task *T = new Task;
    db = T->getData();
    makeConnection();
    addTask();
}

toDo::~toDo()
{
    delete ui;
}

void toDo :: makeConnection()
{
    connect (ui->actionNew_Task, SIGNAL(triggered()), this, SLOT(newTask()));
}

void toDo :: newTask()
{
    Task *T = new Task;
    T->setModal(true);
    T->exec();
    addTask();

}

void toDo :: addTask()
{

        //Lire le tableau TodayTasks
    //Connecter le model à la vue
    auto modelT = new QSqlQueryModel;
    //Preparer la requette de model
    auto queryT = QSqlQuery(db);
    QString viewT {"SELECT * FROM TodayTasks"};
    queryT.exec(viewT);
    //Connecter le model à la requette
    modelT->setQuery(queryT);
    //Connecter le model à la vue
    ui->tableView->setModel(modelT);

        //Lire le tableau PendingTasks
    //Connecter le model à la vue
    auto modelP = new QSqlQueryModel;
    //Preparer la requette de model
    auto queryP = QSqlQuery(db);
    QString viewP {"SELECT * FROM PendingTasks"};
    queryP.exec(viewP);
    //Connecter le model à la requette
    modelP->setQuery(queryP);
    //Connecter le model à la vue
    ui->tableView_2->setModel(modelP);

        //Lire le tableau FinishedTasks
    //Connecter le model à la vue
    auto modelF = new QSqlQueryModel;
    //Preparer la requette de model
    auto queryF = QSqlQuery(db);
    QString viewF {"SELECT * FROM FinishedTasks"};
    queryF.exec(viewF);
    //Connecter le model à la requette
    modelF->setQuery(queryF);
    //Connecter le model à la vue
    ui->tableView_3->setModel(modelF);
}
