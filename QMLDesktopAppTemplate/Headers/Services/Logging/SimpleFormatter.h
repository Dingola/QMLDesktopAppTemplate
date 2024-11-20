#pragma once

#include <QDateTime>

#include "Services/Logging/LogFormatter.h"

namespace QmlApp
{
	class SimpleFormatter : public LogFormatter
	{
	public:
		SimpleFormatter() = default;

		[[nodiscard]] QString format(const LogMessage& log_message, const QMessageLogContext& context) override;

	};
} // namespace QmlApp
