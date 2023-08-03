#include "spreadsheet.h"
#include <QPixmap>
#include <QMenuBar>
#include <QToolBar>
#include <QApplication>
#include <QMessageBox>
#include "godialog.h"
#include "finddialog.h"
#include <QFileDialog>
#include <QTextStream>
#include <QMutableStringListIterator>
#include <QTableWidgetSelectionRange>
#include <QDebug>
#include <QStandardItem>
#include <QSettings>
#include <QString>



spreadSheet::spreadSheet(QWidget *parent)
    : QMainWindow(parent)
{
    spreadsheet = new QTableWidget;
    spreadsheet->setRowCount(20);
    spreadsheet->setColumnCount(10);
    setCentralWidget(spreadsheet);

    //creer les actions
    createActions();
    //creer les menus
    createMenus();
    //cree la barre d'outils
    createToolBars();
    //realiser les connexions
    makeConnexions();

    //labels pour la barre d'état
    cellLocation = new QLabel("(1, 1)");
    cellFormula = new QLabel("");
    statusBar()->addPermanentWidget(cellLocation);
    statusBar()->addPermanentWidget(cellFormula);

    //Changer les label du spreadsheet
    QStringList labels;
    //Remplir la liste des label
    for(char letter = 'A'; letter <='Z'; letter++)
        labels <<QString(letter);
    spreadsheet->setVerticalHeaderLabels(labels);

    //Initier le champ de current file
    currentFile = nullptr;
    setWindowTitle("Buffer");
}

spreadSheet::~spreadSheet()
{
    delete spreadsheet;

    delete newFile;
    delete loadFile;
    delete saveFile;
    delete saveAsFile;
    delete quit;
    delete cutFile;
    delete row;
    delete column;
    delete all;
    delete showGrid;
    delete about;
    delete aboutQt;
    delete goCell;
    delete findText;

    delete fileMenu;
    delete editMenu;
    delete helpMenu;
}

void spreadSheet :: createActions()
{
    //Pour construire une action, il nous faut en générale 4 étapes

    //Etape 1 : Lui choisir une icone
    QPixmap quitIcon(":/quit_icon.png");
    QPixmap newIcon(":/new_file.png");
    QPixmap saveIcon(":/save_file");
    QPixmap cutIcon(":/cut_icon.png");
    QPixmap goIcon(":/go_to_icon.png");
    QPixmap searchIcon(":/search_icon.png");


    //Etape 2 : Creer l'action
    quit = new QAction(quitIcon, "&Quit", this);
    newFile = new QAction(newIcon,"&New File",this);
    saveFile = new QAction(saveIcon, "&Save File",this);
    loadFile = new QAction("&Load File",this);
    cutFile = new QAction(cutIcon, "&Cut File",this);
    saveAsFile = new QAction(saveIcon, "&Save As File",this);
    row = new QAction("Row",this);
    column = new QAction("Column",this);
    all = new QAction("&Select All",this);
    showGrid = new QAction("Show Grid",this);
    aboutQt = new QAction("&About Qt",this);
    about = new QAction("About",this);
    goCell = new QAction(goIcon,"Go to Cell",this);
    findText = new QAction(searchIcon,"Search",this);
    loadCSv = new QAction( "Load CSV File", this);

    //Etape 3 : Lui choisir un racourci
    quit->setShortcut(tr("Ctrl+Q"));
    newFile->setShortcut(tr("Ctrl+N"));
    saveFile->setShortcut(tr("Ctrl+S"));
    saveAsFile->setShortcut(tr("Ctrl+Shift+S"));
    all->setShortcut(tr("Ctrl+A"));
    cutFile->setShortcut(tr("Ctrl+X"));
    loadFile->setShortcut(tr("Ctrl+O"));
    loadCSv->setShortcut(tr("Ctrl+Shift+O"));
    findText->setShortcut(tr("Ctrl+F"));

    for (int i = 0; i < MaxRecentFiles; ++i) {
            recentFileActions[i] = new QAction(this);
            recentFileActions[i]->setVisible(false);
            connect(recentFileActions[i], SIGNAL(triggered()),
                    this, SLOT(openRecentFile()));
        }
}

void spreadSheet :: createMenus()
{
    //Creer le menu file
    fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(newFile);
    fileMenu->addAction(loadFile);
    fileMenu->addAction(loadCSv);
    fileMenu->addAction(saveFile);
    fileMenu->addAction(saveAsFile);
    fileMenu->addSeparator();
    fileMenu->addSeparator();
    fileMenu->addAction(cutFile);
    fileMenu->addSeparator();
    recentFileMenu = fileMenu->addMenu("Recent Files");
    separatorAction = fileMenu->addSeparator();
    for (int i = 0; i < MaxRecentFiles; ++i)
            fileMenu->addAction(recentFileActions[i]);
    fileMenu->addSeparator();
    fileMenu->addAction(quit);
    updateRecentFile();

    //Creer le menu help
    helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(about);
    helpMenu->addAction(aboutQt);

    //Creer le menu d'édition
    editMenu = menuBar()->addMenu("&Edit");
    auto select = editMenu->addMenu("Select");
    select->addAction(row);
    select->addAction(column);
    select->addAction(all);
    editMenu->addAction(showGrid);

    for (int i = 0; i < MaxRecentFiles; ++i)
           fileMenu->addAction(recentFileActions[i]);


}


