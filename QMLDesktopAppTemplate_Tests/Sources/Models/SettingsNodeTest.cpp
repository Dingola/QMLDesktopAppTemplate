#include "Models/SettingsNodeTest.h"

// Test case for constructor
TEST_F(SettingsNodeTest, ConstructorTest)
{
    // Test group, key, and value
    QString group = "TestGroup";
    QString key = "TestKey";
    QVariant value = "TestValue";
    SettingsNode* settings_node = new SettingsNode(group, key, value);
    EXPECT_EQ(settings_node->get_group(), group);
    EXPECT_EQ(settings_node->get_key(), key);
    EXPECT_EQ(settings_node->get_value(), value);
    delete settings_node;

    // Test group and key only
    group = "TestGroup";
    key = "TestKey";
    settings_node = new SettingsNode(group, key);
    EXPECT_EQ(settings_node->get_group(), group);
    EXPECT_EQ(settings_node->get_key(), key);
    EXPECT_EQ(settings_node->get_value(), QVariant());
    delete settings_node;
}

// Test case for append_child() method
TEST_F(SettingsNodeTest, AppendChildTest)
{
    // Test appending a child node
    SettingsNode* child_node = new SettingsNode("ChildGroup", "ChildKey", "ChildValue");
    m_settings_node->append_child(child_node);
    QVector<SettingsNode*> child_items = m_settings_node->child_items();
    EXPECT_EQ(child_items.size(), 1);
    EXPECT_EQ(child_items[0], child_node);

    // Test appending multiple child nodes
    SettingsNode* child_node_1 = new SettingsNode("ChildGroup1", "ChildKey1", "ChildValue1");
    SettingsNode* child_node_2 = new SettingsNode("ChildGroup2", "ChildKey2", "ChildValue2");
    m_settings_node->append_child(child_node_1);
    m_settings_node->append_child(child_node_2);
    child_items = m_settings_node->child_items();
    EXPECT_EQ(child_items.size(), 3);
    EXPECT_EQ(child_items[0], child_node);
    EXPECT_EQ(child_items[1], child_node_1);
    EXPECT_EQ(child_items[2], child_node_2);
}

// Test case for get_child() method
TEST_F(SettingsNodeTest, GetChildTest)
{
    // Test getting a child node
    SettingsNode* child_node = new SettingsNode("ChildGroup", "ChildKey", "ChildValue");
    m_settings_node->append_child(child_node);
    SettingsNode* result_node = m_settings_node->get_child(0);
    EXPECT_EQ(result_node, child_node);

    // Test when no child node exists at the specified index
    result_node = m_settings_node->get_child(1);
    EXPECT_EQ(result_node, nullptr);
}

// Test case for child_items() method
TEST_F(SettingsNodeTest, ChildItemsTest)
{
    // Test getting child items
    SettingsNode* child_node_1 = new SettingsNode("ChildGroup1", "ChildKey1", "ChildValue1");
    SettingsNode* child_node_2 = new SettingsNode("ChildGroup2", "ChildKey2", "ChildValue2");
    m_settings_node->append_child(child_node_1);
    m_settings_node->append_child(child_node_2);
    QVector<SettingsNode*> child_items = m_settings_node->child_items();
    EXPECT_EQ(child_items.size(), 2);
    EXPECT_EQ(child_items[0], child_node_1);
    EXPECT_EQ(child_items[1], child_node_2);

    // Test when no child items exist
    m_settings_node->clear();
    child_items = m_settings_node->child_items();
    EXPECT_TRUE(child_items.isEmpty());
}

// Test case for child_count() method
TEST_F(SettingsNodeTest, ChildCountTest)
{
    // Test getting child count
    SettingsNode* child_node_1 = new SettingsNode("ChildGroup1", "ChildKey1", "ChildValue1");
    SettingsNode* child_node_2 = new SettingsNode("ChildGroup2", "ChildKey2", "ChildValue2");
    m_settings_node->append_child(child_node_1);
    m_settings_node->append_child(child_node_2);
    int child_count = m_settings_node->child_count();
    EXPECT_EQ(child_count, 2);

    // Test when no child items exist
    m_settings_node->clear();
    child_count = m_settings_node->child_count();
    EXPECT_EQ(child_count, 0);
}

// Test case for column_count() method
TEST_F(SettingsNodeTest, ColumnCountTest)
{
    // Test getting column count
    int column_count = m_settings_node->column_count();
    EXPECT_EQ(column_count, 3);
}

// Test case for data() method
TEST_F(SettingsNodeTest, DataTest)
{
    // Test getting data for each column
    QVariant group_data = m_settings_node->data(0);
    QVariant key_data = m_settings_node->data(1);
    QVariant value_data = m_settings_node->data(2);
    EXPECT_EQ(group_data, m_settings_node->get_group());
    EXPECT_EQ(key_data, m_settings_node->get_key());
    EXPECT_EQ(value_data, m_settings_node->get_value());
}

// Test case for set_data() method
TEST_F(SettingsNodeTest, SetDataTest)
{
    // Test setting data for each column
    QString new_group = "NewGroup";
    QString new_key = "NewKey";
    QVariant new_value = "NewValue";
    m_settings_node->set_data(0, new_group);
    m_settings_node->set_data(1, new_key);
    m_settings_node->set_data(2, new_value);
    EXPECT_EQ(m_settings_node->get_group(), new_group);
    EXPECT_EQ(m_settings_node->get_key(), new_key);
    EXPECT_EQ(m_settings_node->get_value(), new_value);
}

