#pragma once

#include <QLocale>
#include <QObject>
#include <QString>
#include <QTranslator>

namespace QmlApp
{
class Translator: public QObject
{
        Q_OBJECT

    public:
        explicit Translator(QObject* parent = nullptr);
        ~Translator() override = default;

        // NOLINTBEGIN(modernize-use-trailing-return-type)
        [[nodiscard]] Q_INVOKABLE bool load_translation(const QString& language);
        [[nodiscard]] Q_INVOKABLE bool load_translation(const QLocale& locale);
        [[nodiscard]] Q_INVOKABLE bool load_default_translation();

        [[nodiscard]] Q_INVOKABLE QString get_current_language() const;
        // NOLINTEND(modernize-use-trailing-return-type)

    private:
        auto remove_none_empty_translators() -> void;
        [[nodiscard]] auto load(const QLocale& locale, const QString& filename,
                                QTranslator& translator) -> bool;

    signals:
        void languageChanged();

    private:
        QTranslator m_qt_translator;
        QTranslator m_app_translator;
        QString m_translations_path;
        QLocale m_current_locale;
};
}  // namespace QmlApp
