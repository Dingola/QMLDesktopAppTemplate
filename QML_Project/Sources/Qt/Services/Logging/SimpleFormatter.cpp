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
	 * The message type is color-coded for better readability in the console.
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
		QString color_code;

		switch (log_message.get_type())
		{
			case QtDebugMsg:
				msg_type = "[Debug    ]:";
				color_code = "\033[92m"; // Light Green
				break;
			case QtWarningMsg:
				msg_type = "[Warning  ]:";
				color_code = "\033[93m"; // Light Yellow
				break;
			case QtInfoMsg:
				msg_type = "[Info     ]:";
				color_code = "\033[94m"; // Light Blue
				break;
			case QtCriticalMsg:
				msg_type = "[Critical ]:";
				color_code = "\033[91m"; // Light Red
				break;
			case QtFatalMsg:
				msg_type = "[Fatal    ]:";
				color_code = "\033[95m"; // Light Magenta
				break;
			default:
				msg_type = "[Unknown  ]:";
				color_code = "\033[0m"; // Reset
				break;
		}

		QString reset_code = "\033[0m"; // Reset color
		QString context_color_code = "\033[95m"; // Light Purple

		return QString("%1%2%3 %4 - %5 (%6%7%8:%9%10, %11%12%13)")
			.arg(color_code)
			.arg(msg_type)
			.arg(reset_code)
			.arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
			.arg(local_msg.constData())
			.arg(context_color_code)
			.arg(file)
			.arg(reset_code)
			.arg(context.line)
			.arg(reset_code)
			.arg(context_color_code)
			.arg(function)
			.arg(reset_code);
	}
} // namespace QmlApp
