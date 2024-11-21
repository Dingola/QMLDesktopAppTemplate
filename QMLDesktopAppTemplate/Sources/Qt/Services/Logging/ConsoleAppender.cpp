/**
 * @file ConsoleAppender.cpp
 * @brief This file contains the implementation of the ConsoleAppender class.
 */

#include "Services/Logging/ConsoleAppender.h"

#include <QDebug>

namespace QmlApp
{
    /**
     * @brief Constructs a ConsoleAppender object with the given formatter.
     *
     * This constructor initializes the ConsoleAppender object with the provided LogFormatter object.
     *
     * @param formatter The LogFormatter object to use for formatting log messages.
     */
    ConsoleAppender::ConsoleAppender(const QSharedPointer<LogFormatter>& formatter)
        : LogAppender(formatter)
    {
    }

    /**
     * @brief Appends the specified log message to the console.
     *
     * This function formats the log message using the provided formatter and outputs it to the console
     * using the appropriate Qt logging function based on the message type.
     *
     * @param message The log message to append to the console.
     * @param context The context of the log message.
     */
    void ConsoleAppender::append(const LogMessage& message, const QMessageLogContext& context)
    {
        QString formatted_message = m_formatter->format(message, context);

        switch (message.get_type())
        {
            case QtDebugMsg:
                qDebug().nospace().noquote() << formatted_message;
                break;
            case QtInfoMsg:
                qInfo().nospace().noquote() << formatted_message;
                break;
            case QtWarningMsg:
                qWarning().nospace().noquote() << formatted_message;
                break;
            case QtCriticalMsg:
                qCritical().nospace().noquote() << formatted_message;
                break;
            case QtFatalMsg:
                qFatal().nospace().noquote() << formatted_message;
                break;
            default:
                break;
        }
    }
} // namespace QmlApp
