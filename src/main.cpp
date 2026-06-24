#include "mainwindow.hpp"
#include "ttr_api_reqs.hpp"

#include <curl/curl.h>
#include <QApplication>
#include <sodium.h>
#include <QMessageBox>
#include <filesystem>

int main(int argc, char* argv[])
{
	#ifdef _WIN32
		//set CWD to exe directory so all relative config/... paths resolve correctly regardless of where windows launches the process from
		std::filesystem::current_path(
			std::filesystem::path(argv[0]).parent_path()
		);
	#endif

	//QApplication must exists before and messagebox
	QApplication app(argc, argv);

	try 
	{
		if(sodium_init() == -1)	
			throw std::runtime_error("libsodium initialization failed inside main");

		//try to make the chromium browser a little bit faster on old hardware
		qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--disable-gpu-compositing");

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
