/*#ifndef STAGE_PLAY
#define STAGE_PLAY
namespace game_framework {

	class StagePlay
	{
	public:
		StagePlay();
		~StagePlay();
		StagePlay* Click();							
		static void LoadBitmap();			
		void OnMove(bool mute = false);		
		void OnShow();	
		void InitClick();
		void SetDestination(int, int);
		int GetCurrentX();					
		int GetCurrentY();
		int GetPower();	
		int GetTopLeftX();					
		int GetTopLeftY();					
		int GetTopLeft(char c);

	private:
		static CMovingBitmap box, green,red, blue, orange, purple, yellow;
		bool on;
		int style, x, y, dx, dy,power, pushX, pushY;
	};
}
#endif*/
