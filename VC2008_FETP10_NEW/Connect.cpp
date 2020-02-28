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

/*
/**put these lines in password.h**/
/*string server   = "192.168.43.102";
//string server   = "192.168.1.234";
string username = "xxxxxx";
string password = "xxxxxx"; // 
*/
#include "password.h" // not to be included if git .. ? missing in compilation 

   sql::ResultSet  *resultSet=NULL;    // ResultSet to hold the results
    sql::Driver     *driver; // MySQL Driver Object
    sql::Connection *connection; // MySQL connection Object
    sql::Statement  *statement;   // Statement which holds SQL commands
   int CH_LOG_AFX_ID,CH_LOG_LIST_ID,rscount;

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
        //statement->execute("USE moodle");
        statement->execute("USE absensi");
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
				"select fpinfo.* from fpinfo WHERE LEFT_PINKY=%d OR LEFT_RING=%d OR LEFT_MIDDLE=%d OR LEFT_INDEX=%d OR LEFT_THUMB=%d OR RIGHT_THUMB=%d OR RIGHT_INDEX=%d OR RIGHT_MIDDLE=%d OR RIGHT_RING=%d OR RIGHT_PINKY=%d"
					,FPID,FPID,FPID,FPID,FPID,FPID,FPID,FPID,FPID,FPID);
			
			
			/*sprintf(sql,
				"select fpinfo.* from fpinfo WHERE LEFT_PINKY=%d OR LEFT_THUMB=%d OR RIGHT_THUMB=%d "
					,FPID,FPID,FPID);
			*/
			//logList(CH_LOG_LIST_ID,sql);
				
				sql::ResultSet *restmp= statement->executeQuery(sql);
				int rowc=restmp->rowsCount();
				
				if(rowc<1){
					delete restmp;
					logList(CH_LOG_LIST_ID,"cant find person id in db");
					return -1;
				}

				restmp->first();
				int ret=restmp->getInt(2); //this is not right join so its 2 not 17
				delete restmp;
				return ret;
			}catch (sql::SQLException &e){
				SetDlgItemText(GetActiveWindow(),CH_LOG_AFX_ID,e.what());
						MessageBox(GetActiveWindow(),e.what(),"Error",MB_OK);

			}
		}
	}

	return -1;
}

/***
	move to person_id or move to last if not found
***/
void MoveToPersonWithPersonID(int person_id){

		//logList(CH_LOG_LIST_ID,"moving...");
		

	if(resultSet){
		resultSet->first();

		while(true&&!resultSet->isLast()){

			if(resultSet->getInt(PERSON_ID_COL_NUMBER)==person_id) {
			//	logList(CH_LOG_LIST_ID,"move found ");
				return ;
			}

			if(resultSet->isLast()) {
				return ;
			}
			
			//logList(CH_LOG_LIST_ID,"moving...");
			resultSet->next();
		}

	}


}


int mysql_logIdentified1N(int FPID,int SCORE, int PFN,const char* reg_name){

	char info[40]={0};
	sprintf(info,"logIdentified1N into mysql");
	logList(CH_LOG_LIST_ID,info);
	if(statement){
		char  sql [200]={0};
		sprintf(sql,"insert IDENTIFIED1N (FPID, SCORE,PFN,REGNAME) values (%d, %d,%d, '%s' ) ",
						FPID,SCORE,PFN,reg_name);
		logList(CH_LOG_LIST_ID,sql);
		try{
			int ret=statement->executeUpdate(sql);
			return ret;
		}catch (sql::SQLException &e){
				SetDlgItemText(GetActiveWindow(),CH_LOG_AFX_ID,e.what());
						MessageBox(GetActiveWindow(),e.what(),"Error",MB_OK);
		}

	}	
	return -1;
}

