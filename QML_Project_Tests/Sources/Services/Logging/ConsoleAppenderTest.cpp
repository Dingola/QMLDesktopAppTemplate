#include "Services/Logging/ConsoleAppenderTest.h"

#include <QDebug>
#include <iostream>
#include <sstream>

QTextStream* ConsoleAppenderTest::m_text_stream = nullptr;
QBuffer ConsoleAppenderTest::m_buffer;

ConsoleAppenderTest::ConsoleAppenderTest()
{
    m_buffer.open(QIODevice::WriteOnly);
    m_text_stream = new QTextStream(&m_buffer);
}

ConsoleAppenderTest::~ConsoleAppenderTest()
{
    delete m_text_stream;
}

void ConsoleAppenderTest::SetUp()
{
    m_console_appender =
        QSharedPointer<ConsoleAppender>::create(QSharedPointer<SimpleFormatter>::create());
}

void ConsoleAppenderTest::TearDown()
{
    m_console_appender.reset();
}

/**
 * @brief Custom message handler to redirect qDebug output to the buffer.
 *
 * This function is used to handle Qt debug messages and redirect them to
 * the QTextStream buffer for capturing console output during tests.
 *
 * @param type The type of the message (QtDebugMsg, QtInfoMsg, etc.).
 * @param context The context of the message (file, line, function, category).
 * @param msg The message content.
 */
void ConsoleAppenderTest::customMessageHandler(QtMsgType type, const QMessageLogContext& context,
                                               const QString& msg)
{
    Q_UNUSED(type);
    Q_UNUSED(context);
    (*m_text_stream) << msg << Qt::endl;
}

/**
 * @brief Captures the console output generated by a given function.
 *
 * This method temporarily installs a custom message handler to redirect
 * Qt debug messages to a buffer. It then executes the provided function
 * and captures any console output generated during its execution.
 * After the function completes, the original message handler is restored,
 * and the captured output is returned as a string.
 *
 * @param func The function whose console output is to be captured.
 * @return A string containing the captured console output.
 */
std::string ConsoleAppenderTest::capture_console_output(std::function<void()> func)
{
    // Custom message handler to redirect qDebug output to the buffer
    auto original_handler = qInstallMessageHandler(
        [](QtMsgType type, const QMessageLogContext& context, const QString& msg) {
            customMessageHandler(type, context, msg);
        });

    m_text_stream->flush();
    func();
    qInstallMessageHandler(original_handler);

    return m_buffer.data().toStdString();
}

/**
 * @brief Tests that a log message is correctly appended to the console.
 *
 * This test verifies that when a log message is logged, it is correctly
 * appended to the console by the appender. It checks that the log message
 * type, message content, and log context (file, line, function, category)
 * are correctly passed to the appender.
 */
TEST_F(ConsoleAppenderTest, LogMessageIsAppended)
{
    QtMsgType type = QtDebugMsg;
    QMessageLogContext context(__FILE__, __LINE__, Q_FUNC_INFO, "category");
    QString message = "Test message";
    SimpleFormatter formatter;
    QString expected_message = formatter.format(LogMessage(type, message), context);

    std::string output = capture_console_output(
        [&]() { m_console_appender->append(LogMessage(type, message), context); });

    ASSERT_NE(output.find(expected_message.toStdString()), std::string::npos);
}

/**
 * @brief Tests that log messages with different types are correctly appended to the console.
 *
 * This test verifies that when log messages with different types (Debug, Info, Warning, Critical)
 * are logged, they are correctly appended to the console by the appender.
 */
TEST_F(ConsoleAppenderTest, LogMessageWithDifferentTypes)
{
    struct TestCase {
            QtMsgType type;
            QString message;
    };

    std::vector<TestCase> test_cases = {{QtDebugMsg, "Debug message"},
                                        {QtInfoMsg, "Info message"},
                                        {QtWarningMsg, "Warning message"},
                                        {QtCriticalMsg, "Critical message"}};

    SimpleFormatter formatter;

    for (const auto& test_case: test_cases)
    {
        QMessageLogContext context(__FILE__, __LINE__, Q_FUNC_INFO, "category");
        QString expected_message =
            formatter.format(LogMessage(test_case.type, test_case.message), context);

        std::string output = capture_console_output([&]() {
            m_console_appender->append(LogMessage(test_case.type, test_case.message), context);
        });

        ASSERT_NE(output.find(expected_message.toStdString()), std::string::npos);
    }
}

