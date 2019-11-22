#include <QCoreApplication>
#include <QDebug>
#include <QFile>

#include <windows.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

#ifdef _WIN32
    QFile qFile("./example.txt");
    qFile.open(QIODevice::WriteOnly);

//    HANDLE hFile;
//    auto dwSize = GetFileSize (hFile, nullptr);
//    if (dwSize == INVALID_FILE_SIZE)
//    {
//        auto dwError = GetLastError() ;
//        qWarning() << QString("Error %1").arg(dwError);
//    }
#endif

    return a.exec();
}
