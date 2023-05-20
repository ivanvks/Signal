#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTabWidget>
#include <QPushButton>
#include <QLabel>
#include "connectdatabase.h"
#include "configwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void openNewWindow();
    void updateDatabaseConnectionStatus(bool connected);
    void updateConnection(); // Новый слот для сохранения настроек
private:
    QTabWidget *tabWidget;
    QPushButton *button;
    QLabel* connectionStatusIcon;
    ConnectDatabase *connectDatabase;

};
#endif // MAINWINDOW_H
