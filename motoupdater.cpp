#include "motoupdater.h"
#include <QFile>

MotoUpdater::MotoUpdater(QWidget *parent)
    : QWidget(parent)
{
    networkManagerSearch = new QNetworkAccessManager;
    networkManagerDownload = new QNetworkAccessManager;

    procUnpacker = new QProcess;
    procInstaller = new QProcess;

    boxAbout = new QMessageBox;

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

    btnDownload->setDisabled(true);
    btnInstall->setDisabled(true);

    QObject::connect(networkManagerSearch, &QNetworkAccessManager::finished, this, &MotoUpdater::onSearchResult);
    QObject::connect(networkManagerDownload, &QNetworkAccessManager::finished, this, &MotoUpdater::onDownloadResult);

    QObject::connect(btnSearch, SIGNAL(clicked()), this, SLOT(Search()));
    QObject::connect(btnDownload, SIGNAL(clicked()), this, SLOT(Download()));
    QObject::connect(btnRecovery, SIGNAL(clicked()), this, SLOT(Recovery()));
    QObject::connect(btnInstall, SIGNAL(clicked()), this, SLOT(Install()));
    QObject::connect(btnAbout, SIGNAL(clicked()), this, SLOT(About()));
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

    delete networkManagerSearch;
    delete networkManagerDownload;

    delete procUnpacker;
    delete procInstaller;

    delete boxAbout;
}

void MotoUpdater::onSearchResult(QNetworkReply *reply)
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

void MotoUpdater::onDownloadResult(QNetworkReply *reply)
{
    if(!reply->error())
    {
        QFile nFile("/sdcard/update.zip");
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
    fCurrentVersion.close();

    /*
     * Get link to updated file and download this file
    */
    QString site = "https://ac973k.github.io/update/" + QString::number(iCurrentVersion) + "/version";

    networkManagerSearch->get(QNetworkRequest(QUrl(site)));

    QFile fNewVersion("/sdcard/version");
    fNewVersion.open(QFile::ReadOnly);

    tmpStr = fNewVersion.readLine();
    int iNewVersion = tmpStr.toInt();

    if(iCurrentVersion < iNewVersion)
    {
        QString sNewVersion = "Доступна новая версия: " + QString::number(iNewVersion);
        textLog->append(sNewVersion);

        btnDownload->setDisabled(false);
        fNewVersion.close();
    }
    else if(iCurrentVersion == iNewVersion)
    {
        textLog->append("Новых обновлений нет!");
        fNewVersion.close();
    }
    else
    {
        textLog->append("Что-то пошло не так...");
        fNewVersion.close();
    }
}

void MotoUpdater::Download()
{
    QFile fNewVersion("/sdcard/version");
    fNewVersion.open(QFile::ReadOnly);

    QString tmpStr = fNewVersion.readLine();
    int iNewVersion = tmpStr.toInt();

    fNewVersion.close();

    textLog->append("Готовим ссылку...");

    QString site = "https://ac973k.github.io/update/" + QString::number(iNewVersion) + "/update.zip";

    networkManagerDownload->get(QNetworkRequest(QUrl(site)));

    textLog->append("Загружаем...");

    btnInstall->setDisabled(false);

    textLog->append("Готово...");
}

void MotoUpdater::Install()
{
    procUnpacker->setProcessChannelMode(QProcess::SeparateChannels);
    procUnpacker->start("su", QStringList() << "-c" << "busybox" << "unzip" << "/sdcard/update.zip" << "-d" << "/data/local/tmp/");

    textLog->append(procUnpacker->readAll());

    procInstaller->setProcessChannelMode(QProcess::SeparateChannels);
    procInstaller->start("su", QStringList() << "-c" << "sh" << "/data/local/tmp/update/installer/install.sh");

    textLog->append(procInstaller->readAll());
}

void MotoUpdater::Recovery()
{
    system("su -c reboot recovery");
}

void MotoUpdater::About()
{
    boxAbout->setTextFormat(Qt::RichText);
        boxAbout->setText("Motorola Update Manager"

        "\n Разработано с помощью QT Framework."
        ""
        "\n Links:"
        "\n https://qt.io"
        "\nРазраб: Danilka Terentyev(4pda: AC97; GitHub: ac973k; vk: id498051587)"
        ""
        "\n Специально для Moto C 4G(Namath)");
        boxAbout->exec();
}
