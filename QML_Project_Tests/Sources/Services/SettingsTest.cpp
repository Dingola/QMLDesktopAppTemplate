#include "Services/SettingsTest.h"

// Test case for getValue() method
TEST_F(SettingsTest, GetValueTest)
{
    // Test when key exists
    QString key = "key1";
    QVariant value = "default value";
    m_settings->setValue(key, value);
    QVariant result_value = m_settings->getValue(key);
    EXPECT_EQ(result_value, value);

    // Test when key exists in group
    QString group = "General";
    key = "key2";
    m_settings->setValue(group, key, value);
    result_value = m_settings->getValue(group, key);
    EXPECT_EQ(result_value, value);

    // Test when key does not exist
    key = "key3";
    result_value = m_settings->getValue(key);
    EXPECT_EQ(result_value, QVariant());

    // Test when key does not exist in group
    key = "key4";
    result_value = m_settings->getValue(group, key);
    EXPECT_EQ(result_value, QVariant());

    // Test when key does not exist and default value is provided
    key = "key5";
    QVariant default_value = "test default value";
    result_value = m_settings->getValue(key, default_value);
    EXPECT_EQ(result_value, default_value);

    // Test when key does not exist in group and default value is provided
    key = "key6";
    QVariant default_value_2 = "test default value 2";
    result_value = m_settings->getValue(group, key, default_value);
    EXPECT_EQ(result_value, default_value);
}

// Test case for setValue() method
TEST_F(SettingsTest, SetValueTest)
{
    // Test when key does not exist
    QString key = "new key";
    QVariant value = "new value";
    m_settings->setValue(key, value);
    QStringList keys = m_settings->allKeys();
    EXPECT_TRUE(keys.contains(key));

    // Test when key does not exist in group
    QString group = "General";
    QString key_2 = "new key 2";
    value = "new value 2";
    m_settings->setValue(group, key_2, value);
    keys = m_settings->childKeys(group);
    EXPECT_TRUE(keys.contains(key_2));

    // Test when same key exists
    value = "updated value";
    m_settings->setValue(key, value);
    QVariant updated_value = m_settings->getValue(key);
    EXPECT_EQ(updated_value, value);

    // Test when same key exists in group
    value = "updated value 2";
    m_settings->setValue(group, key_2, value);
    updated_value = m_settings->getValue(group, key_2);
    EXPECT_EQ(updated_value, value);
}

// Test case for childGroups() method
TEST_F(SettingsTest, ChildGroupsTest)
{
    // Test when no child groups exist
    QStringList groups = m_settings->childGroups();
    EXPECT_TRUE(groups.isEmpty());

    // Test when child groups exist
    QString group = "TestGroup";
    QString key = "new key";
    QVariant value = "new value";
    m_settings->setValue(group, key, value);
    groups = m_settings->childGroups();
    EXPECT_TRUE(groups.contains(group));
}

// Test case for childKeys() method
TEST_F(SettingsTest, ChildKeysTest)
{
    // Test when no child keys exist
    QString group = "General";
    QStringList keys = m_settings->childKeys(group);
    EXPECT_TRUE(keys.isEmpty());

    // Test when child keys exist
    QString key = "TestKey";
    QVariant value = "TestValue";
    m_settings->setValue(group, key, value);
    keys = m_settings->childKeys(group);
    EXPECT_TRUE(keys.contains(key));
}

// Test case for allKeys() method
TEST_F(SettingsTest, AllKeysTest)
{
    // Test when no keys exist
    QStringList keys = m_settings->allKeys();
    EXPECT_TRUE(keys.isEmpty());

    // Test when keys exist
    QString key1 = "key1";
    QVariant value1 = "value1";
    m_settings->setValue(key1, value1);

    QString key2 = "key2";
    QVariant value2 = "value2";
    m_settings->setValue(key2, value2);

    keys = m_settings->allKeys();
    EXPECT_TRUE(keys.contains(key1));
    EXPECT_TRUE(keys.contains(key2));
}

