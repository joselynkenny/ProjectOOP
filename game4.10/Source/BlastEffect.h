#pragma once
#ifndef BLASTEFFECT_H
#define BLASTEFFECT_H

/*
namespace game_framework{
	class BlastEffect
	{
	public:
		virtual ~BlastEffect() {};
		virtual void LoadBitmap() {};
		virtual void OnShow() {};
		virtual void OnMove() {};
		virtual void SetTopLeft(int x, int y);
		virtual bool IsEnd() = 0;
	protected:
		int x, y;
		int style;
	};

	class NormalBlast :public BlastEffect 
	{
	public:
		NormalBlast();
		NormalBlast(int style, int x, int y);
		static void LoadBitmap();
		void OnMove();
		void OnShow();
		bool IsEnd();
	private:
		static CMovingBitmap normalBlast[6][10];
		static CMovingBitmap shatter[6][15];
		double size;
		int currentShow;
		int shift[3][3];				
		int shatterPosition[3][2];			
		int shatterShow[3];
		const int totalShow;
	};
}
*/

#endif