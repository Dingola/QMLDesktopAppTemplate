/**
 * @file LogMessage.cpp
 * @brief This file contains the implementation of the LogMessage class.
 */

#include "Services/Logging/LogMessage.h"

namespace QmlApp
{
/**
 * @brief Constructs a LogMessage object with the given type and message.
 *
 * This constructor initializes the LogMessage object with the provided message type and message
 * content.
 *
 * @param type The type of the log message.
 * @param message The content of the log message.
 */
LogMessage::LogMessage(QtMsgType type, QString message): m_type(type), m_message(std::move(message))
{}

/**
 * @brief Gets the type of the log message.
 *
 * @return The type of the log message.
 */
auto LogMessage::get_type() const -> QtMsgType
{
    return m_type;
}

/**
 * @brief Gets the content of the log message.
 *
 * @return The content of the log message.
 */
auto LogMessage::get_message() const -> const QString&
{
    return m_message;
}
}  // namespace QmlApp
