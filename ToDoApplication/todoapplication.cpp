#include "todoapplication.h"
#include "ui_todoapplication.h"
#include "task.h"
#include "ui_task.h"


toDoApplication::toDoApplication(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::toDoApplication)
{
    ui->setupUi(this);
    makeConnection();
}

toDoApplication::~toDoApplication()
{
    delete ui;
}

void toDoApplication :: makeConnection()
{
    connect (ui->actionNew_File, SIGNAL(triggered()), this, SLOT(newTask()));
}

void toDoApplication :: newTask()
{
    Task *T = new Task;
    T->setModal(true);
    T->exec();
}


//void toDoApplication::on_pushButton_2Clicked()
//{

////    auto description = U->lineEdit->text();
////    auto tag = U->comboBox->currentText();
////    auto date = U->dateEdit->date();

////    // Message qui sera afficher
////    display = tag + " " + "task :" + description + "  " + "for" +date.toString("yy/MM/dd");

////    ui->listWidget->addItem(description);
//    ui->listWidget->addItem("Yoooo");

//}

