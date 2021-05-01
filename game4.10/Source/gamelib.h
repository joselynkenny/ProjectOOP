/*
 * gamelib.h: ¥»ÀÉ®×Àx¹CÀ¸¬ÛÃöªºclassªºinterface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *		1. Add ENABLE_AUDIO flag.
 *   2004-03-02 V4.0
 *		1. Add CInteger class.
 *      2. Add CGameState abstract class and adjust CGame to apply
 *         state pattern for switching game states.
 *   2004-03-08 V4.1
 *      1. Add OPEN_AS_FULLSCREEN flag.
 *      2. The Game Engine now becomes a framework.
 *   2005-07-28
 *      1. Add GAME_ASSERT macro to display run time errors gracefully.
 *      2. Remove CDDarw::CheckSystem(). It is useless.
 *   2005-09-08
 *      1. Eliminate CSpecialEffect::Abort. It is useless now.
 *      2. Add SHOW_GAME_CYCLE_TIME flag.
 *      3. Add DEFAULT_BG_COLOR flag;
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add MOUSEMOVE Handler for CGame and CGameState.
 *      2. Add _TRACE preprocessor flag for VC++.net.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Remove constantness of CAnimation::DELAY_COUNT.
 *      3. Enhance CAnimation to support SetDelayCount(), Reset(), and IsFinalBitmap().
 *      4. Remove CAnimation::GetLocation() and CMovingBitmap::GetLocation().
 *      5. Bitmap coordinate can no longer be set by CMovingBitmap::LoadBitmap().
 *         Defauts to (0,0).
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *      2. Fix bug: audio is now correctly recovered after a sleep or suspension of windows.
 *      3. Support ENABLE_GAME_PAUSE.
 *   2008-02-15 V4.4
 *      1. Add setup project for Visual studio 2005.
 *      2. Support bitmap scaling when ShowBitmap(scale) is called.
 *      3. Add namespace game_framework.
 *      4. Make the class CGame a singleton so that MFC can access it easily.
 *      5. Support loading of bitmap from bmp file.
 *      6. Support ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Rewrite CAudio with MCI commands to eliminate dependency with DirectMusic.
*/

/////////////////////////////////////////////////////////////////////////////
// ©w¸q¹CÀ¸¥i³]©wªºÀô¹Ò»P±ø¥ó
/////////////////////////////////////////////////////////////////////////////

#define SIZE_X				 1280		// ³]©w¹CÀ¸µe­±ªº¸ÑªR«×¬°640x480
#define SIZE_Y				 720		// µù¡G­Y¤£¨Ï¥Î¼Ð·Çªº¸ÑªR«×¡A«h¤£¯à¤Á´«¨ì¥þ¿Ã¹õ
#define OPEN_AS_FULLSCREEN	 false		// ¬O§_¥H¥þ¿Ã¹õ¤è¦¡¶}±Ò¹CÀ¸
#define SHOW_LOAD_PROGRESS   true		// ¬O§_Åã¥Üloading(OnInit)ªº¶i«×
#define DEFAULT_BG_COLOR	 RGB(0,0,0)	// ¹CÀ¸µe­±¹w³]ªº­I´ºÃC¦â(¶Â¦â)
#define GAME_CYCLE_TIME		 33		    // ¨C33ms¶]¤@¦¸Move¤ÎShow(¨C¬í30¦¸)
#define SHOW_GAME_CYCLE_TIME false		// ¬O§_¦bdebug modeÅã¥Ücycle time
#define ENABLE_GAME_PAUSE	 true		// ¬O§_¤¹³\¥H Ctrl-Q ¼È°±¹CÀ¸
#define ENABLE_AUDIO		 true		// ±Ò°Ê­µ®Ä¤¶­±
#define KIRI				 5
#define KANAN				 8

/////////////////////////////////////////////////////////////////////////////
// ©w¸qCGame¤ÎCGameState©Ò¨Ï¥Îªº¤T­Óª¬ºA±`¼Æ
/////////////////////////////////////////////////////////////////////////////

enum GAME_STATES {
	GAME_STATE_INIT,
	GAME_STATE_START,
	GAME_STATE_RUN,
	GAME_STATE_OVER
};

/////////////////////////////////////////////////////////////////////////////
// Header for STL (Standard Template Library)
/////////////////////////////////////////////////////////////////////////////

#include <list>
#include <vector>
#include <map>
using namespace std;
#include "Stage.h"


