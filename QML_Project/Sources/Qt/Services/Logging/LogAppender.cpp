#include "Services/Logging/LogAppender.h"

namespace QmlApp
{
	/**
	 * @brief Constructs a LogAppender object with a default SimpleFormatter.
	 *
	 * This constructor initializes the LogAppender object with a default SimpleFormatter
	 * and sets the log level to QtDebugMsg.
	 */
	LogAppender::LogAppender()
		: m_formatter(QSharedPointer<SimpleFormatter>::create())
		, m_log_level(QtMsgType::QtDebugMsg)
	{
	}

	/**
	 * @brief Constructs a LogAppender object.
	 *
	 * This constructor initializes the LogAppender object with the provided LogFormatter
	 * and sets the log level to QtDebugMsg.
	 *
	 * @param formatter The LogFormatter object to use for formatting log messages.
	 */
	LogAppender::LogAppender(const QSharedPointer<LogFormatter>& formatter)
		: m_formatter(formatter)
		, m_log_level(QtMsgType::QtDebugMsg)
	{
	}

	/**
	 * @brief Appends a log message to the log appender.
	 *
	 * This method checks if the log message type is greater than or equal to the log level
	 * of the appender. If it is, the message is appended by calling the internal_append method.
	 *
	 * @param message The log message to append.
	 * @param context The context of the log message.
	 */
	void LogAppender::append(const LogMessage& message, const QMessageLogContext& context)
	{
		if (message.get_type() >= m_log_level)
		{
			internal_append(message, context);
		}
	}

	/**
	 * @brief Sets the formatter for the log appender.
	 *
	 * This method sets the formatter used by the log appender to format log messages.
	 *
	 * @param formatter The formatter to set.
	 */
	void LogAppender::set_formatter(const QSharedPointer<LogFormatter>& formatter)
	{
		m_formatter = formatter;
	}

	/**
	 * @brief Sets the log level of the log appender.
	 *
	 * This method sets the log level of the log appender. Messages with a type lower than
	 * this level will be discarded.
	 *
	 * @param level The log level to set.
	 */
	void LogAppender::set_log_level(QtMsgType level)
	{
		m_log_level = level;
	}

	/**
	 * @brief Returns the current log level of the log appender.
	 *
	 * This method returns the current log level of the log appender.
	 *
	 * @return The current log level of the log appender.
	 */
	QtMsgType LogAppender::get_log_level() const
	{
		return m_log_level;
	}

} // namespace QmlApp
