namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѷ|�@���u�����y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class StagePlay {
	public:
		StagePlay();
		void LoadBitmap();
		void OnShow();
		void OnMove();
	private:
		int x, y;
		int floor;
		bool rising;
		int initial_velocity;
		int velocity;
		CAnimation animation;
	};
}
