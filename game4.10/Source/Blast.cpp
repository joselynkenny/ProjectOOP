#include "stdafx.h"
#include <omp.h>
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Blast.h"

namespace game_framework {
	static int redBmp[] = { IDB_RED_EXPL1, IDB_RED_EXPL2, IDB_RED_EXPL3, IDB_RED_EXPL4, IDB_RED_EXPL5,
							IDB_RED_EXPL6, IDB_RED_EXPL7, IDB_RED_EXPL8, IDB_RED_EXPL9, IDB_RED_EXPL10,
							IDB_RED_SHAT1, IDB_RED_SHAT2, IDB_RED_SHAT3, IDB_RED_SHAT4, IDB_RED_SHAT5,
							IDB_RED_SHAT6, IDB_RED_SHAT7, IDB_RED_SHAT8, IDB_RED_SHAT9, IDB_RED_SHAT10,
							IDB_RED_SHAT11, IDB_RED_SHAT12, IDB_RED_SHAT13, IDB_RED_SHAT14, IDB_RED_SHAT15,
							IDB_RED_V_EXPL1, IDB_RED_V_EXPL2, IDB_RED_V_EXPL3, IDB_RED_V_EXPL4, IDB_RED_V_EXPL5,
							IDB_RED_V_EXPL6, IDB_RED_V_EXPL7, IDB_RED_V_EXPL8, IDB_RED_V_EXPL9, IDB_RED_V_EXPL10,
							IDB_RED_V_EXPL11, IDB_RED_V_EXPL12, IDB_RED_V_EXPL13, IDB_RED_V_EXPL14, IDB_RED_V_EXPL15,
							IDB_RED_V_EXPL16, IDB_RED_V_EXPL17, IDB_RED_V_EXPL18, IDB_RED_V_EXPL19, IDB_RED_V_EXPL20,
							IDB_RED_V_EXPL21, IDB_RED_V_EXPL22, IDB_RED_V_EXPL23, IDB_RED_V_EXPL24, IDB_RED_V_EXPL25,
							IDB_RED_V_EXPL26, IDB_RED_V_EXPL27, IDB_RED_V_EXPL28, IDB_RED_V_EXPL29, IDB_RED_V_EXPL30,
							IDB_RED_H_EXPL1, IDB_RED_H_EXPL2, IDB_RED_H_EXPL3, IDB_RED_H_EXPL4, IDB_RED_H_EXPL5,
							IDB_RED_H_EXPL6, IDB_RED_H_EXPL7, IDB_RED_H_EXPL8, IDB_RED_H_EXPL9, IDB_RED_H_EXPL10,
							IDB_RED_H_EXPL11, IDB_RED_H_EXPL12, IDB_RED_H_EXPL13, IDB_RED_H_EXPL14, IDB_RED_H_EXPL15,
							IDB_RED_H_EXPL16, IDB_RED_H_EXPL17, IDB_RED_H_EXPL18, IDB_RED_H_EXPL19, IDB_RED_H_EXPL20,
							IDB_RED_H_EXPL21, IDB_RED_H_EXPL22, IDB_RED_H_EXPL23, IDB_RED_H_EXPL24, IDB_RED_H_EXPL25,
							IDB_RED_H_EXPL26, IDB_RED_H_EXPL27, IDB_RED_H_EXPL28, IDB_RED_H_EXPL29, IDB_RED_H_EXPL30},

