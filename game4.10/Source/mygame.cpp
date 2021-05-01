/*
 * mygame.cpp: ���ɮ��x�C��������class��implementation
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
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <stdlib.h>
#include <ddraw.h>
#include <set>
#include <string.h>
#include <string>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include <iostream>
#include <algorithm>

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// CGameStateInit
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
	playBtnClicked = finishLoaded = false;
}

void CGameStateInit::OnInit()
{
	ShowInitProgress(0);	
	//BackgroundMenu
	BackgroundMenu.LoadBitmap("Bitmaps\\InitBackground.bmp");

	CAudio::Instance()->Load(AUDIO_STAGE, "sounds\\Overworld_Level_Select.mp3");
	CAudio::Instance()->Load(AUDIO_BTN_CLICK, "sounds\\button_press.wav");
	CAudio::Instance()->Load(AUDIO_BTN_RELEASE, "sounds\\button_release.wav");
	
	int playBtnBmp[] = { IDB_PLAYBUTTON_1, IDB_PLAYBUTTON_2, IDB_PLAYBUTTON_3, IDB_PLAYBUTTON_4,
						 IDB_PLAYBUTTON_5, IDB_PLAYBUTTON_6, IDB_PLAYBUTTON_7, IDB_PLAYBUTTON_8,
						 IDB_PLAYBUTTON_9, IDB_PLAYBUTTON_10, IDB_PLAYBUTTON_11, IDB_PLAYBUTTON_12};

	for (int i = 0; i < 12; i++) {
		playButton.AddBitmap(playBtnBmp[i], RGB(0, 0, 0));
	}

	playButton.SetDelayCount(4);
	clickedPlayButton.LoadBitmap("Bitmaps\\PlayButtonClicked.bmp", RGB(0, 0, 0));
	
	//LogoTiffy
	int LogoTiffy_list[] = { IDB_LOGOTIFFY0, IDB_LOGOTIFFY1, IDB_LOGOTIFFY2, IDB_LOGOTIFFY3, IDB_LOGOTIFFY4, IDB_LOGOTIFFY5, IDB_LOGOTIFFY6, IDB_LOGOTIFFY7, IDB_LOGOTIFFY8,IDB_LOGOTIFFY9,
		IDB_LOGOTIFFY8, IDB_LOGOTIFFY7, IDB_LOGOTIFFY6, IDB_LOGOTIFFY5, IDB_LOGOTIFFY4, IDB_LOGOTIFFY3, IDB_LOGOTIFFY2, IDB_LOGOTIFFY1, IDB_LOGOTIFFY0 };
	
	for (int i = 0; i < 19; i++) {
		LogoTiffy.AddBitmap(LogoTiffy_list[i], RGB(255, 255, 255));
	}

	LogoTiffy.SetDelayCount(4);

	//LogoToffee
	int LogoToffee_list[] = { IDB_LOGOTOFFEE1, IDB_LOGOTOFFEE2, IDB_LOGOTOFFEE3, IDB_LOGOTOFFEE4, IDB_LOGOTOFFEE5, IDB_LOGOTOFFEE6,
		IDB_LOGOTOFFEE5, IDB_LOGOTOFFEE4, IDB_LOGOTOFFEE3, IDB_LOGOTOFFEE2, IDB_LOGOTOFFEE1};
	
	for (int i = 0; i < 11; i++) {
		LogoToffee.AddBitmap(LogoToffee_list[i], RGB(255, 255, 255));
	}

	LogoToffee.SetDelayCount(3);
	Sleep(300);	

	//LogoCandy
	int LogoCandy_list[] = { IDB_LOGOCANDY1, IDB_LOGOCANDY2, IDB_LOGOCANDY3, IDB_LOGOCANDY4, IDB_LOGOCANDY5, IDB_LOGOCANDY6, IDB_LOGOCANDY7, IDB_LOGOCANDY8,IDB_LOGOCANDY9, IDB_LOGOCANDY10,
		IDB_LOGOCANDY11, IDB_LOGOCANDY12, IDB_LOGOCANDY13, IDB_LOGOCANDY14, IDB_LOGOCANDY15, IDB_LOGOCANDY16, IDB_LOGOCANDY17, IDB_LOGOCANDY18, IDB_LOGOCANDY19, IDB_LOGOCANDY20,
		IDB_LOGOCANDY19, IDB_LOGOCANDY18, IDB_LOGOCANDY17, IDB_LOGOCANDY16, IDB_LOGOCANDY15, IDB_LOGOCANDY14, IDB_LOGOCANDY13, IDB_LOGOCANDY12, IDB_LOGOCANDY11, IDB_LOGOCANDY10,
		IDB_LOGOCANDY11, IDB_LOGOCANDY12, IDB_LOGOCANDY13, IDB_LOGOCANDY14, IDB_LOGOCANDY15, IDB_LOGOCANDY16, IDB_LOGOCANDY17,IDB_LOGOCANDY16, IDB_LOGOCANDY15, IDB_LOGOCANDY14,
		IDB_LOGOCANDY13, IDB_LOGOCANDY12, IDB_LOGOCANDY11, IDB_LOGOCANDY10, IDB_LOGOCANDY9, IDB_LOGOCANDY8 };
	
	for (int i = 0; i < 46; i++) {
		LogoCandy.AddBitmap(LogoCandy_list[i], RGB(255, 255, 255));
	}

	LogoCandy.SetDelayCount(1);
	LogoCandy.SetCycle(false);

	finishLoaded = true;
	OnBeginState();
}

void CGameStateInit::OnBeginState()
{
	if (finishLoaded) {
		LogoCandy.Reset();
		playBtnClicked = false;	
		if (music) {
			CAudio::Instance()->Play(AUDIO_STAGE, true);
		}
	}
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';
	//if (nChar == KEY_SPACE)
		//GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
	//else if (nChar == KEY_ESC)								// Demo �����C������k
		//PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// �����C��
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(ButtonOnClick(point, playButton)) {
		playBtnClicked = true;
	} else {
		playBtnClicked = false;
	}
}

void CGameStateInit::OnLButtonUp(UINT nFlags, CPoint point) {
	if (ButtonOnClick(point, playButton)) {
		GotoGameState(GAME_STATE_START);
	}
	else {
		playBtnClicked = false;
	}
}

void CGameStateInit::OnMove() {
	LogoCandy.OnMove();

	if (!playBtnClicked)
		playButton.OnMove();

	LogoTiffy.OnMove();
	LogoToffee.OnMove();
}

void CGameStateInit::OnShow()
{
	//BackgroundMenu

	BackgroundMenu.SetTopLeft(0,0);
	BackgroundMenu.ShowBitmap();

	//LogoCandy
	LogoCandy.SetTopLeft(250, -50);
	LogoCandy.OnShow();

	//LogoTiffy
	LogoTiffy.SetTopLeft(95, 400);
	LogoTiffy.OnShow();

	//LogoToffee
	LogoToffee.SetTopLeft(700, 60);
	LogoToffee.OnShow();

	//PlayButton
	if (playBtnClicked)	{
		clickedPlayButton.SetTopLeft(SIZE_X / 2 - playButton.Width() / 2, SIZE_Y / 5 * 4 - playButton.Height());
		clickedPlayButton.ShowBitmap();
	} else {
		playButton.SetTopLeft(SIZE_X / 2 - playButton.Width() / 2, SIZE_Y / 5 * 4 - playButton.Height());
		playButton.OnShow();
	}

}	

void CGameStateInit::SetMusic(bool music)
{
	this->music = music;

	if (music)
		CAudio::Instance()->Play(AUDIO_STAGE, true);
	else
		CAudio::Instance()->Stop(AUDIO_STAGE);
}

/////////////////////////////////////////////////////////////////////////////
// CGameStateStart
/////////////////////////////////////////////////////////////////////////////

CGameStateStart::CGameStateStart(CGame *g)
	: CGameState(g),scroll(false),area(0),mouseDisplayment(0), inertia(0)
{
	TapUp = false; TapDown = false;
	scroll_Y = -3600;

	int Pos[][2] = { {270,4030},{495,3980},{530,3850},{320,3870},{135,3910},
						 {135,3750},{340,3690},{570,3720},{770,3800},{960,3840},
						 {1085,3750},{1010,3600},{760,3540},{520,3590},{280,3585} };
	
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 2; j++) {
			StagePos[i][j] = Pos[i][j];
		}
	}
	
}

CGameStateStart::~CGameStateStart()
{
	for (unsigned i = 0; i < stages.size(); i++) {
		delete stages[i];
	}
}

void CGameStateStart::OnInit()
{
	StageStart.LoadBitmap("Bitmaps\\Stage.bmp");
	stageNum.SetType(1);

	int StageButton[5] = { IDB_STAGE_BUTTON_BLUE, IDB_STAGE_BUTTON_RED, IDB_STAGE_BUTTON_GREEN, IDB_STAGE_BUTTON_YELLOW, IDB_STAGE_BUTTON_GREY };

	for (int i = 0; i < 5; i++) {
		stageButton[i].LoadBitmap(StageButton[i], RGB(255, 255, 255));
	}

	star1.LoadBitmap("Bitmaps\\SmallRedStar.bmp", RGB(255, 255, 255));
	star2.LoadBitmap("Bitmaps\\SmallGreenStar.bmp", RGB(255, 255, 255));
	star3.LoadBitmap("Bitmaps\\SmallYellowStar.bmp", RGB(255, 255, 255));

	for (int i = 0; i < MAX_STAGE + 1; i++) {
		stages.push_back(new Stage(i + 1));
		stages[i]->LoadStage();
	}

}

void CGameStateStart::OnMouseMove(UINT nFlags, CPoint p) {
	if (scroll)
	{
		int displayment = p.y - clickVertical;
		scroll_Y = clickScroll + displayment;
		inertia = displayment < 0 ? -20 : 20;
	}

}
void CGameStateStart::SetUp(bool status)
{
	if (status && scroll_Y <= 0)
		scroll_Y += 10;
}
void CGameStateStart::SetDown(bool status)
{
	if (status && scroll_Y >= -3600)
		scroll_Y -= 10;
}

void CGameStateStart::OnMove()
{
	if (area > 0) 
		scroll_Y += area--;
	else if (area < 0)
		scroll_Y += area++;
	
	SetUp(TapUp);
	SetDown(TapDown);

	if (!scroll && inertia > 0)
		scroll_Y += inertia--;
	else if (!scroll && inertia < 0)
		scroll_Y += inertia++;
}

void CGameStateStart::OnBeginState()
{
}

void CGameStateStart::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT = 0x25; 
	const char KEY_UP = 0x26; 
	const char KEY_RIGHT = 0x27; 
	const char KEY_DOWN = 0x28; 

	if (nChar == KEY_UP) {
		TapUp = true;
		TapDown = false;
	}
	if (nChar == KEY_DOWN) {
		TapUp = false;
		TapDown = true;
	}
}

void CGameStateStart::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';
	const char KEY_UP = 0x26;
	const char KEY_DOWN = 0x28;

	if (nChar == KEY_UP) TapUp = false;
	if (nChar == KEY_DOWN) TapDown =false;
	if (nChar == KEY_SPACE)
		GotoGameState(GAME_STATE_RUN);						
	else if (nChar == KEY_ESC)								
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	
}

void CGameStateStart::OnLButtonDown(UINT nFlags, CPoint p)
{
	scroll = true;
	clickHorizontal = p.x;
	clickVertical = p.y;
	clickScroll = scroll_Y;
}

void CGameStateStart::OnLButtonUp(UINT nFlags, CPoint point)	
{
	scroll = false;
	int x = point.x;
	int y = point.y - scroll_Y;

	for (int i = 0; i < MAX_STAGE; i++) {
		if (StagePos[i][0] < x && x < (StagePos[i][0] + 60) && StagePos[i][1] < y && (y < StagePos[i][1] + 60))
		{
			if (stages[i]->IsUnlock())
			{
				current_stage = i;
				gameArea.LoadStage(stages, i);
				GotoGameState(GAME_STATE_RUN);
			}
		}
	}
}

int CGameStateStart::GetDigit(int n)
{
	n = abs(n);
	int digit = 0;

	while (n > 0)
	{
		digit++;
		n /= 10;
	}

	return digit == 0 ? 1 : digit;
}

void CGameStateStart::OnShow()
{
	StageStart.SetTopLeft(0, scroll_Y);
	StageStart.ShowBitmap();

	if (scroll_Y < 0 && scroll_Y < -3600)
		scroll_Y = -3600;

	if (scroll_Y > 0 && scroll_Y > -3600)
		scroll_Y = 0;

	if (scroll_Y > -3000)
	{
		comingSoon.SetTopLeft(SIZE_X / 2 - comingSoon.Width() / 2, SIZE_Y / 2 - comingSoon.Height() / 2);
		comingSoon.ShowBitmap();
	}

	for (int i = 0; i < MAX_STAGE; i++)
	{
		int xStar = StagePos[i][0] - 10, xButton = StagePos[i][0] - 5;
		int yStar = StagePos[i][1] + scroll_Y + 65, yButton = StagePos[i][1] - 3 + scroll_Y;
		stageNum.SetInteger(i + 1);

		if (stages[i]->IsUnlock())
		{
			if (stages[i]->GetLastScoreHistory() >= stages[i]->GetScoreThree())
			{
				ShowStageButton(3, i, xButton, yButton);
				ShowStars(3, xStar, yStar);
			}
			else if (stages[i]->GetLastScoreHistory() >= stages[i]->GetScoreTwo())
			{
				ShowStageButton(2, i, xButton, yButton);
				ShowStars(2, xStar, yStar);
			}
			else if (stages[i]->GetLastScoreHistory() >= stages[i]->GetScoreOne())
			{
				ShowStageButton(1, i, xButton, yButton);
				ShowStars(1, xStar, yStar);
			}
			else if (stages[i]->GetLastScoreHistory() < stages[i]->GetScoreOne())
			{
				ShowStageButton(0, i, xButton, yButton);
			}
		}
		else
			ShowStageButton(4, i, xButton, yButton);
	}
}

void CGameStateStart::ShowStageButton(int stageBtn, int stage, int xButton, int yButton)
{
	stageButton[stageBtn].SetTopLeft(xButton, yButton);
	stageButton[stageBtn].ShowBitmap();

	
	if (stages[stage]->IsUnlock())
	{
		stageNum.SetTopLeft(xButton + ((stageButton[stageBtn].Width() / 2) - (10 * GetDigit(stage) / 2)), yButton + (stageButton[stageBtn].Height() / 4));
		stageNum.ShowBitmap();
	}
}

void CGameStateStart::ShowStars(int amount, int xStar, int yStar)
{
	if (amount == 3)
	{
		star3.SetTopLeft(xStar, yStar);
		star3.ShowBitmap();
		star3.SetTopLeft(xStar + 30, yStar + 5);
		star3.ShowBitmap();
		star3.SetTopLeft(xStar + 60, yStar);
		star3.ShowBitmap();
	}
	else if (amount >= 1)
	{
		star1.SetTopLeft(xStar, yStar);
		star1.ShowBitmap();

		if (amount == 2)
		{
			star2.SetTopLeft(xStar + 30, yStar + 5);
			star2.ShowBitmap();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGameStateRun
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame* g) : CGameState(g)
{}

CGameStateRun::~CGameStateRun()
{}

void CGameStateRun::OnBeginState()
{
	background.SetTopLeft(0, 0);
}

void CGameStateRun::OnMove()
{
	gameArea.OnMove();

	if (gameArea.IsGameOver())
	{
		//GotoGameState(GAME_STATE_OVER);
	}
}

void CGameStateRun::OnInit()
{
	background.LoadBitmap("Bitmaps\\Play.bmp");
	gameArea.LoadBitmap();
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	gameArea.OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	gameArea.OnKeyUp(nChar, nRepCnt, nFlags);
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)
{
	gameArea.OnLButtonDown(nFlags, point);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)
{
	gameArea.OnLButtonUp(nFlags, point);
}

void CGameStateRun::OnShow()
{
	background.ShowBitmap();
	gameArea.OnShow();
}

/////////////////////////////////////////////////////////////////////////////
// CGameStateOver
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
	currentScore.SetType(2);
	currentScore.SetType(3);
	nextBtnClicked = retryBtnClicked = exitBtnClicked = false;
}

void CGameStateOver::OnMove()
{
	exitButton.OnMove();
	nextButton.OnMove();
	retryButton.OnMove();
}

void CGameStateOver::OnBeginState()
{
	currentStage = current_stage + 1;
	currentScore = (int)stages[current_stage]->GetCurrentScore();
	isFail = stages[current_stage]->IsFail();
	nextBtnClicked = retryBtnClicked = false;
}

void CGameStateOver::OnInit()
{
	backgroundOver.LoadBitmap("Bitmaps/Play.bmp");

	scoreBoardOver.LoadBitmap("Bitmaps/score_state_over.bmp", RGB(0, 0, 0));

	redStar.LoadBitmap("Bitmaps/RedStar.bmp", RGB(251, 230, 239));
	greenStar.LoadBitmap("Bitmaps/GreenStar.bmp", RGB(251, 230, 239));
	yellowStar.LoadBitmap("Bitmaps/YellowStar.bmp", RGB(251, 230, 239));
	emptyStar.LoadBitmap("Bitmaps/ContainerStar.bmp", RGB(251, 230, 239));
	failed.LoadBitmap("Bitmaps/Failed.bmp", RGB(251, 230, 239));

	exitButton.AddBitmap("Bitmaps/ExitButton-0.bmp", RGB(255, 255, 255));
	exitButton.AddBitmap("Bitmaps/ExitButton-1.bmp", RGB(255, 255, 255));
	exitButton.AddBitmap("Bitmaps/ExitButton-2.bmp", RGB(255, 255, 255));
	exitButton.AddBitmap("Bitmaps/ExitButton-1.bmp", RGB(255, 255, 255));
	exitButton.SetDelayCount(8);
	exitButtonClicked.LoadBitmap("Bitmaps\\ExitButtonClicked.bmp", RGB(255, 255, 255));

	int nextBtn[] = { IDB_NEXTBTN_0, IDB_NEXTBTN_1, IDB_NEXTBTN_2, IDB_NEXTBTN_3, IDB_NEXTBTN_4,
					  IDB_NEXTBTN_5, IDB_NEXTBTN_6, IDB_NEXTBTN_7, IDB_NEXTBTN_8, IDB_NEXTBTN_9 };

	int retryBtn[] = { IDB_RETRYBTN_0, IDB_RETRYBTN_1, IDB_RETRYBTN_2, IDB_RETRYBTN_3, IDB_RETRYBTN_4,
					   IDB_RETRYBTN_5, IDB_RETRYBTN_6, IDB_RETRYBTN_7, IDB_RETRYBTN_8, IDB_RETRYBTN_9 };
	

	for (int i = 0; i < 10; i++)
	{
		nextButton.AddBitmap(nextBtn[i], RGB(251, 230, 239));
		retryButton.AddBitmap(retryBtn[i], RGB(251, 230, 239));
	}

	nextButton.SetDelayCount(4);
	retryButton.SetDelayCount(4);

	nextButtonClicked.LoadBitmap("Bitmaps\\NextButtonClicked.bmp", RGB(251, 230, 239));
	retryButtonClicked.LoadBitmap("Bitmaps\\RetryButtonClicked.bmp", RGB(251, 230, 239));
}

void CGameStateOver::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (ButtonOnClick(point, exitButton))
	{
		exitBtnClicked = true;
	}

	if (ButtonOnClick(point, retryButton))
	{
		retryBtnClicked = true;
	}

	if (ButtonOnClick(point, nextButton) && !isFail)
	{
		nextBtnClicked = true;
	}
}

void CGameStateOver::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (ButtonOnClick(point, exitButton))
	{
		GotoGameState(GAME_STATE_START);		
	}

	if (ButtonOnClick(point, retryButton))
	{
		gameArea.LoadStage(stages, current_stage);
		GotoGameState(GAME_STATE_RUN);	
	}

	if (ButtonOnClick(point, nextButton) && !isFail && currentStage.GetInteger() != MAX_STAGE)
	{
		current_stage += 1;
		gameArea.LoadStage(stages, current_stage);
		GotoGameState(GAME_STATE_RUN);		
	}

	nextBtnClicked = retryBtnClicked = exitBtnClicked = false;
}

int CGameStateOver::GetDigit(int n)
{
	n = abs(n);
	int digit = 0;

	while (n > 0)
	{
		digit++;
		n /= 10;
	}

	return digit == 0 ? 1 : digit;
}

void CGameStateOver::ShowButtons()
{
	int exitBtnTopLX = scoreBoardOver.Left() + scoreBoardOver.Width() - exitButton.Width();
	int exitBtnTopLY = scoreBoardOver.Top() + 30;
	int retryBtnTopLX = (backgroundOver.Width() / 2) + (isFail || (current_stage + 1 == 15) ? -nextButton.Width() / 2 : 20 - nextButton.Width());
	int retryBtnTopLY = (backgroundOver.Height() / 2) - (scoreBoardOver.Height() / 2) + 530;
	int nextBtnTopLX = (backgroundOver.Width() / 2) - 20;
	int nextBtnTopLY = (backgroundOver.Height() / 2) - (scoreBoardOver.Height() / 2) + 530;

	if (exitBtnClicked)
	{
		exitButtonClicked.SetTopLeft(exitBtnTopLX, exitBtnTopLY);
		exitButtonClicked.ShowBitmap();
	}
	else
	{
		exitButton.SetTopLeft(exitBtnTopLX, exitBtnTopLY);
		exitButton.OnShow();
	}

	if (retryBtnClicked)
	{
		retryButtonClicked.SetTopLeft(retryBtnTopLX, retryBtnTopLY);
		retryButtonClicked.ShowBitmap();
	}
	else
	{
		retryButton.SetTopLeft(retryBtnTopLX, retryBtnTopLY);
		retryButton.OnShow();
	}

	if (isFail)
	{
		failed.SetTopLeft((backgroundOver.Width() / 2) - (failed.Width() / 2), (backgroundOver.Height() / 2) - (scoreBoardOver.Height() / 2) + 180);
		failed.ShowBitmap();
	}
	else if (current_stage + 1 != 15)
	{
		if (nextBtnClicked)
		{
			nextButtonClicked.SetTopLeft(nextBtnTopLX, nextBtnTopLY);
			nextButtonClicked.ShowBitmap();
		}
		else
		{
			nextButton.SetTopLeft(nextBtnTopLX, nextBtnTopLY);
			nextButton.OnShow();
		}
	}

}

void CGameStateOver::ShowStars(int amount, int xStar, int yStar)
{
	if (amount == 3)
	{
		yellowStar.SetTopLeft(xStar, yStar);
		yellowStar.ShowBitmap();
		yellowStar.SetTopLeft(xStar + 110 + 20, yStar - 20);
		yellowStar.ShowBitmap();
		yellowStar.SetTopLeft(xStar + 220 + 40, yStar);
		yellowStar.ShowBitmap();
	}
	else if (amount >= 1)
	{
		redStar.SetTopLeft(xStar, yStar);
		redStar.ShowBitmap();

		if (amount == 2)
		{
			greenStar.SetTopLeft(xStar + 110 + 20, yStar - 20);
			greenStar.ShowBitmap();
		}
		else {
			emptyStar.SetTopLeft(xStar + 110 + 20, yStar - 20);
			emptyStar.ShowBitmap();
		}
		emptyStar.SetTopLeft(xStar + 220 + 40, yStar);
		emptyStar.ShowBitmap();
	}
	else {
		emptyStar.SetTopLeft(xStar, yStar);
		emptyStar.ShowBitmap();
		emptyStar.SetTopLeft(xStar + 110 + 20, yStar - 20);
		emptyStar.ShowBitmap();
		emptyStar.SetTopLeft(xStar + 220 + 40, yStar);
		emptyStar.ShowBitmap();
	}
}

void CGameStateOver::OnShow()
{
	backgroundOver.SetTopLeft(0, 0);
	backgroundOver.ShowBitmap();

	scoreBoardOver.SetTopLeft((backgroundOver.Width() / 2) - (scoreBoardOver.Width() / 2), (backgroundOver.Height() / 2) - (scoreBoardOver.Height() / 2));
	scoreBoardOver.ShowBitmap();

	currentStage.SetTopLeft((backgroundOver.Width() / 2) + 60, (backgroundOver.Height() / 2) - (scoreBoardOver.Height() / 2) + 55);
	currentStage.ShowBitmap();

	int xStar = (backgroundOver.Width() / 2) - (370 / 2);
	int yStar = (backgroundOver.Height() / 2) - (scoreBoardOver.Height() / 2) + 180;

	if (stages[current_stage]->GetCurrentScore() >= stages[current_stage]->GetScoreThree() && !isFail)
	{	
		ShowStars(3, xStar, yStar);
	}
	else if (stages[current_stage]->GetCurrentScore() >= stages[current_stage]->GetScoreTwo() && !isFail)
	{	
		ShowStars(2, xStar, yStar);
	}
	else if (stages[current_stage]->GetCurrentScore() >= stages[current_stage]->GetScoreOne() && !isFail)
	{	
		ShowStars(1, xStar, yStar);
	}
	else if (stages[current_stage]->GetCurrentScore() < stages[current_stage]->GetScoreOne() && !isFail)
	{	
		ShowStars(0, xStar, yStar);
	}

	currentScore.SetTopLeft((backgroundOver.Width() / 2) - (60 * GetDigit(currentScore.GetInteger()) / 2), (backgroundOver.Height() / 2) - (scoreBoardOver.Height() / 2) + 390);
	currentScore.ShowBitmap();
	ShowButtons();
}

}