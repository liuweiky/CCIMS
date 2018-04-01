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

//void CCMIS::CloseTxt(QCloseEvent *event)
//{
//    if (QMessageBox::information
//            (this, QObject::tr("关闭"),
//             QObject::tr("退了就别回来了，这里到处都是BUG"),
//             QObject::tr("好的"), QObject::tr("我再待一会"), 0, 1) == 0) {
//        event->accept();
//    }else {
//        event->ignore();
//    }
//}

bool AboutUI::PDlg (QProgressDialog* progressDlg,CCMIS* mCCMIS,
                    unsigned int AllNumber)
{
    bool result = false;
    progressDlg->setWindowModality(Qt::WindowModal);
    //如果运行时间小于3，进度条就不会显示（测试时请置0）
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
