#pragma once

#include <QDateTime>

#include "Services/Logging/LogFormatter.h"

namespace QmlApp
{
/**
 * @class SimpleFormatter
 * @brief A simple log formatter that formats log messages with type, date, time, and context.
 *
 * This class provides a simple implementation of the LogFormatter interface.
 * It formats log messages by including the message type, current date and time,
 * the message itself, and the file, line, and function where the log was generated.
 */
class SimpleFormatter: public LogFormatter
{
    public:
        /**
         * @brief Constructs a SimpleFormatter object.
         */
        SimpleFormatter() = default;

        /**
         * @brief Formats the log message according to the specified context.
         *
         * @param log_message The log message to format.
         * @param context The context of the log message.
         * @return The formatted log message as a QString.
         */
        [[nodiscard]] auto format(const LogMessage& log_message,
                                  const QMessageLogContext& context) -> QString override;
};
}  // namespace QmlApp
