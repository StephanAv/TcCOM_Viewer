#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QVBoxLayout>
#include <memory>
#include "tccom_objectmodel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Central Layout
    QWidget     m_centralWidget;
    QVBoxLayout m_mainLayout;

    // Contente
    QTreeView m_treeView;
    TcCOM_ObjectModel *m_TcComNodeModel;

private:

    //std::shared_ptr<TcCOM_ObjectModel> m_tccomNodeModel;
};
#endif // MAINWINDOW_H
