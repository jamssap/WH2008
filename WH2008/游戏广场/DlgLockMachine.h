#ifndef LOCK_MACHINE_FILE_HEAD
#define LOCK_MACHINE_FILE_HEAD
#pragma once

class CDlgLockMachine : public CSkinDialogEx
{
	//变量定义
public:
	CString								m_strPassword;
	CString								m_strDescribe;
	bool								m_bLock;

	//控件变量
private:
	CSkinButton							m_btOK;
	CSkinButton							m_btCancel;
	

public:
	CDlgLockMachine(CWnd* pParent = NULL);
	virtual ~CDlgLockMachine();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();

		DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CDlgLockMachine)
protected:
	virtual void OnOK();
};

#endif