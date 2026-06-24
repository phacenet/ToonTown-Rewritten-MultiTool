#include <curl/curl.h>
#include <QApplication>
#include <sodium.h>
#include <QMessageBox>

#include "mainwindow.hpp"
#include "ttr_api_reqs.hpp"

int main(int argc, char* argv[])
{
	try 
	{
		if(sodium_init() == -1)	
			throw std::runtime_error("libsodium initialization failed inside main");

		//try to make the chromium browser a little bit faster on old hardware
		qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--disable-gpu-compositing");

		QApplication app(argc, argv);
		MainWindow window;

		window.show();
		
		return app.exec();
	}
	catch(const std::exception& e)
	{
		QMessageBox::critical(nullptr, "Fatal Error", QString("An unhandled error occurred:\n\n") + e.what());
		return 1;
	}
	catch(...)
	{
		QMessageBox::critical(nullptr, "Fatal Error", "An unknown fatal error occurred.");
		return 1;
	}
}
