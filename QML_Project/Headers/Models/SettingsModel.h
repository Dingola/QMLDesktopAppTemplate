#pragma once

#include <QAbstractItemModel>
#include <QVariant>

#include "Services/Settings.h"
#include "SettingsNode.h"

namespace QmlApp
{
enum SettingsDataRole
{
    GroupRole = Qt::UserRole + 1,
    KeyRole,
    ValueRole
};

class SettingsModel: public QAbstractItemModel
{
        Q_OBJECT

    public:
        explicit SettingsModel(Settings* settings = nullptr, QObject* parent = nullptr);
        ~SettingsModel() override;

        // Required overrides for QAbstractItemModel
        [[nodiscard]] auto index(int row, int column, const QModelIndex& parent = QModelIndex())
            const -> QModelIndex override;
        [[nodiscard]] auto parent(const QModelIndex& index) const -> QModelIndex override;
        [[nodiscard]] auto rowCount(const QModelIndex& parent = QModelIndex()) const
            -> int override;
        [[nodiscard]] auto columnCount(const QModelIndex& parent = QModelIndex()) const
            -> int override;
        [[nodiscard]] auto data(const QModelIndex& index,
                                int role = Qt::DisplayRole) const -> QVariant override;
        auto setData(const QModelIndex& index, const QVariant& value,
                     int role = Qt::EditRole) -> bool override;
        [[nodiscard]] auto flags(const QModelIndex& index) const -> Qt::ItemFlags override;
        [[nodiscard]] auto roleNames() const -> QHash<int, QByteArray> override;

        // Custom methods to interact with settings
        // NOLINTBEGIN(modernize-use-trailing-return-type)
        [[nodiscard]] Q_INVOKABLE QVariant
        getValue(const QString& key, const QString& group = "General",
                 const QVariant& default_value = QVariant()) const;
        Q_INVOKABLE void setValue(const QString& key, const QVariant& value,
                                  const QString& group = "General");

        Q_INVOKABLE void loadFromFile(const QString& file_path);
        Q_INVOKABLE void saveToFile(const QString& file_path);
        // NOLINTEND(modernize-use-trailing-return-type)

    private:
        auto load_settings_from_app_settings() -> void;

        auto create_node(const QString& group, const QString& key, const QVariant& value,
                         SettingsNode* parent = nullptr) -> SettingsNode*;
        auto create_or_update_key_node(const QString& key, const QVariant& value,
                                       SettingsNode* group_node) -> SettingsNode*;
        [[nodiscard]] auto get_leaf_nodes() const -> QList<SettingsNode*>;
        auto collect_leaf_nodes(SettingsNode* node, QList<SettingsNode*>& leaf_nodes) const -> void;

        auto reset() -> void;

    private:
        Settings* m_settings;
        bool m_sync_with_app_settings = true;
        SettingsNode* m_root_node;
};
}  // namespace QmlApp
