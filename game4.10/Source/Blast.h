#pragma once
#ifndef BLAST_H
#define BLAST_H

namespace game_framework
{
	class Blast
	{
	public:
		virtual ~Blast() {};
		virtual void LoadBitmap() {};
		virtual void OnShow() {};
		virtual void OnMove() {};
		virtual void SetTopLeft(int x, int y);
		virtual bool IsEnd() = 0;
	protected:
		int x, y;
		int style;
		bool *sound;
	};

	class NormalBlast :public Blast 
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

	class LineBlast :public Blast
	{
	public:
		LineBlast(int style, int x, int y, int power);
		static void LoadBitmap();
		void OnMove();
		void OnShow();
		bool IsEnd();
	private:
		static CMovingBitmap horizontal[6][30];
		static CMovingBitmap vertical[6][30];
		int currentShow;
		int powerStyle;
	};

	class MagicBlast :public Blast
	{
	public:
		MagicBlast(int x, int y);
		MagicBlast(CPoint);
		bool IsEnd();
		static void LoadBitmap();
		void OnMove();
		void OnShow();
		bool operator==(const MagicBlast& rhs);
	private:
		static CMovingBitmap bmp[4];
		int currentShow;
		int delay;
		int x, y;
	};

	class SuperBlast :public Blast
	{
	public:
		SuperBlast(int x, int y, int delay = 0, bool showAll = false);
		~SuperBlast();
		void AddPoint(int x, int y);
		bool IsEnd();
		static void LoadBitmap();
		void OnMove();
		void OnShow();
	private:
		void ShowLightning(bool showAll = false);
		void DrawLine(CDC*, const CPoint&, const CPoint&);
		list<CPoint>* GetRoutePoints(CPoint, CPoint);
		static CAnimation chocolate;
		vector<CPoint> target;
		list<MagicBlast> magicBlasts;
		size_t currentShow;
		int lightningDelay;		
		bool showAll;			
	};
}
#endif
