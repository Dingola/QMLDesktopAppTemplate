/**
 * @file SimpleFormatter.cpp
 * @brief This file contains the implementation of the SimpleFormatter class.
 */

#include "Services/Logging/SimpleFormatter.h"

namespace QmlApp
{
	/**
	 * @brief Formats the log message according to the specified context.
	 *
	 * This function formats the log message by including the message type, current date and time,
	 * the message itself, and the file, line, and function where the log was generated.
	 *
	 * @param log_message The log message to format.
	 * @param context The context of the log message.
	 * @return The formatted log message as a QString.
	 */
	QString SimpleFormatter::format(const LogMessage& log_message, const QMessageLogContext& context)
	{
		const char* file = context.file ? context.file : "";
		const char* function = context.function ? context.function : "";
		QByteArray local_msg = log_message.get_message().toLocal8Bit();
		QString msg_type;

		switch (log_message.get_type())
		{
			case QtDebugMsg:
				msg_type = "[Debug    ]:";
				break;
			case QtWarningMsg:
				msg_type = "[Warning  ]:";
				break;
			case QtInfoMsg:
				msg_type = "[Info     ]:";
				break;
			case QtCriticalMsg:
				msg_type = "[Critical ]:";
				break;
			case QtFatalMsg:
				msg_type = "[Fatal    ]:";
				break;
			default:
				msg_type = "[Unknown  ]:";
				break;
		}

		return QString("%1 %2 - %3 (%4:%5, %6)")
			.arg(msg_type)
			.arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
			.arg(local_msg.constData())
			.arg(file)
			.arg(context.line)
			.arg(function);
	}
} // namespace QmlApp
