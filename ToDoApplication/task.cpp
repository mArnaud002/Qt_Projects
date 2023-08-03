#include "task.h"
#include "ui_task.h"
#include "todoapplication.h"

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

void Task :: saveTaskSlot()
{

    auto description = ui->lineEdit->text();
    auto tag = ui->comboBox->currentText();
    auto date = ui->dateEdit->date();

    // Message qui sera afficher
    display = tag + " " + "task :" + description + "  " + "for" +date.toString("yy/MM/dd");

    U->listWidget->addItem("Yoooooo");
}