		orangeBmp[] = { IDB_ORANGE_EXPL1, IDB_ORANGE_EXPL2, IDB_ORANGE_EXPL3, IDB_ORANGE_EXPL4, IDB_ORANGE_EXPL5,
					    IDB_ORANGE_EXPL6, IDB_ORANGE_EXPL7, IDB_ORANGE_EXPL8, IDB_ORANGE_EXPL9, IDB_ORANGE_EXPL10,
						IDB_ORANGE_SHAT1, IDB_ORANGE_SHAT2, IDB_ORANGE_SHAT3, IDB_ORANGE_SHAT4, IDB_ORANGE_SHAT5,
						IDB_ORANGE_SHAT6, IDB_ORANGE_SHAT7, IDB_ORANGE_SHAT8, IDB_ORANGE_SHAT9, IDB_ORANGE_SHAT10,
						IDB_ORANGE_SHAT11, IDB_ORANGE_SHAT12, IDB_ORANGE_SHAT13, IDB_ORANGE_SHAT14, IDB_ORANGE_SHAT15,
						IDB_ORANGE_V_EXPL1, IDB_ORANGE_V_EXPL2, IDB_ORANGE_V_EXPL3, IDB_ORANGE_V_EXPL4, IDB_ORANGE_V_EXPL5,
						IDB_ORANGE_V_EXPL6, IDB_ORANGE_V_EXPL7, IDB_ORANGE_V_EXPL8, IDB_ORANGE_V_EXPL9, IDB_ORANGE_V_EXPL10,
						IDB_ORANGE_V_EXPL11, IDB_ORANGE_V_EXPL12, IDB_ORANGE_V_EXPL13, IDB_ORANGE_V_EXPL14, IDB_ORANGE_V_EXPL15,
						IDB_ORANGE_V_EXPL16, IDB_ORANGE_V_EXPL17, IDB_ORANGE_V_EXPL18, IDB_ORANGE_V_EXPL19, IDB_ORANGE_V_EXPL20,
						IDB_ORANGE_V_EXPL21, IDB_ORANGE_V_EXPL22, IDB_ORANGE_V_EXPL23, IDB_ORANGE_V_EXPL24, IDB_ORANGE_V_EXPL25,
						IDB_ORANGE_V_EXPL26, IDB_ORANGE_V_EXPL27, IDB_ORANGE_V_EXPL28, IDB_ORANGE_V_EXPL29, IDB_ORANGE_V_EXPL30,
					    IDB_ORANGE_H_EXPL1, IDB_ORANGE_H_EXPL2, IDB_ORANGE_H_EXPL3, IDB_ORANGE_H_EXPL4, IDB_ORANGE_H_EXPL5,
					    IDB_ORANGE_H_EXPL6, IDB_ORANGE_H_EXPL7, IDB_ORANGE_H_EXPL8, IDB_ORANGE_H_EXPL9, IDB_ORANGE_H_EXPL10,
					    IDB_ORANGE_H_EXPL11, IDB_ORANGE_H_EXPL12, IDB_ORANGE_H_EXPL13, IDB_ORANGE_H_EXPL14, IDB_ORANGE_H_EXPL15,
						IDB_ORANGE_H_EXPL16, IDB_ORANGE_H_EXPL17, IDB_ORANGE_H_EXPL18, IDB_ORANGE_H_EXPL19, IDB_ORANGE_H_EXPL20,
						IDB_ORANGE_H_EXPL21, IDB_ORANGE_H_EXPL22, IDB_ORANGE_H_EXPL23, IDB_ORANGE_H_EXPL24, IDB_ORANGE_H_EXPL25,
						IDB_ORANGE_H_EXPL26, IDB_ORANGE_H_EXPL27, IDB_ORANGE_H_EXPL28, IDB_ORANGE_H_EXPL29, IDB_ORANGE_H_EXPL30 },

