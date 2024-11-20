#pragma once

#include <QString>
#include <QDebug>

namespace QmlApp
{
	class LogMessage
	{
	public:
		LogMessage(QtMsgType type = QtDebugMsg,
				   const QString& message = QString());
		virtual ~LogMessage() = default;

		[[nodiscard]] QtMsgType get_type() const;
		[[nodiscard]] const QString& get_message() const;

	private:
		QtMsgType m_type;
		QString m_message;

	};
} // namespace QmlApp
