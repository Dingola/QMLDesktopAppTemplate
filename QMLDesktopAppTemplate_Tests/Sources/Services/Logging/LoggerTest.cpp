#include "Services/Logging/LoggerTest.h"

using ::testing::_;
using ::testing::Invoke;

void LoggerTest::SetUp()
{
	m_mock_appender = QSharedPointer<MockLogAppender>::create();
	Logger::get_instance().clear_appenders();
	Logger::get_instance().add_appender(m_mock_appender);
}

void LoggerTest::TearDown()
{
	Logger::get_instance().clear_appenders();
}

/**
 * @brief Tests that a log message is correctly appended to the log.
 *
 * This test verifies that when a log message is logged, it is correctly
 * appended to the log by the mock appender. It checks that the log message
 * type, message content, and log context (file, line, function, category)
 * are correctly passed to the appender.
 */
TEST_F(LoggerTest, LogMessageIsAppended)
{
	QtMsgType type = QtDebugMsg;
	QMessageLogContext context(__FILE__, __LINE__, Q_FUNC_INFO, "category");
	QString message = "Test message";

	EXPECT_CALL(*m_mock_appender, internal_append(_, _))
		.WillOnce(Invoke([&](const LogMessage& log_message, const QMessageLogContext& log_context)
						 {
							 EXPECT_EQ(log_message.get_type(), type);
							 EXPECT_EQ(log_message.get_message(), message);
							 EXPECT_STREQ(log_context.file, context.file);
							 EXPECT_EQ(log_context.line, context.line);
							 EXPECT_STREQ(log_context.function, context.function);
							 EXPECT_STREQ(log_context.category, context.category);
						 }));

	Logger::get_instance().log(type, context, message);
}

/**
 * @brief Tests that a log message is correctly appended to multiple appenders.
 *
 * This test verifies that when a log message is logged, it is correctly
 * appended to multiple appenders. It checks that the log message is passed
 * to both the primary mock appender and an additional mock appender.
 */
TEST_F(LoggerTest, LogMessageToMultipleAppenders)
{
	auto another_mock_appender = QSharedPointer<MockLogAppender>::create();
	Logger::get_instance().add_appender(another_mock_appender);

	QtMsgType type = QtDebugMsg;
	QMessageLogContext context(__FILE__, __LINE__, Q_FUNC_INFO, "category");
	QString message = "Test message";

	EXPECT_CALL(*m_mock_appender, internal_append(_, _)).Times(1);
	EXPECT_CALL(*another_mock_appender, internal_append(_, _)).Times(1);

	Logger::get_instance().log(type, context, message);
}

/**
 * @brief Tests that the log level is correctly set and retrieved.
 *
 * This test verifies that the log level can be set and retrieved correctly.
 */
TEST_F(LoggerTest, SetAndGetLogLevel)
{
	Logger::get_instance().set_log_level(QtWarningMsg);
	EXPECT_EQ(Logger::get_instance().get_log_level(), QtWarningMsg);

	Logger::get_instance().set_log_level(QtCriticalMsg);
	EXPECT_EQ(Logger::get_instance().get_log_level(), QtCriticalMsg);
}

/**
 * @brief Tests that log messages below the set log level are not appended.
 *
 * This test verifies that log messages with a type below the set log level
 * are not appended to the log by the mock appender.
 */
TEST_F(LoggerTest, LogMessagesBelowLogLevelAreNotAppended)
{
	Logger::get_instance().set_log_level(QtWarningMsg);

	QtMsgType type = QtDebugMsg;
	QMessageLogContext context(__FILE__, __LINE__, Q_FUNC_INFO, "category");
	QString message = "Test message";

	EXPECT_CALL(*m_mock_appender, internal_append(_, _)).Times(0);

	Logger::get_instance().log(type, context, message);
}

/**
 * @brief Tests that log messages at or above the set log level are appended.
 *
 * This test verifies that log messages with a type at or above the set log level
 * are appended to the log by the mock appender.
 */
TEST_F(LoggerTest, LogMessagesAtOrAboveLogLevelAreAppended)
{
	Logger::get_instance().set_log_level(QtWarningMsg);

	QtMsgType type = QtWarningMsg;
	QMessageLogContext context(__FILE__, __LINE__, Q_FUNC_INFO, "category");
	QString message = "Test message";

	EXPECT_CALL(*m_mock_appender, internal_append(_, _)).Times(1);

	Logger::get_instance().log(type, context, message);
}
