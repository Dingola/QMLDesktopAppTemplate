#pragma once

#include <QFile>
#include <QString>
#include <QTextStream>

#include "Services/Logging/LogAppender.h"
#include "Services/Logging/SimpleFormatter.h"

namespace QmlApp
{
	class FileAppender : public LogAppender
	{
	public:
		FileAppender(const QString& file_path = "", const QSharedPointer<LogFormatter>& formatter = QSharedPointer<SimpleFormatter>::create());

		void append(const LogMessage& message, const QMessageLogContext& context) override;

	private:
		QFile m_log_file;
		QTextStream m_log_stream;
	};
} // namespace QmlApp
