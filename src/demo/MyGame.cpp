#include "MyGame.h"

MyGame::MyGame() : AbstractGame(), score(0), lives(2), numKeys(1000), gameWon(false), box(10, 6, 30, 30) {
	TTF_Font * font = ResourceManager::loadFont("res/fonts/ShinyCrystal.ttf", 72);
	gfx->useFont(font);
	gfx->setVerticalSync(true);

    for (int i = 0; i < numKeys; i++) {
        std::shared_ptr<GameKey> k = std::make_shared<GameKey>();
        k->isAlive = true;
        k->pos = Point2(getRandom(0, 800), getRandom(0, 600));
        gameKeys.push_back(k);
    }
}

MyGame::~MyGame() {

}

void MyGame::handleKeyEvents() {
	int speed = 5;

	if (eventSystem->isPressed(Key::W)) {
		velocity.y = -speed;
	}

	if (eventSystem->isPressed(Key::S)) {
		velocity.y = speed;
	}

	if (eventSystem->isPressed(Key::A)) {
		velocity.x = -speed;
	}

	if (eventSystem->isPressed(Key::D)) {
		velocity.x = speed;
	}
}

void MyGame::update() {
	/*box.x += velocity.x;
	box.y += velocity.y;

	for (auto key : gameKeys) {
		if (key->isAlive && box.contains(key->pos)) {
			score += 500;
			key->isAlive = false;
			numKeys--;
		}
	} */

	velocity.x = 0;
    velocity.y = 0;

	if (numKeys == 0) {
		gameWon = true;
	} 

	for (auto key : gameKeys)
		if (key->isAlive)
			key->pos.x += -1;

	for (auto key : gameKeys)
		if (key->isAlive)
			key->pos.y += +1;
	
}

void MyGame::render() {
	gfx->setDrawColor(SDL_COLOR_AQUA);
	gfx->drawRect(box);

	gfx->setDrawColor(SDL_COLOR_ORANGE);
	for (auto key : gameKeys)
        if (key->isAlive)
		    gfx->drawCircle(key->pos, 1);
}

void MyGame::renderUI() {
	gfx->setDrawColor(SDL_COLOR_GREEN);
	std::string scoreStr = std::to_string(score);
	gfx->drawText(scoreStr, 780 - scoreStr.length() * 50, 25);

	if (gameWon)
		gfx->drawText("YOU WON", 250, 500);
}