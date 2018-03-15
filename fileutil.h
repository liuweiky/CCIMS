#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <fstream>
#include <sstream>
#include <string>

using namespace std;

//static string FILE_FOLDER = "files";
static string FILE_SERIAL_NUMBER = "serial_number.txt";

class FileUtil
{
public:
    FileUtil();
    static bool writeLine(string);
    static bool writeSerialNumbers(string);
    static string readSerialNumbers();
};

#endif // FILEUTIL_H
