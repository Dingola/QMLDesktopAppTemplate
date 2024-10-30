#pragma once

#include <gtest/gtest.h>

#include <QCoreApplication>
#include <QFile>
#include <QTextStream>

#include "Models/SettingsModel.h"

using namespace QmlApp;

class SettingsModelTest : public ::testing::Test
{
public:
    AppSettings* m_app_settings = nullptr;
    SettingsModel* m_settings_model = nullptr;

protected:
    void SetUp() override
    {
        m_app_settings = new AppSettings();
        m_settings_model = new SettingsModel(m_app_settings);
    }

    void TearDown() override
    {
        m_app_settings->clear();
        delete m_app_settings;
        delete m_settings_model;
    }
};

// Test case for index() method
TEST_F(SettingsModelTest, IndexTest)
{
    // Test when parent index is invalid and row and column are not within a valid range
    QModelIndex index = m_settings_model->index(0, 0);
    EXPECT_FALSE(index.isValid());
    EXPECT_EQ(index.row(), -1);
    EXPECT_EQ(index.column(), -1);

    // Test when parent index is invalid and row and column are within a valid range
    const QString key = "new key";
    const QVariant value = "new value";
    m_settings_model->setValue(key, value);
    index = m_settings_model->index(0, 0);
    EXPECT_TRUE(index.isValid());
    EXPECT_EQ(index.row(), 0);
    EXPECT_EQ(index.column(), 0);

    // Test when parent index is invalid and only row is within a valid range
    index = m_settings_model->index(0, 3);
    EXPECT_FALSE(index.isValid());
    EXPECT_EQ(index.row(), -1);
    EXPECT_EQ(index.column(), -1);

    // Test when parent index is invalid and only column is within a valid range
    index = m_settings_model->index(2, 0);
    EXPECT_FALSE(index.isValid());
    EXPECT_EQ(index.row(), -1);
    EXPECT_EQ(index.column(), -1);
}

// Test case for parent() method
TEST_F(SettingsModelTest, ParentTest)
{
    // Test when index is valid
    QModelIndex index;
    QModelIndex parent_index = m_settings_model->parent(index);
    EXPECT_FALSE(parent_index.isValid());

    // Test when index is valid
    QString key = "new key";
    QVariant value = "new value";
    m_settings_model->setValue(key, value);
    index = m_settings_model->index(0, 0);
    parent_index = m_settings_model->parent(index);
    EXPECT_TRUE(index.isValid());
    EXPECT_FALSE(parent_index.isValid());
    EXPECT_EQ(parent_index.row(), -1);
    EXPECT_EQ(parent_index.column(), -1);

    key = "new key 2";
    value = "new value 2";
    m_settings_model->setValue(key, value, "test_group");

    // Get the index of the "test_group" group
    QModelIndex group_index;
    for (int row = 0; row < m_settings_model->rowCount(); row++)
    {
        QModelIndex index = m_settings_model->index(row, 0);
        if (m_settings_model->data(index) == "test_group")
        {
            group_index = index;
            break;
        }
    }

    // Check if the group index is valid
    EXPECT_TRUE(group_index.isValid());

    // Get the parent index of the group index
    parent_index = m_settings_model->parent(group_index);

    // Check if the parent index is invalid and equals the root index
    QModelIndex root_index = m_settings_model->index(0, 0);
    EXPECT_FALSE(parent_index.isValid());
    EXPECT_EQ(parent_index, QModelIndex());
}

// Test case for rowCount() method
TEST_F(SettingsModelTest, RowCountTest)
{
    // Test when parent index is invalid
    QModelIndex parent_index;
    int row_count = m_settings_model->rowCount(parent_index);
    EXPECT_EQ(row_count, 0);

    // Test when parent index is invalid and a value has been set
    const QString key = "new key";
    const QVariant value = "new value";
    m_settings_model->setValue(key, value);
    row_count = m_settings_model->rowCount(parent_index);
    EXPECT_EQ(row_count, 1);

    // Test when parent index is valid and a value has been set
    parent_index = m_settings_model->index(0, 1);
    row_count = m_settings_model->rowCount(parent_index);
    EXPECT_TRUE(parent_index.isValid());
    EXPECT_EQ(row_count, 1);

    // Test when parent index is invalid and two values with same group has been set
    const QString key_2 = "new key 2";
    const QVariant value_2 = "new value 2";
    m_settings_model->setValue(key_2, value_2);
    row_count = m_settings_model->rowCount();
    EXPECT_EQ(row_count, 1);  // Only one group

    // Test when parent index is valid and two values with same group has been set
    parent_index = m_settings_model->index(0, 1);
    row_count = m_settings_model->rowCount(parent_index);
    EXPECT_TRUE(parent_index.isValid());
    EXPECT_EQ(row_count, 2);  // Two keys in the group
}

