#include <QFile>
#include <QTextStream>
#include "configwindow.h"
#include <QVBoxLayout>
#include <QDialog>
#include <QFile>
#include <QLabel>
#include <QFormLayout>
#include <QPushButton>
#include <QStringList>
#include <QDebug>
#include <QMessageBox>
#include <QSettings>
#include "connectdatabase.h"
#include "configwindow.h"

ConfigWindow::ConfigWindow(QWidget *parent)
    : QDialog(parent)
{

 QIcon icon(":/images/images/settings.png");
 setWindowIcon(icon);
    setWindowTitle("Настройка сети"); // Установка заголовка окна
    setFixedSize(450, 525);

    labelHostDb = new QLabel("Хост базы данных:", this);
    lineHostDb = new QLineEdit(this);
    labelPortDb = new QLabel("Порт базы данных:", this);
    lineEditPortDb = new QLineEdit(this);

    labelNameDb = new QLabel("Название базы данных:", this);
    lineNameDb = new QLineEdit(this);

    labelNameUserDb = new QLabel("Имя пользователя:", this);
    lineEditNameUserDb = new QLineEdit(this);

    labelPassDb = new QLabel("Пароль:", this);
    lineEditPassDb = new QLineEdit(this);

    labelTarget = new QLabel("Target:", this);
    lineEditTarget = new QLineEdit(this);

    labelWebHost = new QLabel("Хост web service:", this);
    lineEditWebHost = new QLineEdit(this);

    // Прочитать текст из файла config.conf
        loadFromFile();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout(this);
    formLayout->addRow(labelHostDb, lineHostDb);
    formLayout->addRow(labelPortDb, lineEditPortDb);

    formLayout->addRow(labelNameDb, lineNameDb);
    formLayout->addRow(labelNameUserDb, lineEditNameUserDb);

    formLayout->addRow(labelPassDb, lineEditPassDb);


    formLayout->addRow(labelTarget, lineEditTarget);
    formLayout->addRow(labelTarget, lineEditTarget);


    formLayout->addRow(labelWebHost, lineEditWebHost);

    mainLayout->addLayout(formLayout);
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch(); // Add a stretch spacer

    saveButton = new QPushButton(" Сохранить ", this);
    saveButton->setFixedSize(saveButton->sizeHint());

    connect(saveButton, &QPushButton::clicked, this, &ConfigWindow::saveToFile);

    buttonLayout->addWidget(saveButton);
    cancelButton = new QPushButton(" Отменить ввод ", this);
    cancelButton->setFixedSize(cancelButton->sizeHint());
    connect(cancelButton, &QPushButton::clicked, this, &ConfigWindow::cancelChanges);

    buttonLayout->addWidget(cancelButton);
    mainLayout->addStretch(1);
    mainLayout->addLayout(buttonLayout);

    // Создание чекбокса
    checkBox = new QCheckBox("Изменить", this);
    checkBox->setChecked(false);

    connect(checkBox, &QCheckBox::stateChanged, this, &ConfigWindow::toggleFields);

    // Добавление чекбокса в основной макет
    mainLayout->addWidget(checkBox);
    toggleFields();

}

void ConfigWindow::saveToFile()
{
    QString hostDb = lineHostDb->text();
    QString portDb = lineEditPortDb->text();
    QString nameDb = lineNameDb->text();
    QString nameUserDb = lineEditNameUserDb->text();
    QString passDb = lineEditPassDb->text();
    QString target = lineEditTarget->text();
    QString webHost = lineEditWebHost->text();

    QSettings settings("config.conf", QSettings::IniFormat);

    // Задаем параметры базы данных для взаимодействия с ASUV
    settings.beginGroup("DataBase");
    settings.setValue("host", hostDb);
    settings.setValue("port", portDb);
    settings.setValue("name", nameDb);
    settings.setValue("user", nameUserDb);
    settings.setValue("pass", passDb);
    settings.endGroup();

    // Задаем параметры периодичности опроса базы данных ASUV
    settings.beginGroup("Target");
    settings.setValue("target", target);
    settings.endGroup();

    // Задаем параметры для взаимодействия с web service
    settings.beginGroup("WebService");
    settings.setValue("host", webHost);
    settings.endGroup();

    originalText = hostDb; // Обновить оригинальный текст
emit settingsSaved();/// испустили сигнал, что данные обновились
}
///////////////////////////////////////////////////////////////

