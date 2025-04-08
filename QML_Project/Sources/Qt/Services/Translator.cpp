/**
 * @file Translator.cpp
 * @brief This file contains the implementation of the Translator class.
 */

#include "Services/Translator.h"

#include <QCoreApplication>
#include <QDir>

namespace QmlApp
{
/**
 * @brief Constructs a Translator object with the given parent.
 *
 * @param parent The parent object.
 */
Translator::Translator(QObject* parent)
    : QObject(parent),
      m_qt_translator(),
      m_app_translator(),
      m_translations_path(QCoreApplication::applicationDirPath() + "/translations"),
      m_current_locale()
{
    QDir translations_dir(m_translations_path);

    if (!translations_dir.exists())
    {
        qDebug() << "The translation folder does not exist: " << m_translations_path;
    }
}

// NOLINTBEGIN(modernize-use-trailing-return-type)

/**
 * @brief Loads the language translations for the specified language.
 *
 * @param language The language to load translations for.
 * @return True if the translations were loaded successfully, false otherwise.
 */
bool Translator::load_translation(const QString& language)
{
    return load_translation(QLocale(language));
}

/**
 * @brief Loads the language translations for the specified locale.
 *
 * This method attempts to load the Qt provided translation file and the app-specific translation
 * file for the specified locale. If both files are loaded successfully, the translators are
 * installed and the languageChanged signal is emitted. If either of the files fails to load, the
 * method attempts to load the translations for the default language.
 *
 * @param locale The locale to load translations for.
 * @return True if the translations were loaded successfully, false otherwise.
 */
bool Translator::load_translation(const QLocale& locale)
{
    remove_none_empty_translators();
    qDebug() << "Attempting to load translations for the language" << locale << "from"
             << m_translations_path;
    bool result = load(locale, QStringLiteral("qt"), m_qt_translator);

    if (result)
    {
        result = load(locale, QStringLiteral("app"), m_app_translator);

        if (result)
        {
            qDebug() << (result ? "Successfully loaded the translators for locale"
                                : "Failed to load the application translator for locale")
                     << locale;
            qApp->installTranslator(&m_qt_translator);
            qApp->installTranslator(&m_app_translator);
            m_current_locale = locale;
            emit languageChanged();
        }
    }
    else
    {
        qDebug() << "Failed to load the Qt translator for locale" << locale;
    }

    // Attempt to load the default translation if it hasn't been tried yet.
    // This is done if a translation (other than the default) has been chosen but failed to load.
    if (!result && (QLocale(QStringLiteral("en_EN")) != locale))
    {
        qDebug() << "Attempting to load the default translation";
        result = load_default_translation();
    }

    return result;
}

/**
 * @brief Loads the translations for the default language.
 *
 * @return True if the translations were loaded successfully, false otherwise.
 */
bool Translator::load_default_translation()
{
    return load_translation(QLocale(QStringLiteral("en_EN")));
}

/**
 * @brief Returns the current language.
 *
 * @return The current language.
 */
QString Translator::get_current_language() const
{
    return m_current_locale.name();
}

// NOLINTEND(modernize-use-trailing-return-type)

/**
 * @brief Removes the installed translators if they are not empty.
 */
auto Translator::remove_none_empty_translators() -> void
{
    if (!m_qt_translator.isEmpty())
    {
        qApp->removeTranslator(&m_qt_translator);
    }

    if (!m_app_translator.isEmpty())
    {
        qApp->removeTranslator(&m_app_translator);
    }
}

/**
 * @brief Loads the translations for the specified locale and filename into the given translator.
 *
 * @param locale The locale to load translations for.
 * @param filename The filename of the translation file.
 * @param translator The translator object to load the translations into.
 * @return True if the translations were loaded successfully, false otherwise.
 */
auto Translator::load(const QLocale& locale, const QString& filename,
                      QTranslator& translator) -> bool
{
    return translator.load(locale, filename, QStringLiteral("_"), m_translations_path);
}
}  // namespace QmlApp
