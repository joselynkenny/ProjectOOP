#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Candy.h"

namespace game_framework
{
	static int	redBmpId[8] = {IDB_RED_C, IDB_RED_CLICKED, IDB_RED_HOR, IDB_RED_HOR_C, IDB_RED_VER, IDB_RED_VER_C, IDB_RED_PACK, IDB_RED_PACK_C },
				orangeBmpId[8] = { IDB_ORANGE_C, IDB_ORANGE_CLICKED, IDB_ORANGE_HOR, IDB_ORANGE_HOR_C, IDB_ORANGE_VER, IDB_ORANGE_VER_C, IDB_ORANGE_PACK, IDB_ORANGE_PACK_C },
				yellowBmpId[8] = { IDB_YELLOW_C, IDB_YELLOW_CLICKED, IDB_YELLOW_HOR, IDB_YELLOW_HOR_C, IDB_YELLOW_VER, IDB_YELLOW_VER_C, IDB_YELLOW_PACK, IDB_YELLOW_PACK_C },
				greenBmpId[8] = { IDB_GREEN_C, IDB_GREEN_CLICKED, IDB_GREEN_HOR, IDB_GREEN_HOR_C, IDB_GREEN_VER, IDB_GREEN_VER_C, IDB_GREEN_PACK, IDB_GREEN_PACK_C },
				blueBmpId[8] = { IDB_BLUE_C, IDB_BLUE_CLICKED, IDB_BLUE_HOR, IDB_BLUE_HOR_C, IDB_BLUE_VER, IDB_BLUE_VER_C, IDB_BLUE_PACK, IDB_BLUE_PACK_C },
				purpleBmpId[8] = { IDB_PURPLE_C, IDB_PURPLE_CLICKED, IDB_PURPLE_HOR, IDB_PURPLE_HOR_C, IDB_PURPLE_VER, IDB_PURPLE_VER_C, IDB_PURPLE_PACK, IDB_PURPLE_PACK_C },
				audioID[4] = {AUDIO_CANDY_LAND1, AUDIO_CANDY_LAND2, AUDIO_CANDY_LAND3, AUDIO_CANDY_LAND4 };

	CMovingBitmap
		Candy::normal[6], Candy::normalClick[6],
		Candy::horizon[6], Candy::horizonClick[6],
		Candy::vertical[6], Candy::verticalClick[6],
		Candy::pack[6], Candy::packClick[6],
		Candy::chocolate[6], Candy::chocolateClick[6];

	Candy::Candy(int id, int x, int y)
		: style(id), rawStyle(id), x(x), y(y), dx(x), dy(y), onClick(false), dropSpeed(0), power(0),
		pushX(0), pushY(0), sound(&CGameState::sound)
	{}

	Candy::Candy(int x, int y)
		: style(-1), x(x), y(y), dx(x), dy(y), sound(&CGameState::sound)
	{}

	Candy::Candy()
		: style(-1), sound(&CGameState::sound)
	{}

	Candy::~Candy()
	{}

	void Candy::LoadBitmap()
	{
		int *bmpID[] = { blueBmpId, purpleBmpId, orangeBmpId, greenBmpId , redBmpId, yellowBmpId };

		for (int i = 0; i < 6; i++)
		{
			normal[i].LoadBitmap(bmpID[i][0], RGB(255, 255, 255));
			normalClick[i].LoadBitmap(bmpID[i][1], RGB(255, 255, 255));

			horizon[i].LoadBitmap(bmpID[i][2], RGB(255, 255, 255));
			horizonClick[i].LoadBitmap(bmpID[i][3], RGB(255, 255, 255));

			vertical[i].LoadBitmap(bmpID[i][4], RGB(255, 255, 255));
			verticalClick[i].LoadBitmap(bmpID[i][5], RGB(255, 255, 255));

			pack[i].LoadBitmap(bmpID[i][6], RGB(255, 255, 255));
			packClick[i].LoadBitmap(bmpID[i][7], RGB(255, 255, 255));

			chocolate[i].LoadBitmap(IDB_SUPER, RGB(255, 255, 255));
			chocolateClick[i].LoadBitmap(IDB_SUPER_C, RGB(255, 255, 255));
		}
	}

