#include "downloader.h"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QFile>
#include <QDir>

Downloader::Downloader(QObject* parent) :
    BaseClass(parent)
{
    // Подключаемся к сигналу finished
    connect(&m_manager, &QNetworkAccessManager::finished, this, &Downloader::onReply);
}

bool Downloader::get(const QUrl& url)
{
    if (url.isEmpty())
    {
        return false;
    }

    // Cоздаём объект класса файла для скачивания
    // здесь имеется целевая директория и имя файла, которое выделяется из URL
    QString path = "/sdcard/";
    path.append(url.fileName());
    m_file = new QFile(path);
    // Пробуем открыть файл
    if (!m_file->open(QIODevice::WriteOnly))
    {
        delete m_file;
        m_file = nullptr;
        return false;
    }

    // Создаём запрос
    QNetworkRequest request(url);
    // Обязательно разрешаем переходить по редиректам
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    // Запускаем скачивание
    m_currentReply = m_manager.get(request);

    // После чего сразу подключаемся к сигналам о готовности данных к чтению и обновлению прогресса скачивания
    connect(m_currentReply, &QNetworkReply::readyRead, this, &Downloader::onReadyRead);
    connect(m_currentReply, &QNetworkReply::downloadProgress, this, &Downloader::updateDownloadProgress);
    return true;
}

void Downloader::onReadyRead()
{
    // Если есть данные и файл открыт
    if (m_file)
    {
        // записываем их в файл
        m_file->write(m_currentReply->readAll());
    }
    m_file->close();
}

void Downloader::onReply(QNetworkReply* reply)
{
    // По завершению запроса
    if (reply->error() == QNetworkReply::NoError)
    {
        // сохраням файл
        m_file->flush();
        m_file->close();
    }
    else
    {
        // Или удаляем его в случае ошибки
        m_file->remove();
    }

    delete m_file;
    m_file = nullptr;
    reply->deleteLater();
}
