#pragma once
#ifndef BLASTEFFECT_H
#define BLASTEFFECT_H


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

	class LineBlast :public BlastEffect
	{
	public:
		LineBlast(int style, int x, int y, int power);
		static void LoadBitmap();
		void OnMove();
		void OnShow();
		bool IsLast();
	private:
		static CMovingBitmap horizontal[6][30];
		static CMovingBitmap vertical[6][30];
		int curShow;
		int powStyle;
	};

	class MagicBlast :public BlastEffect
	{
	public:
		MagicBlast(int x, int y);
		MagicBlast(CPoint);
		bool IsLast();
		static void LoadBitmap();
		void OnMove();
		void OnShow();
		bool operator==(const MagicBlast& rhs);
	private:
		static CMovingBitmap bmp[4];
		int curShow;
		int delay;
		int x, y;
	};

	class SuperBlast :public BlastEffect
	{
	public:
		SuperBlast(int x, int y, int delay = 0, bool showAll = false);
		~SuperBlast();
		void AddPoint(int x, int y);
		bool IsLast();
		static void LoadBitmap();
		void OnMove();
		void OnShow();
	private:
		void ShowLightning(bool showAll = false);
		void DrawLine(CDC*, const CPoint&, const CPoint&);
		list<CPoint>* GetRoutePoints(CPoint, CPoint);

		static CAnimation chocalate;
		vector<CPoint> target;
		list<MagicBlast> magicBlasts;
		int curShow;
		int lightningDelay;		
		bool showAll;			
	};
}


#endif