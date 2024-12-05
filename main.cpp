
#include <QtWidgets/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    try {
        QApplication app(argc, argv);
        
        MainWindow window;
        window.show();
        
        return app.exec();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
