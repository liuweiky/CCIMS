#ifndef TABLE_FUNCS_H
#define TABLE_FUNCS_H

//为了三个search window

#include<QTableWidget>
#include<QDateEdit>
#include<QCheckBox>
#include<QPushButton>
#include"ccmis.h"

template<class Table_Type>
class Table_Parent{
private:
    QDateEdit* mStart_Edit;
    QDateEdit* mFinish_Edit;
    QPushButton* mSearch_Btn;
    QPushButton* mReset_Btn;
    QPushButton* mExport_Btn;
    CCMIS* mCCMIS;

public:
    Table_Parent(QDateEdit* start_edit,QDateEdit* finish_edit,
                QPushButton* search_btn,QPushButton* reset_btn,
                QPushButton* export_btm,CCMIS* ccmis_sys);


};



Table_Parents::Table_Parent(QDateEdit* start_edit,QDateEdit* finish_edit,
            QPushButton* search_btn,QPushButton* reset_btn,
            QPushButton* export_btm,CCMIS* ccmis_sys)
            :mStart_Edit(start_edit),mFinish_Edit(finish_edit),
              mSear

{}




class Admin_Table : public Table_Parent{
private:

};





#endif // TABLE_FUNCS_H