	void Candy::OnMove(bool mute)
	{
		if (pushX != 0 || pushY != 0)
		{
			int offsetX = pushX > 0 ? 1 : -1;
			int offsetY = pushY > 0 ? 1 : -1;

			if (pushX != 0)
			{
				x += offsetX;
				pushX -= offsetX;
			}

			if (pushY != 0)
			{
				y += offsetY;
				pushY -= offsetY;
			}
		}

		int fixSpeed = GAME_CYCLE_TIME * 5 / 16;

		if (y != dy && x != dx)
		{
			y < dy ? y += fixSpeed : y -= fixSpeed;
			x < dx ? x += fixSpeed : x -= fixSpeed;
		}
		else if (x != dx) {
			x > dx ? x -= fixSpeed : x += fixSpeed;
		}
		else if (y < dy)
		{
			y += dropSpeed;
			dropSpeed += GAME_CYCLE_TIME * 2 / 16;

			if (y > dy)
			{
				y = dy;
				dropSpeed = 0;
			}
		}

		y > dy ? y -= fixSpeed * 2 : y;
	}

	void Candy::OnShow()
	{
		if (!style) return;

		CMovingBitmap *idle, *click;
		GetCurrentShow(&idle, &click);

		if (!onClick)
		{
			idle->SetTopLeft(x, y);
			idle->ShowBitmap();
		}
		else
		{
			click->SetTopLeft(x, y);
			click->ShowBitmap();
		}
	}

	void Candy::SetDestination(int x, int y)
	{
		dx = x;
		dy = y;
	}

	void Candy::SetDestination(int y)
	{
		dy = y;
	}

	int Candy::GetStyle()
	{
		return style;
	}

	void Candy::SetStyle(int style)
	{
		this->style = style;
	}

	int Candy::GetTopLeftX()
	{
		return dx;
	}

	int Candy::GetTopLeftY()
	{
		return dy;
	}

	int Candy::GetTopLeft(char c)
	{
		switch (c)
		{
		case 'x': return GetTopLeftX();
		case 'y': return GetTopLeftY();
		default: return 0;
		}
	}

	int Candy::GetCurrentX()
	{
		return x;
	}

	int Candy::GetCurrentY()
	{
		return y;
	}

	bool Candy::IsMoving()
	{
		if (style <= 0) {
			return 0;
		}

		return x != dx || y != dy;
	}

	bool Candy::IsClicked()
	{
		return onClick;
	}

	void Candy::Delete()
	{
		power = 0;
		style = 0;
	}

	Candy* Candy::Click()
	{
		if (onClick == true) {
			onClick = false;
		}
		else {
			onClick = true;
		}

		return this;
	}

	void Candy::SetPower(int power)
	{
		this->power = power;
	}

	int Candy::GetPower()
	{
		return power;
	}

	void Candy::Relive()
	{
		style = rawStyle;
	}

	void Candy::InitClick()
	{
		onClick = false;
	}

	void Candy::Push(int x, int y)
	{
		this->x = x > 0 ? this->x + 20 : x < 0 ? this->x - 20 : this->x;
		this->y = y > 0 ? this->y + 20 : y < 0 ? this->y - 20 : this->y;
	}

	void Candy::GetCurrentShow(CMovingBitmap **idle, CMovingBitmap **click)
	{
		switch (power)
		{
		case 0:
			*idle = &normal[style - 1];
			*click = &normalClick[style - 1];
			break;
		case 1:
			*idle = &horizon[style - 1];
			*click = &horizonClick[style - 1];
			break;
		case 2:
			*idle = &vertical[style - 1];
			*click = &verticalClick[style - 1];
			break;
		case 3:
			*idle = &pack[style - 1];
			*click = &packClick[style - 1];
			break;
		case 4:
			*idle = &chocolate[style - 1];
			*click = &chocolateClick[style - 1];
			break;
		}
	}
}