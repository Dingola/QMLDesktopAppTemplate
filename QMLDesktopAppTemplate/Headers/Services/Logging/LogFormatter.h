#pragma once

#include <QString>
#include <QMessageLogContext>

#include "Services/Logging/LogMessage.h"

namespace QmlApp
{
	class LogFormatter
	{
	public:
		LogFormatter() = default;
		virtual ~LogFormatter() = default;

		[[nodiscard]] virtual QString format(const LogMessage& log_message, const QMessageLogContext& context) = 0;

	};
} // namespace QmlApp
