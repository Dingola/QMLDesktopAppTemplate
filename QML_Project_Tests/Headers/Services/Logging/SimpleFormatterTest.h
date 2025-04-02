#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Services/Logging/LogMessage.h"
#include "Services/Logging/SimpleFormatter.h"

using namespace QmlApp;

class SimpleFormatterTest: public ::testing::Test
{
    protected:
        void SetUp() override;
        void TearDown() override;

        QSharedPointer<SimpleFormatter> m_formatter;
};
