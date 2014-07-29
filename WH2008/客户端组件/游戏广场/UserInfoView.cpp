#include "Stdafx.h"
#include "Resource.h"
#include "GlobalUnits.h"
#include "UserInfoView.h"

//////////////////////////////////////////////////////////////////////////

//颜色定义
#define CR_TEXT						RGB(255,255,255)					//字体颜色
#define CR_BACKGROUP				RGB(255,232,160)					//背景颜色


#define IDC_BT_EXCHANGE_LOVELINESS	100									//兑换魅力
//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CUserInfoView, CDialog)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BT_EXCHANGE_LOVELINESS,OnBnClickedExchangeLoveliness)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//构造函数
CUserInfoView::CUserInfoView() : CDialog(IDD_USER_INFO)
{
	//状态变量
	m_nTitleHeight=0;
	m_bShowInfo=false;
	m_bCreateFlag=false;

	return;
}

//析构函数
CUserInfoView::~CUserInfoView()
{
}

//控件绑定
VOID CUserInfoView::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
}

//初始化函数
BOOL CUserInfoView::OnInitDialog()
{
	__super::OnInitDialog();

	//加载资源
	UpdateSkinResource();

	//获取大小
	CImageHandle HandleTitleM(&m_ImageTitleM);
	m_nTitleHeight=m_ImageTitleM.GetHeight();

	//移动窗口
	SetWindowPos(NULL,0,0,0,m_nTitleHeight,SWP_NOMOVE|SWP_NOZORDER);

	//设置变量
	m_bCreateFlag=true;

	return TRUE;
}

//标题高度
UINT CUserInfoView::GetTitleHeight()
{
	return m_nTitleHeight;
}

//更新信息
VOID CUserInfoView::UpdateUserInfo()
{
	//更新界面
	Invalidate();

	return;
}

//显示信息
VOID CUserInfoView::ShowUserInfo(bool bShowInfo)
{
	//状态判断
	if (m_bShowInfo==bShowInfo) return;

	//设置变量
	m_bShowInfo=bShowInfo;

	//更新界面
	Invalidate();

	return;
}

//更新资源
bool CUserInfoView::UpdateSkinResource()
{
	//获取资源
	tagControlViewImage & ControlViewImage=g_GlobalUnits.m_ControlViewImage;
	HINSTANCE hInstance=g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

	m_ImageTitleL.SetLoadInfo(ControlViewImage.uUserInfoL,hInstance);
	m_ImageTitleM.SetLoadInfo(ControlViewImage.uUserInfoM,hInstance);
	m_ImageTitleR.SetLoadInfo(ControlViewImage.uUserInfoR,hInstance);

	//创建按钮
	if (NULL==m_btExchangeLoveliness.m_hWnd) m_btExchangeLoveliness.Create(TEXT(""),WS_CHILD,CRect(0,0,0,0),this,IDC_BT_EXCHANGE_LOVELINESS);
	m_btExchangeLoveliness.SetButtonImage(IDB_BT_BUY_MEMBER_VALUE,AfxGetInstanceHandle(),false);

	return true;
}

