#include <QCoreApplication>
#include <QDebug>
#include <QFile>

#include <windows.h>
#include <io.h>

static const QString FILE_PATH = "./example.txt";
static const QString text = "poop";

void writeText(const QString &text);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

#ifdef _WIN32
    QFile qFile("./example.txt");

    writeText(text);
    qFile.open(QIODevice::ReadOnly);

    auto fd = qFile.handle();    // C descriptor
    HANDLE hFile = reinterpret_cast<HANDLE>(_get_osfhandle(fd));

    auto dwSize = GetFileSize (hFile, nullptr);
    if (dwSize == INVALID_FILE_SIZE)
    {
        auto dwError = GetLastError() ;
        qWarning() << QString("Error %1").arg(dwError);
    }
    else
    {
        qInfo() << QString("Success, size is %1").arg(dwSize);
    }
#endif

    return a.exec();
}

void writeText(const QString &text) {
    QFile qFile(FILE_PATH);
    qFile.open(QIODevice::WriteOnly);

    uint64_t textLength = static_cast<uint64_t>(text.length());
    char *data = new char[textLength];
    strncpy(data, qPrintable(text), textLength);

    qFile.write(data, text.length());
    qFile.close();
}