		greenBmp[] = { IDB_GREEN_EXPL1, IDB_GREEN_EXPL2, IDB_GREEN_EXPL3, IDB_GREEN_EXPL4, IDB_GREEN_EXPL5,
					   IDB_GREEN_EXPL6, IDB_GREEN_EXPL7, IDB_GREEN_EXPL8, IDB_GREEN_EXPL9, IDB_GREEN_EXPL10,
					   IDB_GREEN_SHAT1, IDB_GREEN_SHAT2, IDB_GREEN_SHAT3, IDB_GREEN_SHAT4, IDB_GREEN_SHAT5,
					   IDB_GREEN_SHAT6, IDB_GREEN_SHAT7, IDB_GREEN_SHAT8, IDB_GREEN_SHAT9, IDB_GREEN_SHAT10,
					   IDB_GREEN_SHAT11, IDB_GREEN_SHAT12, IDB_GREEN_SHAT13, IDB_GREEN_SHAT14, IDB_GREEN_SHAT15,
					   IDB_GREEN_V_EXPL1, IDB_GREEN_V_EXPL2, IDB_GREEN_V_EXPL3, IDB_GREEN_V_EXPL4, IDB_GREEN_V_EXPL5,
					   IDB_GREEN_V_EXPL6, IDB_GREEN_V_EXPL7, IDB_GREEN_V_EXPL8, IDB_GREEN_V_EXPL9, IDB_GREEN_V_EXPL10,
					   IDB_GREEN_V_EXPL11, IDB_GREEN_V_EXPL12, IDB_GREEN_V_EXPL13, IDB_GREEN_V_EXPL14, IDB_GREEN_V_EXPL15,
					   IDB_GREEN_V_EXPL16, IDB_GREEN_V_EXPL17, IDB_GREEN_V_EXPL18, IDB_GREEN_V_EXPL19, IDB_GREEN_V_EXPL20,
					   IDB_GREEN_V_EXPL21, IDB_GREEN_V_EXPL22, IDB_GREEN_V_EXPL23, IDB_GREEN_V_EXPL24, IDB_GREEN_V_EXPL25,
					   IDB_GREEN_V_EXPL26, IDB_GREEN_V_EXPL27, IDB_GREEN_V_EXPL28, IDB_GREEN_V_EXPL29, IDB_GREEN_V_EXPL30,
					   IDB_GREEN_H_EXPL1, IDB_GREEN_H_EXPL2, IDB_GREEN_H_EXPL3, IDB_GREEN_H_EXPL4, IDB_GREEN_H_EXPL5,
					   IDB_GREEN_H_EXPL6, IDB_GREEN_H_EXPL7, IDB_GREEN_H_EXPL8, IDB_GREEN_H_EXPL9, IDB_GREEN_H_EXPL10,
					   IDB_GREEN_H_EXPL11, IDB_GREEN_H_EXPL12, IDB_GREEN_H_EXPL13, IDB_GREEN_H_EXPL14, IDB_GREEN_H_EXPL15,
					   IDB_GREEN_H_EXPL16, IDB_GREEN_H_EXPL17, IDB_GREEN_H_EXPL18, IDB_GREEN_H_EXPL19, IDB_GREEN_H_EXPL20,
					   IDB_GREEN_H_EXPL21, IDB_GREEN_H_EXPL22, IDB_GREEN_H_EXPL23, IDB_GREEN_H_EXPL24, IDB_GREEN_H_EXPL25,
					   IDB_GREEN_H_EXPL26, IDB_GREEN_H_EXPL27, IDB_GREEN_H_EXPL28, IDB_GREEN_H_EXPL29, IDB_GREEN_H_EXPL30 },

