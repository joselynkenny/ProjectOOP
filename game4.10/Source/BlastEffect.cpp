#include "stdafx.h"
#include <omp.h>
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "BlastEffect.h"


/*
namespace gameframework {
	static int redBmp[] = { IDB_RED_EXPL1, IDB_RED_EXPL2, IDB_RED_EXPL3, IDB_RED_EXPL4, IDB_RED_EXPL5,
						    IDB_RED_EXPL6, IDB_RED_EXPL7, IDB_RED_EXPL8, IDB_RED_EXPL9, IDB_RED_EXPL10 },

			   orangeBmp[] = { IDB_ORANGE_EXPL1, IDB_ORANGE_EXPL2, IDB_ORANGE_EXPL3, IDB_ORANGE_EXPL4, IDB_ORANGE_EXPL5,
							 IDB_ORANGE_EXPL6, IDB_ORANGE_EXPL7, IDB_ORANGE_EXPL8, IDB_ORANGE_EXPL9, IDB_ORANGE_EXPL10 },

			   greenBmp[] = {IDB_GREEN_EXPL1, IDB_GREEN_EXPL2, IDB_GREEN_EXPL3, IDB_GREEN_EXPL4, IDB_GREEN_EXPL5,
							 IDB_GREEN_EXPL6, IDB_GREEN_EXPL7, IDB_GREEN_EXPL8, IDB_GREEN_EXPL9, IDB_GREEN_EXPL10 },

			   blueBmp[] = { IDB_BLUE_EXPL1, IDB_BLUE_EXPL2, IDB_BLUE_EXPL3, IDB_BLUE_EXPL4, IDB_BLUE_EXPL5,
							 IDB_BLUE_EXPL6, IDB_BLUE_EXPL7, IDB_BLUE_EXPL8, IDB_BLUE_EXPL9, IDB_BLUE_EXPL10 },

			   yellowBmp[] = { IDB_YELLOW_EXPL1, IDB_YELLOW_EXPL2, IDB_YELLOW_EXPL3, IDB_YELLOW_EXPL4, IDB_YELLOW_EXPL5,
					           IDB_YELLOW_EXPL6, IDB_YELLOW_EXPL7, IDB_YELLOW_EXPL8, IDB_YELLOW_EXPL9, IDB_YELLOW_EXPL10 },

			   purpleBmp[] = { IDB_PURPLE_EXPL1, IDB_PURPLE_EXPL2, IDB_PURPLE_EXPL3, IDB_PURPLE_EXPL4, IDB_PURPLE_EXPL5,
						       IDB_PURPLE_EXPL6, IDB_PURPLE_EXPL7, IDB_PURPLE_EXPL8, IDB_PURPLE_EXPL9, IDB_PURPLE_EXPL10 },

	void BlastEffect::SetTopLeft(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	CMovingBitmap NormalBlast::normalBlast[6][10], NormalBlast::shatter[6][15];

	NormalBlast::NormalBlast() :currentShow(0), totalShow(0) {
		this->style = style;
		SetTopLeft(x, y);

		int direction[] = { -2, -1, 0, 2, 1 };

		#pragma omp parallel for
		for (int i = 0; i < totalShow; i++) {
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
				if (shift[i][2])
					shatterShow[i] = (shatterShow[i] - 1) < 0 ? (shatterShow[i] - 1) + 15 : (shatterShow[i] - 1);	//counter-clockwise
				else 
					shatterShow[i] = (shatterShow[i] + 1) % 15;	//clockwise
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

	bool NormalBlast::End()
	{
		return (currentShow == 25);
	}
}
*/
