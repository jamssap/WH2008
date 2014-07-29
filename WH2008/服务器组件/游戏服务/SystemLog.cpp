// SystemLog.cpp : implementation file
//

#include "stdafx.h"
#include "SystemLog.h"
#include <shlwapi.h>
#include <stdlib.h>
// CSystemLog

CSystemLog::CSystemLog() : m_pFile(NULL)
{
}

CSystemLog::~CSystemLog()
{
	Close();
}

BOOL CSystemLog::Create( WORD wKinid, WORD wServerID, LPCTSTR pszKindName, LPTSTR pszOutFileName)
{
	ASSERT(m_pFile==NULL);

	TCHAR szCurrentDir[MAX_PATH]={0};
	TCHAR szTime[32]={0};
	TCHAR szServerID[32]={0};

	//当前日期
	CTime tm = CTime::GetCurrentTime();
	sprintf(szTime,TEXT("%d-%.2d-%.2d.txt"),tm.GetYear(),tm.GetMonth(),tm.GetDay());

	sprintf(szServerID,TEXT("[%d]"),wServerID);

	GetCurrentDirectory(MAX_PATH,szCurrentDir);

	strcat(szCurrentDir,TEXT("\\ServerLog"));

	if (!PathIsDirectory(szCurrentDir))
		CreateDirectory(szCurrentDir, NULL);

	strcat(szCurrentDir,TEXT("\\"));
	strcat(szCurrentDir,pszKindName);
	strcat(szCurrentDir,szServerID);

	if (!PathIsDirectory(szCurrentDir))
		CreateDirectory(szCurrentDir, NULL);

	strcat(szCurrentDir,TEXT("\\"));
	strcat(szCurrentDir,szTime);

	if (!PathFileExists(szCurrentDir))
		m_pFile=fopen(szCurrentDir,TEXT("wt"));
	else
		m_pFile=fopen(szCurrentDir,TEXT("a+t"));

	if (m_pFile==NULL)
	{
		ASSERT(FALSE);
		return FALSE;
	}

	if (pszOutFileName)
		strcpy(pszOutFileName,szCurrentDir);

	return TRUE;
}

void CSystemLog::Close()
{
	if (m_pFile)
	{
		fclose(m_pFile);
		m_pFile=NULL;
	}
}

int CSystemLog::WriteLog( LPCTSTR pszFormat, ... )
{
	m_ThreadLock.Lock();
	static TCHAR szBuffer[1024]={0};

	va_list args;
	int pos,len;

	//增加时间
	CTime tm = CTime::GetCurrentTime();
	pos = sprintf(szBuffer,TEXT("[%d-%.2d-%.2d %.2d:%.2d:%.2d] "), 
		tm.GetYear(),tm.GetMonth(),tm.GetDay(),
		tm.GetHour(),tm.GetMinute(),tm.GetSecond());

	//读取参数
	va_start(args,pszFormat);
	len = _vscprintf(pszFormat,args) + pos;
	vsprintf(&szBuffer[pos],pszFormat,args); 
	va_end(args);

	//增加换行
	strcat(szBuffer,TEXT("\n"));
	++len;

	fwrite(szBuffer, sizeof(TCHAR), len, m_pFile);
	fflush(m_pFile);

	m_ThreadLock.Unlock();

	return len;
}

int CSystemLog::WriteString( LPCTSTR pszString )
{
	m_ThreadLock.Lock();
	int len;
	CTime tm = CTime::GetCurrentTime();

	len= fprintf(m_pFile,TEXT("[%d-%.2d-%.2d %.2d:%.2d:%.2d] %s\n"),
		tm.GetYear(),tm.GetMonth(),tm.GetDay(),
		tm.GetHour(),tm.GetMinute(),tm.GetSecond(),
		pszString);
	
	fflush(m_pFile);

	m_ThreadLock.Unlock();

	return len;
}

CSystemLog& CSystemLog::GetInstance()
{
	static CSystemLog log;
	return log;
}


