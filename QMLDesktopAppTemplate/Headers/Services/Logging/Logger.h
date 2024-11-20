#pragma once

#include <QString>
#include <QList>
#include <QSharedPointer>

#include "Common/Singleton.h"
#include "Services/Logging/LogAppender.h"

namespace QmlApp
{
	class Logger : public Singleton<Logger>
	{
		friend class Singleton<Logger>;

	private:
		Logger() = default;

	public:
		void log(QtMsgType type, const QMessageLogContext& context, const QString& msg);
		void add_appender(const QSharedPointer<LogAppender>& appender);

	private:
		QList<QSharedPointer<LogAppender>> m_appenders;

	};
} // namespace QmlApp
