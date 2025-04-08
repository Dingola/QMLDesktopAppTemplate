#pragma once

#include <gtest/gtest.h>

#include <QBuffer>
#include <QTextStream>

#include "Services/Logging/ConsoleAppender.h"
#include "Services/Logging/LogMessage.h"
#include "Services/Logging/SimpleFormatter.h"

using namespace QmlApp;

class ConsoleAppenderTest: public ::testing::Test
{
    public:
        ConsoleAppenderTest();
        ~ConsoleAppenderTest() override;

    protected:
        void SetUp() override;
        void TearDown() override;

    public:
        static auto capture_console_output(std::function<void()> func) -> std::string;
        static auto customMessageHandler(QtMsgType type, const QMessageLogContext& context,
                                         const QString& msg) -> void;

    public:
        QSharedPointer<ConsoleAppender> m_console_appender;
        static QTextStream* m_text_stream;
        static QBuffer m_buffer;
};
