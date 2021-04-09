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
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "StagePlay.h"



 

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
		LogoCandy.Reset();	//reset animation of candy crush logo
		playBtnClicked = false;	//reset playbutton state
	}
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';
	if (nChar == KEY_SPACE)
		GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
	else if (nChar == KEY_ESC)								// Demo �����C������k
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// �����C��
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
	if (!playBtnClicked) playButton.OnMove();
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
}

void CGameStateStart::OnInit()
{
	//Stages
	StageStart.LoadBitmap("Bitmaps\\Stage.bmp");
	stageNum.SetType(1);

	int StageButton[5] = { IDB_STAGE_BUTTON_BLUE, IDB_STAGE_BUTTON_RED, IDB_STAGE_BUTTON_GREEN, IDB_STAGE_BUTTON_YELLOW, IDB_STAGE_BUTTON_GREY };

	for (int i = 0; i < 5; i++) {
		stageButton[i].LoadBitmap(StageButton[i], RGB(255, 255, 255));
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
	if (!scroll && inertia > 0) scroll_Y += inertia--;
	else if (!scroll && inertia < 0) scroll_Y += inertia++;
	//OnMouseMove(1);
}

void CGameStateStart::OnBeginState()
{
}

void CGameStateStart::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT = 0x25; // keyboard���b�Y
	const char KEY_UP = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN = 0x28; // keyboard�U�b�Y
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
}

void CGameStateStart::OnShow()
{
	//Stage
	StageStart.SetTopLeft(0, scroll_Y);
	StageStart.ShowBitmap();

	if (scroll_Y < 0 && scroll_Y < -3600)
		scroll_Y = -3600;
	if (scroll_Y > 0 && scroll_Y > -3600)
		scroll_Y = 0;
}

void CGameStateStart::ShowStageButton(int stageBtn, int stage, int xButton, int yButton)
{
	stageButton[stageBtn].SetTopLeft(xButton, yButton);
	stageButton[stageBtn].ShowBitmap();

	/*
	if (stages[stage]->IsUnlock())
	{
		stageNum.SetTopLeft(xButton + ((stageButton[stageBtn].Width() / 2) - (10 * GetDigit(stage) / 2)), yButton + (stageButton[stageBtn].Height() / 4));
		stageNum.ShowBitmap();
	}
	*/
}
/////////////////////////////////////////////////////////////////////////////
// CGameStateOver
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	counter--;
	if (counter < 0)
		GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState()
{
	counter = 30 * 5; // 5 seconds
}

void CGameStateOver::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
	//
	// �}�l���J���
	//
	Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �̲׶i�׬�100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
/////////////////////////////////////////////////////////////////////////////

CPractice::CPractice()
{
	x = y = 0;
}

void CPractice::OnMove()
{
	if (y <= SIZE_Y) {
		x += 3;
		y += 3;
	}
	else {
		x = y = 0;
	}
}

void CPractice::LoadBitmap()
{
	pic.LoadBitmapA(IDB_TESTAJ);
}

void CPractice::OnShow()
{
	pic.SetTopLeft(x, y);
	pic.ShowBitmap();
}


void CBouncingBall::SetXY(int x, int y) 
{
	this->x = x;
	this->y = y;
}

void CBouncingBall::SetFloor(int floor)
{
	this->floor = floor;
}

void CBouncingBall::SetVelocity(int velocity)
{
	this->velocity = velocity;
	this->initial_velocity = velocity;
}
#include <iostream>
CGameMap::CGameMap()
	:X(500), Y(200), MW(50), MH(50) 
{
	//Candy1, Candy2 = 5;
	/*int map_init[5][8] ={{3,3,3,3,3,3,3,3},
						{3,3,3,3,3,3,3,3},
						{3,3,3,3,3,3,3,3},
						{3,3,3,3,3,3,3,3},
						{3,3,3,3,3,3,3,3} };*/
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 8; j++)
			map[i][j] = rand()%5;
	random_num = 0;
	bballs = NULL;
}

void CGameMap::LoadBitmaps()
{
	blue.LoadBitmap(IDB_BLUE_C);
	green.LoadBitmap(IDB_GREEN_C, RGB(255, 255, 255));
	orange.LoadBitmap(IDB_ORANGE_C, RGB(255, 255, 255));
	purple.LoadBitmap(IDB_PURPLE_C, RGB(255, 255, 255));
	red.LoadBitmap(IDB_RED_C, RGB(255, 255, 255));
	yellow.LoadBitmap(IDB_YELLOW_C, RGB(255, 255, 255));
	box.LoadBitmap("Bitmaps\\box.bmp");
	
}
CGameMap* CGameMap::Click(){
	on = on == true ? false : true;
	return this;
}
 /*bool CGameMap::OnClick(const CPoint& point, CMovingBitmap& button){
	if (button.Left() <= point.x && point.x <= (button.Left() + button.Width()) &&
		button.Top() <= point.y && point.y <= (button.Top() + button.Height()))
	{
		return true;
	}
	else
	{
		return false;
	}
}*/
 bool CGameMap::Friend(int ii,int jj,int i, int j)
 {
	 if ((ii - 1 == i || ii + 1 == i) && (jj - 1 == j || j + 1 == j))
		 return true;
	 else 
		return false;
	
 }
