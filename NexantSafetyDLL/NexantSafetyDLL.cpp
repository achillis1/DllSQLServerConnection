#include "NexantSafetyDLL.h"

extern "C"
{
	int _stdcall myGetSQL(staffinfo mystaffinfo[], int nLength, LPCSTR pszString){
		int returnVal;
		char strSelect[1000];

		SQLHENV henv;
		SQLHDBC hdbc;
		SQLHSTMT hstmt;
		SQLRETURN retcode;

		SQLCHAR OutConnStr[255];
		SQLSMALLINT OutConnStrLen;

		char firstname[VARCHARLEN], lastname[VARCHARLEN], shortid[VARCHARLEN], eid[VARCHARLEN], supeid[VARCHARLEN];
		SQLINTEGER cbFirstName, cbLastName, cbShortID, cbEID, cbSupEID;

		char rolename[VARCHARLEN], role[VARCHARLEN];
		SQLINTEGER cbRolename, cbRole;

		HWND desktopHandle = GetDesktopWindow();   // desktop's window handle

		nLength = 0;

		systeminfo systable[1];

		//staffinfo mystaffinfo[AS];
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

					retcode = SQLDriverConnect( // SQL_NULL_HDBC
						hdbc,
						desktopHandle,
						(SQLCHAR*)"DRIVER={SQL Server};SERVER=SACSQL03;Database=Safety;UID=SafetyUsr;PWD=SafetyPwd1",
						_countof("DRIVER={SQL Server};SERVER=SACSQL03;Database=Safety;UID=SafetyUsr;PWD=SafetyPwd1"),
						OutConnStr,
						255,
						&OutConnStrLen,
						SQL_DRIVER_NOPROMPT);

					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
						retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

						strcpy(strSelect, "select * from DingStaffInfo A inner join DingStaffInfo B on A.SupEID = B.EID where B.shortID = '");
						strcat(strSelect, pszString);
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
									
									SQLGetData(hstmt, 1, SQL_C_CHAR, mystaffinfo[nLength].FirstName, VARCHARLEN, &cbFirstName);
									SQLGetData(hstmt, 2, SQL_C_CHAR, mystaffinfo[nLength].LastName, VARCHARLEN, &cbLastName);
									SQLGetData(hstmt, 3, SQL_C_CHAR, mystaffinfo[nLength].EID, VARCHARLEN, &cbEID);
									SQLGetData(hstmt, 4, SQL_C_CHAR, mystaffinfo[nLength].ShortID, VARCHARLEN, &cbShortID);
									SQLGetData(hstmt, 5, SQL_C_CHAR, mystaffinfo[nLength].SupEID, VARCHARLEN, &cbSupEID);

									nLength++;
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

	int _stdcall myAdd(int a, int b)
	{
		return(a + b);
	}

	int __stdcall fctHoldingArray(double arr[], long nLength)
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

	int __stdcall teststr(LPCSTR pszString)
	{
		char strSelect[1000];
		//char empName[] = "wfan";
		//empName = "wfan";

		strcpy_s(strSelect, pszString);

		return 0;
	}
}