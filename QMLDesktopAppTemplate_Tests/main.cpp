#include <gtest/gtest.h>
#include <QApplication>

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	QApplication app(argc, argv);
	app.setApplicationName(QStringLiteral("QmlAppTest"));
	app.setOrganizationName(QStringLiteral("QmlDesktopAppTemplate_Tests"));
	app.setOrganizationDomain(QStringLiteral("AdrianHelbig.de"));

	return RUN_ALL_TESTS();
}
