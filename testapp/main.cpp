#include <QApplication>
#include "prison.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    main_window foo;
    foo.show();
    return app.exec();
}
