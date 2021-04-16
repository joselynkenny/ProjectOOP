/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
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
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/

#include "CEraser.h"
#include "CBall.h"
#include "CBouncingBall.h"
#include "StagePlay.h"


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	/////////////////////////////////////////////////////////////////////////////
	// CGameStateInit
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								
		void OnBeginState();							
		void OnKeyUp(UINT, UINT, UINT); 				
		void OnLButtonDown(UINT nFlags, CPoint point);  
		void OnLButtonUp(UINT nFlags, CPoint point);
	protected:
		void OnShow();									
		void OnMove();
		void SetMusic(bool);
	private:
		CMovingBitmap BackgroundMenu, clickedPlayButton;
		CAnimation LogoCandy, LogoTiffy, LogoToffee, playButton;
		bool playBtnClicked, finishLoaded;
	};
	/////////////////////////////////////////////////////////////////////////////
	// CGameStateStart
	/////////////////////////////////////////////////////////////////////////////
	
	class CGameStateStart : public CGameState {
	public:
		CGameStateStart(CGame *g);
		~CGameStateStart();
		void OnInit();  				
		void OnBeginState();
		void OnKeyUp(UINT, UINT, UINT);
		void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
		void OnLButtonUp(UINT nFlags, CPoint point);
		void OnLButtonDown(UINT nFlags, CPoint point);
		void OnMouseMove(UINT nFlags, CPoint point);
		void SetUp(bool status);
		void SetDown(bool status);
		
	protected:
		void OnShow();	
		void OnMove();
	private:
		void ShowStageButton(int, int, int, int);
		CMovingBitmap StageStart, stageButton[5];
		int scroll_Y,area,Level[2][2];;
		bool scroll,TapUp,TapDown;
		int StagePos[15][2];
		CInteger stageNum;
		LONG clickVertical, clickHorizontal, clickScroll;
		int mouseDisplayment, inertia;
	};
	
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////
	class CPractice {
	public:
		CPractice();
		void LoadBitmap();
		void OnMove();
		void OnShow();
	private:
		CMovingBitmap pic;
		int x, y;
	};

	class CGameMap
	{
	public:
		CGameMap();
		CGameMap* CGameMap::Click();
		void LoadBitmaps();
		void OnShow();
		void OnMove();
		void OnKeyDown(UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);
		void OnLButtonUp(UINT nFlags, CPoint point);
		void RandomBouncingBall();
		bool threecandy(int map[5][8]);
		bool fourcandy(int map[5][8]);
		bool fivecandy(int map[5][8]);
		bool dropcandy(int map[5][8]);
		void InitializeBouncingBall(int, int, int);
		bool Friend(int ii, int jj, int i, int j);
		bool OnClick(const CPoint& point, CMovingBitmap& button);
		~CGameMap();
	protected:
		const int X, Y;
		const int MW, MH;
		CBouncingBall* bballs;
		int random_num;
		
	private:
		//vector<StagePlay*> TotalCandy;
		CMovingBitmap box, green, red, blue, orange, purple, yellow,
					  blue_clicked, green_clicked, red_clicked, orange_clicked, purple_clicked, yellow_clicked,
					  blue_ver, green_ver, red_ver, orange_ver, purple_ver, yellow_ver;
		int map[5][8];
		int TotalCandy, ii, jj;
		bool on, swap, candyClicked;	
	};
	class CBouncingBall;

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		const int		NUMBALLS;	// 球的總數
		CPractice		c_practice;
		CGameMap		gamemap;
		CMovingBitmap	backgrounds,box;	// 背景圖
		CMovingBitmap	practice;	// 背景圖
		int				picX, picY;
		CMovingBitmap	help;		// 說明圖
		CBall			*ball;		// 球的陣列
		CMovingBitmap	corner;		// 角落圖
		CEraser			eraser;		// 拍子
		CInteger		hits_left;	// 剩下的撞擊數
		CBouncingBall   bball;		// 反覆彈跳的球

	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;	// 倒數之計數器
	};

}
