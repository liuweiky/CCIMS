#ifndef COMMON_FUNCS_H
#define COMMON_FUNCS_H

#include <QString>
#include <QTextCodec>
#include <string>
#include <QTableWidget>
#include <QFileDialog>
#include <QDesktopServices>
#include <QMessageBox>
//#include <QAxObject>

using std::string;

struct Date
{
    int year;
    int month;
    int day;
    Date (unsigned long NumDate){
        year = NumDate / 10000;
        month = int(NumDate / 100 % 100);
        day = int(NumDate % 100);
    }
    static unsigned long DateToNum(int yr,int mth,int dy){
        return yr*10000 + mth*100+dy;
    }
};

struct Time
{
    int hour;
    int minute;
    int second;
    Time(unsigned long NumTime){
        //时间数字段有两种可能，一种带秒，一种不带秒
        if(NumTime < 9999){
            second = 0;
            minute = NumTime%100;
            hour = int(NumTime/100);
        }else if(NumTime < 999999){
            second = NumTime % 100;
            minute = int(NumTime / 100 % 100);
            hour = int(NumTime / 10000);
        }
    }

    static unsigned int TimeToNum(int hr,int min,int sec = 0){
        return hr*10000 + min * 100 + sec;
    }
};

class COMMON_FUNCS
{
public:


//    static void Table2Excel(QTableWidget *table,QString title)
//    {
//        QString fileName = QFileDialog::getSaveFileName(table, "保存",
//                QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
//                "Excel 文件(*.xls *.xlsx)");
//        if (fileName!="")
//        {
//            QAxObject *excel = new QAxObject;
//            if (excel->setControl("Excel.Application")) //连接Excel控件
//            {
//                excel->dynamicCall("SetVisible (bool Visible)","false");//不显示窗体
//                excel->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
//                QAxObject *workbooks = excel->querySubObject("WorkBooks");//获取工作簿集合
//                workbooks->dynamicCall("Add");//新建一个工作簿
//                QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//获取当前工作簿
//                QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);
//                int i,j,colcount=table->columnCount();
//                QAxObject *cell,*col;
//                //标题行
//                cell=worksheet->querySubObject("Cells(int,int)", 1, 1);
//                cell->dynamicCall("SetValue(const QString&)", title);
//                cell->querySubObject("Font")->setProperty("Size", 18);
//                //调整行高
//                worksheet->querySubObject("Range(const QString&)", "1:1")->setProperty("RowHeight", 30);
//                //合并标题行
//                QString cellTitle;
//                cellTitle.append("A1:");
//                cellTitle.append(QChar(colcount - 1 + 'A'));
//                cellTitle.append(QString::number(1));
//                QAxObject *range = worksheet->querySubObject("Range(const QString&)", cellTitle);
//                range->setProperty("WrapText", true);
//                range->setProperty("MergeCells", true);
//                range->setProperty("HorizontalAlignment", -4108);//xlCenter
//                range->setProperty("VerticalAlignment", -4108);//xlCenter
//                //列标题
//                for(i=0;i<colcount;i++)
//                {
//                    QString columnName;
//                    columnName.append(QChar(i  + 'A'));
//                    columnName.append(":");
//                    columnName.append(QChar(i + 'A'));
//                    col = worksheet->querySubObject("Columns(const QString&)", columnName);
//                    col->setProperty("ColumnWidth", table->columnWidth(i)/6);
//                    cell=worksheet->querySubObject("Cells(int,int)", 2, i+1);
//                    columnName=table->horizontalHeaderItem(i)->text();
//                    cell->dynamicCall("SetValue(const QString&)", columnName);
//                    cell->querySubObject("Font")->setProperty("Bold", true);
//                    cell->querySubObject("Interior")->setProperty("Color",QColor(191, 191, 191));
//                    cell->setProperty("HorizontalAlignment", -4108);//xlCenter
//                    cell->setProperty("VerticalAlignment", -4108);//xlCenter
//                }
//                //数据区
//                for(i=0;i<table->rowCount();i++){
//                    for (j=0;j<colcount;j++)
//                    {
//                        worksheet->querySubObject("Cells(int,int)", i+3, j+1)->dynamicCall("SetValue(const QString&)", table->item(i,j)?table->item(i,j)->text():"");
//                    }
//                }
//                //画框线
//                QString lrange;
//                lrange.append("A2:");
//                lrange.append(colcount - 1 + 'A');
//                lrange.append(QString::number(table->rowCount() + 2));
//                range = worksheet->querySubObject("Range(const QString&)", lrange);
//                range->querySubObject("Borders")->setProperty("LineStyle", QString::number(1));
//                range->querySubObject("Borders")->setProperty("Color", QColor(0, 0, 0));
//                //调整数据区行高
//                QString rowsName;
//                rowsName.append("2:");
//                rowsName.append(QString::number(table->rowCount() + 2));
//                range = worksheet->querySubObject("Range(const QString&)", rowsName);
//                range->setProperty("RowHeight", 20);
//                workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(fileName));//保存至fileName
//                workbook->dynamicCall("Close()");//关闭工作簿
//                excel->dynamicCall("Quit()");//关闭excel
//                delete excel;
//                excel=NULL;
//                if (QMessageBox::question(NULL,"完成","文件已经导出，是否现在打开？",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
//                {
//                    QDesktopServices::openUrl(QUrl("file:///" + QDir::toNativeSeparators(fileName)));
//                }
//            }
//            else
//            {
//                QMessageBox::warning(NULL,"错误","未能创建 Excel 对象，请安装 Microsoft Excel。",QMessageBox::Apply);
//            }
//        }
//    }

    // QString(Unicode) -> std::string (UTF8)
    static string ToUTF8String(const QString& qstr)
    {
//        QByteArray arr = qstr.toUtf8();
//        string cstr = arr.data();
//        return cstr;
        return string((const char *)qstr.toLocal8Bit());
    }

    // std::string (UTF8) -> QString(Unicode)
    static QString UTF8ToQString(const string& cstr)
    {
        QString qstr = QString::fromUtf8(cstr.c_str(), cstr.length());
        return qstr;
    }

    // QString(Unicode) -> std::string (GBK)
   static string ToGBKString(const QString& qstr)
   {
       QTextCodec* pCodec = QTextCodec::codecForName("gb2312");
       if(!pCodec) return "";

       QByteArray arr = pCodec->fromUnicode(qstr);
       string cstr = arr.data();
       return cstr;
   }

   // std::string (GBK) -> QString(Unicode)
   static QString GBKToQString(const string& cstr)
   {
       QTextCodec* pCodec = QTextCodec::codecForName("gb2312");
       if(!pCodec) return "";

       QString qstr = pCodec->toUnicode(cstr.c_str(), cstr.length());
       return qstr;
   }
};

#endif // COMMON_FUNCS_H
