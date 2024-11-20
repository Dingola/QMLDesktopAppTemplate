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
	 * This constructor initializes the LogMessage object with the provided message type and message content.
	 *
	 * @param type The type of the log message.
	 * @param message The content of the log message.
	 */
	LogMessage::LogMessage(QtMsgType type, const QString& message)
		: m_type(type)
		, m_message(message)
	{
	}

	/**
	 * @brief Gets the type of the log message.
	 *
	 * @return The type of the log message.
	 */
	QtMsgType LogMessage::get_type() const
	{
		return m_type;
	}

	/**
	 * @brief Gets the content of the log message.
	 *
	 * @return The content of the log message.
	 */
	const QString& LogMessage::get_message() const
	{
		return m_message;
	}
} // namespace QmlApp
