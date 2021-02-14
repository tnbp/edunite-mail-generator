#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QApplication>
#include <QClipboard>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->emailDate->setDate(QDate::currentDate());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonQuit_clicked()
{
    QCoreApplication::quit();
}

void MainWindow::on_buttonGenerate_clicked()
{
    const QString mailGreetingFormalMale = "Sehr geehrter Herr %1,";
    const QString mailGreetingFormalFemale = "Sehr geehrte Frau %1,";
    const QString mailGreetingFormalGeneric = "Sehr geehrte Familie %1,";
    const QString mailGreetingInformal = "Hallo %1,";

    const QString mailBodyFormalParent = "ich habe das Passwort für Ihren Edunite-Zugang auf %1 gesetzt. Sie müssen es beim nächsten Login ändern.";
    const QString mailBodyFormalChild = "ich habe das Passwort für %1 Edunite-Zugang auf %2 gesetzt. Es muss beim nächsten Login geändert werden.";
    const QString mailBodyFormalSelf = "ich habe das Passwort für Ihren Edunite-Zugang auf %1 gesetzt. Sie müssen es beim nächsten Login ändern.";
    const QString mailBodyFormalSelfParents = "ich habe das Passwort für den Edunite-Zugang Ihrer Eltern auf %1 gesetzt. Es muss beim nächsten Login geändert werden.";
    const QString mailBodyFormalAll = "ich habe die Passwörter für alle Edunite-Zugänge auf %1 gesetzt. Die Passwörter müssen jeweils beim nächsten Login geändert werden.";
    const QString mailBodyInformalParent = "ich habe das Passwort für den Edunite-Zugang deiner Eltern auf %1 gesetzt. Es muss beim nächsten Login geändert werden.";
    const QString mailBodyInformalChild = "ich habe das Passwort für deinen Edunite-Zugang auf %1 gesetzt. Es muss beim nächsten Login geändert werden.";

    const QString mailBodyListSingleLogin = "Die zugehörige Login-Adresse lautet: %1";

    const QString mailBodyListAllAccounts = "Die zugehörigen Login-Adressen lauten:";
    const QString mailBodyListAllAccountsParent = "%1 (Eltern-Zugang)";
    const QString mailBodyListAllAccountsChild = "%1 (%2 Zugang)";

    const QString mailBodyPasswordWarningFormal = "BITTE ACHTEN SIE DARAUF, BEIM KOPIEREN DES PASSWORTS KEINE ÜBERZÄHLIGEN LEERZEICHEN ODER ZEILENUMBRÜCHE ZU MARKIEREN.";
    const QString mailBodyPasswordWarningInformal = "BITTE ACHTE DARAUF, BEIM KOPIEREN DES PASSWORTS KEINE ÜBERZÄHLIGEN LEERZEICHEN ODER ZEILENUMBRÜCHE ZU MARKIEREN.";

    const QString mailClosing = "Mit freundlichem Gruß\n%1";

    QString finalMailText;

    const QString pronounYour = ui->recipType->currentIndex()?QString("Ihr"):QString("dein");

    if (ui->recipType->currentIndex() == 2) {
        switch (ui->recipGender->currentIndex()) {
            case 0:
            finalMailText.append(mailGreetingFormalMale.arg(ui->recipName->text()));
            break;

            case 1:
            finalMailText.append(mailGreetingFormalFemale.arg(ui->recipName->text()));
            break;

            default:
            finalMailText.append(mailGreetingFormalGeneric.arg(ui->recipName->text()));
            break;
        }
        finalMailText.append("\n\n");
        switch (ui->patientType->currentIndex()) {
            case 0:
            finalMailText.append(mailBodyFormalChild.arg(MainWindow::makeGenitive(ui->patientName->text())).arg(QString("Riedberg")+QString(ui->emailDate->date().toString(QString("ddMMyy")))));
            finalMailText.append("\n");
            finalMailText.append(mailBodyListSingleLogin.arg(ui->patientLogin_child->text()));
            break;

            case 1:
            finalMailText.append(mailBodyFormalParent.arg(QString("Riedberg")+QString(ui->emailDate->date().toString(QString("ddMMyy")))));
            finalMailText.append("\n");
            finalMailText.append(mailBodyListSingleLogin.arg(ui->patientLogin_parent->text()));
            break;

            default:
            finalMailText.append(mailBodyFormalAll.arg(QString("Riedberg")+QString(ui->emailDate->date().toString(QString("ddMMyy")))));
            finalMailText.append("\n\n");
            finalMailText.append(mailBodyListAllAccounts);
            finalMailText.append("\n");
            finalMailText.append(mailBodyListAllAccountsParent.arg(ui->patientLogin_parent->text()));
            finalMailText.append("\n");
            finalMailText.append(mailBodyListAllAccountsChild.arg(ui->patientLogin_child->text()).arg(MainWindow::makeGenitive(ui->patientName->text())));
            break;
        }
    }
    else if (ui->recipType->currentIndex() == 1) {
        switch (ui->recipGender->currentIndex()) {
            case 0:
            finalMailText.append(mailGreetingFormalMale.arg(ui->recipName->text()));
            break;

            case 1:
            finalMailText.append(mailGreetingFormalFemale.arg(ui->recipName->text()));
            break;

            default:
            finalMailText.append(mailGreetingInformal.arg(ui->recipName->text()));
            break;
        }
        finalMailText.append("\n\n");
        switch (ui->patientType->currentIndex()) {
            case 0:
            finalMailText.append(mailBodyFormalSelf.arg(QString("Riedberg")+QString(ui->emailDate->date().toString(QString("ddMMyy")))));
            finalMailText.append("\n");
            finalMailText.append(mailBodyListSingleLogin.arg(ui->patientLogin_child->text()));
            break;

            case 1:
            finalMailText.append(mailBodyFormalSelfParents.arg(QString("Riedberg")+QString(ui->emailDate->date().toString(QString("ddMMyy")))));
            finalMailText.append("\n");
            finalMailText.append(mailBodyListSingleLogin.arg(ui->patientLogin_parent->text()));
            break;

            default:
            finalMailText.append(mailBodyFormalAll.arg(QString("Riedberg")+QString(ui->emailDate->date().toString(QString("ddMMyy")))));
            finalMailText.append("\n\n");
            finalMailText.append(mailBodyListAllAccounts);
            finalMailText.append("\n");
            finalMailText.append(mailBodyListAllAccountsParent.arg(ui->patientLogin_parent->text()));
            finalMailText.append("\n");
            finalMailText.append(mailBodyListAllAccountsChild.arg(ui->patientLogin_child->text()).arg(pronounYour));
            break;
        }
    }
    else {
        finalMailText.append(mailGreetingInformal.arg(ui->recipName->text()));
        finalMailText.append("\n\n");
        switch (ui->patientType->currentIndex()) {
            case 0:
            finalMailText.append(mailBodyInformalChild.arg(QString("Riedberg")+QString(ui->emailDate->date().toString(QString("ddMMyy")))));
            finalMailText.append("\n");
            finalMailText.append(mailBodyListSingleLogin.arg(ui->patientLogin_child->text()));
            break;

            case 1:
            finalMailText.append(mailBodyInformalParent.arg(QString("Riedberg")+QString(ui->emailDate->date().toString(QString("ddMMyy")))));
            finalMailText.append("\n");
            finalMailText.append(mailBodyListSingleLogin.arg(ui->patientLogin_parent->text()));
            break;

            default:
            finalMailText.append(mailBodyFormalAll.arg(QString("Riedberg")+QString(ui->emailDate->date().toString(QString("ddMMyy")))));
            finalMailText.append("\n\n");
            finalMailText.append(mailBodyListAllAccounts);
            finalMailText.append("\n");
            finalMailText.append(mailBodyListAllAccountsParent.arg(ui->patientLogin_parent->text()));
            finalMailText.append("\n");
            finalMailText.append(mailBodyListAllAccountsChild.arg(ui->patientLogin_child->text()).arg(pronounYour));
            break;
        }
    }
    finalMailText.append("\n\n");
    if (ui->recipType->currentIndex() == 0) finalMailText.append(mailBodyPasswordWarningInformal);
    else finalMailText.append(mailBodyPasswordWarningFormal);
    finalMailText.append("\n\n");
    finalMailText.append(mailClosing.arg(ui->signatureName->text()));
    ui->plainTextEditMailBody->setPlainText(finalMailText);
}

