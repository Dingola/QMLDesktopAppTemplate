/**
 * @file SettingsModel.cpp
 * @brief This file contains the implementation of the SettingsModel class.
 */

#include "Models/SettingsModel.h"

namespace QmlApp
{
	/**
	 * @brief Constructs a SettingsModel object with the given AppSettings and parent.
	 *
	 * This constructor initializes the SettingsModel object with the provided AppSettings object
	 * and sets up the group and key mappings. The parent object is also set.
	 *
	 * @param app_settings The AppSettings object to use for retrieving and updating settings.
	 * @param parent The parent object.
	 */
	SettingsModel::SettingsModel(AppSettings* app_settings, QObject* parent)
		: m_app_settings(app_settings), m_sync_with_app_settings(true), QAbstractItemModel(parent)
	{
		Q_ASSERT(app_settings != nullptr);

		m_root_node = new SettingsNode("Root", "");
		load_settings_from_app_settings();
	}

	/**
	 * @brief Returns the index of the item in the model with the specified row, column, and parent index.
	 *
	 * @param row The row of the item.
	 * @param column The column of the item.
	 * @param parent The parent index.
	 * @return The index of the item.
	 */
	QModelIndex SettingsModel::index(int row, int column, const QModelIndex& parent) const
	{
		if (!hasIndex(row, column, parent))
		{
			return QModelIndex();
		}

		SettingsNode* parent_node = nullptr;

		if (!parent.isValid())
		{
			parent_node = m_root_node;
		}
		else
		{
			parent_node = static_cast<SettingsNode*>(parent.internalPointer());
		}

		SettingsNode* child_node = parent_node->get_child(row);

		if (child_node)
		{
			return createIndex(row, column, child_node);
		}
		else
		{
			return QModelIndex();
		}
	}

	/**
	 * @brief Returns the parent index of the item with the specified index.
	 *
	 * @param index The index of the item.
	 * @return The parent index of the item.
	 */
	QModelIndex SettingsModel::parent(const QModelIndex& index) const
	{
		if (!index.isValid())
		{
			return QModelIndex();
		}

		SettingsNode* child_node = static_cast<SettingsNode*>(index.internalPointer());
		SettingsNode* parent_node = child_node->get_parent_item();

		if (parent_node == m_root_node)
		{
			return QModelIndex();
		}

		return createIndex(parent_node->row(), 0, parent_node);
	}

	/**
	 * @brief Returns the number of rows under the specified parent index.
	 *
	 * @param parent The parent index.
	 * @return The number of rows.
	 */
	int SettingsModel::rowCount(const QModelIndex& parent) const
	{
		SettingsNode* parent_node = nullptr;

		if (!parent.isValid())
		{
			parent_node = m_root_node;
		}
		else
		{
			parent_node = static_cast<SettingsNode*>(parent.internalPointer());
		}

		return parent_node->child_count();
	}

	/**
	 * @brief Returns the number of columns under the specified parent index.
	 *
	 * @param parent The parent index.
	 * @return The number of columns.
	 */
	int SettingsModel::columnCount(const QModelIndex& parent) const
	{
		int result = 0;

		if (parent.isValid())
		{
			result = static_cast<SettingsNode*>(parent.internalPointer())->column_count();
		}
		else
		{
			result = m_root_node->column_count();
		}

		return result;
	}

	/**
	 * @brief Returns the data for the specified index and role.
	 *
	 * @param index The index of the item.
	 * @param role The role of the data.
	 * @return The data for the index and role.
	 */
	QVariant SettingsModel::data(const QModelIndex& index, int role) const
	{
		QVariant result;

		if (!index.isValid())
		{
			result = QVariant();
		}

		SettingsNode* node = static_cast<SettingsNode*>(index.internalPointer());

		if (role == Qt::DisplayRole || role == Qt::EditRole)
		{
			result = node->data(index.column());
		}
		else
		{
			switch (role)
			{
				case GroupRole:
					result = node->get_group();
					break;
				case KeyRole:
					result = node->get_key();
					break;
				case ValueRole:
					result = node->get_value();
					break;
				default:
					break;
			}
		}

		return result;
	}