/////////////////////////////////////////////////////////////////////////////
// ¦^³øµ{¦¡¿ù»~¥Îªºmacro
// ³Æµù¡G³o¸Ì¨Ï¥Îmacro¥H«K«O¯dÀÉ®×¦WºÙ¤Î¦æ¸¹¡A§Q©ódebug¡C
/////////////////////////////////////////////////////////////////////////////

#define GAME_ASSERT(boolexp,str)											\
		if (!(boolexp)) {													\
			int id;															\
			char s[300]="";													\
			sprintf(s,"Game fatal error:\n\n%s\n\nFile: %s\n\nLine: %d"		\
				"\n\n(Press Retry to debug the application, "				\
				"if it is executed in debug mode.)"							\
				"\n(Press Cancel otherwise.)",								\
				 str , __FILE__,__LINE__);									\
			id = AfxMessageBox(s, MB_RETRYCANCEL);							\
			if (id == IDCANCEL)												\
				exit(1);													\
			AfxDebugBreak();												\
		}

namespace game_framework {

/////////////////////////////////////////////////////////////////////////////
// ³o­Óclass´£¨Ñ®É¶¡¡B¿ù»~µ¥±±¨î
// ¤@¯ëªº¹CÀ¸¨Ã¤£»Ýª½±µ¾Þ§@³o­Óª«¥ó¡A¦]¦¹¥i¥H¤£ºÞ³o­Óclassªº¨Ï¥Î¤èªk
/////////////////////////////////////////////////////////////////////////////

class CSpecialEffect {
public:
	static void  SetCurrentTime();					// Àx¦s¥Ø«eªº®É¶¡¦Üctime
	static DWORD GetEllipseTime();					// Åª¨ú¥Ø«eªº®É¶¡ - ctime
	static int   GetCurrentTimeCount();				// Åª¨úÀx¦sctimeªº¦¸¼Æ
	static void  Delay(DWORD ms);					// ©µ¿ð x ms
	static void  DelayFromSetCurrentTime(DWORD ms);	// ¦Ûctime°_ºâ¡A©µ¿ð x ms
private:
	static DWORD ctime;
	static int	 ctimeCount;
};

/////////////////////////////////////////////////////////////////////////////
// ³o­Óclass·|«Ø¥ßDirectDrawª«¥ó¡A¥H´£¨Ñ¨ä¥Lclass¨Ï¥Î
// ¤@¯ëªº¹CÀ¸¨Ã¤£»Ýª½±µ¾Þ§@³o­Óª«¥ó¡A¦]¦¹¥i¥H¤£ºÞ³o­Óclassªº¨Ï¥Î¤èªk
/////////////////////////////////////////////////////////////////////////////

class CDDraw {
	friend class CMovingBitmap;
public:
	~CDDraw();
	static void  BltBackColor(DWORD);		// ±NBack plain¥þ³¡µÛ¤W«ü©wªºÃC¦â
	static void  BltBackToPrimary();		// ±NBack plain¶K¦ÜPrimary plain
	static CDC*  GetBackCDC();				// ¨ú±oBack PlainªºDC (device context)
	static void  GetClientRect(CRect &r);	// ¨ú±o³]©wªº¸ÑªR«×
	static void  Init(int, int);			// Initialize direct draw
	static void  ReleaseBackCDC();			// ©ñ±¼Back PlainªºDC (device context)
	static bool  SetFullScreen(bool);		// ³]©w¬°¥þ¿Ã¹õ¼Ò¦¡/µøµ¡¼Ò¦¡
	static bool  IsFullScreen();			// ¦^µª¬O§_¬°¥þ¿Ã¹õ¼Ò¦¡/µøµ¡¼Ò¦¡
private:
	CDDraw();								// private constructor
	static void  BltBitmapToBack(unsigned SurfaceID, int x, int y);
	static void  BltBitmapToBack(unsigned SurfaceID, int x, int y, double factor);
	static void  BltBitmapToBitmap(unsigned SourceID, unsigned TargetID, int x, int y);
	static void	 CheckDDFail(char *s);
	static bool  CreateSurface();
	static bool  CreateSurfaceFullScreen();
	static bool  CreateSurfaceWindowed();
	static void  LoadBitmap(int i, int IDB_BITMAP);
	static void  LoadBitmap(int i, char *filename);
	static DWORD MatchColorKey(LPDIRECTDRAWSURFACE lpDDSurface, COLORREF color);
	static int   RegisterBitmap(int IDB_BITMAP, COLORREF ColorKey);
	static int   RegisterBitmap(char *filename, COLORREF ColorKey);
	static void  ReleaseSurface();
	static void  RestoreSurface();
	static void  SetColorKey(unsigned SurfaceID, COLORREF color);
    static HDC					hdc;
	static CDC					cdc;
	static CView				*pCView;
    static LPDIRECTDRAW2		lpDD;
	static LPDIRECTDRAWCLIPPER	lpClipperPrimary;   
	static LPDIRECTDRAWCLIPPER	lpClipperBack;   
	static LPDIRECTDRAWSURFACE	lpDDSPrimary;
	static LPDIRECTDRAWSURFACE	lpDDSBack;
	static vector<LPDIRECTDRAWSURFACE>	lpDDS;
    static HRESULT				ddrval;
	static vector<int>			BitmapID;
	static vector<string>		BitmapName;
	static vector<CRect>		BitmapRect;
	static vector<COLORREF>		BitmapColorKey;
	static bool					fullscreen;
	static CDDraw				ddraw;
	static int					size_x, size_y;
};

/////////////////////////////////////////////////////////////////////////////
// ³o­Óclass´£¨Ñ°ÊºA(¥i¥H²¾°Ê)ªº¹Ï§Î
// ¨C­ÓPublic Interfaceªº¥Îªk³£­nÀ´¡AImplementation¥i¥H¤£À´
/////////////////////////////////////////////////////////////////////////////

class CMovingBitmap {
public:
	CMovingBitmap();
	int   Height();						// ¨ú±o¹Ï§Îªº°ª«×
	int   Left();						// ¨ú±o¹Ï§Îªº¥ª¤W¨¤ªº x ®y¼Ð
	void  LoadBitmap(int, COLORREF=CLR_INVALID);		// ¸ü¤J¹Ï¡A«ü©w¹Ïªº½s¸¹(resource)¤Î³z©ú¦â
	void  LoadBitmap(char *, COLORREF=CLR_INVALID);	// ¸ü¤J¹Ï¡A«ü©w¹ÏªºÀÉ¦W¤Î³z©ú¦â
	void  LoadBitmap(string&, COLORREF = CLR_INVALID);
	void  SetTopLeft(int,int);			// ±N¹Ïªº¥ª¤W¨¤®y¼Ð²¾¦Ü (x,y)
	void  ShowBitmap();					// ±N¹Ï¶K¨ì¿Ã¹õ
	void  ShowBitmap(double factor);	// ±N¹Ï¶K¨ì¿Ã¹õ factor < 1®ÉÁY¤p¡A>1®É©ñ¤j¡Cª`·N¡G»Ý­nVGA¥dµwÅéªº¤ä´©¡A§_«h·|«ÜºC
	void  ShowBitmap(CMovingBitmap &);	// ±N¹Ï¶K¨ì¨ì¥t¤@±i¹Ï¤W (¶È¨Ñ¯S®í¥Î³~)
	int   Top();						// ¨ú±o¹Ï§Îªº¥ª¤W¨¤ªº y ®y¼Ð
	int   Width();						// ¨ú±o¹Ï§Îªº¼e«×
protected:
	CRect    location;			// location of the bitmap
	bool     isBitmapLoaded;	// whether a bitmap has been loaded
	unsigned SurfaceID;			// the surface id of this bitmap
};

/////////////////////////////////////////////////////////////////////////////
// ³o­Óclass´£¨Ñ¥i¥H²¾°Êªº°Êµe
// ¨C­ÓPublic Interfaceªº¥Îªk³£­nÀ´¡AImplementation¥i¥H¤£À´
/////////////////////////////////////////////////////////////////////////////

class CAnimation {
public:
	CAnimation(int = 10, bool cycle = true);				// Constructor (預設動畫播放頻率每1/3秒換一張圖)
	void  AddBitmap(int, COLORREF = CLR_INVALID);
	// 增加一張圖形至動畫(圖的編號及透明色)
	void  AddBitmap(char *, COLORREF = CLR_INVALID);
	// 增加一張圖形至動畫(圖的編號及透明色)
	int   GetCurrentBitmapNumber();	// 取得正在撥放的bitmap是第幾個bitmap
	int   Height();					// 取得動畫的高度
	bool  IsFinalBitmap();			// 回傳正在撥放的bitmap是否為最後一個bitmap
	int   Left();					// 取得動畫的左上角的 x 座標
	void  OnMove();					// 依頻率更換bitmap
	void  OnShow();					// 將動畫貼到螢幕
	void  Reset();					// 重設播放順序回到第一張圖形
	void  SetCycle(bool);
	void  SetDelayCount(int);		// 設定動畫播放速度的常數(越大越慢)
	void  SetTopLeft(int, int);		// 將動畫的左上角座標移至 (x,y)
	int   Top();					// 取得動畫的左上角的 y 座標
	int   Width();					// 取得動畫的寬度
private:
	list<CMovingBitmap>				bmp;			// list of CMovingBitmap
	list<CMovingBitmap>::iterator	bmp_iter;		// list iterator
	int								bmp_counter;	// 儲存bmp_iter為第n個bmp
	int								delay_counter;	// 延緩動畫播放速度的計數器
	int								delay_count;	// 動畫播放速度的常數
	int								x, y;			// 動畫的座標
	bool							cycle;			// Animation will stop at last bmp if cycle = false
};

/////////////////////////////////////////////////////////////////////////////
// ³o­Óclass´£¨ÑÅã¥Ü¾ã¼Æ¹Ï§Îªº¯à¤O
// ¨C­ÓPublic Interfaceªº¥Îªk³£­nÀ´¡AImplementation¥i¥H¤£À´
/////////////////////////////////////////////////////////////////////////////

class CInteger {
	friend int operator+(const CInteger& lhs, const CInteger& rhs);
	friend int operator-(const CInteger& lhs, const CInteger& rhs);
	friend int operator*(const CInteger& lhs, const CInteger& rhs);
	friend int operator/(const CInteger& lhs, const CInteger& rhs);
	friend bool operator==(const CInteger& lhs, const CInteger& rhs);
	friend bool operator<(const CInteger& lhs, const CInteger& rhs);
	friend bool operator<=(const CInteger& lhs, const CInteger& rhs);
	friend bool operator>(const CInteger& lhs, const CInteger& rhs);
	friend bool operator>=(const CInteger& lhs, const CInteger& rhs);
public:
	CInteger();
	CInteger(int);
	CInteger(double);
	int  GetInteger();			
	void LoadBitmap();			
	void operator+=(const int rhs);
	void operator++(int);
	void operator++();
	void operator-=(const int rhs);
	void operator--(int);
	void operator--();
	void operator*=(const int rhs);
	void operator/=(const int rhs);
	void operator=(const int rhs);
	void SetInteger(int);		
	void SetTopLeft(int, int);	
	void ShowBitmap();			
	void SetDigit(int digit);   
	void SetType(int Type);
private:
	int NUMDIGITS;			// 共顯示NUMDIGITS個位數
	static CMovingBitmap digit[44]; // 儲存0..9及負號之圖形(bitmap)
	int x, y;						// 顯示的座標
	int n;							// 整數值
	bool isBmpLoaded;				// 是否已經載入圖形
	int type;
};

/////////////////////////////////////////////////////////////////////////////
// «Å§i©|¥¼©w¸qªºclass
/////////////////////////////////////////////////////////////////////////////

class CGame;
class CGameStateInit;
class CGameStateStart;
class CGameStateRun;
class CGameStateOver;

/////////////////////////////////////////////////////////////////////////////
// ³o­Óclass¬°¹CÀ¸ªº¦UºØª¬ºA¤§Base class(¬O¤@­Óabstract class)
// ¨C­ÓPublic Interfaceªº¥Îªk³£­nÀ´¡AImplementation¥i¥H¤£À´
/////////////////////////////////////////////////////////////////////////////


class CGameState {
public:
	CGameState(CGame *g);
	void OnDraw();			// Template Method
	void OnCycle();			// Template Method
	bool OnClick(const CPoint& point, CMovingBitmap& button);
	//
	// virtual functions, ¥ÑÄ~©ÓªÌ´£¨Ñimplementation
	//
	virtual ~CGameState() {}								// virtual destructor
	virtual void OnBeginState() {}							// ³]©w¨C¦¸¶i¤J³o­Óª¬ºA®É©Ò»Ýªºªì­È
	virtual void OnInit() {}								// ª¬ºAªºªì­È¤Î¹Ï§Î³]©w
	virtual void OnKeyDown(UINT, UINT, UINT) {}				// ³B²zÁä½LDownªº°Ê§@
	virtual void OnKeyUp(UINT, UINT, UINT) {}				// ³B²zÁä½LUpªº°Ê§@
	virtual void OnLButtonDown(UINT nFlags, CPoint point) {}// ³B²z·Æ¹«ªº°Ê§@
	virtual void OnLButtonUp(UINT nFlags, CPoint point) {}	// ³B²z·Æ¹«ªº°Ê§@
	virtual void OnMouseMove(UINT nFlags, CPoint point) {}  // ³B²z·Æ¹«ªº°Ê§@ 
	virtual void OnRButtonDown(UINT nFlags, CPoint point) {}// ³B²z·Æ¹«ªº°Ê§@
	virtual void OnRButtonUp(UINT nFlags, CPoint point) {}	// ³B²z·Æ¹«ªº°Ê§@
	static bool sound, music;
protected:
	void GotoGameState(int state);							// ¸õÅD¦Ü«ü©wªºstate
	void ShowInitProgress(int percent);						// Åã¥Üªì©l¤Æªº¶i«×
	bool ButtonOnClick(const CPoint& point, CMovingBitmap& button);
	bool ButtonOnClick(const CPoint& point, CAnimation& button);

