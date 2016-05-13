#include "DllConnection.h"

//extern "C"
//{
//
//	int _stdcall myAdd(int a, int b)
//	{
//		return(a + b);
//	}

	//int _stdcall myGetSQL(){
	int main(){
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

		char firstname[VARCHARLEN], lastname[VARCHARLEN], shortid[VARCHARLEN],eid[VARCHARLEN], supeid[VARCHARLEN];
		SQLINTEGER cbFirstName, cbLastName, cbShortID, cbEID, cbSupEID;
		//SQLINTEGER eid, cbEID;
		//SQLBIGINT supeid, cbSupEID;
		

		HWND desktopHandle = GetDesktopWindow();   // desktop's window handle

		//table employee[AS];
		long nLength;
		nLength = 0;

		systeminfo systable[1];

		staffinfo mystaffinfo[AS];

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

					//retcode = SQLDriverConnect( // SQL_NULL_HDBC
					//	hdbc,
					//	desktopHandle,
					//	(SQLCHAR*)"DRIVER={SQL Server};SERVER=(local);Database=NexantSafetyStaging;UID=foo;PWD=f00Welcome1",
					//	_countof("DRIVER={SQL Server};SERVER=(local);Database=NexantSafetyStaging;UID=foo;PWD=f00Welcome1"),
					//	OutConnStr,
					//	255,
					//	&OutConnStrLen,
					//	SQL_DRIVER_NOPROMPT);

					retcode = SQLDriverConnect( // SQL_NULL_HDBC
						hdbc,
						desktopHandle,
						(SQLCHAR*)"DRIVER={SQL Server};SERVER=SACSQL03;Database=Safety;UID=SafetyUsr;PWD=SafetyPwd1",
						_countof("DRIVER={SQL Server};SERVER=SACSQL03;Database=Safety;UID=SafetyUsr;PWD=SafetyPwd1"),
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
							(SQLCHAR *)"select * from StaffInfo",
							SQL_NTS);
						if (retcode == SQL_SUCCESS) {
							while (TRUE) {
								retcode = SQLFetch(hstmt);
								if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO) {
									printf("Error!\n");
								}
								if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO){

									//table *tmpemployee = (struct table*)malloc(sizeof(struct table));

									//SQLGetData(hstmt, 1, SQL_C_ULONG, &sCustID, 0, &cbCustID);
									//SQLGetData(hstmt, 2, SQL_C_CHAR, szName, NAME_LEN, &cbName);
									//SQLGetData(hstmt, 3, SQL_C_CHAR, szPhone, PHONE_LEN, &cbPhone);
									//SQLGetData(hstmt, 4, SQL_C_DOUBLE, &cSalary, 0, &cbSalary);


									SQLGetData(hstmt, 1, SQL_C_CHAR, firstname, VARCHARLEN, &cbFirstName);
									SQLGetData(hstmt, 2, SQL_C_CHAR, lastname, VARCHARLEN, &cbLastName);
									SQLGetData(hstmt, 3, SQL_C_CHAR, eid, VARCHARLEN, &cbEID);
									SQLGetData(hstmt, 4, SQL_C_CHAR, shortid, VARCHARLEN, &cbShortID);
									SQLGetData(hstmt, 5, SQL_C_CHAR, supeid, VARCHARLEN, &cbSupEID);

									//employee[nLength].EmployeeNumber = sCustID;
									//strcpy_s(employee[nLength].FirstName, szName);
									//strcpy_s(employee[nLength].LastName, szPhone);
									//employee[nLength].hourlySalary = cSalary;

									//strcpy_s(mystaffinfo[nLength].FirstName ,firstname);
									//strcpy_s(mystaffinfo[nLength].LastName, lastname);
									//strcpy_s(mystaffinfo[nLength].EID, eid);
									//strcpy_s(mystaffinfo[nLength].ShortID, shortid);
									//strcpy_s(mystaffinfo[nLength].SupEID, supeid);

									memcpy(mystaffinfo[nLength].FirstName, firstname, sizeof(firstname));
									memcpy(mystaffinfo[nLength].LastName, lastname, sizeof(lastname));
									memcpy(mystaffinfo[nLength].EID, eid, sizeof(eid));
									memcpy(mystaffinfo[nLength].ShortID, shortid, sizeof(shortid));
									memcpy(mystaffinfo[nLength].SupEID, supeid, sizeof(supeid));


									nLength++;

									//printf("%4d, %9d, %s, %s\n", nLength, sCustID, szName, szPhone);
									printf("%16s, %16s,%8d,%16s, %8d\n", firstname, lastname, eid, shortid, supeid);

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
//}
