#include "Services/Logging/SimpleFormatterTest.h"

void SimpleFormatterTest::SetUp()
{
	m_formatter = QSharedPointer<SimpleFormatter>::create();
}

void SimpleFormatterTest::TearDown()
{
	m_formatter.reset();
}

/**
 * @brief Tests that the formatter correctly formats a debug log message.
 */
TEST_F(SimpleFormatterTest, FormatDebugMessage)
{
	QtMsgType type = QtDebugMsg;
	QMessageLogContext context(__FILE__, __LINE__, Q_FUNC_INFO, "category");
	QString message = "Debug message";
	LogMessage log_message(type, message);

	QString formatted_message = m_formatter->format(log_message, context);

	EXPECT_TRUE(formatted_message.contains("[Debug    ]:"));
	EXPECT_TRUE(formatted_message.contains(message));
	EXPECT_TRUE(formatted_message.contains(__FILE__));
	EXPECT_TRUE(formatted_message.contains(Q_FUNC_INFO));
}

/**
 * @brief Tests that the formatter correctly formats an info log message.
 */
TEST_F(SimpleFormatterTest, FormatInfoMessage)
{
	QtMsgType type = QtInfoMsg;
	QMessageLogContext context(__FILE__, __LINE__, Q_FUNC_INFO, "category");
	QString message = "Info message";
	LogMessage log_message(type, message);

	QString formatted_message = m_formatter->format(log_message, context);

	EXPECT_TRUE(formatted_message.contains("[Info     ]:"));
	EXPECT_TRUE(formatted_message.contains(message));
	EXPECT_TRUE(formatted_message.contains(__FILE__));
	EXPECT_TRUE(formatted_message.contains(Q_FUNC_INFO));
}

/**
 * @brief Tests that the formatter correctly formats a warning log message.
 */
TEST_F(SimpleFormatterTest, FormatWarningMessage)
{
	QtMsgType type = QtWarningMsg;
	QMessageLogContext context(__FILE__, __LINE__, Q_FUNC_INFO, "category");
	QString message = "Warning message";
	LogMessage log_message(type, message);

	QString formatted_message = m_formatter->format(log_message, context);

	EXPECT_TRUE(formatted_message.contains("[Warning  ]:"));
	EXPECT_TRUE(formatted_message.contains(message));
	EXPECT_TRUE(formatted_message.contains(__FILE__));
	EXPECT_TRUE(formatted_message.contains(Q_FUNC_INFO));
}

/**
 * @brief Tests that the formatter correctly formats a critical log message.
 */
TEST_F(SimpleFormatterTest, FormatCriticalMessage)
{
	QtMsgType type = QtCriticalMsg;
	QMessageLogContext context(__FILE__, __LINE__, Q_FUNC_INFO, "category");
	QString message = "Critical message";
	LogMessage log_message(type, message);

	QString formatted_message = m_formatter->format(log_message, context);

	EXPECT_TRUE(formatted_message.contains("[Critical ]:"));
	EXPECT_TRUE(formatted_message.contains(message));
	EXPECT_TRUE(formatted_message.contains(__FILE__));
	EXPECT_TRUE(formatted_message.contains(Q_FUNC_INFO));
}

/**
 * @brief Tests that the formatter correctly formats a fatal log message.
 */
TEST_F(SimpleFormatterTest, FormatFatalMessage)
{
	QtMsgType type = QtFatalMsg;
	QMessageLogContext context(__FILE__, __LINE__, Q_FUNC_INFO, "category");
	QString message = "Fatal message";
	LogMessage log_message(type, message);

	QString formatted_message = m_formatter->format(log_message, context);

	EXPECT_TRUE(formatted_message.contains("[Fatal    ]:"));
	EXPECT_TRUE(formatted_message.contains(message));
	EXPECT_TRUE(formatted_message.contains(__FILE__));
	EXPECT_TRUE(formatted_message.contains(Q_FUNC_INFO));
}