// Test case for columnCount() method
TEST_F(SettingsModelTest, ColumnCountTest)
{
    // Test when parent index is invalid
    QModelIndex parent_index;
    int column_count = m_settings_model->columnCount(parent_index);
    EXPECT_EQ(column_count, 3);

    // Test when parent index is valid
    const QString key = "new key";
    const QVariant value = "new value";
    m_settings_model->setValue(key, value);
    parent_index = m_settings_model->index(0, 1);
    column_count = m_settings_model->columnCount(parent_index);
    EXPECT_TRUE(parent_index.isValid());
    EXPECT_EQ(column_count, 3);
}

// Test case for data() method
TEST_F(SettingsModelTest, DataTest)
{
    // Test when index is invalid
    QModelIndex group_index;
    QModelIndex key_index;
    QVariant data = m_settings_model->data(group_index);
    EXPECT_FALSE(data.isValid());

    // Test when index is valid and role is invalid
    const QString key = "new key";
    const QVariant value = "new value";
    m_settings_model->setValue(key, value);
    group_index = m_settings_model->index(0, 0);
    key_index = m_settings_model->index(0, 0, group_index);
    data = m_settings_model->data(key_index, -1);
    EXPECT_FALSE(data.isValid());

    // Test when index is valid and role is ValueRole
    data = m_settings_model->data(key_index, SettingsDataRole::ValueRole);
    EXPECT_TRUE(data.isValid());
    EXPECT_EQ(data, value);

    // Test when index is valid and role is KeyRole
    data = m_settings_model->data(key_index, SettingsDataRole::KeyRole);
    EXPECT_TRUE(data.isValid());
    EXPECT_EQ(data, key);
}

// Test case for setData() method
TEST_F(SettingsModelTest, SetDataTest)
{
    // Test when index is invalid
    QModelIndex group_index;
    const QVariant value = "new value";
    bool result = m_settings_model->setData(group_index, value);
    ASSERT_FALSE(result);

    // Test when index is valid and role is invalid
    const QString key = "new key";
    const QVariant value_2 = "new value 2";
    m_settings_model->setValue(key, value);
    group_index = m_settings_model->index(0, 0);
    QModelIndex key_index = m_settings_model->index(0, 2, group_index);
    result = m_settings_model->setData(key_index, value_2, -1);  // Update the value
    ASSERT_FALSE(result);

    // Test when index is valid and role is valid
    result = m_settings_model->setData(key_index, value_2, Qt::EditRole);  // Update the value
    QVariant result_value = m_settings_model->getValue(key);
    EXPECT_EQ(result_value, value_2);
}

