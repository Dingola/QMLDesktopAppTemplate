#pragma once

#include <gtest/gtest.h>

#include "Services/Logging/FileAppender.h"
#include "Services/Logging/LogMessage.h"
#include "Services/Logging/SimpleFormatter.h"

using namespace QmlApp;

class FileAppenderTest : public ::testing::Test
{
protected:
	void SetUp() override;
	void TearDown() override;

public:
	QSharedPointer<FileAppender> m_file_appender;
	QString m_test_file_path;
};
