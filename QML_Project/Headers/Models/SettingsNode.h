#pragma once

#include <QString>
#include <QVariant>
#include <QVector>

namespace QmlApp
{
class SettingsNode
{
    public:
        explicit SettingsNode(const QString& group, const QString& key,
                              const QVariant& value = QVariant(), SettingsNode* parent = nullptr);
        virtual ~SettingsNode();

        void append_child(SettingsNode* child);
        [[nodiscard]] SettingsNode* get_child(int row) const;
        [[nodiscard]] QVector<SettingsNode*> child_items() const;

        [[nodiscard]] int child_count() const;
        [[nodiscard]] int column_count() const;

        [[nodiscard]] QVariant data(int column) const;
        void set_data(int column, const QVariant& value);

        [[nodiscard]] int row() const;
        [[nodiscard]] SettingsNode* get_parent_item() const;

        [[nodiscard]] bool has_parent() const;
        [[nodiscard]] bool has_children() const;

        [[nodiscard]] SettingsNode* find_node_by_group(const QString& group) const;
        [[nodiscard]] SettingsNode* find_node_by_key(const QString& key) const;

        void set_value(const QVariant& value);

        [[nodiscard]] QString get_group() const;
        [[nodiscard]] QString get_key() const;
        [[nodiscard]] QVariant get_value() const;

        [[nodiscard]] QString get_full_group() const;

        void clear();

    private:
        QString m_group;
        QString m_key;
        QVariant m_value;
        QVector<SettingsNode*> m_child_items;
        SettingsNode* m_parent_item;
};
}  // namespace QmlApp
