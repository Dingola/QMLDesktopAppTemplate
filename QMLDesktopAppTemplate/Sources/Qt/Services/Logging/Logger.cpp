/**
 * @file Logger.cpp
 * @brief This file contains the implementation of the Logger class.
 */

#include "Services/Logging/Logger.h"
#include "Services/Logging/LogMessage.h"

namespace QmlApp
{
	/**
	 * @brief Logs a message with the specified type and context.
	 *
	 * This function creates a LogMessage object with the specified type and message,
	 * and then appends it to all registered log appenders.
	 *
	 * @param type The type of the log message.
	 * @param context The context of the log message.
	 * @param msg The log message.
	 */
	void Logger::log(QtMsgType type, const QMessageLogContext& context, const QString& msg)
	{
		LogMessage log_message(type, msg);

		if (type >= m_log_level)
		{
			for (const auto& appender : m_appenders)
			{
				if (appender != nullptr)
				{
					appender->append(log_message, context);
				}
			}
		}
	}

	/**
	 * @brief Adds a log appender to the logger.
	 *
	 * This function appends the specified log appender to the list of registered log appenders.
	 *
	 * @param appender The log appender to add.
	 */
	void Logger::add_appender(const QSharedPointer<LogAppender>& appender)
	{
		m_appenders.append(appender);
	}

	/**
	 * @brief Clears all log appenders from the logger.
	 *
	 * This function removes all log appenders from the list of registered log appenders.
	 */
	void Logger::clear_appenders()
	{
		m_appenders.clear();
	}

	/**
	 * @brief Sets the log level of the logger.
	 *
	 * This function sets the log level of the logger to the specified level.
	 * It specifies which message levels will be logged by this logger.
	 * Message levels lower than this value will be discarded.
	 *
	 * @param level The log level to set.
	 */
	void Logger::set_log_level(QtMsgType level)
	{
		m_log_level = level;
	}

	/**
	 * @brief Returns the current log level of the logger.
	 *
	 * This function returns the current log level of the logger.
	 * The log level determines which message levels are being logged.
	 *
	 * @return The current log level of the logger.
	 */
	QtMsgType Logger::get_log_level() const
	{
		return m_log_level;
	}

} // namespace QmlApp
