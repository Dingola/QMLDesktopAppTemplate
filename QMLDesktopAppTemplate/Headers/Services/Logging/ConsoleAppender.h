#pragma once

#include "Services/Logging/LogAppender.h"
#include "Services/Logging/SimpleFormatter.h"

namespace QmlApp
{
	class ConsoleAppender : public LogAppender
	{
	public:
		ConsoleAppender(const QSharedPointer<LogFormatter>& formatter = QSharedPointer<SimpleFormatter>::create());

		void append(const LogMessage& message, const QMessageLogContext& context) override;

	};
} // namespace QmlApp
