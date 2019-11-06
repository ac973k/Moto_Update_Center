#ifndef MOTOUPDATER_H
#define MOTOUPDATER_H

#include <QWidget>

#include <QPushButton>
#include <QTextEdit>

#include <QGridLayout>

#include <QProcess>

#include "downloader.h"

class MotoUpdater : public QWidget
{
    Q_OBJECT

public:
    MotoUpdater(QWidget *parent = nullptr);
    ~MotoUpdater();

private:
    QPushButton *btnUpdater;
    QPushButton *btnAbout;

    QTextEdit *textLog;

    QGridLayout *mainLayout;

    Downloader m_downloader;

private slots:
    void Search();
    void Download();
    void Install();
    void Recovery();

    void onUpdateProgress(qint64 bytesReceived, qint64 bytesTotal);
};
#endif // MOTOUPDATER_H
