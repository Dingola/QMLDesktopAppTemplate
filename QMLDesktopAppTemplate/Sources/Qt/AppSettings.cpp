/**
 * @file AppSettings.cpp
 * @brief This file contains the implementation of the AppSettings class.
 */

#include "AppSettings.h"

#include <QCoreApplication>

namespace QmlApp
{
    /**
     * @brief Constructs an AppSettings object with the given parent.
     *
     * @param parent The parent object.
     */
    AppSettings::AppSettings(QObject* parent)
        : QObject(parent), m_settings(QCoreApplication::organizationName(), QCoreApplication::applicationName())
    {}

    /**
     * @brief Gets the value associated with the specified key from the settings.
     *
     * @param key The key of the value to retrieve.
     * @param default_value The default value to return if the key does not exist.
     * @return The value associated with the key, or the default value if the key does not exist.
     */
    QVariant AppSettings::getValue(const QString& key, const QVariant& default_value) const
    {
        return m_settings.value(key, default_value);
    }

    /**
     * @brief Sets the value associated with the specified key in the settings.
     *
     * @param key The key of the value to set.
     * @param value The value to set.
     */
    void AppSettings::setValue(const QString& key, const QVariant& value)
    {
        m_settings.setValue(key, value);
    }

    /**
     * @brief Loads the settings from the specified file.
     *
     * This function clears the existing settings and loads the settings from the specified file.
     *
     * @param file_path The file path of the settings file to load.
     */
    void AppSettings::loadFromFile(const QString& file_path)
    {
        QSettings file_settings(file_path, QSettings::IniFormat);
        m_settings.clear();

        for (const auto& key : file_settings.allKeys())
        {
            m_settings.setValue(key, file_settings.value(key));
        }
    }

    /**
     * @brief Saves the settings to the specified file.
     *
     * This function saves the current settings to the specified file.
     *
     * @param file_path The file path of the settings file to save.
     */
    void AppSettings::saveToFile(const QString& file_path)
    {
        QSettings file_settings(file_path, QSettings::IniFormat);

        for (const auto& key : m_settings.allKeys())
        {
            file_settings.setValue(key, m_settings.value(key));
        }
    }
} // namespace QmlApp