	/**
	 * @brief Sets the data for the specified index and role.
	 *
	 * @param index The index of the item.
	 * @param value The value to set.
	 * @param role The role of the data.
	 * @return True if the data was set successfully, false otherwise.
	 */
	bool SettingsModel::setData(const QModelIndex& index, const QVariant& value, int role)
	{
		bool result = index.isValid() && role == Qt::EditRole;

		if (result)
		{
			SettingsNode* node = static_cast<SettingsNode*>(index.internalPointer());
			node->set_data(index.column(), value);

			if (m_sync_with_app_settings)
			{
				QStringList groups = node->get_full_group().split('/');
				groups.takeFirst(); // root
				QString group = groups.takeFirst();
				QString key = (groups.size() > 1) ? groups.join("/") + "/" + node->get_key() : node->get_key();
				QVariant value = node->get_value();
				m_app_settings->setValue(group, key, value);
			}

			emit dataChanged(index, index, { role });
		}

		return result;
	}

	/**
	 * @brief Returns the item flags for the specified index.
	 *
	 * @param index The index of the item.
	 * @return The item flags.
	 */
	Qt::ItemFlags SettingsModel::flags(const QModelIndex& index) const
	{
		if (!index.isValid())
		{
			return Qt::NoItemFlags;
		}

		return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
	}

	/**
	 * @brief Returns the role names for the model
	 *
	 * @return The role names for the model
	 */
	QHash<int, QByteArray> SettingsModel::roleNames() const
	{
		QHash<int, QByteArray> names;
		names[GroupRole] = "Group";
		names[KeyRole] = "Key";
		names[ValueRole] = "Value";
		names[Qt::DisplayRole] = "Display";

		return names;
	}

	/**
	 * @brief Returns the value associated with the specified key and group.
	 *
	 * @param key The key of the value.
	 * @param group The group of the value.
	 * @param default_value The default value to return if the key does not exist.
	 * @return The value associated with the key and group, or the default value if the key does not exist.
	 */
	QVariant SettingsModel::getValue(const QString& key, const QString& group, const QVariant& default_value) const
	{
		return m_app_settings->getValue(group, key, default_value);
	}

	/**
	 * @brief Sets the value associated with the specified key and group.
	 *
	 * If the group does not exist, it will be created. If the key does not exist, it will be added.
	 * If the key already exists, its value will be updated.
	 *
	 * @param key The key of the value.
	 * @param value The value to set.
	 * @param group The group of the value.
	 */
	void SettingsModel::setValue(const QString& key, const QVariant& value, const QString& group)
	{
		QStringList key_parts = key.split('/');
		QString current_group_name = group;
		SettingsNode* parent_node = m_root_node;
		SettingsNode* group_node = parent_node->find_node_by_group(current_group_name);
		SettingsNode* key_node = nullptr;
		SettingsNode* sub_group_node = nullptr;
		QModelIndex key_node_model_index;

		// If the root group node does not exist, create it.
		if (group_node == nullptr)
		{
			group_node = create_node(current_group_name, "", QVariant(""), parent_node);
		}

		// Create or update the key if the group is a root group
		if (key_parts.size() == 1)
		{
			key_node = group_node->find_node_by_key(key);

			if (key_node == nullptr)
			{
				create_node("", key, value, group_node);
			}
			else
			{
				key_node_model_index = index(key_node->row(), 2, createIndex(group_node->row(), 0, group_node));
				setData(key_node_model_index, value, Qt::EditRole);
			}
		}
		else
		{
			// Create subgroups if they do not exist
			for (int i = 0; i < key_parts.size() - 1; i++)
			{
				current_group_name = key_parts[i];
				sub_group_node = group_node->find_node_by_group(current_group_name);

				// If the subgroup does not exist, create it
				if (sub_group_node == nullptr)
				{
					sub_group_node = create_node(current_group_name, "", QVariant(""), group_node);
				}

				group_node = sub_group_node;
			}

			// Create or update the key in the last subgroup
			key_node = group_node->find_node_by_key(key_parts.last());

			if (key_node == nullptr)
			{
				create_node("", key_parts.last(), value, group_node);
			}
			else
			{
				key_node_model_index = index(key_node->row(), 2, createIndex(group_node->row(), 0, group_node));
				setData(key_node_model_index, value, Qt::EditRole);
			}
		}

		if (m_sync_with_app_settings)
		{
			m_app_settings->setValue(group, key, value);
		}
	}

