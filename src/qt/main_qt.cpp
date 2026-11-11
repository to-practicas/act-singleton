#include <QApplication>
#include "MainWindow.h"
#include "ConfigManager.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Carga config.ini (si existe) en la unica instancia de ConfigManager.
    ConfigManager::instance().load();

    MainWindow w;
    w.show();
    return app.exec();
}
