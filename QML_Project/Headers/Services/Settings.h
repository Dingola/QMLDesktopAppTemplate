#pragma once

#include <QObject>
#include <QSettings>

namespace QmlApp
{
class Settings: public QObject
{
        Q_OBJECT

    public:
        explicit Settings(QObject* parent = nullptr);
        virtual ~Settings() = default;

        [[nodiscard]] Q_INVOKABLE QVariant
        getValue(const QString& key, const QVariant& default_value = QVariant()) const;
        [[nodiscard]] Q_INVOKABLE QVariant getValue(const QString& group, const QString& key,
                                                    const QVariant& default_value = QVariant());

        Q_INVOKABLE void setValue(const QString& key, const QVariant& value);
        Q_INVOKABLE void setValue(const QString& group, const QString& key, const QVariant& value);

        [[nodiscard]] Q_INVOKABLE QStringList childGroups() const;
        [[nodiscard]] Q_INVOKABLE QStringList childGroups(const QString& group);
        [[nodiscard]] Q_INVOKABLE QStringList childKeys(const QString& group);
        [[nodiscard]] Q_INVOKABLE QStringList allKeys() const;

        [[nodiscard]] Q_INVOKABLE bool contains(const QString& key);
        [[nodiscard]] Q_INVOKABLE bool contains(const QString& group, const QString& key);

        Q_INVOKABLE void loadFromFile(const QString& file_path,
                                      QSettings::Format format = QSettings::IniFormat);
        Q_INVOKABLE void saveToFile(const QString& file_path,
                                    QSettings::Format format = QSettings::IniFormat);

        Q_INVOKABLE void clear();

    private:
        void copy_settings(QSettings& source, QSettings& destination);

    private:
        QSettings m_settings;
};
}  // namespace QmlApp