// Test case for flags() method
TEST_F(SettingsModelTest, FlagsTest)
{
    // Test when index is invalid
    QModelIndex index;
    Qt::ItemFlags flags = m_settings_model->flags(index);
    EXPECT_EQ(flags, Qt::NoItemFlags);

    // Test when index is valid
    const QString key = "new key";
    const QVariant value = "new value";
    m_settings_model->setValue(key, value);
    index = m_settings_model->index(0, 0);
    flags = m_settings_model->flags(index);
    EXPECT_EQ(flags, Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
}

// Test case for getValue() method
TEST_F(SettingsModelTest, GetValueTest)
{
    // Test when key exists
    QString key = "key1";
    QVariant value = "default value";
    m_settings_model->setValue(key, value);
    QVariant result_value = m_settings_model->getValue(key);
    EXPECT_EQ(result_value, value);

    // Test when key does not exist
    key = "key2";
    result_value = m_settings_model->getValue(key);
    EXPECT_EQ(result_value, QVariant());

    // Test when key does not exist and default value is provided
    key = "key2";
    QVariant default_value = "test default value";
    result_value = m_settings_model->getValue(key, "General", default_value);
    EXPECT_EQ(result_value, default_value);
}

// Test case for setValue() method
TEST_F(SettingsModelTest, SetValueTest)
{
    // Test when key does not exist
    QString key = "new key";
    QVariant value = "new value";
    m_settings_model->setValue(key, value);
    QVariant result = m_settings_model->getValue(key);
    EXPECT_EQ(result, value);

    // Test when same key exists
    value = "updated value";
    m_settings_model->setValue(key, value);
    QVariant updated_value = m_settings_model->getValue(key);
    EXPECT_EQ(updated_value, value);
}

// Test case for loadFromFile() method
TEST_F(SettingsModelTest, LoadFromFileTest)
{
    QString exe_path = QCoreApplication::applicationDirPath();
	QString file_path = exe_path + "/settingsmodeltest_load_settings.ini";
	QFile file(file_path);

	if (file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream stream(&file);
        stream << "[%General]\n";
        stream << "key1=value1\n";
        stream << "key2=value2\n";
        stream << "[TestGroup]\n";
        stream << "key3=value3\n";
        stream << "key4=value4\n";
        stream << "[TestGroup_2]\n";
        stream << "group3/key1=value00\n";
        stream << "group2/group3/key2=value01\n";
        stream << "[TestGroup_3]\n";
        stream << "group3/key1=value02\n";
		file.close();
	}

    m_settings_model->loadFromFile(file_path);

    QVariant result_1 = m_settings_model->getValue("key1", "General");
    QVariant result_2 = m_settings_model->getValue("key2", "General");
    QVariant result_3 = m_settings_model->getValue("key3", "TestGroup");
    QVariant result_4 = m_settings_model->getValue("key4", "TestGroup");
    QVariant result_5 = m_settings_model->getValue("group3/key1", "TestGroup_2");
    QVariant result_6 = m_settings_model->getValue("group2/group3/key2", "TestGroup_2");
    QVariant result_7 = m_settings_model->getValue("group3/key1", "TestGroup_3");
    EXPECT_EQ(result_1, QVariant("value1"));
    EXPECT_EQ(result_2, QVariant("value2"));
    EXPECT_EQ(result_3, QVariant("value3"));
    EXPECT_EQ(result_4, QVariant("value4"));
    EXPECT_EQ(result_5, QVariant("value00"));
    EXPECT_EQ(result_6, QVariant("value01"));
    EXPECT_EQ(result_7, QVariant("value02"));

    QFile::remove(file_path);
}

// Test case for saveToFile() method
TEST_F(SettingsModelTest, SaveToFileTest)
{
    // Test when file path is valid
    QString exe_path = QCoreApplication::applicationDirPath();
    QString file_path = exe_path + "/settingsmodeltest_save_settings.ini";
    m_settings_model->setValue("key1", "value1");
    m_settings_model->setValue("key2", "value2");
    m_settings_model->setValue("key3", "value3", "TestGroup");
    m_settings_model->setValue("key4", "value4", "TestGroup");
    m_settings_model->setValue("group3/key1", "value00", "TestGroup_2");
    m_settings_model->setValue("group2/group3/key2", "value01", "TestGroup_2");
    m_settings_model->setValue("group3/key1", "value02", "TestGroup_3");

    m_settings_model->saveToFile(file_path);

    AppSettings result_app_settings = AppSettings();
    SettingsModel result_settings_model = SettingsModel(&result_app_settings);
    result_settings_model.loadFromFile(file_path);

    QVariant result_1 = result_settings_model.getValue("key1", "General");
    QVariant result_2 = result_settings_model.getValue("key2", "General");
    QVariant result_3 = result_settings_model.getValue("key3", "TestGroup");
    QVariant result_4 = result_settings_model.getValue("key4", "TestGroup");
    QVariant result_5 = result_settings_model.getValue("group3/key1", "TestGroup_2");
    QVariant result_6 = result_settings_model.getValue("group2/group3/key2", "TestGroup_2");
    QVariant result_7 = result_settings_model.getValue("group3/key1", "TestGroup_3");
    EXPECT_EQ(result_1, QVariant("value1"));
    EXPECT_EQ(result_2, QVariant("value2"));
    EXPECT_EQ(result_3, QVariant("value3"));
    EXPECT_EQ(result_4, QVariant("value4"));
    EXPECT_EQ(result_5, QVariant("value00"));
    EXPECT_EQ(result_6, QVariant("value01"));
    EXPECT_EQ(result_7, QVariant("value02"));

    QFile::remove(file_path);
}
