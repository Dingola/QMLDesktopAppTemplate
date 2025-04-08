#pragma once

#include <QString>
#include <QVariant>
#include <QVector>

namespace QmlApp
{
class SettingsNode
{
    public:
        explicit SettingsNode(QString group, QString key, QVariant value = QVariant(),
                              SettingsNode* parent = nullptr);
        virtual ~SettingsNode();

        auto append_child(SettingsNode* child) -> void;
        [[nodiscard]] auto get_child(int row) const -> SettingsNode*;
        [[nodiscard]] auto child_items() const -> QVector<SettingsNode*>;

        [[nodiscard]] auto child_count() const -> int;
        [[nodiscard]] auto column_count() const -> int;

        [[nodiscard]] auto data(int column) const -> QVariant;
        void set_data(int column, const QVariant& value);

        [[nodiscard]] auto row() const -> int;
        [[nodiscard]] auto get_parent_item() const -> SettingsNode*;

        [[nodiscard]] auto has_parent() const -> bool;
        [[nodiscard]] auto has_children() const -> bool;

        [[nodiscard]] auto find_node_by_group(const QString& group) const -> SettingsNode*;
        [[nodiscard]] auto find_node_by_key(const QString& key) const -> SettingsNode*;

        auto set_value(const QVariant& value) -> void;

        [[nodiscard]] auto get_group() const -> QString;
        [[nodiscard]] auto get_key() const -> QString;
        [[nodiscard]] auto get_value() const -> QVariant;

        [[nodiscard]] auto get_full_group() const -> QString;

        auto clear() -> void;

    private:
        QString m_group;
        QString m_key;
        QVariant m_value;
        QVector<SettingsNode*> m_child_items;
        SettingsNode* m_parent_item;
};
}  // namespace QmlApp
