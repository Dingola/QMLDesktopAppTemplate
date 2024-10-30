/**
 * @file QmlApplication.cpp
 * @brief This file contains the implementation of the QmlApplication class.
 */

#include "QmlApplication.h"

#include <QApplication>
#include <QDebug>
#include <QString>
#include <QQmlContext>

namespace QmlApp
{
    /**
     * @brief Constructs a QmlApplication object with the given parent.
     * 
     * @param parent The parent object.
     */
    QmlApplication::QmlApplication(QObject* parent)
        : QObject(parent), m_engine(), m_settings(), m_settings_model(&m_settings), m_translator()
    {
        qmlRegisterType<SettingsModel>("QmlApp.Models.SettingsModel", 1, 0, "SettingsModel");
        qmlRegisterType<Settings>("QmlApp.Services.Settings", 1, 0, "Settings");
        qmlRegisterType<Translator>("QmlApp.Services.Translator", 1, 0, "Translator");
        m_engine.rootContext()->setContextProperty(QStringLiteral("settings_model"), &m_settings_model);
        m_engine.rootContext()->setContextProperty(QStringLiteral("translator"), &m_translator);

        // Load settings on startup
        m_settings_model.loadFromFile("settings.ini");

        // Save settings on application exit
        connect(qApp, &QApplication::aboutToQuit, [this]() {
            m_settings_model.saveToFile("settings.ini");
        });

        connect(&m_translator, &Translator::languageChanged, this, [this]() {
            m_engine.retranslate();
        });
    }

    /**
     * @brief Loads the QML file from the specified URL.
     * 
     * @param url The URL of the QML file to load.
     */
    void QmlApplication::load(const QUrl& url)
    {
        m_engine.load(url);
    }

    /**
     * @brief Loads the QML file from the specified file path.
     * 
     * @param file_path The file path of the QML file to load.
     */
    void QmlApplication::load(const QString& file_path)
    {
        m_engine.load(QUrl(file_path));
    }

    /**
     * @brief Executes the QML application.
     * 
     * This function loads the QML file from the specified URL or file path.
     * If the root QML file is not loaded, it attempts to load the default QML file "qrc:/Sources/QML/main.qml".
     * If the root QML file is loaded successfully, it executes the QML application.
     * 
     * @return The exit code of the application.
     */
    int QmlApplication::exec()
    {
        int result = -1;
        bool root_qml_file_loaded = !m_engine.rootObjects().isEmpty();

        if (!root_qml_file_loaded)
        {
            m_engine.load(QUrl(QStringLiteral("qrc:/Sources/QML/main.qml")));
            root_qml_file_loaded = !m_engine.rootObjects().isEmpty();
        }

        if (root_qml_file_loaded)
        {
            result = qApp->exec();
        }
        else
        {
            qWarning() << "Failed to load QML file. No Objects were instantiated by the QmlApplicationEngine.";
        }

        return result;
    }
} // namespace QmlApp