void MainWindow::on_buttonCopyToClipboard_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(ui->plainTextEditMailBody->toPlainText());
}

QString MainWindow::makeGenitive(QString name) const
{
    if (name.endsWith("s") || name.endsWith("z") || name.endsWith("x")) name.append("'");
    else name.append("s");
    return name;
}

void MainWindow::on_recipType_currentIndexChanged()
{
    MainWindow::toggleDisabled();
}

void MainWindow::on_patientType_currentIndexChanged()
{
    MainWindow::toggleDisabled();
}

void MainWindow::toggleDisabled() {
    int recipType = ui->recipType->currentIndex();
    int patientType = ui->patientType->currentIndex();

    //const int RECIP_CHILD_INFORMAL = 0;
    const int RECIP_CHILD_FORMAL = 1;
    const int RECIP_PARENT = 2;

    const int PATIENT_CHILD = 0;
    const int PATIENT_PARENT = 1;
    const int PATIENT_ALL = 2;

    // enable or disable gender selector? -> enable only if recip is parent or formal child!
    if (recipType == RECIP_PARENT || recipType == RECIP_CHILD_FORMAL) {
        ui->recipGender->setDisabled(false);
    }
    else {
        ui->recipGender->setDisabled(true);
    }
    // enable patient name? -> enable only if patient is child OR all!
    if (patientType == PATIENT_CHILD || patientType == PATIENT_ALL) {
        // but not if recip is child!
        if (recipType == RECIP_PARENT) ui->patientName->setDisabled(false);
        else ui->patientName->setDisabled(true);
    }
    else {
        ui->patientName->setDisabled(true);
    }
    // enable patientLogin_child? -> enable if patient is child or all!
    if (patientType == PATIENT_CHILD || patientType == PATIENT_ALL) {
        ui->patientLogin_child->setDisabled(false);
    }
    else {
        ui->patientLogin_child->setDisabled(true);
    }
    // enable patientLogin_parent? -> enable if patient is parent or all!
    if (patientType == PATIENT_PARENT || patientType == PATIENT_ALL) {
        ui->patientLogin_parent->setDisabled(false);
    }
    else {
        ui->patientLogin_parent->setDisabled(true);
    }
}