		blueBmp[] = { IDB_BLUE_EXPL1, IDB_BLUE_EXPL2, IDB_BLUE_EXPL3, IDB_BLUE_EXPL4, IDB_BLUE_EXPL5,
					  IDB_BLUE_EXPL6, IDB_BLUE_EXPL7, IDB_BLUE_EXPL8, IDB_BLUE_EXPL9, IDB_BLUE_EXPL10,
					  IDB_BLUE_SHAT1, IDB_BLUE_SHAT2, IDB_BLUE_SHAT3, IDB_BLUE_SHAT4, IDB_BLUE_SHAT5,
					  IDB_BLUE_SHAT6, IDB_BLUE_SHAT7, IDB_BLUE_SHAT8, IDB_BLUE_SHAT9, IDB_BLUE_SHAT10,
					  IDB_BLUE_SHAT11, IDB_BLUE_SHAT12, IDB_BLUE_SHAT13, IDB_BLUE_SHAT14, IDB_BLUE_SHAT15,
					  IDB_BLUE_V_EXPL1, IDB_BLUE_V_EXPL2, IDB_BLUE_V_EXPL3, IDB_BLUE_V_EXPL4, IDB_BLUE_V_EXPL5,
					  IDB_BLUE_V_EXPL6, IDB_BLUE_V_EXPL7, IDB_BLUE_V_EXPL8, IDB_BLUE_V_EXPL9, IDB_BLUE_V_EXPL10,
					  IDB_BLUE_V_EXPL11, IDB_BLUE_V_EXPL12, IDB_BLUE_V_EXPL13, IDB_BLUE_V_EXPL14, IDB_BLUE_V_EXPL15,
					  IDB_BLUE_V_EXPL16, IDB_BLUE_V_EXPL17, IDB_BLUE_V_EXPL18, IDB_BLUE_V_EXPL19, IDB_BLUE_V_EXPL20,
					  IDB_BLUE_V_EXPL21, IDB_BLUE_V_EXPL22, IDB_BLUE_V_EXPL23, IDB_BLUE_V_EXPL24, IDB_BLUE_V_EXPL25,
					  IDB_BLUE_V_EXPL26, IDB_BLUE_V_EXPL27, IDB_BLUE_V_EXPL28, IDB_BLUE_V_EXPL29, IDB_BLUE_V_EXPL30,
					  IDB_BLUE_H_EXPL1, IDB_BLUE_H_EXPL2, IDB_BLUE_H_EXPL3, IDB_BLUE_H_EXPL4, IDB_BLUE_H_EXPL5,
					  IDB_BLUE_H_EXPL6, IDB_BLUE_H_EXPL7, IDB_BLUE_H_EXPL8, IDB_BLUE_H_EXPL9, IDB_BLUE_H_EXPL10,
					  IDB_BLUE_H_EXPL11, IDB_BLUE_H_EXPL12, IDB_BLUE_H_EXPL13, IDB_BLUE_H_EXPL14, IDB_BLUE_H_EXPL15,
					  IDB_BLUE_H_EXPL16, IDB_BLUE_H_EXPL17, IDB_BLUE_H_EXPL18, IDB_BLUE_H_EXPL19, IDB_BLUE_H_EXPL20,
					  IDB_BLUE_H_EXPL21, IDB_BLUE_H_EXPL22, IDB_BLUE_H_EXPL23, IDB_BLUE_H_EXPL24, IDB_BLUE_H_EXPL25,
					  IDB_BLUE_H_EXPL26, IDB_BLUE_H_EXPL27, IDB_BLUE_H_EXPL28, IDB_BLUE_H_EXPL29, IDB_BLUE_H_EXPL30 },

		yellowBmp[] = { IDB_YELLOW_EXPL1, IDB_YELLOW_EXPL2, IDB_YELLOW_EXPL3, IDB_YELLOW_EXPL4, IDB_YELLOW_EXPL5,
						IDB_YELLOW_EXPL6, IDB_YELLOW_EXPL7, IDB_YELLOW_EXPL8, IDB_YELLOW_EXPL9, IDB_YELLOW_EXPL10,
						IDB_YELLOW_SHAT1, IDB_YELLOW_SHAT2, IDB_YELLOW_SHAT3, IDB_YELLOW_SHAT4, IDB_YELLOW_SHAT5,
						IDB_YELLOW_SHAT6, IDB_YELLOW_SHAT7, IDB_YELLOW_SHAT8, IDB_YELLOW_SHAT9, IDB_YELLOW_SHAT10,
						IDB_YELLOW_SHAT11, IDB_YELLOW_SHAT12, IDB_YELLOW_SHAT13, IDB_YELLOW_SHAT14, IDB_YELLOW_SHAT15,
						IDB_YELLOW_V_EXPL1, IDB_YELLOW_V_EXPL2, IDB_YELLOW_V_EXPL3, IDB_YELLOW_V_EXPL4, IDB_YELLOW_V_EXPL5,
						IDB_YELLOW_V_EXPL6, IDB_YELLOW_V_EXPL7, IDB_YELLOW_V_EXPL8, IDB_YELLOW_V_EXPL9, IDB_YELLOW_V_EXPL10,
						IDB_YELLOW_V_EXPL11, IDB_YELLOW_V_EXPL12, IDB_YELLOW_V_EXPL13, IDB_YELLOW_V_EXPL14, IDB_YELLOW_V_EXPL15,
						IDB_YELLOW_V_EXPL16, IDB_YELLOW_V_EXPL17, IDB_YELLOW_V_EXPL18, IDB_YELLOW_V_EXPL19, IDB_YELLOW_V_EXPL20,
						IDB_YELLOW_V_EXPL21, IDB_YELLOW_V_EXPL22, IDB_YELLOW_V_EXPL23, IDB_YELLOW_V_EXPL24, IDB_YELLOW_V_EXPL25,
						IDB_YELLOW_V_EXPL26, IDB_YELLOW_V_EXPL27, IDB_YELLOW_V_EXPL28, IDB_YELLOW_V_EXPL29, IDB_YELLOW_V_EXPL30,
						IDB_YELLOW_H_EXPL1, IDB_YELLOW_H_EXPL2, IDB_YELLOW_H_EXPL3, IDB_YELLOW_H_EXPL4, IDB_YELLOW_H_EXPL5,
						IDB_YELLOW_H_EXPL6, IDB_YELLOW_H_EXPL7, IDB_YELLOW_H_EXPL8, IDB_YELLOW_H_EXPL9, IDB_YELLOW_H_EXPL10,
						IDB_YELLOW_H_EXPL11, IDB_YELLOW_H_EXPL12, IDB_YELLOW_H_EXPL13, IDB_YELLOW_H_EXPL14, IDB_YELLOW_H_EXPL15,
						IDB_YELLOW_H_EXPL16, IDB_YELLOW_H_EXPL17, IDB_YELLOW_H_EXPL18, IDB_YELLOW_H_EXPL19, IDB_YELLOW_H_EXPL20,
						IDB_YELLOW_H_EXPL21, IDB_YELLOW_H_EXPL22, IDB_YELLOW_H_EXPL23, IDB_YELLOW_H_EXPL24, IDB_YELLOW_H_EXPL25,
						IDB_YELLOW_H_EXPL26, IDB_YELLOW_H_EXPL27, IDB_YELLOW_H_EXPL28, IDB_YELLOW_H_EXPL29, IDB_YELLOW_H_EXPL30 },

