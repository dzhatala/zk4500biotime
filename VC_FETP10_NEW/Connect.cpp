// Standard includes
#include "stdafx.h"
#include "Connect.h"
//#include 
//#include 
using namespace std;

// Connector Includes

#include "cppconnection/driver.h"
#include "cppconnection/exception.h"
#include "cppconnection/resultset.h"
#include "cppconnection/statement.h"


// Link to the Connector/C++ library
#pragma comment(lib, "mysqlcppconn.lib")

// Connection details
/*string server   = "localhost";
string username = "root";
string password = "123"; // 
*/

string server   = "192.168.43.102";
string username = "joesmart";
string password = "156354"; // 


void log(int editID,LPSTR msg){
	HWND hwnd=GetActiveWindow();
	//LPSTR s;
	//GetDlgItemText(hwnd,editID,s,-1);
	SetDlgItemText(hwnd,editID,msg);
}
void logList(int listID,LPCSTR msg){
	HWND hwnd=GetActiveWindow();
	LRESULT ret= SendDlgItemMessage(hwnd,listID,LB_ADDSTRING,0,(LPARAM)(msg));
	_ASSERTE (ret!=LB_ERR);
}
    sql::ResultSet  *resultSet=NULL;    // ResultSet to hold the results
    sql::Driver     *driver; // MySQL Driver Object
    sql::Connection *connection; // MySQL connection Object
    sql::Statement  *statement;   // Statement which holds SQL commands
   int CH_LOG_AFX_ID,CH_LOG_LIST_ID,rscount;
int connectTest(int logAFXID,int listLogID){

    //Here is the connection
    //cout << "Hello connect.cpp " ;
	CH_LOG_AFX_ID=logAFXID;
	CH_LOG_LIST_ID=listLogID;
	try{

	log(logAFXID,"Connecting mysql....");
	logList(listLogID,"Connecting mysql....");


        driver = get_driver_instance();

        connection = driver->connect(server, username, password);
        statement = connection->createStatement();
        statement->execute("USE moodle");
        resultSet = statement->executeQuery("select fpinfo.* ,mdl_user.username ,mdl_user.firstname,mdl_user.middlename,mdl_user.lastname,mdl_user.id from fpinfo right join mdl_user on fpinfo.person_id=mdl_user.id order by mdl_user.username");
		rscount = resultSet->rowsCount();
		resultSet->first();
		//resultSet->
        /*while (resultSet->next()){
            // Iterating the result set
            //cout << resultSet->getString(1) << endl;
			//CString cs = resultSet->getString(1);
			//SetDlgItemText(GetActiveWindow(),logAFXID,(LPCSTR)resultSet->getString(1));
        }*/
    }
	catch (sql::SQLException &e){
		SetDlgItemText(GetActiveWindow(),logAFXID,e.what());
		MessageBox(GetActiveWindow(),e.what(),"Error",MB_OK);

       // cout << "Error message: " << e.what() << endl;
        //system("pause");
        return -1;
    }

 	

    //system("pause");*/
    return 0;
}
/***
	return 0 on failed 
*/
int mysql_updateFinger(int person_id,int FPID,const char *finger_column){

	logList(CH_LOG_LIST_ID,"mysql_updateFinger");
	if(connection){
		/* find if exist, the update
			otherwise add new on FPINFO table
		*/

		//if(resultSet->find
		if(statement){
			char sql[64]={0};

			try{
			
				sprintf(sql,"select mdl_user.id from mdl_user where mdl_user.id=%d",person_id);
				logList(CH_LOG_LIST_ID,sql);
				
				sql::ResultSet *restmp= statement->executeQuery(sql);
				int rowc=restmp->rowsCount();
				
				delete restmp;
				if(rowc<1){
					logList(CH_LOG_LIST_ID,"cant find person id in db");
					return -1;
				}

				sql[0]=0;/*emptying string .... */
				sprintf(sql,"select person_id from fpinfo  WHERE person_id=%d",person_id);
				logList(CH_LOG_LIST_ID,sql);
				restmp= statement->executeQuery(sql);
				rowc=restmp->rowsCount();

				delete restmp;
				
				if(rowc<1){
					logList(CH_LOG_LIST_ID,"Not Existed yet, adding new ... ");
					sql[0]=0;/*emptying string .... */
					//sprintf(sql,"update mdl_user set  where mdl_user.id=%d",person_id);
					sprintf(sql,"insert into FPINFO (person_id,%s) values (%d, %d ) ",
						finger_column,person_id,FPID);
					logList(CH_LOG_LIST_ID,sql);
					statement->executeUpdate(sql);
					return 1;
				} else{
					logList(CH_LOG_LIST_ID,"Existed, updating ....");

					sql[0]=0;/*emptying string .... */
					
					sprintf(sql,"update FPINFO set  %s=%d where FPINFO.person_id=%d",finger_column,FPID, person_id);
					logList(CH_LOG_LIST_ID,sql);
					statement->executeUpdate(sql);
					//statement->co
				}

			}catch (sql::SQLException &e){
				SetDlgItemText(GetActiveWindow(),CH_LOG_AFX_ID,e.what());
						MessageBox(GetActiveWindow(),e.what(),"Error",MB_OK);

			}
		}
	}
	return 0;
}

void mysql_close(){
   //Clear resources
	delete resultSet;
    delete statement;
    delete connection;

}

int rs_count(){
	if(resultSet){
		return resultSet->rowsCount();
	}

	return -1;
}

int getPersonID(){
	if(resultSet){
		return resultSet->getInt(PERSON_ID_COL_NUMBER);
		//return resultSet->getString(13)->length();

	}

	return -1;

}



void mysql_next(){
	if(resultSet){
		if(resultSet->isLast()) return ;
		resultSet->next();

	}

}

void mysql_prev(){
	if(resultSet){
		if(resultSet->isFirst()) return ;
		resultSet->previous();

	}

}

void mysql_first(){
	if(resultSet){
		if(resultSet->isFirst()) return ;
		resultSet->first();

	}

}

void mysql_last(){
	if(resultSet){
		if(resultSet->isLast()) return ;
		resultSet->last();

	}

}

void getPersonInfo( char* buffer){

	//char buffer[64]={0};
	if(resultSet){
		sql::SQLString  ss=resultSet->getString(13);
		sprintf(buffer,"%s %s %s %s",ss->c_str(),resultSet->getString(14)->c_str(),resultSet->getString(15)->c_str(),resultSet->getString(16)->c_str());
	}


}

/** return a person_id for a finger FPID ***/
int findPersonWithFPID(int FPID){
	
	if(resultSet){
		
		if(statement){
			char sql[300]={0};

			try{
			sprintf(sql,
				"select fpinfo.* ,mdl_user.username ,mdl_user.firstname,mdl_user.middlename,mdl_user.lastname,mdl_user.id from fpinfo right join mdl_user on fpinfo.person_id=mdl_user.id WHERE  "
					,FPID);
			resultSet = statement->executeQuery(sql);
				logList(CH_LOG_LIST_ID,sql);
				
				sql::ResultSet *restmp= statement->executeQuery(sql);
				int rowc=restmp->rowsCount();
				
				delete restmp;
				if(rowc<1){
					logList(CH_LOG_LIST_ID,"cant find person id in db");
					return -1;
				}
			}catch (sql::SQLException &e){

			}
		}
	}

	return -1;
}