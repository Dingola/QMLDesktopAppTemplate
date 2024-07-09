#pragma once

#include <QObject>
#include <QQmlApplicationEngine>

namespace QmlApp
{
    class QmlApplication : public QObject
    {
        Q_OBJECT

    public:
        QmlApplication(QObject* parent = nullptr);
        virtual ~QmlApplication() = default;

        void load(const QUrl& url);
        void load(const QString& file_path);

        int exec();

    private:
        QQmlApplicationEngine m_engine;

    };
}