void ConfigWindow::cancelChanges()
{

     qDebug() << "Original IP Text:" << originalText;
     // Загрузить оригинальный текст в lineEdit
    lineHostDb->setText(originalText);
    lineEditPortDb->setText(originalText);
    lineNameDb->setText(originalText);
    lineEditNameUserDb->setText(originalText);
    lineEditPassDb->setText(originalText);
    lineEditTarget->setText(originalText);
    lineEditWebHost->setText(originalText);
    loadFromFile();
}

/// Чтение из файла в форму
void ConfigWindow::loadFromFile()
{
    QSettings settings("config.conf", QSettings::IniFormat);

    QString hostDbFromFile = settings.value("DataBase/host").toString();
    QString portDbFromFile = settings.value("DataBase/port").toString();
    QString nameDbFromFile = settings.value("DataBase/name").toString();
    QString userDbFromFile = settings.value("DataBase/user").toString();
    QString passDbFromFile = settings.value("DataBase/pass").toString();
    QString targetFromFile = settings.value("Target/target").toString();
    QString webHostFromFile = settings.value("WebService/host").toString();

    lineHostDb->setText(hostDbFromFile);
    lineEditPortDb->setText(portDbFromFile);
    lineNameDb->setText(nameDbFromFile);
    lineEditNameUserDb->setText(userDbFromFile);
    lineEditPassDb->setText(passDbFromFile);
    lineEditTarget->setText(targetFromFile);
    lineEditWebHost->setText(webHostFromFile);
}

void ConfigWindow::toggleFields()
{
    bool enabled = checkBox->isChecked();
    lineHostDb->setEnabled(enabled);
    lineEditPortDb->setEnabled(enabled);
    lineNameDb->setEnabled(enabled);
    lineEditNameUserDb->setEnabled(enabled);
    lineEditPassDb->setEnabled(enabled);
    lineEditTarget->setEnabled(enabled);
    lineEditWebHost->setEnabled(enabled);
}

void ConfigWindow::createDefaultSettings(const QString& configFilePath)
{
    QSettings settings(configFilePath, QSettings::IniFormat);

    /// Задаем параметры базы данных для взаимодействия с ASUV
    settings.beginGroup( "DataBase" );

    /// Задаем хост базы данных
    settings.setValue( "host", "localhost" );
    /// Задаем порт базы данных
    settings.setValue( "port", "5432" );
    /// Задаем имя базы данных
    settings.setValue( "name", "asuv" );
    /// Задаем имя пользователя
    settings.setValue( "user", "asuv" );
    /// Задаем пароль пользователя
    settings.setValue( "pass", "asuv" );

    settings.endGroup();

    /// Задаем параметры для взаимодействия с web service
    settings.beginGroup( "WebService" );

    /// Задаем хост web service
    settings.setValue( "host", "localhost" );
    /// Задаем порт web service
    settings.setValue( "port", "8080" );
    /// Задаем имя пользователя web service
    settings.setValue( "user", "kassiopeya-d" );
    /// Задаем пароль пользователя web service
    settings.setValue( "pass", "kassiopeya-d" );

    settings.endGroup();

    /// Задаем параметры периодичности опроса базы данных ASUV
    settings.beginGroup( "Target" );

    /// Задаем периодичность опроса базы данных ASUV
    settings.setValue( "target", "10.30.1.205" );

    settings.endGroup();

    /// выводим информацию для пользователя
    qDebug() << "=> config.conf not found";
    qDebug() << "=> Generate new config file...";

}

