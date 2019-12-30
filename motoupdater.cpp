#include "motoupdater.h"
#include <QFile>

MotoUpdater::MotoUpdater(QWidget *parent)
    : QWidget(parent)
{
    networkManager = new QNetworkAccessManager;

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

    QObject::connect(networkManager, &QNetworkAccessManager::finished, this, &MotoUpdater::onResult);
    QObject::connect(btnSearch, SIGNAL(clicked()), this, SLOT(Search()));
}

MotoUpdater::~MotoUpdater()
{
    /*Delete all button*/
    delete btnSearch;
    delete btnDownload;
    delete btnRecovery;
    delete btnInstall;
    delete btnAbout;

    /*Delete TextEdit*/
    delete textLog;

    /*Delete Layouts*/
    delete mainLayout;
}

void MotoUpdater::onResult(QNetworkReply *reply)
{
    if(!reply->error())
    {
        QFile nFile("/sdcard/version");
        nFile.open(QFile::WriteOnly);

        QByteArray bts = reply->readAll();

        nFile.write(bts);

        nFile.close();
    }
    reply->deleteLater();
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

    networkManager->get(QNetworkRequest(QUrl(site)));


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