		purpleBmp[] = { IDB_PURPLE_EXPL1, IDB_PURPLE_EXPL2, IDB_PURPLE_EXPL3, IDB_PURPLE_EXPL4, IDB_PURPLE_EXPL5,
						IDB_PURPLE_EXPL6, IDB_PURPLE_EXPL7, IDB_PURPLE_EXPL8, IDB_PURPLE_EXPL9, IDB_PURPLE_EXPL10,
						IDB_PURPLE_SHAT1, IDB_PURPLE_SHAT2, IDB_PURPLE_SHAT3, IDB_PURPLE_SHAT4, IDB_PURPLE_SHAT5,
						IDB_PURPLE_SHAT6, IDB_PURPLE_SHAT7, IDB_PURPLE_SHAT8, IDB_PURPLE_SHAT9, IDB_PURPLE_SHAT10,
						IDB_PURPLE_SHAT11, IDB_PURPLE_SHAT12, IDB_PURPLE_SHAT13, IDB_PURPLE_SHAT14, IDB_PURPLE_SHAT15,
						IDB_PURPLE_V_EXPL1, IDB_PURPLE_V_EXPL2, IDB_PURPLE_V_EXPL3, IDB_PURPLE_V_EXPL4, IDB_PURPLE_V_EXPL5,
						IDB_PURPLE_V_EXPL6, IDB_PURPLE_V_EXPL7, IDB_PURPLE_V_EXPL8, IDB_PURPLE_V_EXPL9, IDB_PURPLE_V_EXPL10,
						IDB_PURPLE_V_EXPL11, IDB_PURPLE_V_EXPL12, IDB_PURPLE_V_EXPL13, IDB_PURPLE_V_EXPL14, IDB_PURPLE_V_EXPL15,
						IDB_PURPLE_V_EXPL16, IDB_PURPLE_V_EXPL17, IDB_PURPLE_V_EXPL18, IDB_PURPLE_V_EXPL19, IDB_PURPLE_V_EXPL20,
						IDB_PURPLE_V_EXPL21, IDB_PURPLE_V_EXPL22, IDB_PURPLE_V_EXPL23, IDB_PURPLE_V_EXPL24, IDB_PURPLE_V_EXPL25,
						IDB_PURPLE_V_EXPL26, IDB_PURPLE_V_EXPL27, IDB_PURPLE_V_EXPL28, IDB_PURPLE_V_EXPL29, IDB_PURPLE_V_EXPL30,
						IDB_PURPLE_H_EXPL1, IDB_PURPLE_H_EXPL2, IDB_PURPLE_H_EXPL3, IDB_PURPLE_H_EXPL4, IDB_PURPLE_H_EXPL5,
						IDB_PURPLE_H_EXPL6, IDB_PURPLE_H_EXPL7, IDB_PURPLE_H_EXPL8, IDB_PURPLE_H_EXPL9, IDB_PURPLE_H_EXPL10,
						IDB_PURPLE_H_EXPL11, IDB_PURPLE_H_EXPL12, IDB_PURPLE_H_EXPL13, IDB_PURPLE_H_EXPL14, IDB_PURPLE_H_EXPL15,
						IDB_PURPLE_H_EXPL16, IDB_PURPLE_H_EXPL17, IDB_PURPLE_H_EXPL18, IDB_PURPLE_H_EXPL19, IDB_PURPLE_H_EXPL20,
						IDB_PURPLE_H_EXPL21, IDB_PURPLE_H_EXPL22, IDB_PURPLE_H_EXPL23, IDB_PURPLE_H_EXPL24, IDB_PURPLE_H_EXPL25,
						IDB_PURPLE_H_EXPL26, IDB_PURPLE_H_EXPL27, IDB_PURPLE_H_EXPL28, IDB_PURPLE_H_EXPL29, IDB_PURPLE_H_EXPL30 };

