#include "DllConnection.h"

//extern "C"
//{
//
//	int _stdcall myAdd(int a, int b)
//	{
//		return(a + b);
//	}

	//int _stdcall myGetSQL(){

//int addition(int a, int b)
//{
//	int r;
//	r = a + b;
//	return r;
//}


	int main(){
		int returnVal;
		int returnstaffinfo;
		char strSelect[1000];
		char empName[] = "wfan";

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

		char rolename[VARCHARLEN], role[VARCHARLEN];
		SQLINTEGER cbRolename, cbRole;


		HWND desktopHandle = GetDesktopWindow();   // desktop's window handle

		//table employee[AS];
		long nLength;
		nLength = 0;

		systeminfo systable[1];

		staffinfo mystaffinfo[AS];
		staffroles mystaffrole[AS];

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

						//retcode = SQLExecDirect(hstmt,
						//	(SQLCHAR *)"select * from StaffInfo",
						//	SQL_NTS);

//						retcode = SQLExecDirect(hstmt,
//(SQLCHAR *)"select * from ProgramAuthorizations A inner join EmployeeAuthorizations B on A.AuthID = B.AuthID inner join DingStaffInfo C on A.ProgramManager = C.OfficialName where A.pCheck='OK' and A.pStatus='ACTIVE' and B.ShortID='wfan' and C.ShortID='wfan'",
//							SQL_NTS);
						strcpy(strSelect, "select * from DingStaffInfo A inner join DingStaffInfo B on A.SupEID = B.EID where B.shortID = '");
						strcat(strSelect, empName);
						strcat(strSelect, "'");
						retcode = SQLExecDirect(hstmt,
							(SQLCHAR *)strSelect,
							SQL_NTS);

						if (retcode == SQL_SUCCESS) {
							while (TRUE) {
								retcode = SQLFetch(hstmt);
								if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO) {
									printf("Error!\n");
								}
								if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO){

									SQLGetData(hstmt, 1, SQL_C_CHAR, firstname, VARCHARLEN, &cbFirstName);
									SQLGetData(hstmt, 2, SQL_C_CHAR, lastname, VARCHARLEN, &cbLastName);
									SQLGetData(hstmt, 3, SQL_C_CHAR, eid, VARCHARLEN, &cbEID);
									SQLGetData(hstmt, 4, SQL_C_CHAR, shortid, VARCHARLEN, &cbShortID);
									SQLGetData(hstmt, 5, SQL_C_CHAR, supeid, VARCHARLEN, &cbSupEID);

									memcpy(mystaffinfo[nLength].FirstName, firstname, sizeof(firstname));
									memcpy(mystaffinfo[nLength].LastName, lastname, sizeof(lastname));
									memcpy(mystaffinfo[nLength].EID, eid, sizeof(eid));
									memcpy(mystaffinfo[nLength].ShortID, shortid, sizeof(shortid));
									memcpy(mystaffinfo[nLength].SupEID, supeid, sizeof(supeid));


									nLength++;

									printf("%16s, %16s,%8s,%16s, %8s\n", firstname, lastname, eid, shortid, supeid);

								}
								else {
									break;
								}
							}
						}


						// another sql query
						nLength = 0;
						retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
						retcode = SQLExecDirect(hstmt,
							(SQLCHAR *)"select * from StaffRoles",
							SQL_NTS);
						if (retcode == SQL_SUCCESS) {
							while (TRUE) {
								retcode = SQLFetch(hstmt);
								if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO) {
									printf("Error!\n");
								}
								if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO){

									SQLGetData(hstmt, 1, SQL_C_CHAR, firstname, VARCHARLEN, &cbFirstName);
									SQLGetData(hstmt, 2, SQL_C_CHAR, lastname, VARCHARLEN, &cbLastName);
									SQLGetData(hstmt, 3, SQL_C_CHAR, shortid, VARCHARLEN, &cbShortID);
									SQLGetData(hstmt, 4, SQL_C_CHAR, rolename, VARCHARLEN, &cbRolename);
									SQLGetData(hstmt, 5, SQL_C_CHAR, role, VARCHARLEN, &cbRole);

									memcpy(mystaffrole[nLength].FirstName, firstname, sizeof(firstname));
									memcpy(mystaffrole[nLength].LastName, lastname, sizeof(lastname));
									memcpy(mystaffrole[nLength].ShortID, shortid, sizeof(shortid));
									memcpy(mystaffrole[nLength].RoleName, rolename, sizeof(rolename));
									memcpy(mystaffrole[nLength].Role, role, sizeof(role));

									nLength++;

									printf("%16s, %16s,%8s,%16s, %8s\n", firstname, lastname, shortid, rolename, role);

								}
								else {
									break;
								}
							}
						}

						// add more query 


						// Process data
						if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
							SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
						}

						returnVal = nLength;
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
