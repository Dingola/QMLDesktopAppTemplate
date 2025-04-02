#pragma once

#include <gtest/gtest.h>

#include <QCoreApplication>
#include <QFile>
#include <QTextStream>

#include "Models/SettingsModel.h"

using namespace QmlApp;

class SettingsModelTest: public ::testing::Test
{
    public:
        Settings* m_settings = nullptr;
        SettingsModel* m_settings_model = nullptr;

    protected:
        void SetUp() override
        {
            m_settings = new Settings();
            m_settings_model = new SettingsModel(m_settings);
        }

        void TearDown() override
        {
            m_settings->clear();
            delete m_settings;
            delete m_settings_model;
        }
};
