#ifndef SCOREBOARD_H
#define SCOREBOARD_H
namespace game_framework
{
	class ScoreBoard
	{
		friend class Area;
	public:
		ScoreBoard();
		void OnShow();
		void LoadBitmap();
		bool IsReachedTarget();

	private:
		void ShowStars();
		void ShowMoves();
		void ShowScoreBar();
		void ShowScore();
		void ShowTarget();
		CMovingBitmap scoreBar, blackBar, scoreBoard,
					  yellowStar, greenStar, redStar,
					  emptyStar2, emptyStar1,
					  target1, target2;
		CInteger score, moves, target;
		double oneStar, twoStar, threeStar, lastHighScore;
		int mode;
	};
}
#endif