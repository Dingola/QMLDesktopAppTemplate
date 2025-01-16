#pragma once

#include <gtest/gtest.h>

#include <QTextStream>
#include <QBuffer>

#include "Services/Logging/ConsoleAppender.h"
#include "Services/Logging/LogMessage.h"
#include "Services/Logging/SimpleFormatter.h"

using namespace QmlApp;

class ConsoleAppenderTest : public ::testing::Test
{
public:
	ConsoleAppenderTest();
	~ConsoleAppenderTest();

protected:
	void SetUp() override;
	void TearDown() override;

public:
	static std::string capture_console_output(std::function<void()> func);
	static void customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);

public:
	QSharedPointer<ConsoleAppender> m_console_appender;
	static QTextStream* m_text_stream;
	static QBuffer m_buffer;

};
