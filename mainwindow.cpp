#include "mainwindow.h"
#include "tccom_objectmodel.h"

#include <QCoreApplication>
#include <QMessageBox>
#include <QRegExp>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    int minWidth = 500;
    int minHeight = 500;

    /* Setup QAbstractItemModel & QTreeView */

    QStringList args = QCoreApplication::arguments();

    if(args.size() != 2){

        QString errStr =    R"(Program takes AmsNetId [STRING] as argument)";

        QMessageBox messageBox;
        messageBox.setText(errStr);
        messageBox.setIcon(QMessageBox::Critical);
        messageBox.exec();
        exit(EXIT_FAILURE);
    }

    QString AmsNetId = QCoreApplication:: arguments().at(1);

    QRegExp rxNetId("^(?:[0-9]{1,3}\\.){5}[0-9]{1,3}$");

    if(!rxNetId.exactMatch(AmsNetId)){
        QString errStr =    R"(Can't process AmsNetId. An AmsNet consist of exactly 6 bytes, e.g.: 5.69.55.236.1.1)";
        QMessageBox messageBox;
        messageBox.setText(errStr);
        messageBox.setIcon(QMessageBox::Critical);
        messageBox.exec();
        exit(EXIT_FAILURE);
    }

    this->setWindowTitle(QStringLiteral("TcCOM Viewer"));
    this->setMinimumSize(minWidth, minHeight);
}

MainWindow::~MainWindow()
{
}

