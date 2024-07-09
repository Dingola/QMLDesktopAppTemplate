#pragma once

#include <Qobject>
#include <QSettings>

namespace QmlApp
{
	class AppSettings : public QObject
	{
		Q_OBJECT

	public:
		AppSettings(QObject* parent = nullptr);
		virtual ~AppSettings() = default;

		[[nodiscard]] Q_INVOKABLE QVariant getValue(const QString& key, const QVariant& default_value = QVariant()) const;
		Q_INVOKABLE void setValue(const QString& key, const QVariant& value);
		Q_INVOKABLE void loadFromFile(const QString& file_path);
		Q_INVOKABLE void saveToFile(const QString& file_path);

	private:
		QSettings m_settings;

	};
}
