#include "task.h"
#include "ui_task.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "todo.h"

Task::Task(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Task)
{
    ui->setupUi(this);
    ui->dateEdit->setDate( QDate ::currentDate());
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

        // Fichier qui contiendront les taches
    QFile fileToday("C:\\Users\\hp\\Desktop\\QT\\ToDo\\Storage\\task.txt");
    QFile filePending("C:\\Users\\hp\\Desktop\\QT\\ToDo\\Storage\\PendingTask.txt");
    QFile fileFinished("C:\\Users\\hp\\Desktop\\QT\\ToDo\\Storage\\FinishedTask.txt");


    if(date == QDate ::currentDate())
    {
        if(ui->checkBox->isChecked())
        {
            statut = "Finished";

            // Message qui sera afficher
        QString display = tag + " " + "Task :" + " " + description + " " + "for"+ " " +date.toString("dd/MM/yyyy")+ '\t' + "Statut : " + statut;

            if(!fileFinished.open(QFile::WriteOnly| QFile ::Append |QFile::Text))
            {
                QMessageBox::warning(this,"No file","No file like this");
            }
            QTextStream out(&fileFinished);
            out<< display << Qt ::endl;
            fileFinished.close();
        }
        else
        {
            statut = "In progress";

            // Message qui sera afficher
        QString display = tag + " " + "Task :" + " " + description + " " + "for the "+ " " +date.toString("dd/MM/yyyy")+ '\t' + "Statut : " + statut;

            if(!fileToday.open(QFile::WriteOnly| QFile ::Append |QFile::Text))
            {
                QMessageBox::warning(this,"No file","No file like this");
            }
            QTextStream out(&fileToday);
            out<< display << Qt ::endl;
            fileToday.close();
        }
    }
    else
    {
        if(ui->checkBox->isChecked())
        {
            statut = "Finished";

            // Message qui sera afficher
        QString display = tag + " " + "Task :" + " " + description + " " + "for"+ " " +date.toString("dd/MM/yyyy")+ '\t' + "Statut : " + statut;

            if(!fileFinished.open(QFile::WriteOnly| QFile ::Append |QFile::Text))
            {
                QMessageBox::warning(this,"No file","No file like this");
            }
            QTextStream out(&fileFinished);
            out<< display << Qt ::endl;
            fileFinished.close();
        }
        else
        {
            statut = "Pending";

            // Message qui sera afficher
        QString display = tag + " " + "Task :" + " " + description + " " + "for"+ " " +date.toString("dd/MM/yyyy")+ '\t' + "Statut : " + statut;

            if(!filePending.open(QFile::WriteOnly| QFile ::Append |QFile::Text))
            {
                QMessageBox::warning(this,"No file","No file like this");
            }
            QTextStream out(&filePending);
            out<< display << Qt ::endl;
            filePending.close();
        }
    }
    close();
}

