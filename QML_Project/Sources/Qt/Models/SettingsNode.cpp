/**
 * @file SettingsNode.cpp
 * @brief This file contains the implementation of the SettingsNode class.
 */

#include "Models/SettingsNode.h"

namespace QmlApp
{
/**
 * @brief Constructs a SettingsNode object with the specified group, key, value, and parent node.
 *
 * This constructor initializes a SettingsNode object with the provided group, key, value, and
 * parent node.
 *
 * @param group The group of the node.
 * @param key The key of the node.
 * @param value The value of the node.
 * @param parent The parent node.
 */
SettingsNode::SettingsNode(QString group, QString key, QVariant value, SettingsNode* parent)
    : m_group(std::move(group)),
      m_key(std::move(key)),
      m_value(std::move(value)),
      m_parent_item(parent)
{}

/**
 * @brief Destroys the SettingsNode object and frees any allocated memory.
 */
SettingsNode::~SettingsNode()
{
    qDeleteAll(m_child_items);
}

/**
 * @brief Appends a child SettingsNode to the current node.
 *
 * @param child The child SettingsNode to append.
 */
void SettingsNode::append_child(SettingsNode* child)
{
    m_child_items.append(child);
    child->m_parent_item = this;
}

/**
 * @brief Returns the child SettingsNode at the specified row.
 *
 * @param row The row index of the child node.
 * @return The child SettingsNode at the specified row, or nullptr if no child node exists at that
 * index.
 */
auto SettingsNode::get_child(int row) const -> SettingsNode*
{
    return m_child_items.value(row);
}

/**
 * @brief Returns a vector of child SettingsNode objects.
 *
 * @return A vector of child SettingsNode objects.
 */
auto SettingsNode::child_items() const -> QVector<SettingsNode*>
{
    return m_child_items;
}

/**
 * @brief Returns the number of child nodes.
 *
 * @return The number of child nodes.
 */
auto SettingsNode::child_count() const -> int
{
    return m_child_items.count();
}

/**
 * @brief Returns the number of columns in the settings node.
 *
 * @return The number of columns.
 */
auto SettingsNode::column_count() const -> int
{
    return 3;
}

/**
 * @brief Returns the data for the specified column.
 *
 * @param column The column index.
 * @return The data for the specified column.
 */
auto SettingsNode::data(int column) const -> QVariant
{
    QVariant result;

    if (column == 0)
    {
        result = m_group;
    }
    else if (column == 1)
    {
        result = m_key;
    }
    else if (column == 2)
    {
        result = m_value;
    }

    return result;
}

/**
 * @brief Sets the data for the specified column.
 *
 * @param column The column index.
 * @param value The value to set.
 */
auto SettingsNode::set_data(int column, const QVariant& value) -> void
{
    if (column == 0)
    {
        m_group = value.toString();
    }
    else if (column == 1)
    {
        m_key = value.toString();
    }
    else if (column == 2)
    {
        m_value = value;
    }
}

/**
 * @brief Returns the row index of the node.
 *
 * @return The row index of the node.
 */
auto SettingsNode::row() const -> int
{
    int row = 0;

    if (m_parent_item)
    {
        row = m_parent_item->m_child_items.indexOf(const_cast<SettingsNode*>(this));
    }

    return row;
}

/**
 * @brief Returns the parent SettingsNode of the current node.
 *
 * @return The parent SettingsNode of the current node.
 */
auto SettingsNode::get_parent_item() const -> SettingsNode*
{
    return m_parent_item;
}

/**
 * @brief Checks if the node has a parent.
 *
 * @return true if the node has a parent, false otherwise.
 */
auto SettingsNode::has_parent() const -> bool
{
    return (m_parent_item != nullptr);
}

/**
 * @brief Checks if the node has any child nodes.
 *
 * @return true if the node has child nodes, false otherwise.
 */
auto SettingsNode::has_children() const -> bool
{
    return !m_child_items.isEmpty();
}

/**
 * @brief Finds a SettingsNode with the specified group.
 *
 * @param group The group to search for.
 * @return The SettingsNode with the specified group, or nullptr if not found.
 */
auto SettingsNode::find_node_by_group(const QString& group) const -> SettingsNode*
{
    // Check if the current node matches the group
    if (m_group == group)
    {
        return const_cast<SettingsNode*>(this);
    }

    // Iterate through the child nodes
    for (const auto& child: m_child_items)
    {
        // Recursively search for the group in each child node
        SettingsNode* found_node = child->find_node_by_group(group);

        // If the group is found in a child node, return the found node
        if (found_node != nullptr)
        {
            return found_node;
        }
    }

    // Group not found
    return nullptr;
}

/**
 * @brief Finds a SettingsNode with the specified key.
 *
 * @param key The key to search for.
 * @return The SettingsNode with the specified key, or nullptr if not found.
 */
auto SettingsNode::find_node_by_key(const QString& key) const -> SettingsNode*
{
    // Check if the current node matches the key
    if (m_key == key)
    {
        return const_cast<SettingsNode*>(this);
    }

    // Iterate through the child nodes
    for (const auto& child: m_child_items)
    {
        // Recursively search for the key in each child node
        SettingsNode* found_node = child->find_node_by_key(key);

        // If the key is found in a child node, return the found node
        if (found_node != nullptr)
        {
            return found_node;
        }
    }

    // Key not found
    return nullptr;
}

/**
 * @brief Sets the value of the node.
 *
 * @param value The value to set.
 */
auto SettingsNode::set_value(const QVariant& value) -> void
{
    m_value = value;
}

/**
 * @brief Returns the group of the node.
 *
 * @return The group of the node.
 */
auto SettingsNode::get_group() const -> QString
{
    return m_group;
}

/**
 * @brief Returns the key of the node.
 *
 * @return The key of the node.
 */
auto SettingsNode::get_key() const -> QString
{
    return m_key;
}

/**
 * @brief Returns the value of the node.
 *
 * @return The value of the node.
 */
auto SettingsNode::get_value() const -> QVariant
{
    return m_value;
}

/**
 * @brief Returns the full group path of the node.
 *
 * @return The full group path of the node.
 */
auto SettingsNode::get_full_group() const -> QString
{
    QString result;
    SettingsNode* parent = get_parent_item();
    SettingsNode* grand_parent = nullptr;

    if (parent != nullptr)
    {
        grand_parent = parent->get_parent_item();

        if (grand_parent != nullptr)
        {
            result += parent->get_full_group();
            result += "/";
        }

        result += parent->get_group();
    }

    return result;
}

/**
 * @brief Clears the node and its child nodes.
 */
auto SettingsNode::clear() -> void
{
    qDeleteAll(m_child_items);
    m_child_items.clear();
}
}  // namespace QmlApp
