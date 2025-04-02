#pragma once

#include <gtest/gtest.h>

#include "Models/SettingsNode.h"

using namespace QmlApp;

class SettingsNodeTest: public ::testing::Test
{
    public:
        SettingsNode* m_settings_node = nullptr;

    protected:
        void SetUp() override
        {
            m_settings_node = new SettingsNode("TestGroup", "TestKey", "TestValue");
        }

        void TearDown() override
        {
            delete m_settings_node;
        }
};
