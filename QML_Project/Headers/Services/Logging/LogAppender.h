#pragma once

#include <QMessageLogContext>
#include <QSharedPointer>

#include "Services/Logging/LogFormatter.h"
#include "Services/Logging/LogMessage.h"
#include "Services/Logging/SimpleFormatter.h"

namespace QmlApp
{
/**
 * @class LogAppender
 * @brief An abstract base class for log appenders.
 *
 * This class is used to define the interface for log appenders.
 */
class LogAppender
{
    public:
        /**
         * @brief Constructs a LogAppender object with a default SimpleFormatter.
         */
        LogAppender();

        /**
         * @brief Constructs a LogAppender object.
         *
         * @param formatter The LogFormatter object to use for formatting log messages.
         */
        LogAppender(const QSharedPointer<LogFormatter>& formatter);

        /**
         * @brief Destroys the LogAppender object.
         */
        virtual ~LogAppender() = default;

        /**
         * @brief Appends a log message to the log appender.
         *
         * This method appends the specified log message to the log appender.
         * The log message is only appended if its type is greater than or equal to
         * the log level of the appender.
         *
         * @param message The log message to append.
         * @param context The context of the log message.
         */
        auto append(const LogMessage& message, const QMessageLogContext& context) -> void;

        /**
         * @brief Sets the formatter for the log appender.
         *
         * @param formatter The formatter to set.
         */
        auto set_formatter(const QSharedPointer<LogFormatter>& formatter) -> void;

        /**
         * @brief Sets the log level of the log appender.
         *
         * This function sets the log level of the log appender to the specified level.
         * It specifies which message levels will be logged by this appender.
         * Message levels lower than this value will be discarded.
         *
         * @param level The log level to set.
         */
        auto set_log_level(QtMsgType level) -> void;

        /**
         * @brief Returns the current log level of the log appender.
         *
         * @return The current log level of the log appender.
         */
        [[nodiscard]] auto get_log_level() const -> QtMsgType;

    private:
        /**
         * @brief Appends a log message to the log appender.
         *
         * This method is called by the public `append` method to actually append the specified log
         * message to the log appender. The log message is only appended if its type is greater than
         * or equal to the log level of the appender, which is checked in the `append` method.
         *
         * @param message The log message to append.
         * @param context The context of the log message.
         */
        virtual auto internal_append(const LogMessage& message,
                                     const QMessageLogContext& context) -> void = 0;

    protected:
        QSharedPointer<LogFormatter> m_formatter;
        QtMsgType m_log_level;
};

}  // namespace QmlApp
