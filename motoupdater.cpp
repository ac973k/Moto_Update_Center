#include "motoupdater.h"
#include <QFile>

MotoUpdater::MotoUpdater(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QGridLayout;

    textLog = new QTextEdit;

    btnSearch = new QPushButton(tr("Search"));
    btnDownload = new QPushButton(tr("Download"));
    btnRecovery = new QPushButton(tr("Recovery"));
    btnInstall = new QPushButton(tr("Install"));
    btnAbout = new QPushButton(tr("About"));

    mainLayout->addWidget(btnSearch, 0, 0);
    mainLayout->addWidget(btnDownload, 0, 1);
    mainLayout->addWidget(textLog, 1, 0, 1, 2);
    mainLayout->addWidget(btnRecovery, 2, 0);
    mainLayout->addWidget(btnInstall, 2, 1);
    mainLayout->addWidget(btnAbout, 3, 0, 3, 2);

    setLayout(mainLayout);

    QObject::connect(btnSearch, SIGNAL(clicked()), this, SLOT(Search()));
}

MotoUpdater::~MotoUpdater()
{

}

void MotoUpdater::Search()
{   /*Get current version and print to TextEdit*/
    QFile fCurrentVersion("/system/version");
    fCurrentVersion.open(QFile::ReadOnly);

    QString tmpStr = fCurrentVersion.readLine();
    int iCurrentVersion = tmpStr.toInt();

    QString sCurrentVersion = "Текущая версия: " + QString::number(iCurrentVersion);

    textLog->append(sCurrentVersion);

    /*
     * Get link to updated file and download this file
    */
    QString  site = "https://ac973k.github.io/update/" + QString::number(iCurrentVersion);

    QProcess *procSearch = new QProcess;
    procSearch->setProcessChannelMode(QProcess::SeparateChannels);
    procSearch->start("aria2c" , QStringList() << "-d" << "/sdcard/" << site);

    textLog->append(procSearch->readAll());
}

void MotoUpdater::Download()
{

}

void MotoUpdater::Install()
{

}

void MotoUpdater::Recovery()
{

}
