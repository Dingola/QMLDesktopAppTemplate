/**
 * @file main.cpp
 * @brief This file contains the main function of the application.
 */

#include <QGuiApplication>

#include "QmlApplication.h"

using namespace QmlApp;

/**
 * @brief The main function of the application initializes the Qt application, sets necessary attributes,
 * loads the QML application engine, and executes the application event loop.
 * If the QML application engine fails to load the main QML file, the function returns -1.
 * Otherwise, it starts the application event loop and returns the exit code of the application.
 * 
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 * 
 * @return The exit code of the application.
 */
int main(int argc, char *argv[])
{
    // This line ensures that the resources are included in the final application binary when using static linking.
    Q_INIT_RESOURCE(resources);

    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QmlApplication qml_app;

    return qml_app.exec();
}
