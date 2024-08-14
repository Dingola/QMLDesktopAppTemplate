#pragma once

#include <QAbstractItemModel>

#include "AppSettings.h"

namespace QmlApp
{
    class SettingsModel : public QAbstractItemModel
    {
        Q_OBJECT
        Q_PROPERTY(QStringList keys READ keys NOTIFY keysChanged)

    public:
        explicit SettingsModel(AppSettings* app_settings = nullptr, QObject* parent = nullptr);

        // Required overrides for QAbstractItemModel
        QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
        QModelIndex parent(const QModelIndex& index) const override;
        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        int columnCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
        bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
        Qt::ItemFlags flags(const QModelIndex& index) const override;

        // Custom methods to interact with settings
        [[nodiscard]] Q_INVOKABLE QVariant getValue(const QString& key, const QVariant& default_value = QVariant()) const;
        Q_INVOKABLE void setValue(const QString& key, const QVariant& value);
        Q_INVOKABLE void loadFromFile(const QString& file_path);
        Q_INVOKABLE void saveToFile(const QString& file_path);

        [[nodiscard]] QStringList keys() const { return m_keys; }

    signals:
        void keysChanged();

    private:
        AppSettings* m_app_settings;
        QStringList m_keys;

    };
} // namespace QmlApp
