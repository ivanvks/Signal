#include<QVBoxLayout>
#include <QDialog>
#include <QFile>
#include <QLabel>
#include <QFormLayout>
#include <QMessageBox>
#include <QPixmap>
#include "mainwindow.h"
#include "configwindow.h"
#include "connectdatabase.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    tabWidget = new QTabWidget(this);

    QWidget *tab1 = new QWidget();
    tabWidget->addTab(tab1, "Tab 1");

    QWidget *tab2 = new QWidget();
    tabWidget->addTab(tab2, "Tab 2");

    QWidget *tab3 = new QWidget();
    tabWidget->addTab(tab3, "Tab 3");
/////////////////////////////////////////////////////////////////
    button = new QPushButton(this);
    button->setToolTip("Настройка сети");

  button->setIcon(QIcon(":/images/images/ellow.png")); // Устанавливаем изображение иконки

   button->setIconSize(QSize(25, 25));

    int buttonSize = 25;  // Размер кнопки
    button->setFixedSize(buttonSize, buttonSize);
    int borderRadius = buttonSize / 2;  // Радиус скругления

    button->setStyleSheet(QString("QPushButton { border-radius: %1px; }").arg(borderRadius));

    connect(button, &QPushButton::clicked, this, &MainWindow::openNewWindow);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layoutV = new QVBoxLayout(centralWidget);

    connectionStatusIcon = new QLabel(this);
      QPixmap   grayIcon(":/images/images/stat.png"); // Путь к изображению серой иконки

        connectionStatusIcon->setPixmap(grayIcon);

        // Создание горизонтального контейнера для размещения кнопки и иконки
        QHBoxLayout* layoutH = new QHBoxLayout;
        layoutH->addStretch(2);
        layoutH->addWidget( connectionStatusIcon, 0, Qt::AlignRight );
        layoutH->addWidget( button, 0, Qt::AlignRight);

        layoutV->addLayout( layoutH );

        layoutV->addWidget(tabWidget);
        centralWidget->setLayout(layoutV);

        setCentralWidget(centralWidget);

    // Проверяем существует ли файл настроек
    QString configFilePath = "config.conf";

    // Проверяем наличие файла
    QFile file(configFilePath);
    if (!file.exists()) {
        ///Создаем экземпляр класса ConfigWindow
       ConfigWindow configWindow(this);
       configWindow.createDefaultSettings(configFilePath);
        // Файл не найден, выводим предупреждение
        QMessageBox::warning(nullptr, "Внимание!", "Файл настроек сети не найден. Будет создан файл настроек по умолчанию! "
                                                       "Если соединение не установлено, то требуется внести изменения в настройки конфигурации сети "
                                                       " в меню настроек!");

    }
    connectDatabase = new ConnectDatabase(this);
    connect(connectDatabase, &ConnectDatabase::databaseConnected, this, &MainWindow::updateDatabaseConnectionStatus);
    connectDatabase->checkDatabaseConnection();
}

void MainWindow::openNewWindow()
{
    ConfigWindow *configWindow = new ConfigWindow(this);
    connect(configWindow, &ConfigWindow::settingsSaved, this, &MainWindow::updateConnection); // Подключение сигнала к слоту
    configWindow->exec();

}
// Обновление подключения к базе данных
void MainWindow::updateConnection()
{
    connectDatabase->checkDatabaseConnection(); // Обновление подключения к базе данных
}
// смена статусов подключения
void MainWindow::updateDatabaseConnectionStatus(bool connected)
{
    if (connected) {
            QPixmap greenIcon(":/images/images/green.png"); // Путь к изображению зеленой иконки
            connectionStatusIcon->setPixmap(greenIcon);
        } else {
            QPixmap redIcon(":/images/images/red.png"); // Путь к изображению красной иконки
            connectionStatusIcon->setPixmap(redIcon);
        }

}