/**
 * @brief Tests that the found message matches the formatting of the SimpleFormatter.
 *
 * This test verifies that when a log message is logged, the captured output
 * matches the expected format provided by the SimpleFormatter.
 */
TEST_F(ConsoleAppenderTest, FoundMessageMatchesSimpleFormatter)
{
    QtMsgType type = QtDebugMsg;
    QMessageLogContext context(__FILE__, __LINE__, Q_FUNC_INFO, "category");
    QString message = "Formatted message test";
    SimpleFormatter formatter;
    QString expected_message = formatter.format(LogMessage(type, message), context);

    std::string output = capture_console_output(
        [&]() { m_console_appender->append(LogMessage(type, message), context); });

    ASSERT_NE(output.find(expected_message.toStdString()), std::string::npos);
}

/**
 * @brief Tests that log messages below the log level are not appended to the console.
 *
 * This test verifies that when a log message with a type below the log level is logged,
 * it is not appended to the console by the appender.
 */
TEST_F(ConsoleAppenderTest, LogMessageBelowLogLevelIsNotAppended)
{
    m_console_appender->set_log_level(QtWarningMsg);

    QtMsgType type = QtDebugMsg;
    QMessageLogContext context(__FILE__, __LINE__, Q_FUNC_INFO, "category");
    QString message = "This message should not appear";
    SimpleFormatter formatter;
    QString expected_message = formatter.format(LogMessage(type, message), context);

    std::string output = capture_console_output(
        [&]() { m_console_appender->append(LogMessage(type, message), context); });

    ASSERT_EQ(output.find(expected_message.toStdString()), std::string::npos);
}

/**
 * @brief Tests that log messages at or above the log level are appended to the console.
 *
 * This test verifies that when a log message with a type at or above the log level is logged,
 * it is correctly appended to the console by the appender.
 */
TEST_F(ConsoleAppenderTest, LogMessageAtOrAboveLogLevelIsAppended)
{
    m_console_appender->set_log_level(QtWarningMsg);

    struct TestCase {
            QtMsgType type;
            QString message;
    };

    std::vector<TestCase> test_cases = {{QtWarningMsg, "Warning message"},
                                        {QtCriticalMsg, "Critical message"}};

    SimpleFormatter formatter;

    for (const auto& test_case: test_cases)
    {
        QMessageLogContext context(__FILE__, __LINE__, Q_FUNC_INFO, "category");
        QString expected_message =
            formatter.format(LogMessage(test_case.type, test_case.message), context);

        std::string output = capture_console_output([&]() {
            m_console_appender->append(LogMessage(test_case.type, test_case.message), context);
        });

        ASSERT_NE(output.find(expected_message.toStdString()), std::string::npos);
    }
}

/**
 * @brief Tests that the log level can be changed dynamically.
 *
 * This test verifies that the log level of the appender can be changed dynamically,
 * and that log messages are correctly appended or not appended based on the new log level.
 */
TEST_F(ConsoleAppenderTest, LogLevelCanBeChangedDynamically)
{
    m_console_appender->set_log_level(QtWarningMsg);

    QtMsgType type = QtDebugMsg;
    QMessageLogContext context(__FILE__, __LINE__, Q_FUNC_INFO, "category");
    QString message = "This message should not appear";
    SimpleFormatter formatter;
    QString expected_message = formatter.format(LogMessage(type, message), context);

    std::string output = capture_console_output(
        [&]() { m_console_appender->append(LogMessage(type, message), context); });

    ASSERT_EQ(output.find(expected_message.toStdString()), std::string::npos);

    m_console_appender->set_log_level(QtDebugMsg);

    output = capture_console_output(
        [&]() { m_console_appender->append(LogMessage(type, message), context); });

    ASSERT_NE(output.find(expected_message.toStdString()), std::string::npos);
}
