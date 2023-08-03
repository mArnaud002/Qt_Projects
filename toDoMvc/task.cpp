#include "task.h"
#include "ui_task.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>

Task::Task(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Task)
{
    ui->setupUi(this);
    ui->dateEdit->setDate( QDate :: currentDate());

    //Se connecter à la data Base
    connectDatabase();
}

Task::~Task()
{
    delete ui;
}

void Task::on_pushButton_clicked()
{

        //Variables qui récupèrent les valeurs entrées dans le dialogue de tache
    auto description = ui->lineEdit->text();
    auto tag = ui->comboBox->currentText();
    auto date = ui->dateEdit->date();
    QString statut;



    auto todayQuery = QSqlQuery(db);
    auto pendingQuery = QSqlQuery(db);
    auto finishedQuery = QSqlQuery(db);



    if(date == QDate ::currentDate())
    {
        if(ui->checkBox->isChecked())
        {
            statut = "Finished";

                //Query text
            QString finishedTask {"INSERT INTO FinishedTasks VALUES ('%1', '%2', '%3', '%4')"};

                //Exécuter
            if(!finishedQuery.exec(finishedTask.arg(tag).arg(description).arg(date.toString("dd/MM/yyyy")).arg(statut)))
                QMessageBox :: critical(this, "Info","Could not add an entry");

        }
        else
        {
            statut = "In Progress";

                //Query text
            QString todayTask {"INSERT INTO TodayTasks VALUES ('%1', '%2', '%3', '%4')"};

                //Exécuter
            if(!todayQuery.exec(todayTask.arg(tag).arg(description).arg(date.toString("dd/MM/yyyy")).arg(statut)))
                QMessageBox :: critical(this, "Info","Could not add an entry");

        }
    }
    else
    {
        if(ui->checkBox->isChecked())
        {
            statut = "Finished";

                //Query text
            QString finishedTask {"INSERT INTO FinishedTasks VALUES ('%1', '%2', '%3', '%4')"};

                //Exécuter
            if(!finishedQuery.exec(finishedTask.arg(tag).arg(description).arg(date.toString("dd/MM/yyyy")).arg(statut)))
                QMessageBox :: critical(this, "Info","Could not add an entry");

        }
        else
        {
            statut = "Pending";

                //Query text
            QString pendingTask {"INSERT INTO PendingTasks VALUES ('%1', '%2', '%3', '%4')"};

                //Exécuter
            if(!pendingQuery.exec(pendingTask.arg(tag).arg(description).arg(date.toString("dd/MM/yyyy")).arg(statut)))
                QMessageBox :: critical(this, "Info","Could not add an entry");

        }
    }
    close();
}

void Task :: connectDatabase()
{
    //Ajouter la base de donnée avec le driver sqlite
    db = QSqlDatabase :: addDatabase("QSQLITE");

            //Base de donnée pour les taches terminées
    db.setDatabaseName("C:\\Users\\hp\\Desktop\\QT\\toDoMvc\\Storage\\Tasks.sqlite");

    //Ouvrir la base de donnée
    if(!db.open())
        QMessageBox :: critical(this, "Info", "Cannot open the database");

    //Creer la table todayTask
        //1. Definir la requete avec une base de donnée
    auto todayQuery = QSqlQuery(db);

        //2.Définir le texte de la requête
    QString todayCreate {"CREATE TABLE IF NOT EXISTS TodayTasks (Tag VARCHAR(20), Description VARCHAR(100),Due_Date VARCHAR(20), Statut VARCHAR(20))"};

        //3.Exécuter la requette
    if(!todayQuery.exec(todayCreate))
        QMessageBox :: critical(this, "Info", "Cannot create the table");


    //Creer la table pendingTask
    //1. Definir la requete avec une base de donnée
    auto pendingQuery = QSqlQuery(db);

    //2.Définir le texte de la requête
    QString pendingCreate {"CREATE TABLE IF NOT EXISTS PendingTasks (Tag VARCHAR(20), Description VARCHAR(100),Due_Date VARCHAR(20), Statut VARCHAR(20))"};

    //3.Exécuter la requette
    if(!pendingQuery.exec(pendingCreate))
    QMessageBox :: critical(this, "Info", "Cannot create the table");



    //Creer la table finishedTask
    //1. Definir la requete avec une base de donnée
    auto finishedQuery = QSqlQuery(db);

    //2.Définir le texte de la requête
    QString create {"CREATE TABLE IF NOT EXISTS FinishedTasks (Tag VARCHAR(20), Description VARCHAR(100),Due_Date VARCHAR(20), Statut VARCHAR(20))"};

    //3.Exécuter la requette
    if(!finishedQuery.exec(create))
    QMessageBox :: critical(this, "Info", "Cannot create the table");

}

QSqlDatabase Task :: getData() const
{
    return db;
}
