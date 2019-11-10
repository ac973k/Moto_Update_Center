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

    fCurrentVersion.open(QIODevice::ReadOnly);

    QString data = fCurrentVersion.readLine();

    int iCurrentVersion = data.toInt();

    QString test = "Переменная iCurrentVersion: " + QString::number(iCurrentVersion);
    textLog->append(test);

    QString site = "https://ac973k.github.io/update/" + QString::number(iCurrentVersion);

    QUrl url;
    url.setUrl(site);

    m_downloader.get(url);

    QString path = "/sdcard/" + QString::number(iCurrentVersion);

    QFile fNewVersion(path);

    fNewVersion.open(QIODevice::ReadOnly);

    QString data2 = fNewVersion.readLine();

    int iNewVersion = data2.toInt();

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