	virtual void OnMove() {}								// ²¾°Ê³o­Óª¬ºAªº¹CÀ¸¤¸¯À
	virtual void OnShow() = 0;								// Åã¥Ü³o­Óª¬ºAªº¹CÀ¸µe­±
	virtual void SetMusic(bool) {};
	
	CGame *game;
	static Area gameArea;								// 游戲的主要控制
	static vector<Stage*> stages;							// 游戲中所有關卡資料
	static int current_stage;								// 當前/上一次玩過的關卡
	static int MAX_STAGE;

};

/////////////////////////////////////////////////////////////////////////////
// ³o­Óclass¬O¹CÀ¸ªº®Ö¤ß¡A±±¨î¹CÀ¸ªº¶i¦æ
// ¤@¯ëªº¹CÀ¸¨Ã¤£»Ýª½±µ¾Þ§@³o­Óª«¥ó¡A¦]¦¹¥i¥H¤£ºÞ³o­Óclassªº¨Ï¥Î¤èªk
/////////////////////////////////////////////////////////////////////////////

class CGame {
public:
	CGame();										// Constructor
	~CGame();										// Destructor
	bool IsRunning();								// Åª¨ú¹CÀ¸¬O§_¥¿¦b¶i¦æ¤¤
	void OnDraw();									// ¹ïÀ³CGameViewªºOnDraw()
	void OnFilePause();								// ¹CÀ¸¼È°±
	void OnInit();									// ¹CÀ¸Ã¸¹Ï¤Î­µ®Äªºªì©l¤Æ
	void OnInitStates();							// ¹CÀ¸¦Uª¬ºAªºªì­È¤Î¹Ï§Î³]©w
	bool OnIdle();									// ¹CÀ¸ªº¥D°j°é
	void OnKeyDown(UINT, UINT, UINT);				// ³B²zÁä½LDownªº°Ê§@
	void OnKeyUp(UINT, UINT, UINT);					// ³B²zÁä½LUpªº°Ê§@
	void OnKillFocus();								// ¹CÀ¸³Q­¢¼È°±
	void OnLButtonDown(UINT nFlags, CPoint point);	// ³B²z·Æ¹«ªº°Ê§@
	void OnLButtonUp(UINT nFlags, CPoint point);	// ³B²z·Æ¹«ªº°Ê§@
	void OnMouseMove(UINT nFlags, CPoint point);    // ³B²z·Æ¹«ªº°Ê§@ 
	void OnRButtonDown(UINT nFlags, CPoint point);	// ³B²z·Æ¹«ªº°Ê§@
	void OnRButtonUp(UINT nFlags, CPoint point);	// ³B²z·Æ¹«ªº°Ê§@
	void OnResume();								// ³B²z¦Û¡u«Ý©R¡vÁÙ­ìªº°Ê§@
	void OnSetFocus();								// ³B²zFocus
	void OnSuspend();								// ³B²z¡u«Ý©R¡vªº°Ê§@
	void SetGameState(int);
	static CGame *Instance();
private:
	bool			running;			// ¹CÀ¸¬O§_¥¿¦b¶i¦æ¤¤(¥¼³QPause)
	bool            suspended;			// ¹CÀ¸¬O§_³Qsuspended
	const int		NUM_GAME_STATES;	// ¹CÀ¸ªºª¬ºA¼Æ(3­Óª¬ºA)
	CGameState		*gameState;			// pointer«ü¦V¥Ø«eªº¹CÀ¸ª¬ºA
	CGameState		*gameStateTable[4];	// ¹CÀ¸ª¬ºAª«¥óªºpointer
	static CGame	instance;			// ¹CÀ¸°ß¤@ªºinstance
};

}