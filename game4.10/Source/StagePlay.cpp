#include "stdafx.h"
/*#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "StagePlay.h"

namespace game_framework {

	StagePlay::StagePlay()
		: style(-1)
	{	}
	StagePlay::~StagePlay()
	{}
	StagePlay* StagePlay::Click()
	{
		on = on == true ? false : true;
		return this;
	}
	void StagePlay::LoadBitmap() {

		blue.LoadBitmap(IDB_BLUE_C);
		green.LoadBitmap(IDB_GREEN_C, RGB(255, 255, 255));
		orange.LoadBitmap(IDB_ORANGE_C, RGB(255, 255, 255));
		purple.LoadBitmap(IDB_PURPLE_C, RGB(255, 255, 255));
		red.LoadBitmap(IDB_RED_C, RGB(255, 255, 255));
		yellow.LoadBitmap(IDB_YELLOW_C, RGB(255, 255, 255));
	}
	void StagePlay::SetDestination(int x, int y)
	{
		dx = x;
		dy = y;
	}
	void StagePlay::InitClick()
	{
		on = false;
	}
	void StagePlay::OnMove(bool mute)
	{
		if (pushX != 0 || pushY != 0)
		{
			int offsetX = pushX > 0 ? 1 : -1, offsetY = pushY > 0 ? 1 : -1;
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
			return;
		}
	}
	int StagePlay::GetCurrentX()
	{
		return x;
	}
	int StagePlay::GetCurrentY()
	{
		return y;
	}
	int StagePlay::GetPower()
	{
		return power;
	}
	int StagePlay::GetTopLeftX()
	{
		return dx;
	}
	int StagePlay::GetTopLeftY()
	{
		return dy;
	}
	int StagePlay::GetTopLeft(char c)
	{
		switch (c)
		{
		case 'x': return GetTopLeftX();
		case 'y': return GetTopLeftY();
		default: return 0;
		}
	}
}*/