#pragma once

#include <QMessageLogContext>
#include <QSharedPointer>

#include "Services/Logging/LogFormatter.h"
#include "Services/Logging/SimpleFormatter.h"
#include "Services/Logging/LogMessage.h"

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
		LogAppender()
			: m_formatter(QSharedPointer<SimpleFormatter>::create())
		{
		}

		/**
		 * @brief Constructs a LogAppender object.
		 */
		LogAppender(const QSharedPointer<LogFormatter>& formatter)
			: m_formatter(formatter)
		{
		};

		/**
		 * @brief Destroys the LogAppender object.
		 */
		virtual ~LogAppender() = default;

		/**
		 * @brief Appends the specified message to the log.
		 *
		 * @param message The message to append to the log.
		 */
		virtual void append(const LogMessage& message, const QMessageLogContext& context) = 0;

		/**
		 * @brief Sets the formatter for the log appender.
		 *
		 * @param formatter The formatter to set.
		 */
		void set_formatter(const QSharedPointer<LogFormatter>& formatter)
		{
			m_formatter = formatter;
		}

	protected:
		QSharedPointer<LogFormatter> m_formatter;

	};

} // namespace QmlApp
