#pragma once

#include <QMessageLogContext>
#include <QString>

#include "Services/Logging/LogMessage.h"

namespace QmlApp
{
/**
 * @class LogFormatter
 * @brief An abstract base class for log formatters.
 *
 * This class is used to define the interface for log formatters.
 */
class LogFormatter
{
    public:
        /**
         * @brief Constructs a LogFormatter object.
         */
        LogFormatter() = default;

        /**
         * @brief Destroys the LogFormatter object.
         */
        virtual ~LogFormatter() = default;

        /**
         * @brief Formats the specified log message.
         *
         * @param log_message The log message to format.
         * @param context The context of the log message.
         * @return The formatted log message as a QString.
         */
        [[nodiscard]] virtual auto format(const LogMessage& log_message,
                                          const QMessageLogContext& context) -> QString = 0;
};
}  // namespace QmlApp
