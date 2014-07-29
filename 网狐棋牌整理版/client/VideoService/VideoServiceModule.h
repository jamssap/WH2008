#ifndef VIDEO_SERVICE_HEAD_FILE
#define VIDEO_SERVICE_HEAD_FILE

//////////////////////////////////////////////////////////////////////////

//平台头文件
#include "..\..\template\Template.h"
#include "..\..\share\GlobalDef.h"

//消息定义
#include "..\..\msg\CMD_Video.h"

//组件头文件
#include "..\..\template\Module.h"
#include "..\SkinControls\SkinControls.h"
#include "..\GameFrame\GameFrame.h"
#include "..\PropertyModule\FlowerEffectcontrol.h"
//////////////////////////////////////////////////////////////////////////
//公共宏定义

//导出定义
#ifndef VIDEO_SERVICE_CLASS
	#ifdef  VIDEO_SERVICE_DLL
		#define VIDEO_SERVICE_CLASS _declspec(dllexport)
	#else
		#define VIDEO_SERVICE_CLASS _declspec(dllimport)
	#endif
#endif

//模块定义
#ifndef _DEBUG
	#define VIDEO_SERVICE_DLL_NAME	TEXT("VideoService.dll")			//组件 DLL 名字
#else
	#define VIDEO_SERVICE_DLL_NAME	TEXT("VideoService.dll")			//组件 DLL 名字
#endif

//////////////////////////////////////////////////////////////////////////
//结构定义

//连接信息
struct tagVideoNetwordInfo
{
	WORD							wNatPort;							//网络端口
	WORD							wLocalPort;							//网络端口
	DWORD							dwNatAddr;							//网络地址
	DWORD							dwLocalAddr;						//本地地址
};

//////////////////////////////////////////////////////////////////////////

//导出类头文件

#include "VideoServiceControl.h"

//////////////////////////////////////////////////////////////////////////

#endif
