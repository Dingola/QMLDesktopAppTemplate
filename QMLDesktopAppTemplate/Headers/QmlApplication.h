#pragma once

#include <QObject>
#include <QQmlApplicationEngine>

#include "AppSettings.h"
#include "Models/SettingsModel.h"
#include "Services/Translator.h"

namespace QmlApp
{
    class QmlApplication : public QObject
    {
        Q_OBJECT

    public:
        explicit QmlApplication(QObject* parent = nullptr);
        virtual ~QmlApplication() = default;

        void load(const QUrl& url);
        void load(const QString& file_path);

        int exec();

    private:
        QQmlApplicationEngine m_engine;
        AppSettings m_settings;
        SettingsModel m_settings_model;
        Translator m_translator;

    };
} // namespace QmlApp
