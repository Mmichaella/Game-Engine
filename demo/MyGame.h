#ifndef __TEST_GAME_H__
#define __TEST_GAME_H__

#include "../engine/AbstractGame.h"

struct Particle {
	Point2 pos;
	bool isAlive;
	SDL_Color color;
};



class MyGame : public AbstractGame {
	private:
		Rect box;

		Vector2i velocity;

		std::vector<std::shared_ptr<Particle>> Particles;
		

		/* GAMEPLAY */
		int score, numKeys, lives;
		bool gameWon;

		void handleKeyEvents();
		void update();
		void render();
		void renderUI();

	public:
        MyGame();
		~MyGame();
};

#endif