	/**
	 * @brief Loads the settings from the specified file.
	 *
	 * This function clears the existing settings and loads the settings from the specified file.
	 *
	 * @param file_path The file path of the settings file to load.
	 */
	void SettingsModel::loadFromFile(const QString& file_path)
	{
		reset();
		m_app_settings->loadFromFile(file_path);
		load_settings_from_app_settings();
	}

	/**
	 * @brief Saves the settings to the specified file.
	 *
	 * This function saves the current settings to the specified file.
	 *
	 * @param file_path The file path of the settings file to save.
	 */
	void SettingsModel::saveToFile(const QString& file_path)
	{
		if (!m_sync_with_app_settings)
		{
			// Sync the settings with the AppSettings object before saving
			QList<SettingsNode*> leaf_nodes = get_leaf_nodes();

			for (const SettingsNode* node : leaf_nodes)
			{
				QStringList groups = node->get_full_group().split('/');
				qDebug() << "Groups: " << groups;
				groups.takeFirst(); // root
				QString group = groups.takeFirst();
				QString key = (groups.size() > 1) ? groups.join("/") + "/" + node->get_key() : node->get_key();
				QVariant value = node->get_value();
				m_app_settings->setValue(group, key, value); // todo: Alternatively create a new AppSettings object to save the settings directly ( avoids saving the settings twice )
			}
		}

		m_app_settings->saveToFile(file_path);
	}

	/**
	 * @brief Loads the settings from the AppSettings object.
	 */
	void SettingsModel::load_settings_from_app_settings()
	{
		QStringList all_keys = m_app_settings->allKeys();

		for (const QString key : all_keys)
		{
			QStringList key_parts = key.split('/');
			QString group = key_parts.takeFirst();
			QString key_name = key_parts.join('/');
			QVariant value = m_app_settings->getValue(group, key_name);
			setValue(key_name, value, group);
		}
	}

	/**
	 * @brief Creates a new node with the specified group, key, value, and parent node.
	 *
	 * @param group The group of the node.
	 * @param key The key of the node.
	 * @param value The value of the node.
	 * @param parent The parent node.
	 * @return The newly created node.
	 */
	SettingsNode* SettingsModel::create_node(const QString& group, const QString& key, const QVariant& value, SettingsNode* parent)
	{
		SettingsNode* result = nullptr;

		if (parent != nullptr)
		{
			beginInsertRows(createIndex(parent->row(), 0, parent), parent->child_count(), parent->child_count());
			result = new SettingsNode(group, key, value, parent);
			parent->append_child(result);
			endInsertRows();
		}

		return result;
	}

	/**
	 * @brief Returns a list of leaf nodes in the model.
	 */
	QList<SettingsNode*> SettingsModel::get_leaf_nodes() const
	{
		QList<SettingsNode*> leaf_nodes;
		collect_leaf_nodes(m_root_node, leaf_nodes);
		return leaf_nodes;
	}

	/**
	 * @brief Collects all the leaf nodes in the model.
	 *
	 * @param node The node to start collecting from.
	 * @param leaf_nodes The list of leaf nodes to populate.
	 */
	void SettingsModel::collect_leaf_nodes(SettingsNode* node, QList<SettingsNode*>& leaf_nodes) const
	{
		if (node->child_count() == 0)
		{
			leaf_nodes.append(node);
		}
		else
		{
			for (int i = 0; i < node->child_count(); i++)
			{
				collect_leaf_nodes(node->get_child(i), leaf_nodes);
			}
		}
	}

	/**
	 * @brief Resets the model by clearing all the settings.
	 */
	void SettingsModel::reset()
	{
		beginResetModel();
		m_root_node->clear();
		endResetModel();
	}

} // namespace QmlApp
