/**
 * @file main.cpp
 * @brief This file contains the main function of the application.
 */

#include <QGuiApplication>

#include "QmlApplication.h"
#include "Services/Logging/ConsoleAppender.h"
#include "Services/Logging/FileAppender.h"
#include "Services/Logging/Logger.h"
#include "Services/Logging/SimpleFormatter.h"

using namespace QmlApp;

/**
 * @brief The main function of the application initializes the Qt application, sets necessary
 * attributes, loads the QML application engine, and executes the application event loop. If the QML
 * application engine fails to load the main QML file, the function returns -1. Otherwise, it starts
 * the application event loop and returns the exit code of the application.
 *
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 *
 * @return The exit code of the application.
 */
auto main(int argc, char* argv[]) -> int
{
    // This line ensures that the resources are included in the final application binary when using
    // static linking.
    Q_INIT_RESOURCE(resources);

    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);

    QGuiApplication app(argc, argv);
    app.setApplicationName(QStringLiteral("QmlApp"));
    app.setOrganizationName(QStringLiteral("QmlDesktopAppTemplate"));
    app.setOrganizationDomain(QStringLiteral("AdrianHelbig.de"));

    // Set up logging
    auto formatter = QSharedPointer<SimpleFormatter>::create();
    auto console_appender = QSharedPointer<ConsoleAppender>::create(formatter);
    auto file_appender = QSharedPointer<FileAppender>::create("QmlApp.log", formatter);

    Logger::get_instance().add_appender(console_appender);
    Logger::get_instance().add_appender(file_appender);

    // Install the custom message handler
    qInstallMessageHandler(
        [](QtMsgType type, const QMessageLogContext& context, const QString& msg) {
            Logger::get_instance().log(type, context, msg);
        });

    QmlApplication qml_app;

    return qml_app.exec();
}
