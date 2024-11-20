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

		for (const auto& appender : m_appenders)
		{
			if (appender != nullptr)
			{
				appender->append(log_message, context);
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

} // namespace QmlApp
