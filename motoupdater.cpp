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

    QObject::connect(&m_downloader, &Downloader::updateDownloadProgress, this, &MotoUpdater::onUpdateProgress);
    QObject::connect(btnSearch, SIGNAL(clicked()), this, SLOT(Search()));
}

MotoUpdater::~MotoUpdater()
{

}

void MotoUpdater::Search()
{
    QFile fCurrentVersion("/system/version");

    QString data;

    fCurrentVersion.open(QIODevice::ReadOnly);

    data = fCurrentVersion.readLine();

    int iCurrentVersion = data.toInt();

    QString test = "Переменная iCurrentVersion: " + QString::number(iCurrentVersion);
    textLog->append(test);

    std::string site = "https://ac973k.github.io/update/";
    QString sSite = QString::fromStdString(site);
    sSite = sSite + QString::number(iCurrentVersion);

    QUrl url;
    //url.setUrl(sSite);
    url.setUrl("https://ac973k.github.io/update/20181121");

    m_downloader.get(url);

    QString result = "/sdcard/";
    result.append(iCurrentVersion);

    QFile fNewVersion(result);

    fNewVersion.open(QIODevice::ReadOnly);

    data = fNewVersion.readLine();

    int iNewVersion = data.toInt();

    QString test1 = "Переменная iNewVersion: " + QString::number(iNewVersion);
    textLog->append(test1);

    /*
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
        textLog->setPlainText("Что-то пошло не так...");
    }
    */
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
