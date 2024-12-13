#include "MyGame.h"

MyGame::MyGame() : AbstractGame(), score(0), lives(3), numKeys(2750), gameWon(false), box(10, 6, 30, 30) {
	TTF_Font * font = ResourceManager::loadFont("res/fonts/Wkeys.ttf", 2.5);
	gfx->useFont(font);
	gfx->setVerticalSync(true);

    for (int i = 0; i < numKeys; i++) {
		std::shared_ptr<Particle> particle = std::make_shared<Particle>();
		particle->isAlive = true;
		particle->pos = Point2(getRandom(0, 800), getRandom(0, 600));
		Particles.push_back(particle);
		particle->color = getRandomColor(100, 250);
	}
}

MyGame::~MyGame() {

}

void MyGame::handleKeyEvents() {
	if (eventSystem->isPressed(Key::SPACE)) {
		for (auto key : Particles)
			if (key->isAlive)
				key->pos.x += 1;
	}  

	if (eventSystem->isPressed(Key::A)) {
		for (auto key : Particles) {
			if (key->isAlive) {
				key->color = getRandomColor(160, 250);
				key->pos = Point2(getRandom(0, 800), getRandom(0, 600)); 
			}
		}
	}

	if (eventSystem->isPressed(Key::S)) {
		for (auto key : Particles)
			if (key->isAlive)
				key->pos.y -= 1;
	}

	if (eventSystem->isPressed(Key::D)) {
		for (auto key : Particles) {
			if (key->isAlive) {
				key->color = getRandomColor(95, 105); 
				key->pos = Point2(getRandom(300, 500), getRandom(100, 500));
			}
		}
	}

}

void MyGame::update() {
	/*box.x += velocity.x;
	box.y += velocity.y;

	for (auto key : Particles) {
		if (key->isAlive && box.contains(key->pos)) {
			score += 500;
			key->isAlive = false;
			numKeys--;
		}
	}

	velocity.x = 0;
	velocity.y = 0; */

	if (numKeys == 0) {
		gameWon = true;
	}

	/*for (auto key : Particles)
		if (key->isAlive)
	key->pos = Point2(getRandom(0, 800), getRandom(0, 600)); */


} 

void MyGame::render() {
	gfx->setDrawColor(SDL_COLOR_BLACK);
	gfx->drawRect(box);

	for (auto key : Particles)
		if (key->isAlive) {
			gfx->setDrawColor(key->color);
			gfx->drawCircle(key->pos, 1);
		}


	if (eventSystem->isPressed(Mouse::BTN_LEFT)) {
		Point2 mousePos = eventSystem->getMousePos();
		for (auto key : Particles)
			if (key->isAlive)
				key->pos = Point2(getRandom(mousePos.x, mousePos.x + 30),
					getRandom(mousePos.y, mousePos.y + 30));

	}

}; 

void MyGame::renderUI() {
	gfx->setDrawColor(SDL_COLOR_WHITE);
	std::string scoreStr = std::to_string(score);
	gfx->drawText(scoreStr, 780 - scoreStr.length() * 25, 25);

	if (gameWon)
		gfx->drawText("YOU WON", 250, 500); 
} 