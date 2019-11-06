#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>

class QNetworkReply;
class QFile;

class Downloader : public QObject
{
    Q_OBJECT
    using BaseClass = QObject;


public:
    explicit Downloader(QObject *parent = nullptr);

    bool get(const QUrl &url);

signals:
    void updateDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);

private slots:
    void onReadyRead();
    void onReply(QNetworkReply *reply);

private:
    QNetworkReply *m_currentReply {nullptr};
    QFile *m_file {nullptr};
    QNetworkAccessManager m_manager;
};

#endif // DOWNLOADER_H
