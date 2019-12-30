#ifndef MOTOUPDATER_H
#define MOTOUPDATER_H

#include <QWidget>

#include <QPushButton>
#include <QTextEdit>

#include <QGridLayout>

#include <QProcess>
#include <QNetworkAccessManager>
#include <QNetworkReply>

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

    QNetworkAccessManager *networkManagerSearch;
    QNetworkAccessManager *networkManagerDownload;

    QProcess *procUnpacker;
    QProcess *procInstaller;

private slots:
    void Search();
    void Download();
    void Install();
    void Recovery();

    void onSearchResult(QNetworkReply *reply);
    void onDownloadResult(QNetworkReply *reply);
};
#endif // MOTOUPDATER_H