void CGameMap::OnLButtonUp(UINT nFlags, CPoint point) {
	int j= (point.x - 280) / 50;
	int i= (point.y - 35) / 50;
	//std::cout << "j "<< endl;
	//if (!map[i][j]) return;
	//StagePlay* Candy1 = maps[i][j].Click();
	if (TotalCandy == 0) {
		TotalCandy += 1;
		ii = i;
		jj = j;
	}
	else if (TotalCandy== 1)
	{

		if (Friend(ii,jj,i,j))
		{

			int temp = map[ii][jj];
			map[ii][jj] = map[i][j];
			map[i][j] = temp;
			//if (TotalCandy[0]->GetPower() == 4 || TotalCandy[1]->GetPower() == 4 || (TotalCandy[0]->GetPower() && TotalCandy[1]->GetPower()))
			//swap = true;
		}
		//else if (!swap) InitClickedCandy();
		TotalCandy, ii, jj = 0;
	}
}
void CGameMap::OnShow()
{

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 5; j++) {
			box.SetTopLeft(X + (MW*i), Y + (MH*j));
			box.ShowBitmap();
			switch (map[j][i]) {
			case 0:
				yellow.SetTopLeft(X + (MW*i), Y + (MH*j));
				yellow.ShowBitmap();
				break;
			case 1:
				blue.SetTopLeft(X + (MW*i), Y + (MH*j));
				blue.ShowBitmap();
				break;
			case 2:
				green.SetTopLeft(X + (MW*i), Y + (MH*j));
				green.ShowBitmap();
				break;
			case 3:
				orange.SetTopLeft(X + (MW*i), Y + (MH*j));
				orange.ShowBitmap();
				break;
			case 4:
				purple.SetTopLeft(X + (MW*i), Y + (MH*j));
				purple.ShowBitmap();
				break;
			default:
				ASSERT(0);
			}
		}
			
}
void CGameMap::InitializeBouncingBall(int ini_index, int row, int col)
{
	const int VELOCITY = 10;
	const int BALL_PIC_HEIGHT = 15;
	int floor = Y + (row + 1)*MH - BALL_PIC_HEIGHT;

	bballs[ini_index].LoadBitmap();
	bballs[ini_index].SetFloor(floor);
	bballs[ini_index].SetVelocity(VELOCITY + col);
	bballs[ini_index].SetXY(X + col * MW + MW / 2, floor);
}
void CGameMap::RandomBouncingBall()
{
	const int MAX_RAND_NUM = 10;
	random_num = (rand() % MAX_RAND_NUM) + 1;

	delete [] bballs;
	bballs = new CBouncingBall[random_num];
	int ini_index = 0;
	for(int row=0;row<4;row++)
		for(int col=0;col<5;col++)
		{
			if (map[row][col] != 0 && ini_index < random_num)
			{
				InitializeBouncingBall(ini_index, row, col);
				ini_index++;
			}
		}
}
void CGameMap::OnKeyDown(UINT nChar)
{
	const int KEY_SPACE = 0x20;
	if (nChar == KEY_SPACE)
		RandomBouncingBall();
}
void CGameMap::OnMove()
{
	for (int i = 0; i < random_num; i++) 
	{
		bballs[i].OnMove();
	}
}

CGameMap::~CGameMap()
{
	delete[]bballs;
}

CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g), NUMBALLS(28)
{
	ball = new CBall [NUMBALLS];
	picX = picY = 0;
}

CGameStateRun::~CGameStateRun()
{
	delete [] ball;
}

