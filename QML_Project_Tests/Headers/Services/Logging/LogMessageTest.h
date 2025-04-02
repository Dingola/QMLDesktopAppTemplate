#pragma once

#include <gtest/gtest.h>

#include "Services/Logging/LogMessage.h"

using namespace QmlApp;

class LogMessageTest: public ::testing::Test
{
    protected:
        void SetUp() override;
        void TearDown() override;
};
