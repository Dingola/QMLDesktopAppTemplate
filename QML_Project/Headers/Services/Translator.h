#pragma once

#include <QObject>
#include <QTranslator>
#include <QLocale>
#include <QString>

namespace QmlApp
{
	class Translator : public QObject
	{
		Q_OBJECT

	public:
		explicit Translator(QObject* parent = nullptr);
		virtual ~Translator() = default;

		[[nodiscard]] Q_INVOKABLE bool load_translation(const QString& language);
		[[nodiscard]] Q_INVOKABLE bool load_translation(const QLocale& locale);
		[[nodiscard]] Q_INVOKABLE bool load_default_translation();

		[[nodiscard]] Q_INVOKABLE QString get_current_language() const;

	private:
		void remove_none_empty_translators();
		[[nodiscard]] bool load(const QLocale& locale, const QString& filename, QTranslator& translator);

	signals:
		void languageChanged();

	private:
		QTranslator m_qt_translator;
		QTranslator m_app_translator;
		QString m_translations_path;
		QLocale m_current_locale;

	};
} // namespace QmlApp
