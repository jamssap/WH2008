#pragma once



// CSystemLog command target

class CSystemLog : public CObject
{
protected:
	CSystemLog();
	virtual ~CSystemLog();

public:
	BOOL Create(WORD wKinid, WORD wServerID, LPCTSTR pszKindName, LPTSTR pszOutFileName=NULL);
	void Close();
	int WriteLog(LPCTSTR pszFormat, ...);
	int WriteString(LPCTSTR pszString);

	static CSystemLog& GetInstance();
protected:
	FILE	* m_pFile;
	CCriticalSection	m_ThreadLock;
};

#define OUTLOG	(CSystemLog::GetInstance()).WriteLog
#define OUTLOG0 (CSystemLog::GetInstance()).WriteString
