#include "Stdafx.h"
#include "GamePlaza.h"
#include "GameFrame.h"
#include "GlobalUnits.h"
#include "SplashWnd.h"

#include "SEU_QQwry.h"


#include <afxinet.h>
#include <afxext.h>

#import "msxml.dll" 
#import "msxml2.dll" 

using namespace MSXML2;

SEU_QQwry         m_QQDat;

extern BOOL isTelCom=False;

//////////////////////////////////////////////////////////////////////////
DETOUR_TRAMPOLINE(int   WINAPI SetScrollInfoT(HWND, int, LPCSCROLLINFO, BOOL), SetScrollInfo)
DETOUR_TRAMPOLINE(BOOL  WINAPI GetScrollInfoT(HWND, int, LPSCROLLINFO), GetScrollInfo)
DETOUR_TRAMPOLINE(int   WINAPI SetScrollPosT(HWND, int, int, BOOL), SetScrollPos)
DETOUR_TRAMPOLINE(int   WINAPI GetScrollPosT(HWND, int), GetScrollPos)
DETOUR_TRAMPOLINE(BOOL  WINAPI GetScrollRangeT(HWND, int, LPINT, LPINT), GetScrollRange)
DETOUR_TRAMPOLINE(BOOL  WINAPI SetScrollRangeT(HWND, int, int, int, BOOL), SetScrollRange)
DETOUR_TRAMPOLINE(BOOL  WINAPI ShowScrollBarT(HWND, int, BOOL), ShowScrollBar)
DETOUR_TRAMPOLINE(BOOL  WINAPI EnableScrollBarT(HWND, UINT, UINT), EnableScrollBar)

int WINAPI SetScrollInfoD(HWND hwnd, int fnBar, LPCSCROLLINFO lpsi, BOOL bRedraw)
{
	if( SkinSB_IsValid(hwnd) ) return SkinSB_SetScrollInfo(hwnd, fnBar, lpsi, bRedraw);
	else return SetScrollInfoT(hwnd, fnBar, lpsi, bRedraw);
}

BOOL WINAPI GetScrollInfoD(HWND hwnd, int fnBar, LPSCROLLINFO lpsi)
{
	if( SkinSB_IsValid(hwnd) ) return SkinSB_GetScrollInfo(hwnd, fnBar, lpsi);
	else return GetScrollInfoT(hwnd, fnBar, lpsi);
}

int WINAPI SetScrollPosD(HWND hwnd, int nBar, int nPos, BOOL bRedraw)
{
	if( SkinSB_IsValid(hwnd) ) return SkinSB_SetScrollPos(hwnd, nBar, nPos, bRedraw);
	else return SetScrollPosT(hwnd, nBar, nPos, bRedraw);
}

int WINAPI GetScrollPosD(HWND hwnd, int nBar)
{
	if( SkinSB_IsValid(hwnd) ) return SkinSB_GetScrollPos(hwnd, nBar);
	else return GetScrollPosT(hwnd, nBar);
}

BOOL WINAPI SetScrollRangeD(HWND hwnd, int nBar, int nMinPos, int nMaxPos, BOOL bRedraw)
{
	if( SkinSB_IsValid(hwnd) ) return SkinSB_SetScrollRange(hwnd, nBar, nMinPos, nMaxPos, bRedraw);
	else return SetScrollRangeT(hwnd, nBar, nMinPos, nMaxPos, bRedraw);
}

BOOL WINAPI GetScrollRangeD(HWND hwnd, int nBar, LPINT lpMinPos, LPINT lpMaxPos)
{
	if( SkinSB_IsValid(hwnd) ) return SkinSB_GetScrollRange(hwnd, nBar, lpMinPos, lpMaxPos);
	else return GetScrollRangeT(hwnd, nBar, lpMinPos, lpMaxPos);
}

BOOL WINAPI ShowScrollBarD(HWND hwnd, int nBar, BOOL bShow)
{
	if( SkinSB_IsValid(hwnd) ) return SkinSB_ShowScrollBar(hwnd, nBar, bShow);
	else return ShowScrollBarT(hwnd, nBar, bShow);
}

BOOL WINAPI EnableScrollBarD(HWND hwnd, UINT wSBflags, UINT wArrows)
{
	if( SkinSB_IsValid(hwnd) ) return SkinSB_EnableScrollBar(hwnd, wSBflags, wArrows);
	else return EnableScrollBarT(hwnd, wSBflags, wArrows);
}

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGamePlazaApp, CWinApp)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//应用程序对象说明
CGamePlazaApp theApp;

