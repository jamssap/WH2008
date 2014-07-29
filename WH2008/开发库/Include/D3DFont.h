#ifndef D3D_FOUNT_HEAD_FILE
#define D3D_FOUNT_HEAD_FILE

#include "D3DDevice.h"
#include "D3DTexture.h"
#include "D3DEngineHead.h"

//////////////////////////////////////////////////////////////////////////

//常量定义
#define MAX_GRAY_LEVEL				3									//灰度等级
#define MAX_BUFFER_COUNT			512									//缓冲数目

//////////////////////////////////////////////////////////////////////////

//字体子项
struct tagFontItem
{
	//字符信息
	UINT							uChar;								//字体编码
	CD3DTexture						D3DTexture;							//字体纹理

	//输出位置
	CSize							SizeCell;							//单元大小
	CSize							SizeFont;							//字体大小
	CPoint							PointOrigin;						//原点位置
};

//类型定义
typedef CArrayTemplate<tagFontItem *>	CFontItemPtrArray;						//字体数组
typedef CMap<UINT,UINT,tagFontItem *,tagFontItem *>	CFontItemPtrMap;	//字体索引

//////////////////////////////////////////////////////////////////////////

//字体管理
class D3D_ENGINE_CLASS CD3DFont
{
	//配置变量
protected:
	UINT							m_uGrayLevel;						//灰度等级
	UINT							m_uMaxBufferCount;					//缓冲数目

	//字体对象
protected:
	CFont							m_Font;								//字体对象
	TEXTMETRIC						m_TextMetric;						//字体属性

	//内核对象
protected:
	CFontItemPtrMap					m_FontItemPtrMap;					//字体索引
	CFontItemPtrArray				m_FontItemPtrActive;				//字体数组

	//函数定义
public:
	//构造函数
	CD3DFont();
	//析构函数
	virtual ~CD3DFont();

	//缓冲数目
public:
	//缓冲数目
	UINT GetMaxBufferCount() { return m_uMaxBufferCount; }
	//缓冲数目
	VOID SetMaxBufferCount(UINT uMaxBufferCount) { m_uMaxBufferCount=uMaxBufferCount; }

	//创建函数
public:
	//删除字体
	bool DeleteFont();
	//创建字体
	bool CreateFont(LOGFONT & LogFont, UINT uGrayLevel);
	//创建字体
	bool CreateFont(INT nPointSize, LPCTSTR lpszFaceName, UINT uGrayLevel);

	//输出字体
public:
	//输出字体
	bool DrawText(CD3DDevice * pD3DDevice, LPCTSTR pszString, CRect rcDraw,UINT uFormat, D3DCOLOR D3DColor);
	//输出字体
	bool DrawText(CD3DDevice * pD3DDevice, LPCTSTR pszString, INT nXPos, INT nYPos, UINT uFormat, D3DCOLOR D3DColor);

	//字体管理
private:
	//创建字体
	tagFontItem * ActiveFontItem(CD3DDevice * pD3DDevice, UINT uChar);
	//计算位置
	CSize CalePostion(CD3DDevice * pD3DDevice, LPCTSTR pszString, UINT uFormat, INT nAreaWidth);
};

//////////////////////////////////////////////////////////////////////////

#endif