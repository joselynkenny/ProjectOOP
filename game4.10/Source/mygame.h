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

#include <set>
#include "Candy.h"
#include "Stage.h"
#include "ScoreBoard.h"
#include "Area.h"

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
		int GetDigit(int n);
		
	protected:
		void OnShow();	
		void OnMove();
		
	private:
		void ShowStageButton(int, int, int, int);
		void ShowStars(int, int, int);
		CMovingBitmap star1, star2, star3, comingSoon;
		CInteger stageNum;
		CMovingBitmap StageStart, stageButton[5];
		int scroll_Y, area, Level[2][2];;
		bool scroll,TapUp,TapDown;
		int StagePos[15][2];
		LONG clickVertical, clickHorizontal, clickScroll;
		int mouseDisplayment, inertia;
	};
	
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////
	
	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);						
		~CGameStateRun();
		void OnBeginState();							
		void OnInit();  								
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  
		void OnLButtonUp(UINT nFlags, CPoint point);	
	protected:
		void OnMove();									
		void OnShow();									

	private:
		CMovingBitmap	background;	
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();
		void OnLButtonDown(UINT nFlags, CPoint point);			
		void OnLButtonUp(UINT nFlags, CPoint point);			
		void OnInit();
	protected:
		void OnMove();									
		void OnShow();									
		int GetDigit(int);								
	private:
		void ShowButtons();
		void ShowStars(int, int, int);

		int counter, stageNum;	
		bool isFail;
		CMovingBitmap backgroundOver;	
		CMovingBitmap scoreBoardOver;
		CInteger currentScore;
		CInteger currentStage;
		CMovingBitmap redStar, greenStar, yellowStar, emptyStar, failed;
		CMovingBitmap exitButtonClicked, nextButtonClicked, retryButtonClicked;
		CAnimation exitButton, nextButton, retryButton;
		bool exitBtnClicked, nextBtnClicked, retryBtnClicked;
	};

}
