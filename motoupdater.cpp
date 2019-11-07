#include "motoupdater.h"
#include <fstream>

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

    QObject::connect(&m_downloader, &Downloader::updateDownloadProgress, this, &MotoUpdater::onUpdateProgress);
    QObject::connect(btnSearch, SIGNAL(clicked()), this, SLOT(Search()));
}

MotoUpdater::~MotoUpdater()
{

}

void MotoUpdater::Search()
{
    std::ifstream fCurrentVersion("/system/version");
    int iCurrentVersion;

    fCurrentVersion >> iCurrentVersion;

    std::string site = "http://motoc.at.ua/update/";
    QString sSite = QString::fromStdString(site);
    sSite = sSite + QString::number(iCurrentVersion);
    sSite += ".noext";

    QUrl url;
    //url.setUrl(sSite);
    url.setUrl("https://motoc.at.ua/update/20181121.noext");

    m_downloader.get(url);

    auto result = "/sdcard/" + std::to_string(iCurrentVersion);
    std::string sNewVer = result + ".noext";

    std::ifstream fNewVersion(sNewVer);
    int iNewVersion;

    fNewVersion >> iNewVersion;

    if (iCurrentVersion < iNewVersion)
    {
        textLog->setPlainText("Доступна новая версия!");
        btnDownload->setDisabled(false);
    }
    else if (iCurrentVersion == iNewVersion)
    {
        textLog->setPlainText("Новых обновлений нет!");
    }
    else
    {
        //textLog->setPlainText("Что-то пошло не так...");
    }
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

void MotoUpdater::onUpdateProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    while(bytesReceived < bytesTotal)
    {
        textLog->setText("Загружено " + bytesReceived);
    }
}
