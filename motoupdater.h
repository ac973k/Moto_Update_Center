#ifndef MOTOUPDATER_H
#define MOTOUPDATER_H

#include <QWidget>

#include <QPushButton>
#include <QTextEdit>

#include <QGridLayout>

#include <QProcess>

class MotoUpdater : public QWidget
{
    Q_OBJECT

public:
    MotoUpdater(QWidget *parent = nullptr);
    ~MotoUpdater();

private:
    QPushButton *btnSearch;
    QPushButton *btnDownload;
    QPushButton *btnInstall;
    QPushButton *btnRecovery;
    QPushButton *btnAbout;

    QTextEdit *textLog;

    QGridLayout *mainLayout;

private slots:
    void Search();
    void Download();
    void Install();
    void Recovery();
};
#endif // MOTOUPDATER_H
