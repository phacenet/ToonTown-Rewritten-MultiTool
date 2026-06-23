#include <curl/curl.h>
#include <QApplication>
#include <sodium.h>
#include <error.h>

#include "mainwindow.hpp"
#include "ttr_api_reqs.hpp"

int main(int argc, char* argv[])
{
	if(sodium_init() == -1)	
		throw std::runtime_error("libsodium initialization failed inside main");

	QApplication app(argc, argv);
	MainWindow window;

	window.show();
	
	return app.exec();
}
