#include "fileutil.h"

FileUtil::FileUtil()
{

}

bool FileUtil::writeLine(string line)
{
    ofstream out(
                FILE_SERIAL_NUMBER,
                ios::app);

    if (out.is_open())
    {
        out << line << "\n";
        out.close();
        return true;
    } else {
        return false;
    }
}

bool FileUtil::writeSerialNumbers(string numbers)
{
    ofstream out(FILE_SERIAL_NUMBER);

    if (out.is_open())
    {
        out << numbers;
        if (numbers[numbers.length() - 1] != '\n')
            out << '\n';
        out.close();
        return true;
    } else {
        return false;
    }
}

string FileUtil::readSerialNumbers()
{
    ifstream in(FILE_SERIAL_NUMBER);

    if (in.is_open())
    {
        ostringstream tmp;
        tmp << in.rdbuf();
        string s;
        s = tmp.str();
        in.close();
        return s;
    } else {
        return "";
    }
}
