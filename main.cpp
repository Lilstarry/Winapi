#include <QCoreApplication>
#include <QDebug>
#include <QFile>

#include <windows.h>
#include <io.h>

static const QString DIR_NAME = "./";
static const QString FILE_PATH = DIR_NAME + "example.txt";

static const QString text = "poop";

bool dirExists(const QString &path);
void writeText(const QString &text);
void printFileSize();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

#ifdef _WIN32
    if(dirExists(QFile(DIR_NAME).fileName()))
    {
        writeText(text);
        printFileSize();
    }
    else
    {
        qCritical() << "Directory is not exist";
    }
#endif

    return a.exec();
}

#ifdef _WIN32
bool dirExists(const QString &path)
{
    DWORD const f_attrib = GetFileAttributesA(path.toStdString().c_str());
    return f_attrib != INVALID_FILE_ATTRIBUTES &&
           (f_attrib & FILE_ATTRIBUTE_DIRECTORY);
}

void writeText(const QString &text)
{
    QFile qFile(FILE_PATH);
    qFile.open(QIODevice::WriteOnly);

    uint64_t textLength = static_cast<uint64_t>(text.length());
    char *data = new char[textLength];
    strncpy(data, qPrintable(text), textLength);

    qFile.write(data, text.length());
    qFile.close();
}

void printFileSize()
{
    QFile qFile(FILE_PATH);
    qFile.open(QIODevice::ReadOnly);

    auto fd = qFile.handle();    // C descriptor
    HANDLE hFile = reinterpret_cast<HANDLE>(_get_osfhandle(fd));

    auto dwSize = GetFileSize (hFile, nullptr);
    if (dwSize == INVALID_FILE_SIZE)
    {
        auto dwError = GetLastError() ;
        qCritical() << QString("Error %1").arg(dwError);
    }
    else
    {
        qInfo() << QString("Success, size is %1").arg(dwSize);
    }
}
#endif