//构造函数
CGamePlazaApp::CGamePlazaApp()
{
	//_CrtSetBreakAlloc(123);
}

CGamePlazaApp::~CGamePlazaApp()
{
	SafeDelete(m_pDispOM);

	// 卸载钩子
	DetourRemove((PBYTE)SetScrollInfoT, (PBYTE)SetScrollInfoD);
	DetourRemove((PBYTE)SetScrollPosT, (PBYTE)SetScrollPosD);
	DetourRemove((PBYTE)GetScrollInfoT, (PBYTE)GetScrollInfoD);
	DetourRemove((PBYTE)GetScrollPosT, (PBYTE)GetScrollPosD);
	DetourRemove((PBYTE)SetScrollRangeT, (PBYTE)SetScrollRangeD);
	DetourRemove((PBYTE)GetScrollRangeT, (PBYTE)GetScrollRangeD);
	DetourRemove((PBYTE)ShowScrollBarT, (PBYTE)ShowScrollBarD);
	DetourRemove((PBYTE)EnableScrollBarT, (PBYTE)EnableScrollBarD);
}

//初始化函数
BOOL CGamePlazaApp::InitInstance()
{

	   	TCHAR szModuleName[MAX_PATH]={0};
		GetModuleFileName(AfxGetInstanceHandle(),szModuleName,MAX_PATH);
		PathRemoveFileSpec(szModuleName);

		CString m_update;
        m_update.Format("%s",__argv[1]);
		if(m_update=="(null)")
		{
		  	strcat(szModuleName,_T("\\AutoUpdate.exe"));		
			WinExec(szModuleName, SW_SHOWDEFAULT);
			Sleep(3000);
			PostQuitMessage(0);
	
		}
		else
		{
		 
		
		}
	__super::InitInstance();

	//判断是否重入
#ifndef _DEBUG
	bool bExistIGame=false;
	CMutex Mutex(FALSE,MAIN_DLG_CLASSNAME,NULL);
	if (Mutex.Lock(0)==FALSE) bExistIGame=true;
	CWnd * pIGameWnd=CWnd::FindWindow(MAIN_DLG_CLASSNAME,NULL);
	if (pIGameWnd!=NULL) 
	{ 
		bExistIGame=true;
		if (pIGameWnd->IsIconic()) pIGameWnd->ShowWindow(SW_RESTORE);
		pIGameWnd->SetActiveWindow();
		pIGameWnd->BringWindowToTop();
		pIGameWnd->SetForegroundWindow();
	}
	if (bExistIGame==true) return FALSE;
#endif


	CFont TitleFont;
	CSkinMenu::SetSelectDisableMode(GetProfileInt(_T("SkinMenu"),_T("Selection"),1));
	CSkinMenu::SetXpBlending(GetProfileInt(_T("SkinMenu"),_T("Gloom"),1));
	if(TitleFont.CreatePointFont(140,_T("Comic Sans MS")))
		CSkinMenu::SetMenuTitleFont(&TitleFont);

	CSplashWnd::EnableSplashScreen(TRUE);

	// 加载钩子
	DetourFunctionWithTrampoline((PBYTE)SetScrollInfoT, (PBYTE)SetScrollInfoD);
	DetourFunctionWithTrampoline((PBYTE)GetScrollInfoT, (PBYTE)GetScrollInfoD);
	DetourFunctionWithTrampoline((PBYTE)SetScrollPosT, (PBYTE)SetScrollPosD);
	DetourFunctionWithTrampoline((PBYTE)GetScrollPosT, (PBYTE)GetScrollPosD);
	DetourFunctionWithTrampoline((PBYTE)SetScrollRangeT, (PBYTE)SetScrollRangeD);
	DetourFunctionWithTrampoline((PBYTE)GetScrollRangeT, (PBYTE)GetScrollRangeD);
	DetourFunctionWithTrampoline((PBYTE)ShowScrollBarT, (PBYTE)ShowScrollBarD);
	DetourFunctionWithTrampoline((PBYTE)EnableScrollBarT, (PBYTE)EnableScrollBarD);


	//程序初始化
	AfxOleInit();
	AfxInitRichEdit();
	AfxInitRichEdit2();
	InitCommonControls();
	AfxEnableControlContainer();

	//设置注册表
	SetRegistryKey(szSystemRegKey);

	////加载界面库
	//CSkinAttribute::LoadSkinAttribute(QUERY_OBJECT_INTERFACE(m_SkinRecordFile,IUnknownEx));

	//加载配置
	g_GlobalOption.LoadOptionParameter();

	//全局信息
	if (g_GlobalUnits.InitGlobalUnits()==false)
	{
		ShowInformation(TEXT("游戏广场初始化失败，程序即将退出！"),0,MB_ICONSTOP);
		return FALSE;
	}
    

		
		GetModuleFileName(AfxGetInstanceHandle(),szModuleName,MAX_PATH);
		PathRemoveFileSpec(szModuleName);


		TCHAR szQQWry[MAX_PATH]=TEXT("");
		_sntprintf(szQQWry,sizeof(szQQWry),TEXT("%s\\qqwry.dat"),szModuleName);
		m_QQDat.SetPath(szQQWry);
		CString OnlineIP,Address;
		//OnlineIP="60.12.54.70";
		OnlineIP=GetOnLineIP();
		//AfxMessageBox(OnlineIP);

	
        
		Address=m_QQDat.IPtoAdd(OnlineIP);
        //AfxMessageBox(Address);


		

		
		int m_index=Address.Find("通");
		if(m_index>0)//电信登录口
		{

		 //AfxMessageBox("网通！！");
		   isTelCom=FALSE;
		}
		else//网通登录口
		{
		 // AfxMessageBox("电信！！");
		  isTelCom=TRUE;
		}








	//变量定义
	WNDCLASS WndClasss;
	ZeroMemory(&WndClasss,sizeof(WndClasss));

	//注册窗口
	WndClasss.style=CS_DBLCLKS;
	WndClasss.lpfnWndProc=DefWindowProc;
	WndClasss.lpszClassName=MAIN_DLG_CLASSNAME;
	WndClasss.hInstance=AfxGetInstanceHandle();
	WndClasss.hIcon=LoadIcon(MAKEINTRESOURCE(IDR_MAINFRAME));
	WndClasss.hCursor=LoadStandardCursor(MAKEINTRESOURCE(IDC_ARROW));
	if (AfxRegisterClass(&WndClasss)==FALSE) AfxThrowResourceException();

	m_pDispOM = new CImpIDispatch;
	AfxEnableControlContainer(new CCustomOccManager); 

	//建立窗口
	CGameFrame * pMainFrame=new CGameFrame();
	pMainFrame->CreateEx(NULL, MAIN_DLG_CLASSNAME,TEXT(""),
		WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
		0,0,0,0, NULL, NULL);
	m_pMainWnd=pMainFrame;

	return TRUE;
}
CString CGamePlazaApp::GetOnLineIP()
{

    CInternetSession   mySession(NULL,0); 
    CHttpFile*   myHttpFile=NULL;    
	 CString   m_SiteInfo="";//页面源码 
    try 
    { 
       
        
        CString   myData; 
        myHttpFile=(CHttpFile*)mySession.OpenURL("http://city.ip138.com/city0.asp"); 
        while(myHttpFile->ReadString(myData)) 
        {            
    
            m_SiteInfo=m_SiteInfo+"\r\n"; 
            
            m_SiteInfo+=myData; 
        }        

        int x=m_SiteInfo.Find("<center>");
        m_SiteInfo.Delete(0,x+8);

        int x1=m_SiteInfo.Find("</center>");
        m_SiteInfo.Delete(x1,m_SiteInfo.GetLength()-x1);
        


		int index=m_SiteInfo.Find("[");
		m_SiteInfo=m_SiteInfo.Right(m_SiteInfo.GetLength()-index-1);
       // AfxMessageBox(m_SiteInfo);
		
	
		//index=m_SiteInfo.Find("[");
		//m_SiteInfo=m_SiteInfo.Right(m_SiteInfo.GetLength()-index-1);
		//m_SiteInfo=m_SiteInfo.Left(m_SiteInfo.GetLength()-2);
		///m_SiteInfo="222.248.34.5]";

		//int len=m_SiteInfo.GetLength();
  //      
		//m_SiteInfo=m_SiteInfo.GetBuffer(len-1);

        m_SiteInfo=m_SiteInfo.Left(m_SiteInfo.Find("]"));
		//m_SiteInfo=m_SiteInfo.Right(len-1);
		//len=m_SiteInfo.GetLength();
		//m_SiteInfo=m_SiteInfo.Left(len-2);



      //  AfxMessageBox(m_SiteInfo);   //显示页面源码 
        myHttpFile->Close(); 
        mySession.Close(); 
    
    } 
    
    catch   (...)    
    { 
        myHttpFile->Close(); 
        mySession.Close(); 

		return "error";
	}

    return m_SiteInfo;


}   



//////////////////////////////////////////////////////////////////////////

