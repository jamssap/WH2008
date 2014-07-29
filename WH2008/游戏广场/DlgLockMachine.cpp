#include "stdafx.h"
#include "resource.h"
#include "DlgLockMachine.h"
#include ".\dlglockmachine.h"


IMPLEMENT_DYNAMIC(CDlgLockMachine, CSkinDialogEx)
CDlgLockMachine::CDlgLockMachine(CWnd* pParent /*=NULL*/)
	: CSkinDialogEx(IDD_LOCK, pParent)
{
	m_bLock=true;
}

CDlgLockMachine::~CDlgLockMachine()
{
}

void CDlgLockMachine::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX,IDOK,m_btOK);
	DDX_Control(pDX,IDCANCEL,m_btCancel);
	DDX_Text(pDX,IDC_PASSWORD,m_strPassword);	
	DDX_Text(pDX,IDC_DESCRIBE,m_strDescribe);		
}


BEGIN_MESSAGE_MAP(CDlgLockMachine, CSkinDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDlgLockMachine message handlers

HBRUSH CDlgLockMachine::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	UINT uButtonID=GetWindowLong(GetSafeHwnd(),GWL_ID);
	if (CTLCOLOR_STATIC==nCtlColor && pWnd->GetSafeHwnd()!=GetDlgItem(IDC_BAK_PASSWORD)->GetSafeHwnd())
	{
		pDC->SetTextColor(RGB(255,0,0));
		return m_SkinAttribute.m_brBackGround;
	}
	
	HBRUSH hbr = __super::OnCtlColor(pDC, pWnd, nCtlColor);

	return hbr;
}

BOOL CDlgLockMachine::OnInitDialog()
{
	__super::OnInitDialog();

	if (m_bLock) 
	{
		SetWindowText(TEXT("绑定操作"));
		SetDlgItemText(IDOK,TEXT("锁机"));
	}
	else
	{
		SetWindowText(TEXT("解锁操作"));
		SetDlgItemText(IDOK,TEXT("解锁"));
	}

	//设置变量
	m_strPassword=TEXT("");

	//更新变量
	UpdateData(FALSE);

	//设置焦点
	GetDlgItem(IDC_PASSWORD)->SetFocus();

	return TRUE;
}

void CDlgLockMachine::OnOK()
{
	UpdateData(TRUE);

	if (m_strPassword.IsEmpty())
	{
		MessageBox(TEXT("请输入银行密码"),TEXT("系统提示"));
		GetDlgItem(IDC_PASSWORD)->SetFocus();
		return ;
	}

	CSkinDialogEx::OnOK();
}