void spreadSheet :: createToolBars()
{
    auto toolBar1=addToolBar("Tool Bar");
    toolBar1->addAction(quit);
    toolBar1->addAction(newFile);
    auto toolBar2=addToolBar("Tool Bar2");
    toolBar2->addAction(aboutQt);
    toolBar2->addAction(goCell);
    toolBar2->addAction(findText);
}

void spreadSheet :: makeConnexions()
{
    //Etape 4 : Lui choisir un slot
    connect(quit, &QAction :: triggered, this, &QMainWindow :: close);

    connect(aboutQt, &QAction :: triggered, this, &spreadSheet :: aboutQtSlot);

    connect(all, &QAction :: triggered, spreadsheet, &QTableWidget :: selectAll);

    connect(row, &QAction :: triggered, spreadsheet, &QTableWidget :: selectRow);

    connect(column, &QAction :: triggered, spreadsheet, &QTableWidget :: selectColumn);

    showGrid->setCheckable(true);
    showGrid->setChecked(spreadsheet->showGrid());
    connect(showGrid,&QAction::triggered,spreadsheet,&QTableWidget::setShowGrid);

    //connectting the chane of any element in the spreadsheet with the update status bar
    connect(spreadsheet, &QTableWidget::cellClicked, this,  &spreadSheet::updateStatusBar);

    //Connection pour le go to cell
    connect(goCell, &QAction ::triggered,this, &spreadSheet:: goCellSlot);

    //Connection pour le find text
    connect(findText, &QAction :: triggered, this, &spreadSheet :: findTextSlot);

    //Connecter le save Action au save Slot
    connect(saveFile, &QAction ::triggered, this, &spreadSheet :: saveSlot);

    //
    connect(saveAsFile, &QAction :: triggered, this, &spreadSheet :: saveAs);

    //Connecter le load Action au load Slot
    connect(loadFile, &QAction ::triggered, this, &spreadSheet :: loadSlot);

    //
    connect(loadCSv, &QAction ::triggered, this, &spreadSheet :: loadCsvSlot);

    connect(newFile, &QAction :: triggered, this, &spreadSheet :: newFileSlot);

}

void spreadSheet :: saveContent(QString fileName)const
{
    //Syntaxe C++
    // ofstream out(fileName)  -------. /out.close();

    //Syntaxe C
    //FILE * fid = fopen(fileName, "w")         fclose(fid);

    //En Qt
    // un pointeur sur le fichier d'interet
    QFile file(fileName);
    //Ouvrir le fichier
    if(file.open(QIODevice :: WriteOnly))
    {
        QTextStream out(&file);

        //Parcourir les cellules et sauvegarder leur contenu
        for ( int i = 0; i < spreadsheet->rowCount() ; i++ )
            for (int j = 0; j < spreadsheet->columnCount() ; j++ )
            {
                auto cell = spreadsheet->item(i,j);
                if (cell)
                {
                    out << i << "," << j << "," <<cell->text() <<Qt::endl;
                }
            }
    }
        //Fermer le ficher
    file.close();
}

void spreadSheet :: loadContent(QString fileName) const
{
    QFile file(fileName);
    if(file.open(QIODevice :: ReadOnly))
    {
        QTextStream in(&file);
        QString line;

        while (!in.atEnd())
        {
            line = in.readLine();
            auto tokens = line.split(',');
            int row = tokens[0].toInt();
            int col = tokens[1].toInt();
            spreadsheet->setItem(row,col, new QTableWidgetItem(tokens[2]));
        }
    }

    file.close();
}

void spreadSheet :: loadCsvFile(QString fileName) const
{

    QFile file(fileName);

    if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
           qDebug() << "File not exists";
       } else {
           // Create a thread to retrieve data from a file
           QTextStream in(&file);
           //Reads the data up to the end of file
           while (!in.atEnd())
           {
               QString line = in.readLine();
               // Adding to the model in line with the elements
               QList<QStandardItem *> standardItemsList;
               // consider that the line separated by semicolons into columns
               for (QString item : line.split(";"))
               {
                   standardItemsList.append(new QStandardItem(item));
               }
               spreadsheet->insertRow(spreadsheet->rowCount());
           }
           file.close();
       }
}

QString spreadSheet :: strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void spreadSheet :: aboutQtSlot()
{
    QMessageBox :: aboutQt(this, "About Me");
}

void spreadSheet :: updateStatusBar(int row,int col)
{
    QString cell{"(%0, %1)"};
    cellLocation->setText(cell.arg(row+1).arg(col+1));
}

