#ifndef CANDY_H
#define CANDY_H

namespace game_framework
{
	class Candy
	{
	public:
		Candy(int, int, int);
		Candy(int, int);
		Candy();
		~Candy();
		Candy* Click();						
		int GetCurrentX();					
		int GetCurrentY();					
		int GetPower();						
		int GetStyle();						
		int GetTopLeftX();					
		int GetTopLeftY();					
		int GetTopLeft(char c);				
		void InitClick();					
		bool IsMoving();					
		bool IsClicked();					
		void Delete();						
		static void LoadBitmap();			
		void OnMove(bool mute = false);		
		void OnShow();						
		void Push(int, int);				
		void Relive();						
		void SetDestination(int, int);		
		void SetDestination(int);			
		void SetStyle(int);					
		void SetPower(int);					
	private:
		void GetCurrentShow(CMovingBitmap**, CMovingBitmap**);
		static CMovingBitmap normal[6], normalClick[6],
							 horizon[6], horizonClick[6],
							 vertical[6], verticalClick[6],
							 pack[6], packClick[6],
							 chocolate[6], chocolateClick[6];
		bool *sound;
		int style, rawStyle;		
		int power;
		int x, y, dx, dy, pushX, pushY;			
		bool onClick;
		int dropSpeed;
	};
}

#endif
