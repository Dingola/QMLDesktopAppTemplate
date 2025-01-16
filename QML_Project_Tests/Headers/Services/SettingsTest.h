#pragma once

#include <gtest/gtest.h>

#include <QCoreApplication>
#include <QFile>
#include <QTextStream>

#include "Services/Settings.h"

using namespace QmlApp;

class SettingsTest : public ::testing::Test
{
public:
    Settings* m_settings = nullptr;

protected:
    void SetUp() override
    {
        m_settings = new Settings();
    }

    void TearDown() override
    {
        m_settings->clear();
        delete m_settings;
    }
};