//绘画背景
BOOL CUserInfoView::OnEraseBkgnd(CDC * pDC)
{
	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//建立缓冲
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),24);

	//创建 DC
	CDC BufferDC;
	BufferDC.CreateCompatibleDC(pDC);
	BufferDC.SelectObject(ImageBuffer);

	//加载资源
	CImageHandle HandleTitleL(&m_ImageTitleL);
	CImageHandle HandleTitleM(&m_ImageTitleM);
	CImageHandle HandleTitleR(&m_ImageTitleR);

	//绘画背景
	m_ImageTitleL.BitBlt(BufferDC,0,0);

	//填充中间
	for (INT nXPos=m_ImageTitleL.GetWidth();nXPos<rcClient.Width();nXPos+=m_ImageTitleM.GetWidth())
	{
		m_ImageTitleM.BitBlt(BufferDC,nXPos,0);
	}

	//绘画背景
	m_ImageTitleR.BitBlt(BufferDC,rcClient.Width()-m_ImageTitleR.GetWidth()-6,0);

	//设置 DC
	BufferDC.SetTextColor(RGB(255,255,255));
	BufferDC.SetBkMode(TRANSPARENT);
	BufferDC.SelectObject(CSkinResourceManager::GetDefaultFont());

	//用户信息
	if (m_bShowInfo==true)
	{
		//变量定义
		tagGlobalUserData & GlobalUserInfo=g_GlobalUnits.GetGolbalUserData();

		//用户头像
		//g_GlobalUnits.m_UserFaceRes->DrawNormalFace(&BufferDC,10,12,GlobalUserInfo.wFaceID,GlobalUserInfo.dwUserID,GlobalUserInfo.dwCustomFaceVer);

		//构造位置
		TCHAR szBuffer[255]=TEXT("");
		CRect rcUserID(200,30,rcClient.Width()-20,17);
		CRect rcAccounts(100,82,rcClient.Width()-20,27);
		CRect rcUnderWrite(100,108,rcClient.Width()-20,50);

		//用户帐号
		//_sntprintf(szBuffer,CountArray(szBuffer),TEXT("用户帐号：%s [ %ld ]"),GlobalUserInfo.szAccounts,GlobalUserInfo.dwGameID);
		_sntprintf(szBuffer,CountArray(szBuffer),TEXT("%ld"),GlobalUserInfo.dwGameID);

        HFONT   hf; 
		LOGFONT   lf; 
		lf.lfHeight=10; 
		lf.lfWidth=10; 
		lf.lfEscapement=1;
		lf.lfItalic=0;
		lf.lfUnderline=0;
		lf.lfStrikeOut=0;
		lf.lfCharSet=1;
		hf=CreateFontIndirect(&lf); 
		SelectObject(BufferDC,hf); 

        BufferDC.DrawText(szBuffer,lstrlen(szBuffer),&rcUserID,DT_VCENTER|DT_WORD_ELLIPSIS|DT_SINGLELINE);
		_sntprintf(szBuffer,CountArray(szBuffer),TEXT("用户帐号：%s"),GlobalUserInfo.szAccounts);
		BufferDC.DrawText(szBuffer,lstrlen(szBuffer),&rcAccounts,DT_VCENTER|DT_WORD_ELLIPSIS|DT_SINGLELINE);

		//会员信息
		LPCTSTR pszMemberOrder[]={TEXT("非会员"),TEXT("红钻会员"),TEXT("蓝钻会员"),TEXT("黄钻会员"),TEXT("紫钻会员")};
		if (GlobalUserInfo.cbMember<CountArray(pszMemberOrder))
		{
			_sntprintf(szBuffer,CountArray(szBuffer),TEXT("会员等级：%s"),pszMemberOrder[GlobalUserInfo.cbMember]);
			BufferDC.DrawText(szBuffer,lstrlen(szBuffer),&rcUnderWrite,DT_VCENTER|DT_WORD_ELLIPSIS|DT_SINGLELINE);
		}

		//移动按钮
		CRect reButton;
		m_btExchangeLoveliness.ShowWindow(SW_SHOW);
		m_btExchangeLoveliness.GetWindowRect(reButton);
		m_btExchangeLoveliness.MoveWindow(rcClient.Width()-reButton.Width()-30,rcClient.Height()-reButton.Height()-10,reButton.Width(),reButton.Height());
	}

	//绘画界面
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),&BufferDC,0,0,SRCCOPY);

	//清理资源
	BufferDC.DeleteDC();
	ImageBuffer.Destroy();

	return TRUE;
}

//魅力兑换
void CUserInfoView::OnBnClickedExchangeLoveliness()
{
	ShellExecute(NULL,TEXT("open"),TEXT("http://www.52e8.com/BuyMember.asp"),NULL,NULL,SW_SHOWDEFAULT);
}
//////////////////////////////////////////////////////////////////////////