// Test case for contains() method
TEST_F(SettingsTest, ContainsTest)
{
    // Test when key exists
    QString key = "key1";
    QVariant value = "default value";
    m_settings->setValue(key, value);
    bool exists = m_settings->contains(key);
    EXPECT_TRUE(exists);

    // Test when key and group exists
    QString group = "General";
    key = "key2";
    value = "default value 2";
    m_settings->setValue(group, key, value);
    exists = m_settings->contains(group, key);
    EXPECT_TRUE(exists);

    // Test when key does not exist
    key = "key3";
    exists = m_settings->contains(group, key);
    EXPECT_FALSE(exists);
}

// Test case for clear() method
TEST_F(SettingsTest, ClearTest)
{
    // Test when settings are not empty
    QString key = "key1";
    QVariant value = "default value";
    m_settings->setValue(key, value);
    m_settings->clear();
    QStringList keys = m_settings->childKeys("General");
    EXPECT_TRUE(keys.isEmpty());
}

// Test case for loadFromFile() method
TEST_F(SettingsTest, LoadFromFileTest)
{
    QString exe_path = QCoreApplication::applicationDirPath();
    QString file_path = exe_path + "/appsettingstest_load_settings.ini";
    QFile file(file_path);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << "[General]\n";
        stream << "key1=value1\n";
        stream << "key2=value2\n";
        stream << "[%General]\n";
        stream << "key3=value3\n";
        stream << "[TestGroup]\n";
        stream << "Group/key4=value4\n";
        stream << "[TestGroup_2]\n";
        stream << "Group_2/Group/key5=value5\n";
        file.close();
    }

    m_settings->loadFromFile(file_path);

    QVariant result_1 = m_settings->getValue("key1");
    QVariant result_2 = m_settings->getValue("key2");
    QVariant result_3 = m_settings->getValue("General", "key3");
    QVariant result_4 = m_settings->getValue("TestGroup", "Group/key4");
    QVariant result_5 = m_settings->getValue("TestGroup_2", "Group_2/Group/key5");
    EXPECT_EQ(result_1, QVariant("value1"));
    EXPECT_EQ(result_2, QVariant("value2"));
    EXPECT_EQ(result_3, QVariant("value3"));
    EXPECT_EQ(result_4, QVariant("value4"));
    EXPECT_EQ(result_5, QVariant("value5"));

    QFile::remove(file_path);
}

// Test case for saveToFile() method
TEST_F(SettingsTest, SaveToFileTest)
{
    QString exe_path = QCoreApplication::applicationDirPath();
    QString file_path = exe_path + "/appsettingstest_save_settings.ini";
    m_settings->setValue("key1", "value1");
    m_settings->setValue("key2", "value2");
    m_settings->setValue("General", "key3", "value3");
    m_settings->setValue("TestGroup", "Group/key4", "value4");
    m_settings->setValue("TestGroup_2", "Group_2/Group/key5", "value5");

    m_settings->saveToFile(file_path);

    Settings result_app_settings = Settings();
    result_app_settings.loadFromFile(file_path);

    QVariant result_1 = result_app_settings.getValue("key1");
    QVariant result_2 = result_app_settings.getValue("key2");
    QVariant result_3 = result_app_settings.getValue("General", "key3");
    QVariant result_4 = result_app_settings.getValue("TestGroup", "Group/key4");
    QVariant result_5 = result_app_settings.getValue("TestGroup_2", "Group_2/Group/key5");
    EXPECT_EQ(result_1, QVariant("value1"));
    EXPECT_EQ(result_2, QVariant("value2"));
    EXPECT_EQ(result_3, QVariant("value3"));
    EXPECT_EQ(result_4, QVariant("value4"));
    EXPECT_EQ(result_5, QVariant("value5"));

    QFile::remove(file_path);
}
