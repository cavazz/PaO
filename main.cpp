#include <QApplication>
#include "View/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow finestra;
    finestra.show();

    return a.exec();
}
