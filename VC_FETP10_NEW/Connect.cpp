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
string username = "joesmarts";
string password = "xxxx"; // 


void log(int editID,LPSTR msg){
	HWND hwnd=GetActiveWindow();
	//LPSTR s;
	//GetDlgItemText(hwnd,editID,s,-1);
	SetDlgItemText(hwnd,editID,msg);
}
void logList(int listID,LPSTR msg){
	HWND hwnd=GetActiveWindow();
	LRESULT ret= SendDlgItemMessage(hwnd,listID,LB_ADDSTRING,0,(LPARAM)(msg));
	_ASSERTE (ret!=LB_ERR);
}
    sql::ResultSet  *resultSet=NULL;    // ResultSet to hold the results
    sql::Driver     *driver; // MySQL Driver Object
    sql::Connection *connection; // MySQL connection Object
    sql::Statement  *statement;   // Statement which holds SQL commands

int connectTest(int logAFXID,int listLogID){

    //Here is the connection
    //cout << "Hello connect.cpp " ;
	try{

	log(logAFXID,"Connecting mysql....");
	logList(listLogID,"Connecting mysql....");


        driver = get_driver_instance();

        connection = driver->connect(server, username, password);
        statement = connection->createStatement();
        statement->execute("USE performance_schema");
        resultSet = statement->executeQuery("show tables");
		int count = resultSet->rowsCount();
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

void mysql_end(){
   //Clear resources
	delete resultSet;
    delete statement;
    delete connection;

}