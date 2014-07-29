#pragma once

//////////////////////////////////////////////////////////////////////////

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif

#ifndef WINVER				// 允许使用特定于 Windows XP 或更高版本的功能。
#define WINVER 0x0501		// 将此值更改为相应的值，以适用于 Windows 的其他版本。
#endif

#ifndef _WIN32_WINNT		// 允许使用特定于 Windows XP 或更高版本的功能。
#define _WIN32_WINNT 0x0501	// 将此值更改为相应的值，以适用于 Windows 的其他版本。
#endif						

#ifndef _WIN32_WINDOWS		// 允许使用特定于 Windows 98 或更高版本的功能。
#define _WIN32_WINDOWS 0x0410 // 将此值更改为适当的值，以指定将 Windows Me 或更高版本作为目标。
#endif

#ifndef _WIN32_IE			// 允许使用特定于 IE 6.0 或更高版本的功能。
#define _WIN32_IE 0x0600	// 将此值更改为相应的值，以适用于 IE 的其他版本。
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS

#define _AFX_ALL_WARNINGS

#include <afxwin.h> 
#include <afxext.h> 
#include <afxdisp.h>

#include <afxdtctl.h>
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>
#endif

//////////////////////////////////////////////////////////////////////////

//系统头文件
#include "Nb30.h"
#include "Afxmt.h"
#include "AfxHtml.h"
#include "AfxInet.h"

//全局头文件
#include "..\..\share\Constant.h"
#include "..\..\share\GlobalDef.h"
#include "..\..\share\GlobalField.h"
#include "..\..\share\GlobalFrame.h"
#include "..\..\share\GlobalRight.h"

//命令头文件
#include "..\..\msg\CMD_Game.h"
#include "..\..\msg\CMD_Plaza.h"
#include "..\..\msg\CMD_Video.h"

//模板库
#include "..\..\template\Template.h"

//组件头文件
#include "..\UserFace\UserFace.h"
#include "..\DownLoad\DownLoad.h"
#include "..\GameRank\GameRank.h"
#include "..\Companion\Companion.h"
#include "..\ChannelModule\ChannelModule.h"
#include "..\ClientShare\ClientShare.h"
#include "..\PropertyModule\PropertyModule.h"
#include "..\SkinControls\SkinControls.h"
#include "..\SkinResource\SkinResourceModule.h"
#include "..\..\common\NetworkService\NetworkServiceHead.h"
#include "..\..\common\ComService\ComService.h"

//////////////////////////////////////////////////////////////////////////
