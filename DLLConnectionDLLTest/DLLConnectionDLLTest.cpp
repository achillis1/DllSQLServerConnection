#include "DllConnection.h"
//#include <iostream>
//#include <windows.h>
//#include <sqlext.h>
//
//#define NAME_LEN 50
//#define PHONE_LEN 50
//
//struct table
//{
//	SQLINTEGER EmployeeNumber;
//	char FirstName[NAME_LEN];
//	char LastName[NAME_LEN];
//	SQLDOUBLE hourlySalary;
//};



extern "C"
{




	int _stdcall myAdd(int a, int b)
	{
		return(a + b);
	}

	int __stdcall fctHoldingArray(double arr[],long nLength)
	{
		double arrLocal[10] = { 10.0, 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0 };
		long nLocal = 10;
		long i = 0;
		for (i = 0; i< min(nLength, nLocal); i++)
		{
			arr[i] = arrLocal[i];
		}
		return int(i);
	}

	int _stdcall myGetSQL(table employee[], long nLength){
		//int main(){
		int returnVal;
		SQLHENV henv;
		SQLHDBC hdbc;
		SQLHSTMT hstmt;
		SQLRETURN retcode;

		SQLCHAR OutConnStr[255];
		SQLSMALLINT OutConnStrLen;
		char      szName[NAME_LEN], szPhone[PHONE_LEN];
		SQLINTEGER   sCustID, cbName;// , cbAge, cbBirthday;
		SQLINTEGER cbCustID, cbPhone;
		SQLDOUBLE cSalary;
		SQLINTEGER cbSalary;

		HWND desktopHandle = GetDesktopWindow();   // desktop's window handle

		nLength = 0;

		returnVal = 0;
		// Allocate environment handle
		retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);

		// Set the ODBC version environment attribute
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
			retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER*)SQL_OV_ODBC3, 0);

			// Allocate connection handle
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);

				// Set login timeout to 5 seconds
				if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
					SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);

					retcode = SQLDriverConnect( // SQL_NULL_HDBC
						hdbc,
						desktopHandle,
						(SQLCHAR*)"DRIVER={SQL Server};SERVER=(local);Database=NexantSafetyStaging;UID=foo;PWD=f00Welcome1",
						_countof("DRIVER={SQL Server};SERVER=(local);Database=NexantSafetyStaging;UID=foo;PWD=f00Welcome1"),
						OutConnStr,
						255,
						&OutConnStrLen,
						SQL_DRIVER_NOPROMPT);

					//retcode = SQLDriverConnect( // SQL_NULL_HDBC
					//	hdbc,
					//	desktopHandle,
					//	(SQLCHAR*)"DRIVER={SQL Server};SERVER=(local);Trusted_Connection=yes",
					//	_countof("DRIVER={SQL Server};SERVER=(local);Trusted_Connection=yes"),
					//	OutConnStr,
					//	255,
					//	&OutConnStrLen,
					//	SQL_DRIVER_NOPROMPT);

					//retcode = SQLDriverConnect( // SQL_NULL_HDBC
					//	hdbc,
					//	desktopHandle,
					//	(SQLCHAR*)"DRIVER={SQL Server Native Client 11.0};SERVER=(local);Trusted_Connection=yes",
					//	_countof("DRIVER={SQL Server Native Client 11.0};SERVER=(local);Trusted_Connection=yes"),
					//	OutConnStr,
					//	255,
					//	&OutConnStrLen,
					//	SQL_DRIVER_NOPROMPT);
					// Allocate statement handle
					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
						retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

						//long fred;
						//fred = SQLExecDirect(hstmt, (SQLCHAR *)"select * from EmployeeTStamp1", SQL_NTS);

						retcode = SQLExecDirect(hstmt,
							(SQLCHAR *)"select * from EmployeeTStamp1",
							SQL_NTS);
						if (retcode == SQL_SUCCESS) {
							while (TRUE) {
								retcode = SQLFetch(hstmt);
								if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO) {
									printf("Error!\n");
								}
								if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO){

									table *tmpemployee = (struct table*)malloc(sizeof(struct table));

									SQLGetData(hstmt, 1, SQL_C_ULONG, &sCustID, 0, &cbCustID);
									SQLGetData(hstmt, 2, SQL_C_CHAR, szName, NAME_LEN, &cbName);
									SQLGetData(hstmt, 3, SQL_C_CHAR, szPhone, PHONE_LEN, &cbPhone);
									SQLGetData(hstmt, 4, SQL_C_DOUBLE, &cSalary, 0, &cbSalary);

									employee[nLength].EmployeeNumber = sCustID;
									strcpy_s(employee[nLength].FirstName, szName);
									strcpy_s(employee[nLength].LastName, szPhone);
									employee[nLength].hourlySalary = cSalary;

									nLength++;

									/* Print the row of data */
									//printf("%-9d %-*s %*s", sCustID, NAME_LEN - 1, szName,
									//	PHONE_LEN - 1, szPhone);
									printf("%9d, %s, %s\n", sCustID, szName, szPhone);

									//fprintf(out, "%-5d %-*s %*s", sCustID, NAME_LEN - 1, szName,
									//	PHONE_LEN - 1, szPhone);
								}
								else {
									break;
								}
							}
						}

						// Process data
						if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
							SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
						}

						returnVal = nLength;
						//printf("%d", returnVal);
						SQLDisconnect(hdbc);
					}

					SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
				}
			}
			SQLFreeHandle(SQL_HANDLE_ENV, henv);
		}
		return returnVal;
	}

}