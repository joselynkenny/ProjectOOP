/*
 * mygame.h: ���ɮ��x�C��������class��interface
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

	enum AUDIO_ID {				// �w�q�U�ح��Ī��s��
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
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	// �C��Member function��Implementation���n����
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
		int  Max(int a,int b,int c,int d,int e);
		void powerVERX(int map[KIRI][KANAN], int i);
		void powerVERY(int map[KIRI][KANAN], int i);
		void PowerActive(int map[KIRI][KANAN],int i,int k);
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
		CMovingBitmap box, green, red, blue, orange, purple, yellow, blue_ver, green_ver, red_ver, orange_ver, purple_ver, yellow_ver,
			blue_hor, green_hor, red_hor, orange_hor, purple_hor, yellow_hor;
		int map[KIRI][KANAN],power[KIRI][KANAN];
		int TotalCandy,ii,jj;
		bool on,swap;
		
		
	};
	class CBouncingBall;

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		const int		NUMBALLS;	// �y���`��
		CPractice		c_practice;
		CGameMap		gamemap;
		CMovingBitmap	backgrounds,box;	// �I����
		CMovingBitmap	practice;	// �I����
		int				picX, picY;
		CMovingBitmap	help;		// ������
		CBall			*ball;		// �y���}�C
		CMovingBitmap	corner;		// ������
		CEraser			eraser;		// ��l
		CInteger		hits_left;	// �ѤU��������
		CBouncingBall   bball;		// ���мu�����y

	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int counter;	// �˼Ƥ��p�ƾ�
	};

}
