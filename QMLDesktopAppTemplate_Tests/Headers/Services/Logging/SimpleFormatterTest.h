#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Services/Logging/SimpleFormatter.h"
#include "Services/Logging/LogMessage.h"

using namespace QmlApp;

class SimpleFormatterTest : public ::testing::Test
{
protected:
    void SetUp() override;
    void TearDown() override;

    QSharedPointer<SimpleFormatter> m_formatter;
};
