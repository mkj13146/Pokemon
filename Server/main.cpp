#include "tcpserver.h"
#include <QApplication>
#include "sql.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TcpServer w;
    w.setWindowTitle("服务器控制台");
    w.show();

    return a.exec();
}
