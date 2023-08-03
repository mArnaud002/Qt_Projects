#include "calculator.h"
#include <QKeyEvent>
#include <QApplication>


Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    createWidgets();
    placeWidget();
    makeConnexions();
    left = nullptr;
    right = nullptr;
    third = nullptr;
    operation = nullptr;
    operation2 = nullptr;

}


Calculator::~Calculator()
{
    delete disp;
    delete layout;
    delete buttonsLayout;
    delete enter;
    delete disp;
    delete left;
    delete right;
    delete third;
    delete operation;
    delete operation2;

}





void Calculator::createWidgets()
{
    //Creating the layouts
    layout = new QVBoxLayout();
    layout->setSpacing(2);

    //grid layout
    buttonsLayout = new QGridLayout;


    //creating the buttons
    for(int i=0; i < 10; i++)
    {
        digits.push_back(new QPushButton(QString::number(i)));
        digits.back()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        digits.back()->resize(sizeHint().width(), sizeHint().height());
    }
    //enter button
    enter = new QPushButton("Enter",this);
    enter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    enter->resize(sizeHint().width(), sizeHint().height());

    // Clear button
    Clear = new QPushButton ("Clear");
    Clear->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    Clear->resize(sizeHint().width(), sizeHint().height());

    //operatiosn buttons
    operations.push_back(new QPushButton("+"));
    operations.push_back(new QPushButton("-"));
    operations.push_back(new QPushButton("*"));
    operations.push_back(new QPushButton("/"));


    //creating the lcd
    disp = new QLCDNumber(this);
    disp->setDigitCount(6);

}


void Calculator::placeWidget()
{

    layout->addWidget(disp);
    layout->addLayout(buttonsLayout);


    //adding the buttons
    for(int i=1; i <10; i++)
        buttonsLayout->addWidget(digits[i], (i-1)/3, (i-1)%3);


    //Adding the operations
    for(int i=0; i < 4; i++)
        buttonsLayout->addWidget(operations[ i], i, 4);


    //Adding the 0 button
    buttonsLayout->addWidget(digits[0], 3, 0);
    //Adding the entr button
    buttonsLayout->addWidget(enter, 3, 1, 1,2);

    //Adding the Clear button
    buttonsLayout->addWidget(Clear,0,5);


    setLayout(layout);
}


void Calculator::changeOperation()
{
    if(operation)
{
    //Getting the sender button
    auto button = dynamic_cast<QPushButton*>(sender());

    //Storing the operation
    operation = new QString{button->text()};

    //Initiating the right button
    right = new int{0};

    //reseting the display
    disp->display(0);
}
    if (operation2)
{
    //Getting the sender button
    auto button2 = dynamic_cast<QPushButton*>(sender());

    //Storing the operation
    operation2 = new QString{button2->text()};

    //Initiating the right button
    third = new int{0};

    //reseting the display
    disp->display(0);
}

}

void Calculator :: newDigit()
{

    //Getting the identity of the button using dynamic_cast
    auto button  = dynamic_cast<QPushButton*>(sender());

    // Each button has his own digit in the text
    auto value = button->text().toInt();

    //Check if we have an operation defined
        if(operation)
        {
            //check if we have a value or not
            if(!right)
                right = new int{value};
            else
                *right = 10 * (*right) + value;

            disp->display(*right);

        }
        if(operation2)
        {
            if(!third)
                third = new int{value};
            else
                *third = 10 * (*left) + value;

            disp->display(*third);
        }

        else
        {
            if(!left)
                left = new int{value};
            else
                *left = 10 * (*left) + value;

            disp->display(*left);
        }

}


void Calculator::clearHistory(){
         disp->display(0);
          delete left;
         left = nullptr;
         delete right;
          right = nullptr;
         delete third;
       delete operation;
        operation = nullptr;

}

void Calculator :: enterAction()
{

    int solution = 0;
    if(operation)
    {
        if (operation == operations[0]->text())
        {
            solution = *left + *right + *third ;
        }
        else if (operation == operations[1]->text())
        {
            solution = *left - *right;
        }
        else if (operation == operations[2]->text())
        {
            solution = *left * *right;
        }
        else if (operation == operations[3]->text())
        {
            solution = *left / *right;
        }
    }
    disp->display(solution);
}

void Calculator::makeConnexions()
{

    //Connecting the digits
     for(int i=0; i <10; i++)
         connect(digits[i], &QPushButton::clicked, this, &Calculator::newDigit);

     //Connecting ths operations
     for(int i=0; i <4; i++)
        connect(operations[i], &QPushButton::clicked, this, &Calculator::changeOperation );

     //Connecting the Clear button
     connect(Clear, &QPushButton :: clicked, this, &Calculator :: clearHistory);

     //Connecting the enter button
     connect(enter, &QPushButton :: clicked, this, &Calculator :: enterAction);

}

void Calculator::keyPressEvent(QKeyEvent *e)
{
    //Exiting the application by a click on escape
    if( e->key() == Qt::Key_Escape)
        qApp->exit(0);


    //You could add more keyboard interation here (like digit to button)
}
