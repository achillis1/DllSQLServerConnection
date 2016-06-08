#include <iostream>
#include <windows.h>
#include <sqlext.h>
#include <stdio.h>
#include <string.h>

#define NAME_LEN 50
#define PHONE_LEN 50
#define AS 1000
#define VARCHARLEN 100

#ifndef TABLE_H
#define TABLE_H

struct table
{
	SQLINTEGER EmployeeNumber;
	char FirstName[NAME_LEN];
	char LastName[NAME_LEN];
	SQLDOUBLE hourlySalary;
};
#endif

#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H
struct systeminfo
{
	char UpdatedBy[VARCHARLEN];
	char EmployeeDashBoard[VARCHARLEN];
	char SiteVisitProgramAuthForm[VARCHARLEN];
	char StaffCensus[VARCHARLEN];
	char ProjectListEE[VARCHARLEN];
	char ProjectListNPE[VARCHARLEN];
	char VividTrainingCompletions[VARCHARLEN];
	char VividTrainingUsers[VARCHARLEN];
	char StaffTracker[VARCHARLEN];
	char SafetyDatabase[VARCHARLEN];
	char TrainingTracker[VARCHARLEN];
};
#endif

#ifndef STAFFINFO_H
#define STAFFINFO_H
struct staffinfo
{
	char FirstName[VARCHARLEN];
	char LastName[VARCHARLEN];
	char EID[VARCHARLEN];
	char ShortID[VARCHARLEN];
	char SupEID[VARCHARLEN];
};
#endif

#ifndef DINGSTAFFINFO_H
#define DINGSTAFFINFO_H
struct dingstaffinfo
{
	char OfficialName[VARCHARLEN];
	char ShortID[VARCHARLEN];
	char EID[VARCHARLEN];
	char SupEID[VARCHARLEN];
};
#endif

#ifndef STAFFROLES_H
#define STAFFROLES_H
struct staffroles
{
	char FirstName[VARCHARLEN];
	char LastName[VARCHARLEN];
	char ShortID[VARCHARLEN];
	char RoleName[VARCHARLEN];
	char Role[VARCHARLEN];
};
#endif

#ifndef TRAININGLIST_H
#define TRAININGLIST_H
struct traininglist
{
	char FirstName[VARCHARLEN];
	char LastName[VARCHARLEN];
	long EID;
	char DateComplete[VARCHARLEN];
	char DateExpires[VARCHARLEN];
	char Course[VARCHARLEN];
};
#endif