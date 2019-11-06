#include "motoupdater.h"

MotoUpdater::MotoUpdater(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QGridLayout;

    textLog = new QTextEdit;

    btnUpdater = new QPushButton(tr("Search"));
    btnAbout = new QPushButton(tr("About"));

    mainLayout->addWidget(textLog);
    mainLayout->addWidget(btnUpdater);
    mainLayout->addWidget(btnAbout);

    setLayout(mainLayout);

    QObject::connect(&m_downloader, &Downloader::updateDownloadProgress, this, &MotoUpdater::onUpdateProgress);
}

MotoUpdater::~MotoUpdater()
{

}

void MotoUpdater::Search()
{
    QString site = "http://site.ru/update/version";
    QUrl url = site;
    m_downloader.get(url);
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
