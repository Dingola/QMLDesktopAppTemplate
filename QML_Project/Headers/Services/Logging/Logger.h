#pragma once

#include <CommonLib/Patterns/Singleton.h>

#include <QList>
#include <QSharedPointer>
#include <QString>

#include "Services/Logging/LogAppender.h"

namespace QmlApp
{
/**
 * @class Logger
 * @brief A singleton class for logging messages.
 *
 * This class provides methods to log messages with different severity levels.
 * It supports adding multiple log appenders to direct log messages to various destinations.
 */
class Logger: public CommonLib::Singleton<Logger>
{
        friend class CommonLib::Singleton<Logger>;

    private:
        Logger() = default;

    public:
        /**
         * @brief Logs a message with the specified type and context.
         *
         * @param type The type of the log message.
         * @param context The context of the log message.
         * @param msg The log message.
         */
        void log(QtMsgType type, const QMessageLogContext& context, const QString& msg);

        /**
         * @brief Adds a log appender to the logger.
         *
         * This function appends the specified log appender to the list of registered log appenders.
         * A log appender is a component that handles the output of log messages to various
         * destinations, such as files, consoles, or remote servers. By adding an appender, you can
         * direct the log messages to the desired output target.
         *
         * @param appender The log appender to add.
         */
        void add_appender(const QSharedPointer<LogAppender>& appender);

        /**
         * @brief Clears all log appenders from the logger.
         */
        void clear_appenders();

        /**
         * @brief Sets the log level of the logger.
         *
         * @param level The log level to set.
         */
        void set_log_level(QtMsgType level);

        /**
         * @brief Returns the current log level of the logger.
         *
         * @return The current log level of the logger.
         */
        [[nodiscard]] auto get_log_level() const -> QtMsgType;

    private:
        QList<QSharedPointer<LogAppender>> m_appenders;
        QtMsgType m_log_level = QtDebugMsg;
};
}  // namespace QmlApp
