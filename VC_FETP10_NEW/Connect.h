

/** logAFXID texedit id ... to place text log error information ...
*/


#ifndef CONNECT_H__
#define CONNECT_H__

int connectTest(int logAFXID,int listLogID);

void logList(int listID,LPCSTR msg);
int rs_count();
int getPersonID();
void mysql_next();
void mysql_prev();
void mysql_last();
void mysql_first();
void getPersonInfo(char* buffer);

#endif