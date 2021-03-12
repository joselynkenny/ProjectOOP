namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѷ|�@���u�����y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class CBouncingBall {
	public:
		CBouncingBall();
		void LoadBitmap();
		void OnShow();
		void OnMove();
		void SetFloor(int);
		void SetXY(int, int);
		void SetVelocity(int);
	private:
		int x, y;
		int floor;
		bool rising;
		int initial_velocity;
		int velocity;
		CAnimation animation;
	};
}