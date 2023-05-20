#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H
#include <QDialog>
#include <QLineEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QCheckBox>

class ConfigWindow : public QDialog
{
    Q_OBJECT

public:
    ConfigWindow(QWidget *parent = nullptr);
void createDefaultSettings(const QString& configFilePath);
private slots:
void saveToFile();
void cancelChanges();
void loadFromFile();
void toggleFields();


//signals:
signals:
    void settingsSaved(); // Объявление сигнала settingsSaved

private:

     QCheckBox* checkBox;

     QLabel  *labelHostDb, *labelPortDb, *labelNameDb, *labelNameUserDb, *labelPassDb, *labelTarget, *labelWebHost;
     QLineEdit *lineHostDb, *lineEditPortDb, *lineNameDb, *lineEditNameUserDb, *lineEditPassDb, *lineEditTarget, *lineEditWebHost;

     QPushButton *saveButton;
     QPushButton *cancelButton;
     QString originalText;
    // ConfigWindow *configWindow; // Добавляем приватное поле для хранения указателя на экземпляр окна настроек
};

#endif // CONFIGWINDOW_H
