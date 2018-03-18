

/** logAFXID texedit id ... to place text log error information ...
*/


#ifndef CONNECT_H__
#define CONNECT_H__

int connectTest(int logAFXID,int listLogID);
enum finger_t{LEFT_P,LEFT_R,LEFT_M,LEFT_I,LEFT_T};

void logList(int listID,LPCSTR msg);
int rs_count();
int getPersonID();
void mysql_next();
void mysql_prev();
void mysql_last();
void mysql_first();
void getPersonInfo(char* buffer);
int mysql_updateFinger(int person_id,int FPID,const char *finger);

#endif