// Test case for row() method
TEST_F(SettingsNodeTest, RowTest)
{
    // Test getting row index
    int row = m_settings_node->row();
    EXPECT_EQ(row, 0);

    // Test when node has parent
    SettingsNode* parent_node = new SettingsNode("ParentGroup", "ParentKey", "ParentValue");
    parent_node->append_child(m_settings_node);
    row = m_settings_node->row();
    EXPECT_EQ(row, 0);
}

// Test case for get_parent_item() method
TEST_F(SettingsNodeTest, GetParentItemTest)
{
    // Test getting parent item
    SettingsNode* parent_item = m_settings_node->get_parent_item();
    EXPECT_EQ(parent_item, nullptr);

    // Test when node has parent
    SettingsNode* parent_node = new SettingsNode("ParentGroup", "ParentKey", "ParentValue");
    parent_node->append_child(m_settings_node);
    parent_item = m_settings_node->get_parent_item();
    EXPECT_EQ(parent_item, parent_node);
}

// Test case for has_parent() method
TEST_F(SettingsNodeTest, HasParentTest)
{
    // Test checking if node has parent
    bool has_parent = m_settings_node->has_parent();
    EXPECT_FALSE(has_parent);

    // Test when node has parent
    SettingsNode* parent_node = new SettingsNode("ParentGroup", "ParentKey", "ParentValue");
    parent_node->append_child(m_settings_node);
    has_parent = m_settings_node->has_parent();
    EXPECT_TRUE(has_parent);
}

// Test case for has_children() method
TEST_F(SettingsNodeTest, HasChildrenTest)
{
    // Test checking if node has children
    bool has_children = m_settings_node->has_children();
    EXPECT_FALSE(has_children);

    // Test when node has children
    SettingsNode* child_node = new SettingsNode("ChildGroup", "ChildKey", "ChildValue");
    m_settings_node->append_child(child_node);
    has_children = m_settings_node->has_children();
    EXPECT_TRUE(has_children);
}

// Test case for find_node_by_group() method
TEST_F(SettingsNodeTest, FindNodeByGroupTest)
{
    // Test finding a node by group
    SettingsNode* child_node = new SettingsNode("ChildGroup", "ChildKey", "ChildValue");
    m_settings_node->append_child(child_node);
    SettingsNode* result_node = m_settings_node->find_node_by_group("ChildGroup");
    EXPECT_EQ(result_node, child_node);

    // Test when node has grandchild
    SettingsNode* grandchild_node = new SettingsNode("GrandchildGroup", "GrandchildKey", "GrandchildValue");
    child_node->append_child(grandchild_node);
    result_node = m_settings_node->find_node_by_group("GrandchildGroup");
    EXPECT_EQ(result_node, grandchild_node);
}

// Test case for find_node_by_key() method
TEST_F(SettingsNodeTest, FindNodeByKeyTest)
{
    // Test finding a node by key
    SettingsNode* child_node = new SettingsNode("ChildGroup", "ChildKey", "ChildValue");
    m_settings_node->append_child(child_node);
    SettingsNode* result_node = m_settings_node->find_node_by_key("ChildKey");
    EXPECT_EQ(result_node, child_node);

    // Test when node has grandchild
    SettingsNode* grandchild_node = new SettingsNode("GrandchildGroup", "GrandchildKey", "GrandchildValue");
    child_node->append_child(grandchild_node);
    result_node = m_settings_node->find_node_by_key("GrandchildKey");
    EXPECT_EQ(result_node, grandchild_node);
}

// Test case for set_value() method
TEST_F(SettingsNodeTest, SetValueTest)
{
    // Test setting value
    QVariant new_value = "NewValue";
    m_settings_node->set_value(new_value);
    EXPECT_EQ(m_settings_node->get_value(), new_value);

    // Test setting value to empty
    m_settings_node->set_value(QVariant());
    EXPECT_EQ(m_settings_node->get_value(), QVariant());
}

// Test case for get_full_group() method
TEST_F(SettingsNodeTest, GetFullGroupTest)
{
    // Test getting full group path
    QString full_group = m_settings_node->get_full_group();
    EXPECT_EQ(full_group, "");

    // Test when node has parent
    SettingsNode* parent_node = new SettingsNode("ParentGroup", "ParentKey", "ParentValue");
    parent_node->append_child(m_settings_node);
    full_group = m_settings_node->get_full_group();
    EXPECT_EQ(full_group, "ParentGroup");

    // Test when node has parent and grandparent
    SettingsNode* grandparent_node = new SettingsNode("GrandparentGroup", "GrandparentKey", "GrandparentValue");
    grandparent_node->append_child(parent_node);
    full_group = m_settings_node->get_full_group();
    EXPECT_EQ(full_group, "GrandparentGroup/ParentGroup");
}

// Test case for clear() method
TEST_F(SettingsNodeTest, ClearTest)
{
    // Test clearing the node
    m_settings_node->clear();
    QVector<SettingsNode*> child_items = m_settings_node->child_items();
    EXPECT_TRUE(child_items.isEmpty());

    // Test clearing the node with children
    SettingsNode* child_node = new SettingsNode("ChildGroup", "ChildKey", "ChildValue");
    m_settings_node->append_child(child_node);
    m_settings_node->clear();
    child_items = m_settings_node->child_items();
    EXPECT_TRUE(child_items.isEmpty());
}

// Test case for destructor
TEST_F(SettingsNodeTest, DestructorTest)
{
    // Test destructor
    SettingsNode* settings_node = new SettingsNode("TestGroup", "TestKey", "TestValue");
    settings_node->append_child(new SettingsNode("ChildGroup", "ChildKey", "ChildValue"));
    delete settings_node;
}
