#ifndef D3D_SOUND_HEAD_FILE
#define D3D_SOUND_HEAD_FILE

#include "D3DEngineHead.h"

//////////////////////////////////////////////////////////////////////////

//声音信息
struct tagWaveDataInfo
{
	DWORD							dwWaveSize;							//数据大小
	LPVOID							pcbWaveData;						//数据指针
	WAVEFORMATEX					WaveFormatEx;						//声音格式
};

//////////////////////////////////////////////////////////////////////////

//声音对象
class D3D_ENGINE_CLASS CD3DSound
{
	//接口变量
public:
	IDirectSound *					m_pIDirectSound;					//设备对象

	//静态变量
public:
	static CD3DSound *				m_pD3DSound;						//对象指针

	//函数定义
public:
	//构造函数
	CD3DSound();
	//析构函数
	virtual ~CD3DSound();

	//功能函数
public:
	//创建环境
	bool CreateD3DSound(HWND hWnd);

	//声音管理
public:
	//加载声音
	bool LoadSoundResource(LPCTSTR pszFileName);
	//加载声音
	bool LoadSoundResource(HINSTANCE hInstance, LPCTSTR pszResource, LPCTSTR pszTypeName);

	//辅助函数
private:
	//声音属性
	bool GetWaveDataInfo(LPVOID pDataBuffer, tagWaveDataInfo & WaveDataInfo);
	//填充缓冲
	bool FillSoundBuffer(IDirectSoundBuffer * pDSBuffer, VOID * pSoundData, DWORD dwSoundSize);

	//创建缓冲
private:
	//创建缓冲
	bool CreateSoundBuffer(IDirectSoundBuffer * * pDSBuffer, tagWaveDataInfo & WaveDataInfo, DWORD dwFlags);
	//创建缓冲
	bool CreateSoundBuffer(IDirectSoundBuffer * * pDSBuffer, INT nChannels, INT nSecs, DWORD nSamplesPerSec, WORD wBitsPerSample, DWORD dwFlags);

	//静态函数
public:
	//获取对象
	static CD3DSound * GetInstance() { return m_pD3DSound; }
};

//////////////////////////////////////////////////////////////////////////

#endif