	void Blast::SetTopLeft(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	CMovingBitmap NormalBlast::normalBlast[6][10], NormalBlast::shatter[6][15];

	NormalBlast::NormalBlast() :currentShow(0), totalShow(0)
	{
		//sound = &CGameState::sound;
	}

	NormalBlast::NormalBlast(int style, int x, int y) : currentShow(0), size(1.8), totalShow(rand() % 2 + 2)
	{
		this->style = style;
		SetTopLeft(x, y);

		int direction[] = { -2, -1, 0, 2, 1 };	

		#pragma omp parallel for
		for (int i = 0; i < totalShow; i++)
		{
			shatterPosition[i][0] = x;
			shatterPosition[i][1] = y;

			shatterShow[i] = rand() % 15;	

			shift[i][0] = direction[rand() % 5];	
			shift[i][1] = direction[rand() % 2 + 3];
			shift[i][2] = rand() % 2;				
		}
	}

	void NormalBlast::LoadBitmap()
	{
		int *bmpID[] = { blueBmp, purpleBmp, orangeBmp, greenBmp , redBmp, yellowBmp };

		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 10; j++)
				normalBlast[i][j].LoadBitmap(bmpID[i][j], RGB(254, 191, 200));

			for (int j = 0; j < 15; j++)
				shatter[i][j].LoadBitmap(bmpID[i][j + 10], RGB(254, 191, 200));
		}
	}

	void NormalBlast::OnMove()
	{
		currentShow++;

		if (currentShow % 2)
			size -= 0.1;

		#pragma omp parallel for
		for (int i = 0; i < totalShow; i++)
		{	
			shatterPosition[i][0] += shift[i][0];
			shatterPosition[i][1] += shift[i][1];

			if (!(currentShow % 3))
			{
				if (shift[i][2]) shatterShow[i] = (shatterShow[i] - 1) < 0 ? (shatterShow[i] - 1) + 15 : (shatterShow[i] - 1);
				else shatterShow[i] = (shatterShow[i] + 1) % 15;
			}
		}
	}

	void NormalBlast::OnShow()
	{
		if (currentShow < 10)
		{
			normalBlast[style - 1][currentShow].SetTopLeft(x - (normalBlast[style - 1][currentShow].Width() / 2) + 25, y - (normalBlast[style - 1][currentShow].Height() / 2) + 25);
			normalBlast[style - 1][currentShow].ShowBitmap();
		}

		if (currentShow >= 4)
		{	
			#pragma omp parallel for
			for (int i = 0; i < totalShow; i++)
			{
				shatter[style - 1][shatterShow[i]].SetTopLeft(shatterPosition[i][0], shatterPosition[i][1]);
				shatter[style - 1][shatterShow[i]].ShowBitmap(size);
			}
		}
	}

	bool NormalBlast::IsEnd()
	{
		return (currentShow == 25);
	}

	CMovingBitmap LineBlast::horizontal[6][30], LineBlast::vertical[6][30];

	LineBlast::LineBlast(int style, int x, int y, int power) :powerStyle(power), currentShow(0)
	{
		this->style = style;
		SetTopLeft(x, y);
		//sound = &CGameState::sound;
	}

	void LineBlast::LoadBitmap()
	{
		int *bmpID[] = { blueBmp, purpleBmp, orangeBmp, greenBmp , redBmp, yellowBmp };

		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 30; j++)
				horizontal[i][j].LoadBitmap(bmpID[i][j + 55], RGB(254, 191, 200));

			for (int j = 0; j < 30; j++)
				vertical[i][j].LoadBitmap(bmpID[i][j + 25], RGB(254, 191, 200));
		}
	}

	void LineBlast::OnMove()
	{
		currentShow++;
	}

	void LineBlast::OnShow()
	{
		//if (*sound && currentShow == 1)
			//CAudio::Instance()->Play(AUDIO_LINE_BLAST, false);

		switch (powerStyle)
		{
		case 1:
			horizontal[style - 1][currentShow].SetTopLeft(x - (horizontal[style - 1][currentShow].Width() / 2 - 25), y);
			horizontal[style - 1][currentShow].ShowBitmap();
			break;
		case 2:
			vertical[style - 1][currentShow].SetTopLeft(x, y - (vertical[style - 1][currentShow].Height() / 2 - 25));
			vertical[style - 1][currentShow].ShowBitmap();
			break;
		default:
			GAME_ASSERT(0, "Invalid power style");
		}
	}

	bool LineBlast::IsEnd()
	{
		return currentShow >= 29;
	}

	CAnimation SuperBlast::chocolate;

	SuperBlast::SuperBlast(int x, int y, int delay, bool showAll) :currentShow(0), lightningDelay(delay), showAll(showAll)
	{
		this->x = x;
		this->y = y;
		chocolate.SetDelayCount(3);
		sound = &CGameState::sound;
	}

	SuperBlast::~SuperBlast()
	{
		//CAudio::Instance()->Stop(AUDIO_SUPER_REMOVE);
	}

	void SuperBlast::OnMove()
	{
		currentShow++;
		chocolate.OnMove();

		for (auto i = magicBlasts.begin(); i != magicBlasts.end();)
		{
			if ((*i).IsEnd())
				i = magicBlasts.erase(i);
			else
			{
				(*i).OnMove();
				i++;
			}
		}
	}

	void SuperBlast::OnShow()
	{
		if (!target.size())
			return;

		showAll ? ShowLightning(true) : ShowLightning();

		for (auto i = magicBlasts.begin(); i != magicBlasts.end(); i++)
		{	
			(*i).OnShow();
		}
	}

	void SuperBlast::ShowLightning(bool showAll)
	{
		chocolate.SetTopLeft(x, y);
		chocolate.OnShow();
		CDC *pDC = CDDraw::GetBackCDC();
		CPen penLighting;
		CPen *pPen;

		penLighting.CreatePen(PS_SOLID | PS_COSMETIC, showAll ? 5 : rand() % 10 + 1, RGB(207, 249, 245));

		pPen = pDC->SelectObject(&penLighting);

		if (showAll)
		{
			for (auto i = target.begin(); i != target.end(); i++)
			{
				DrawLine(pDC, CPoint(x + 25, y + 25), *i); //Draw a lightning from current position to target
			}
		}
		else
		{
			for (int i = lightningDelay; i >= 0; i--)
			{
				if (currentShow - i >= 0 && currentShow - i < target.size())
				{
					DrawLine(pDC, CPoint(x + 25, y + 25), target[currentShow - i]);
				}
			}
		}

		pDC->SelectObject(pPen);
		CDDraw::ReleaseBackCDC();
		Sleep(5);
	}

	void SuperBlast::DrawLine(CDC* pDC, const CPoint& start, const CPoint& end)
	{
		list<CPoint>* route = GetRoutePoints(start, end); 

		pDC->MoveTo(*route->begin());

		for (auto j = route->begin()++; j != route->end(); j++)
		{
			pDC->LineTo(*j);
		}

		delete route;

		MagicBlast blast(end);
		bool blastExists = false;

		for (auto i = magicBlasts.begin(); i != magicBlasts.end(); i++)
		{	
			if ((*i) == blast)
			{
				blastExists = true;
				break;
			}
		}

		if (!blastExists)
			magicBlasts.push_back(blast);
	}

	list<CPoint>* SuperBlast::GetRoutePoints(CPoint start, CPoint end)
	{
		list<CPoint>* route = new list<CPoint>();
		int interval = abs(start.x - end.x) / (abs(start.x - end.x) > 10 ? abs(start.x - end.x) / 10 : abs(start.x - end.x) > 0 ? abs(start.x - end.x) : 1);
		int totalPoint = abs(start.x - end.x) > 10 ? abs(start.x - end.x) / 10 : abs(start.x - end.x);

		int reverse = start.x > end.x ? -1 : 1;

		for (int i = 0; i < totalPoint; i++)
		{
			CPoint point;
			point.x = start.x + interval * i * reverse;
			point.y = (point.x * end.y - point.x * start.y - start.x * end.y + end.x * start.y) / (end.x - start.x);
			route->push_back(point);
		}

		route->push_back(end);

		int j = 0;

		for (auto i = route->begin(); i != route->end(); i++, j++)
		{
			if (j % 2) i->x += rand() % 20 - 10;
			else i->y += rand() % 20 - 10;
		}

		return route;
	}

	void SuperBlast::AddPoint(int x, int y)
	{
		target.push_back(CPoint(x, y));
	}

	bool SuperBlast::IsEnd()
	{
		return ((currentShow >= target.size() + lightningDelay) || (showAll && currentShow >= 10));
	}

	void SuperBlast::LoadBitmap()
	{
		chocolate.AddBitmap("Bitmaps\\BlastSuperCandy1.bmp", RGB(254, 191, 200));
		chocolate.AddBitmap("Bitmaps\\BlastSuperCandy2.bmp", RGB(254, 191, 200));
		chocolate.AddBitmap("Bitmaps\\BlastSuperCandy3.bmp", RGB(254, 191, 200));
		chocolate.AddBitmap("Bitmaps\\BlastSuperCandy4.bmp", RGB(254, 191, 200));
		chocolate.AddBitmap("Bitmaps\\BlastSuperCandy5.bmp", RGB(254, 191, 200));
	}

	CMovingBitmap MagicBlast::bmp[4];

	MagicBlast::MagicBlast(int x, int y) :x(x), y(y), currentShow(0)
	{
		//sound = &CGameState::sound;
	}

	MagicBlast::MagicBlast(CPoint p) : x(p.x), y(p.y), currentShow(0)
	{ }

	bool MagicBlast::IsEnd()
	{
		return currentShow == 3;
	}

	void MagicBlast::LoadBitmap()
	{
		bmp[0].LoadBitmap("Bitmaps\\MagicBlast1.bmp", RGB(255, 255, 255));
		bmp[1].LoadBitmap("Bitmaps\\MagicBlast2.bmp", RGB(255, 255, 255));
		bmp[2].LoadBitmap("Bitmaps\\MagicBlast3.bmp", RGB(255, 255, 255));
		bmp[3].LoadBitmap("Bitmaps\\MagicBlast4.bmp", RGB(255, 255, 255));
	}

	void MagicBlast::OnMove()
	{
		delay = delay == 1 ? 0 : 1;

		if (delay) 
			currentShow++;
	}

	void MagicBlast::OnShow()
	{
		if (delay)
		{
			bmp[currentShow].SetTopLeft(x - bmp[currentShow].Width() / 2, y - bmp[currentShow].Height() / 2);
			bmp[currentShow].ShowBitmap();
		}
	}

	bool MagicBlast::operator==(const MagicBlast & rhs)
	{
		return rhs.x == x && rhs.y == y;
	}
}


