namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供會一直彈跳的球
	// 看懂就可以改寫成自己的程式了
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