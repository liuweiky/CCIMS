#include "aboutui.h"

AboutUI::AboutUI()
{

}

QString AboutUI::ShowDateTime()
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString txt = date.toString("yyyy/MM/dd")+time.toString(" hh:mm:ss");
    return txt;
}

bool AboutUI::PDlg (QProgressDialog* progressDlg,CCMIS* mCCMIS,
                    unsigned int AllNumber)
{
    bool result = false;
    progressDlg->setWindowModality(Qt::WindowModal);
    //如果运行时间小于0，进度条就不会显示（测试时请置0）
    progressDlg->setMinimumDuration(0);
    progressDlg->setWindowTitle(QStringLiteral("请稍候"));
    while (mCCMIS->GetTotalInfoNumber() < AllNumber) {
            progressDlg->setValue(mCCMIS->GetTotalInfoNumber());
            QCoreApplication::processEvents();//避免界面冻结
            if(progressDlg->wasCanceled()) return result;
    }
    progressDlg->close();
    result = true;
    return result;
}
