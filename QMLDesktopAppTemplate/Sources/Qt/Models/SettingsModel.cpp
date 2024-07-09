/**
 * @file SettingsModel.cpp
 * @brief This file contains the implementation of the SettingsModel class.
 */

#include "Models/SettingsModel.h"

namespace QmlApp
{
    /**
     * @brief Constructs a SettingsModel object with the given app settings and parent.
     *
     * @param app_settings The app settings object.
     * @param parent The parent object.
     */
    SettingsModel::SettingsModel(AppSettings* app_settings, QObject* parent)
        : QAbstractItemModel(parent), m_app_settings(app_settings)
    {
        m_keys = m_app_settings->getValue("keys", QStringList()).toStringList();
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
        if (!parent.isValid() && row >= 0 && row < m_keys.size() && column == 0)
        {
            return createIndex(row, column);
        }

        return QModelIndex();
    }

    /**
     * @brief Returns the parent index of the item with the specified index.
     *
     * @param index The index of the item.
     * @return The parent index.
     */
    QModelIndex SettingsModel::parent(const QModelIndex& index) const
    {
        return QModelIndex();
    }

    /**
     * @brief Returns the number of rows under the specified parent index.
     *
     * @param parent The parent index.
     * @return The number of rows.
     */
    int SettingsModel::rowCount(const QModelIndex& parent) const
    {
        if (!parent.isValid())
        {
            return m_keys.size();
        }

        return 0;
    }

    /**
     * @brief Returns the number of columns under the specified parent index.
     *
     * @param parent The parent index.
     * @return The number of columns.
     */
    int SettingsModel::columnCount(const QModelIndex& parent) const
    {
        return 1;
    }

    /**
     * @brief Returns the data for the item with the specified index and role.
     *
     * @param index The index of the item.
     * @param role The role of the data.
     * @return The data for the item.
     */
    QVariant SettingsModel::data(const QModelIndex& index, int role) const
    {
        if (!index.isValid() || index.row() >= m_keys.size() || role != Qt::DisplayRole)
        {
            return QVariant();
        }

        return m_app_settings->getValue(m_keys.at(index.row()));
    }

    /**
     * @brief Sets the data for the item with the specified index and role.
     *
     * @param index The index of the item.
     * @param value The new value for the item.
     * @param role The role of the data.
     * @return True if the data was set successfully, false otherwise.
     */
    bool SettingsModel::setData(const QModelIndex& index, const QVariant& value, int role)
    {
        if (index.isValid() && role == Qt::EditRole)
        {
            m_app_settings->setValue(m_keys.at(index.row()), value);
            emit dataChanged(index, index);
            return true;
        }

        return false;
    }

    /**
     * @brief Returns the flags for the item with the specified index.
     *
     * @param index The index of the item.
     * @return The flags for the item.
     */
    Qt::ItemFlags SettingsModel::flags(const QModelIndex& index) const
    {
        if (!index.isValid())
        {
            return Qt::NoItemFlags;
        }

        return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }

    /**
     * @brief Returns the value for the specified key in the app settings.
     *
     * @param key The key of the value.
     * @param default_value The default value to return if the key does not exist.
     * @return The value for the key.
     */
    QVariant SettingsModel::getValue(const QString& key, const QVariant& default_value) const
    {
        return m_app_settings->getValue(key, default_value);
    }

    /**
     * @brief Sets the value for the specified key in the app settings.
     * If the key does not exist, it adds the key to the model.
     *
     * @param key The key of the value.
     * @param value The value to set.
     */
    void SettingsModel::setValue(const QString& key, const QVariant& value)
    {
        if (!m_keys.contains(key))
        {
            beginInsertRows(QModelIndex(), m_keys.size(), m_keys.size());
            m_keys.append(key);
            endInsertRows();
            emit keysChanged();
        }

        m_app_settings->setValue(key, value);
        int row = m_keys.indexOf(key);
        emit dataChanged(index(row, 0), index(row, 0));
    }

    /**
     * @brief Loads the app settings from the specified file path.
     *
     * @param file_path The file path of the settings file.
     */
    void SettingsModel::loadFromFile(const QString& file_path)
    {
        m_app_settings->loadFromFile(file_path);
        m_keys = m_app_settings->getValue("keys", QStringList()).toStringList();
        emit layoutChanged();
        emit keysChanged();
    }

    /**
     * @brief Saves the app settings to the specified file path.
     *
     * @param file_path The file path to save the settings to.
     */
    void SettingsModel::saveToFile(const QString& file_path)
    {
        m_app_settings->setValue("keys", m_keys);
        m_app_settings->saveToFile(file_path);
    }
}
