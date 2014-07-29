#ifndef D3D_ENGINE_HEAD_HEAD_FILE
#define D3D_ENGINE_HEAD_HEAD_FILE

//////////////////////////////////////////////////////////////////////////
//包含文件

//MFC 文件
#include <Afxmt.h>
#include <AtlBase.h>
#include <AfxTempl.h>
#include <MMSystem.h>

//D3D 文件
#include <D3D9.h>
#include <D3Dx9.h>
#include <DSound.h>

//平台文件
#include "GameFrame.h"

//////////////////////////////////////////////////////////////////////////
//公共定义

//导出定义
#ifndef D3D_ENGINE_CLASS
	#ifdef  D3D_ENGINE_DLL
		#define D3D_ENGINE_CLASS _declspec(dllexport)
	#else
		#define D3D_ENGINE_CLASS _declspec(dllimport)
	#endif
#endif

//模块定义
#ifndef _DEBUG
	#define D3D_ENGINE_DLL_NAME		TEXT("D3DEngine.dll")				//组件名字
#else
	#define D3D_ENGINE_DLL_NAME		TEXT("D3DEngineD.dll")				//组件名字
#endif

//////////////////////////////////////////////////////////////////////////
//导出文件

#ifndef D3D_ENGINE_DLL
	#include "D3DFont.h"
	#include "D3DSound.h"
	#include "D3DEngine.h"
	#include "D3DDirect.h"
	#include "D3DDevice.h"
	#include "D3DSurface.h"
	#include "D3DTexture.h"
	#include "LapseCount.h"
	#include "VirtualEngine.h"
	#include "VirtualWindow.h"
	#include "VirtualButton.h"
#endif

//////////////////////////////////////////////////////////////////////////

#endif