#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString makeGenitive(QString) const;
    void toggleButtonDisabled();
    void toggleDisabled();
    bool isValidEmail(QString);

private:
    Ui::MainWindow *ui;

private slots:
    void on_buttonQuit_clicked();
    void on_buttonGenerate_clicked();
    void on_buttonCopyToClipboard_clicked();
    void on_recipType_currentIndexChanged();
    void on_patientType_currentIndexChanged();
    void on_recipName_textEdited();
    void on_patientName_textEdited();
    void on_patientLogin_child_textEdited();
    void on_patientLogin_parent_textEdited();
    void on_signatureName_textEdited(const QString &arg1);
    void on_emailDate_userDateChanged(const QDate &date);
};

#endif // MAINWINDOW_H
