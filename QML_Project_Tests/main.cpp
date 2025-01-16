#include <gtest/gtest.h>
#include <QApplication>

#include "Services/Logging/Logger.h"
#include "Services/Logging/FileAppender.h"
#include "Services/Logging/ConsoleAppender.h"
#include "Services/Logging/SimpleFormatter.h"

using namespace QmlApp;

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	QApplication app(argc, argv);
	app.setApplicationName(QStringLiteral("QmlAppTest"));
	app.setOrganizationName(QStringLiteral("QmlDesktopAppTemplate_Tests"));
	app.setOrganizationDomain(QStringLiteral("AdrianHelbig.de"));

	// Set up logging
	auto formatter = QSharedPointer<SimpleFormatter>::create();
	auto console_appender = QSharedPointer<ConsoleAppender>::create(formatter);
	auto file_appender = QSharedPointer<FileAppender>::create("QmlApp.log", formatter);

	Logger::get_instance().add_appender(console_appender);
	Logger::get_instance().add_appender(file_appender);

	// Install the custom message handler
	qInstallMessageHandler([](QtMsgType type, const QMessageLogContext& context, const QString& msg)
						   {
							   Logger::get_instance().log(type, context, msg);
						   });

	return RUN_ALL_TESTS();
}
