#pragma once

#include <QDebug>
#include <QString>

namespace QmlApp
{
/**
 * @class LogMessage
 * @brief Represents a log message with a type and content.
 *
 * This class encapsulates a log message, including its type and content.
 */
class LogMessage
{
    public:
        /**
         * @brief Constructs a LogMessage object with the given type and message.
         *
         * @param type The type of the log message.
         * @param message The content of the log message.
         */
        LogMessage(QtMsgType type = QtDebugMsg, QString message = QString());

        /**
         * @brief Destroys the LogMessage object.
         */
        virtual ~LogMessage() = default;

        /**
         * @brief Gets the type of the log message.
         *
         * @return The type of the log message.
         */
        [[nodiscard]] auto get_type() const -> QtMsgType;

        /**
         * @brief Gets the content of the log message.
         *
         * @return The content of the log message.
         */
        [[nodiscard]] auto get_message() const -> const QString&;

    private:
        QtMsgType m_type;
        QString m_message;
};
}  // namespace QmlApp