void spreadSheet :: updateRecentFile()
{
    QSettings settings;
    QStringList files = settings.value("recentFileList").toStringList();

    int numRecentFiles = qMin(files.size(), (int)MaxRecentFiles);

    for (int i = 0; i < numRecentFiles; ++i) {
        QString text = tr("&%1 %2").arg(i + 1).arg(strippedName(files[i]));
        recentFileActions[i]->setText(text);
        recentFileActions[i]->setData(files[i]);
        recentFileActions[i]->setVisible(true);
    }
    for (int j = numRecentFiles; j < MaxRecentFiles; ++j)
        recentFileActions[j]->setVisible(false);

    separatorAction->setVisible(numRecentFiles > 0);
}

void spreadSheet :: openRecentFile()
{


    QAction *action = qobject_cast<QAction *> (sender());
    if (action)
        loadContent(action->data().toString());
}

void spreadSheet:: goCellSlot()
{
    //1. Creer le dialogue
    GoDialog D;

    //2.Executer le dialogue
    auto reply = D.exec();

    //3.Verifier si le dialogue a ete accepte
    if(reply == GoDialog :: Accepted)
    {
        //B32
        //Extraire le texte
        QString cell = D.getCell();

        //a->b->c ------z .......A->b->....L
        //Extraire la ligne
        int row = cell[0].toLatin1() - 'A';

        //Extraire le colonne
        cell = cell.remove(0,1);
        int col = cell.toInt()-1;

        //Changer la cellule
        statusBar()->showMessage("Changing the current cell",2000);
        spreadsheet->setCurrentCell(row,col);

    }
}

void spreadSheet :: findTextSlot()
{
    //1. Creer le dialogue
    FindDialog F;

    //Executer le dialogue
    auto launch = F.exec();
    auto found = false;

    //Verifier si le dialogue a été accepté
    if (launch == FindDialog :: Accepted)
    {
        //Extraire le texte
        QString text = F.getText();
        for ( int i = 0; i < spreadsheet->rowCount() ; i++ )
            for (int j = 0; j < spreadsheet->columnCount() ; j++ )
            {
                if(spreadsheet->item(i,j))
                {
                    if(text == spreadsheet->item(i,j)->text() )
                    {
                        //Changer la cellule
                        statusBar()->showMessage("Searching",2000);
                        spreadsheet->setCurrentCell(i,j);
                        found = true;
                    }
                }
            }
        if(!found)
            QMessageBox::information(this,"Error", "Not found");
    }
}

void spreadSheet :: saveSlot()
{
    //1. Tester si on possède un nom de fichier
    if(!currentFile)
    {

        //Creer factory design
        QFileDialog D; //factory

        //Creer un dialoque pour abtenir le nom du fichier
        auto fileName = D.getSaveFileName();

        //Changer le nom du fichier courant
        currentFile = new QString(fileName);

        //Mettre à jour le titre de la fenêtre
        setWindowTitle(*currentFile);
    }

    //2. Sauvegarder le contrenu
    saveContent(*currentFile);

}

void spreadSheet :: loadSlot()
{
    //1. Tester si on possède un nom de fichier

        //Creer factory design
        QFileDialog D; //factory

        //Creer un dialoque pour abtenir le nom du fichier
        auto fileName = D.getOpenFileName();

        if(fileName != "")
        {
            //Changer le nom du fichier courant
            currentFile = new QString(fileName);

            //Mettre à jour le titre de la fenêtre
            setWindowTitle(*currentFile);

            //2. charger le contrenu
            loadContent(*currentFile);
        }

}

void spreadSheet :: loadCsvSlot()
{
    //1. Tester si on possède un nom de fichier

        //Creer factory design
        QFileDialog D; //factory

        //Creer un dialoque pour abtenir le nom du fichier
        auto fileName = D.getOpenFileName();

        if(fileName != "")
        {
            //Changer le nom du fichier courant
            currentFile = new QString(fileName);

            //Mettre à jour le titre de la fenêtre
            setWindowTitle(*currentFile);

            //2. charger le contrenu
            loadCsvFile(*currentFile);
        }

}
void spreadSheet ::newFileSlot()
{
        spreadSheet *spread = new spreadSheet;
        spread->show();
}

bool spreadSheet ::okToContinue()
{
    if (isWindowModified())
    {
        int r = QMessageBox::warning(this, tr("Spreadsheet"),tr("The document has been modified.\n""Do you want to save your changes?"),QMessageBox::Yes | QMessageBox::No| QMessageBox::Cancel);
        if (r == QMessageBox::Yes) {
            save();
        } else if (r == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

void spreadSheet::save()
{
    if (currentFile->isEmpty()) {
        //saveAsSlot();
        saveSlot();
    } else {
        saveSlot();
    }
}

bool spreadSheet::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                               tr("Save Spreadsheet"), ".",
                               tr("Spreadsheet files (*.sp)"));
    if (fileName.isEmpty())
        return false;
   saveContent(fileName);
    return true;
}
