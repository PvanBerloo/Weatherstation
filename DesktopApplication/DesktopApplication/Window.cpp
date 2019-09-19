#include "Window.h"

#include <QStringListModel>

#include <iostream>
#include <windows.h>

#include "mysql_connection.h"
#include "mysql_driver.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

void openConsole() {
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
}

Window::Window(QWidget *parent) : QMainWindow(parent)
{

	ui.setupUi(this);

	//openConsole();

	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;

	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "weerstation", "wachtwoord123");
	con->setSchema("World");

	sql::Statement* statement = con->createStatement();
	sql::ResultSet *res = statement->executeQuery("SELECT * FROM country;");

	

	QStringList list;
	
	while (res->next()) {
		//std::cout << res->getString(2) << std::endl;
		list.push_back(QString(res->getString(2).c_str()));
	}

	QStringListModel* model = new QStringListModel();
	model->setStringList(list);
	ui.listView->setModel(model);

	delete statement;
	delete res;
	delete con;
}
