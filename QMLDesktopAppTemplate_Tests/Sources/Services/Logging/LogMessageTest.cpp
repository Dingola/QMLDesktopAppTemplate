#include "Services/Logging/LogMessageTest.h"

void LogMessageTest::SetUp()
{
}

void LogMessageTest::TearDown()
{
}

/**
 * @brief Tests the default constructor of LogMessage.
 *
 * This test verifies that the default constructor of LogMessage
 * initializes the type to QtDebugMsg and the message to an empty QString.
 */
TEST_F(LogMessageTest, DefaultConstructor)
{
    LogMessage log_message;
    EXPECT_EQ(log_message.get_type(), QtDebugMsg);
    EXPECT_EQ(log_message.get_message(), QString());
}

/**
 * @brief Tests the parameterized constructor of LogMessage.
 *
 * This test verifies that the parameterized constructor of LogMessage
 * correctly initializes the type and message with the provided values.
 */
TEST_F(LogMessageTest, ParameterizedConstructor)
{
    QtMsgType type = QtWarningMsg;
    QString message = "Test warning message";
    LogMessage log_message(type, message);
    EXPECT_EQ(log_message.get_type(), type);
    EXPECT_EQ(log_message.get_message(), message);
}

/**
 * @brief Tests the get_type method of LogMessage.
 *
 * This test verifies that the get_type method correctly returns the
 * message type initialized in the LogMessage object.
 */
TEST_F(LogMessageTest, GetType)
{
    LogMessage log_message(QtCriticalMsg, "Critical message");
    EXPECT_EQ(log_message.get_type(), QtCriticalMsg);
}

/**
 * @brief Tests the get_message method of LogMessage.
 *
 * This test verifies that the get_message method correctly returns the
 * message content initialized in the LogMessage object.
 */
TEST_F(LogMessageTest, GetMessage)
{
    QString message = "Info message";
    LogMessage log_message(QtInfoMsg, message);
    EXPECT_EQ(log_message.get_message(), message);
}
