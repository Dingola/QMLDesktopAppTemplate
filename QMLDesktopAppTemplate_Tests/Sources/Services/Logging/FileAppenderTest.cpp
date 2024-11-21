#include "Services/Logging/FileAppenderTest.h"

#include <QFile>
#include <QTextStream>

void FileAppenderTest::SetUp()
{
    m_test_file_path = "test_log_file.log";
    m_file_appender = QSharedPointer<FileAppender>::create(m_test_file_path);
}

void FileAppenderTest::TearDown()
{
    m_file_appender.reset();
    QFile::remove(m_test_file_path);
}

/**
 * @brief Tests that a log message is correctly appended to the file.
 *
 * This test verifies that when a log message is logged, it is correctly
 * appended to the file by the appender. It checks that the log message
 * type, message content, and log context (file, line, function, category)
 * are correctly passed to the appender.
 */
TEST_F(FileAppenderTest, LogMessageIsAppended)
{
    QtMsgType type = QtDebugMsg;
    QMessageLogContext context(__FILE__, __LINE__, Q_FUNC_INFO, "category");
    QString message = "Test message";

    m_file_appender->append(LogMessage(type, message), context);

    QFile file(m_test_file_path);
    ASSERT_TRUE(file.open(QIODevice::ReadOnly | QIODevice::Text));
    QTextStream in(&file);
    QString file_content = in.readAll();
    file.close();

    EXPECT_TRUE(file_content.contains(message));
}

/**
 * @brief Tests that a log message with different types is correctly appended to the file.
 *
 * This test verifies that when log messages with different types (Debug, Info, Warning, Critical, Fatal)
 * are logged, they are correctly appended to the file by the appender.
 */
TEST_F(FileAppenderTest, LogMessageWithDifferentTypes)
{
    struct TestCase
    {
        QtMsgType type;
        QString message;
    };

    std::vector<TestCase> test_cases = {
        {QtDebugMsg, "Debug message"},
        {QtInfoMsg, "Info message"},
        {QtWarningMsg, "Warning message"},
        {QtCriticalMsg, "Critical message"},
        {QtFatalMsg, "Fatal message"}
    };

    for (const auto& test_case : test_cases)
    {
        QMessageLogContext context(__FILE__, __LINE__, Q_FUNC_INFO, "category");
        m_file_appender->append(LogMessage(test_case.type, test_case.message), context);
    }

    QFile file(m_test_file_path);
    ASSERT_TRUE(file.open(QIODevice::ReadOnly | QIODevice::Text));
    QTextStream in(&file);
    QString file_content = in.readAll();
    file.close();

    for (const auto& test_case : test_cases)
    {
        EXPECT_TRUE(file_content.contains(test_case.message));
    }
}
