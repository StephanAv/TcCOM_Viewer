#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "tccom_objectmodel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    std::shared_ptr<TcCOM_ObjectModel> m_tccomNodeModel;
};
#endif // MAINWINDOW_H
