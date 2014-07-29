#include "Stdafx.h"
#include "GameServer.h"
#include "GameServerDlg.h"

//应用程序对象
CGameServerApp theApp;

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGameServerApp, CWinApp)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//构造函数
CGameServerApp::CGameServerApp() : CWinApp(TEXT("游戏服务器"))
{
}

//初始化函数
BOOL CGameServerApp::InitInstance()
{
	__super::InitInstance();

	//内部初始化
	AfxInitRichEdit2();
	InitCommonControls();
	AfxEnableControlContainer();

	HMODULE hMod;
	hMod = LoadLibrary(TEXT( "riched20.dll"));

	SetRegistryKey(szSystemRegKey);

	//设置工作目录
	TCHAR szDirWork[MAX_PATH]=TEXT("");
	GetModuleFileName(AfxGetInstanceHandle(),szDirWork,sizeof(szDirWork));
	int nModuleLen=lstrlen(szDirWork);
	int nProcessLen=lstrlen(AfxGetApp()->m_pszExeName)+lstrlen(TEXT(".EXE"));
	szDirWork[nModuleLen-nProcessLen]=0;
	SetCurrentDirectory(szDirWork);

	//创建窗口
	CGameServerDlg GameServerDlg;
	GameServerDlg.DoModal();

	FreeLibrary(hMod);

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
