#pragma once

#include "Services/Logging/LogAppender.h"
#include "Services/Logging/SimpleFormatter.h"

namespace QmlApp
{
	/**
	 * @class ConsoleAppender
	 * @brief A log appender that outputs log messages to the console.
	 *
	 * This class is responsible for appending log messages to the console.
	 * It uses a provided LogFormatter to format the log messages before outputting them.
	 */
	class ConsoleAppender : public LogAppender
	{
	public:
		/**
		 * @brief Constructs a ConsoleAppender object with the given formatter.
		 *
		 * @param formatter The LogFormatter object to use for formatting log messages.
		 *                  If no formatter is provided, a default SimpleFormatter is used.
		 */
		ConsoleAppender(const QSharedPointer<LogFormatter>& formatter = QSharedPointer<SimpleFormatter>::create());

	private:
		/**
		 * @brief Appends the specified log message to the console.
		 *
		 * This method formats the log message using the provided formatter and outputs it to the console
		 * using the appropriate Qt logging function based on the message type.
		 *
		 * @param message The log message to append to the console.
		 * @param context The context of the log message.
		 */
		void internal_append(const LogMessage& message, const QMessageLogContext& context) override;
	};
} // namespace QmlApp