void CGameStateRun::OnBeginState()
{
	const int BALL_GAP = 90;
	const int BALL_XY_OFFSET = 45;
	const int BALL_PER_ROW = 7;
	const int HITS_LEFT = 10;
	const int HITS_LEFT_X = 590;
	const int HITS_LEFT_Y = 0;
//	const int BACKGROUND_X = 60;
	const int ANIMATION_SPEED = 15;
	for (int i = 0; i < NUMBALLS; i++) {				// �]�w�y���_�l�y��
		int x_pos = i % BALL_PER_ROW;
		int y_pos = i / BALL_PER_ROW;
		ball[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
		ball[i].SetDelay(x_pos);
		ball[i].SetIsAlive(true);
	}
	//eraser.Initialize();
	//background.SetTopLeft(0,0);				// �]�w�I�����_�l�y��
	//help.SetTopLeft(0, SIZE_Y - help.Height());			// �]�w�����Ϫ��_�l�y��
	//hits_left.SetInteger(HITS_LEFT);					// ���w�ѤU��������
	//hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// ���w�ѤU�����ƪ��y��
	CAudio::Instance()->Play(AUDIO_LAKE, true);			// ���� WAVE
	CAudio::Instance()->Play(AUDIO_DING, false);		// ���� WAVE
	CAudio::Instance()->Play(AUDIO_NTUT, true);			// ���� MIDI
}

void CGameStateRun::OnMove()							// ���ʹC������
{

	////if (background.Top() > SIZE_Y)
		//background.SetTopLeft(60 ,-background.Height());
	//background.SetTopLeft(background.Left(),background.Top()+1);
	//practice.SetTopLeft(10, 10);
	if (picX <= SIZE_Y) {
		picX += 5;
		picY += 5;
	}
	else {
		picX = picY = 0;
	}
	//practice.SetTopLeft(picX, picY);
	//c_practice.OnMove();
	gamemap.OnMove();
	//
	// ���ʲy
	//
	//int i;
	//for (i=0; i < NUMBALLS; i++)
	//	ball[i].OnMove();
	//
	// �������l
	//
	//eraser.OnMove();
	//
	// �P�_���l�O�_�I��y
	//
	/*for (i=0; i < NUMBALLS; i++)
		if (ball[i].IsAlive() && ball[i].HitEraser(&eraser)) {
			ball[i].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_DING);
			hits_left.Add(-1);
			//
			// �Y�Ѿl�I�����Ƭ�0�A�h����Game Over���A
			//
			if (hits_left.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// ���� WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// ���� MIDI
				GotoGameState(GAME_STATE_OVER);
			}
		}
	//*/
	// ���ʼu�����y
	//
	//bball.OnMove();
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	ShowInitProgress(33);	
	backgrounds.LoadBitmap("Bitmaps\\Play.bmp");

	//int i;
	//for (i = 0; i < NUMBALLS; i++)	
	//	ball[i].LoadBitmap();								
	//eraser.LoadBitmap();					
	//practice.LoadBitmap(IDB_TESTAJ,RGB(255,255,255));
	//practice.LoadBitmap("Bitmaps/Nbmp.bmp");
	//c_practice.LoadBitmap();

	ShowInitProgress(50);
	Sleep(300);

	//help.LoadBitmap(IDB_HELP,RGB(255,255,255));				
	//corner.LoadBitmap(IDB_CORNER);							
	//corner.ShowBitmap(background);							
	//bball.LoadBitmap();							
	//hits_left.LoadBitmap();	
	gamemap.LoadBitmaps();
	
	CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	
	CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	
	CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	
}


void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
	if (nChar == KEY_LEFT)
		eraser.SetMovingLeft(true);
	if (nChar == KEY_RIGHT)
		eraser.SetMovingRight(true);
	if (nChar == KEY_UP)
		eraser.SetMovingUp(true);
	if (nChar == KEY_DOWN)
		eraser.SetMovingDown(true);
	gamemap.OnKeyDown(nChar);
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
	if (nChar == KEY_LEFT)
		eraser.SetMovingLeft(false);
	if (nChar == KEY_RIGHT)
		eraser.SetMovingRight(false);
	if (nChar == KEY_UP)
		eraser.SetMovingUp(false);
	if (nChar == KEY_DOWN)
		eraser.SetMovingDown(false);
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	eraser.SetMovingLeft(true);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	eraser.SetMovingLeft(false);
	gamemap.OnLButtonUp(nFlags, point);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	eraser.SetMovingRight(true);
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	eraser.SetMovingRight(false);
}

void CGameStateRun::OnShow()
{
	//
	//  �`�N�GShow�̭��d�U���n���ʥ��󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
	//        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
	//        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
	//
	//
	//  �K�W�I���ϡB�����ơB�y�B���l�B�u�����y
	//
	backgrounds.SetTopLeft(0, 0);
	backgrounds.ShowBitmap();			// �K�W�I����

	//box.SetTopLeft( 3000 , 500);
	//box.ShowBitmap();


	/*help.ShowBitmap();					// �K�W������
	hits_left.ShowBitmap();
	for (int i=0; i < NUMBALLS; i++)
		ball[i].OnShow();				// �K�W��i���y
	bball.OnShow();						// �K�W�u�����y
	eraser.OnShow();					// �K�W���l
	//
	//  �K�W���W�Υk�U��������
	//*/
	/*
	corner.SetTopLeft(SIZE_X-corner.Width(), SIZE_Y-corner.Height());
	corner.ShowBitmap();
	/*
	practice.ShowBitmap();
	c_practice.OnShow();*/
	gamemap.OnShow();
	//stageplay.OnShow();*/

}
}