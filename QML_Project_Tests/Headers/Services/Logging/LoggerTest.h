#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Services/Logging/Logger.h"
#include "Services/Logging/LogAppender.h"
#include "Services/Logging/LogMessage.h"

using namespace QmlApp;

class MockLogAppender : public LogAppender
{
public:
	MOCK_METHOD(void, internal_append, (const LogMessage& message, const QMessageLogContext& context), (override));

};

class LoggerTest : public ::testing::Test
{
protected:
	void SetUp() override;
	void TearDown() override;

	QSharedPointer<MockLogAppender> m_mock_appender;
};
