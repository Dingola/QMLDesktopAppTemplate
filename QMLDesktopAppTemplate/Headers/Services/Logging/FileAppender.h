#pragma once

#include <QFile>
#include <QString>
#include <QTextStream>

#include "Services/Logging/LogAppender.h"
#include "Services/Logging/SimpleFormatter.h"

namespace QmlApp
{
	/**
	 * @class FileAppender
	 * @brief A log appender that outputs log messages to a file.
	 *
	 * This class is responsible for appending log messages to a file.
	 * It uses a provided LogFormatter to format the log messages before writing them to the file.
	 */
	class FileAppender : public LogAppender
	{
	public:
		/**
		 * @brief Constructs a FileAppender object with the given file path and formatter.
		 *
		 * @param file_path The path of the log file.
		 * @param formatter The formatter to use for formatting log messages.
		 *                  If no formatter is provided, a default SimpleFormatter is used.
		 */
		FileAppender(const QString& file_path = "", const QSharedPointer<LogFormatter>& formatter = QSharedPointer<SimpleFormatter>::create());

	private:
		/**
		 * @brief Appends the specified log message to the log file.
		 *
		 * This method formats the log message using the provided formatter and writes it to the log file.
		 *
		 * @param message The log message to append.
		 * @param context The context of the log message.
		 */
		void internal_append(const LogMessage& message, const QMessageLogContext& context) override;

	private:
		QFile m_log_file;
		QTextStream m_log_stream;
	};
} // namespace QmlApp
