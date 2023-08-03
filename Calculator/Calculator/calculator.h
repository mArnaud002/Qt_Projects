#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QGridLayout>
#include <QVector>
#include <QPushButton>
#include <QLCDNumber>

class Calculator : public QWidget
{
    Q_OBJECT
public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();


public slots:
   void clearHistory();     //Slot to clear the history of operations
   void changeOperation();  //Slot to handle the click on operations
   void newDigit();         //Slot to add the number to the LCD
   void enterAction();      //Slot to manage the actions of the enter button


 // Add you custom slots here

protected:
    void createWidgets();        //Function to create the widgets
    void placeWidget();         // Function to place the widgets
    void makeConnexions();      // Create all the connectivity
    int savingNum();           //Tosave the numbers that have been tap

//events
protected:
    void keyPressEvent(QKeyEvent *e)override;     //Override the keypress events

private:
    QGridLayout *buttonsLayout; // layout for the buttons
    QVBoxLayout *layout;        //main layout for the button
    QVector<QPushButton*> digits;  //Vector for the digits
    QPushButton *enter;  // enter button
    QPushButton *Clear;
    QVector<QPushButton*> operations; //operation buttons
    QLCDNumber *disp;             // Where to display the numbers
    int * left;     //left operand
    int * right; //right operand
    int * third; //third operand
    QString *operation;     //Pointer on the current operation
    QString *operation2;     //Pointer on the second operation
};
#endif // CALCULATOR_H
