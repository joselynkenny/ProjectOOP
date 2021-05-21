#ifndef AREA_H
#define AREA_H

#define MaxHeight 13
#define MaxWidth 20

namespace game_framework
{
	class Area
	{
	public:
		Area();
		~Area();
		int GetScore();									
		void InitCandy(bool drop = true);				
		bool IsGameOver();
		int GetCurrentStage();
		void LoadBitmap();								
		void LoadStage(vector<Stage*>& stages, int);	
		void OnShow();									
		void OnMove();
		void OnKeyDown(UINT, UINT, UINT);				
		void OnKeyUp(UINT, UINT, UINT);					
		void OnLButtonDown(UINT nFlags, CPoint point);	
		void OnLButtonUp(UINT nFlags, CPoint point);		
	private:
		int ClearCombo();								
		int Compare(int, int);							
		void Delay();									
		void DropCandy();
		int DropCandyVertical();
		int DropCandyHorizontal();
		int DeleteCombo(set<Candy*>&);					
		void Find(Candy*, unsigned&, unsigned&);		
		int FindCombo();
		void GetCandies(set<Candy*>&, int, int, int);	
		void GetLine(vector<Candy*>&, vector<Candy*>&, char check);							
		void GetWordBmp(double**, int**, CMovingBitmap**, int);
		void GotoGameStateOver(bool result);
		void InitClickedCandy();						
		void InitGameArea(int);
		bool IsDropping();								
		bool IsNeighbour(Candy&, Candy&);				
		void OnMoveBlasts();
		void OnMoveEnding();
		//void PlayVoiceEffect(int audio_id);
		void PowerAll(int style, int power, int x, int y);	
		int PutCandy();									
		void PutEndingBonus();
		int RemoveContinuous(vector<Candy*>&, char, bool(*)(Candy*, Candy*), set<Candy*>&);	
		void RemoveContinuous(vector<Candy*>&, unsigned, unsigned, char, set<Candy*>&);		
		void ReleaseInOrder();
		void ReleasePower(Candy*, unsigned row = 0, unsigned column = 0);					
		void ReleaseSwap();								
		void RemoveAll(int row, int column);			
		void RemoveRow(unsigned);						
		void RemoveColumn(unsigned);					
		void RemoveSquare(int, int, int);				
		void RemoveStyle(int x, int y, int style = 0);	
		void ShowLoading();								
		void ShowPortal(int position);
		void SwapCandy();								
		void TeleportCandy();
		void UpdateCurPosition();						
		const int x, y;									
		int map[MaxHeight][MaxWidth];					
		int delay, delayRemoveStyle;
		int currentComboSound, totalCandyCleared;
		int MAX_RAND_NUM;								
		bool initiating, ending, running, gameOver;
		bool *sound;
		bool playingVoice;
		bool delayRemove, releaseSwap;
		bool goldFinger;
		Candy* curPosition[MaxHeight][MaxWidth];		
		Candy candies[MaxHeight][MaxWidth];				
		CMovingBitmap area, singleJelly, doubleJelly;	
		CMovingBitmap sweet, tasty, delicious, divine, sugarCrush;	
		CMovingBitmap portalStart1, portalStart2, portalEnd1, portalEnd2;
		vector<Candy*> clickedCandies;					
		vector<Stage*>::iterator stage;					
		list<pair<int, int>> spawnArea;
		list<Blast*> blasts;
		list<list<Candy*>*> removeList;					
		list<Candy*> endingBonus;
		ScoreBoard scoreBoard;
	};
}

#endif 