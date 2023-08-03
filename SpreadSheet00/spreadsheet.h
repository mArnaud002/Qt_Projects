#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QMainWindow>
#include <QTableWidget>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QLabel>
#include <QStatusBar>
#include <QListWidgetItem>

class spreadSheet : public QMainWindow
{
    Q_OBJECT

public:
    spreadSheet(QWidget *parent = nullptr);
    ~spreadSheet();

protected :
    void createActions();   //creer les actions
    void createMenus();     //creer les menus
    void createToolBars();  //creer la barre d'outils
    void makeConnexions();  //realiser les connexions
    void saveContent(QString fileName)const;     //Sauvegarder
    void loadContent(QString fileName)const;     //Ouvrir
    void loadCsvFile(QString fileName)const;
    bool okToContinue();
    void save();
    QString strippedName(const QString &fullFileName);

private slots :
    void updateStatusBar(int, int); //mettre à jour la barre d'état
    void aboutQtSlot();
    void goCellSlot();
    void findTextSlot();
    void saveSlot(); //pour repondre à l'appel de sauvegarde
    void loadSlot(); // pour charger un fichier
    void loadCsvSlot();
    void newFileSlot();
    bool saveAs();
    void updateRecentFile();        // Monter les fichiers récents
    void openRecentFile();  //Ouvrir les fichiers récents


private :

    //Pointeur sur le widget principal
    QTableWidget *spreadsheet;

    //Pointeurs sur les actions
    QAction * newFile;   //Action pour ouvir un fichier
    QAction * saveFile;  //Action pour sauvegarder un fichier
    QAction * loadFile;  //Action pour ouvrir un fichier
    QAction * quit;  //Action pour quitter
    QAction * about; //Action pour afficher les informations
    QAction * aboutQt;   //Action pour afficher les informations sur QT
    QAction * cutFile;  //Action pour couper un fichier
    QAction * saveAsFile;   //Action pour sauvegarder un fichier
    QAction * all;   //Action pour sélectionner tout le spread sheet
    QAction * row;   //Action pour sélectionner un ligne du spread sheet
    QAction * column;   //Action pour sélectionner un colonne du spread sheet
    QAction * showGrid;  //Action pour
    QAction * goCell;   //Action pour aller à la cellule
    QAction * findText; //Action pour chercher le texte
    QAction * loadCSv;


    enum { MaxRecentFiles = 5 };
    int recentFileIds[MaxRecentFiles];
    QAction *recentFileActions[MaxRecentFiles];
    QAction *separatorAction;

    //Pointeurs sur les menus
    QMenu *fileMenu;    //Menu qui regroupe les actions file
    QMenu *helpMenu;    //Menu qui regroupe les action d'aide
    QMenu *editMenu;    //Menu qui permet d'editer
    QMenu *recentFileMenu;  //Menu qui affiche les fichiers récents
    //Pointeurs sur les labels
    QLabel *cellLocation;
    QLabel *cellFormula;

    //Atribut de nom de fichier
    QString * currentFile;
    QStringList * recentFiles;


};
#endif // SPREADSHEET_H