void MainWindow::on_recipName_textEdited()
{
    MainWindow::toggleButtonDisabled();
}

void MainWindow::on_patientName_textEdited()
{
    MainWindow::toggleButtonDisabled();
}

void MainWindow::on_patientLogin_child_textEdited()
{
    MainWindow::toggleButtonDisabled();
}

void MainWindow::on_patientLogin_parent_textEdited()
{
    MainWindow::toggleButtonDisabled();
}

void MainWindow::toggleButtonDisabled()
{
    bool disabled = false;
    if (ui->recipName->text().isEmpty()) disabled = true;
    if (ui->signatureName->text().isEmpty()) disabled = true;
    if (ui->patientName->isEnabled() && ui->patientName->text().isEmpty()) disabled = true;
    if (ui->patientLogin_child->isEnabled() && !MainWindow::isValidEmail(ui->patientLogin_child->text())) disabled = true;
    if (ui->patientLogin_parent->isEnabled() && !MainWindow::isValidEmail(ui->patientLogin_parent->text())) disabled = true;
    ui->buttonGenerate->setDisabled(disabled);
}

bool MainWindow::isValidEmail(QString email)
{
    QRegExp mailREX("\\b[A-Z0-9._%+-äÄöÖüÜß]+@[A-Z0-9äÄöÖüÜß\\-.]+\\.[A-Z]{2,4}\\b");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
    return mailREX.exactMatch(email);
}

void MainWindow::on_signatureName_textEdited(const QString &arg1)
{
    MainWindow::toggleButtonDisabled();
}

void MainWindow::on_emailDate_userDateChanged(const QDate &date)
{
    ui->resultingPassword->setText(QString("Riedberg")+QString(date.toString(QString("ddMMyy"))));
}
