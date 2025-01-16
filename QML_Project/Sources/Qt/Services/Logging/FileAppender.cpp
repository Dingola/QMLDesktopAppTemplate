/**
 * @file FileAppender.cpp
 * @brief This file contains the implementation of the FileAppender class.
 */

#include "Services/Logging/FileAppender.h"

#include <QDebug>

namespace QmlApp
{
	/**
	 * @brief Constructs a FileAppender object with the given file path and formatter.
	 *
	 * This constructor initializes the FileAppender object with the provided file path and formatter.
	 * It attempts to open the log file in append mode. If the file cannot be opened, a warning is logged.
	 *
	 * @param file_path The path of the log file.
	 * @param formatter The formatter to use for formatting log messages.
	 */
	FileAppender::FileAppender(const QString& file_path, const QSharedPointer<LogFormatter>& formatter)
		: m_log_file(file_path)
		, LogAppender(formatter)
	{
		if (m_log_file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
		{
			m_log_stream.setDevice(&m_log_file);
		}
		else
		{
			qWarning() << "Failed to open log file:" << file_path;
		}
	}

	/**
	 * @brief Appends a log message to the log file.
	 *
	 * This function formats the log message using the provided formatter and writes it to the log file.
	 * If the log file is not open, a warning is logged.
	 *
	 * @param message The log message to append.
	 * @param context The context of the log message.
	 */
	void FileAppender::internal_append(const LogMessage& message, const QMessageLogContext& context)
	{
		QString formatted_message = m_formatter->format(message, context);

		if (m_log_file.isOpen())
		{
			m_log_stream << formatted_message << Qt::endl;
		}
		else
		{
			qWarning() << "Log file is not open. Failed to append message:" << formatted_message;
		}
	}
} // namespace QmlApp
