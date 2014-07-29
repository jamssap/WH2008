#ifndef D3D_ENGINE_HEAD_FILE
#define D3D_ENGINE_HEAD_FILE

#include "D3DDevice.h"
#include "D3DTexture.h"
#include "VirtualWindow.h"
#include "D3DEngineHead.h"

//////////////////////////////////////////////////////////////////////////

//游戏引擎
class D3D_ENGINE_CLASS CD3DEngine
{
	//函数定义
public:
	//构造函数
	CD3DEngine();
	//析构函数
	virtual ~CD3DEngine();
};

//////////////////////////////////////////////////////////////////////////

#endif