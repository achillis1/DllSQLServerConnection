#include <iostream>
#include <windows.h>
#include <sqlext.h>
#include <stdio.h>
#include <string.h>

#define NAME_LEN 50
#define PHONE_LEN 50
#define AS 1000
#define VARCHARLEN 255

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