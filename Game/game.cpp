#include "game.h"

float x = 0;
float y = 0;
float z = 0;
float xShape = 0;
float yShape = 0;
float zShape = 0;
float speed = 500;

float timerr = 0.0f; 
//int seconds = 0;
float rotate = 0.0f;

Game::Game() : GameBase(){
	shape = new Shape(rectangle, renderer);
	sprite1 = new Sprite(renderer, false);
	sprite2 = new Sprite(renderer, true);
	sprite3 = new Sprite(renderer, true);
	idle = new Animation();
}

Game::~Game() {

}

int Game::executeGame() {
	//init();
	return 0;
}

void Game::initGame() {
	shape->init();
	shape->setPosition(300, 300,0);
	shape->setScale(300, 300, 300);
	shape->setColor(1,0.5f, 0);

	sprite1->setTexture("res/raw/meme.jpg");
	sprite2->setTexture("res/raw/spriteSheet.png");
	idle->addFrame(0, 0, 525 / 7, 75, 525, 75, 1.0f, 7, 7);
	sprite2->setAnimation(idle);
	sprite2->SetCurrentAnimationIndex(0);
	sprite3->setTexture("res/raw/Sun.png");
	sprite1->setColor(1, 1, 1);
	sprite2->setColor(1, 1, 1);
	sprite3->setColor(1, 1, 1);
	sprite1->setPosition(1180, 620, 0);
	sprite1->setScale(100, 100, 100);
	sprite2->setPosition(window->getWidth()/2, window->getHeight()/2, 0);
	x = window->getWidth() / 2;
	y = window->getHeight() / 2;
	sprite2->setScale(100,100,100);
	sprite3->setPosition(window->getWidth() / 2, 600.0f, 0);
	sprite3->setScale(100,100,100);
}

void Game::updateGame() {
	shape->draw(colorShader);
	sprite1->draw(textureShader);
	sprite2->draw(textureShader);
	sprite2->updateAnimation(getTime());
	sprite3->draw(textureShader);

#pragma region SPRITE_INPUT
	if (input.getKey(D)) {
		x += speed * time.deltaTime();
		sprite2->setPosition(x, y, z);
	}
	if (input.getKey(A)) {
		x -= speed * time.deltaTime();
		sprite2->setPosition(x, y, z);
	}
	if (input.getKey(S)) {
		y -= speed * time.deltaTime();
		sprite2->setPosition(x, y, z);
	}
	if (input.getKey(W)) {
		y += speed * time.deltaTime();
		sprite2->setPosition(x, y, z);
	}
	if (input.getKey(X)) {
		sprite2->transform.position[0] = 100.0f;
	}

#pragma endregion

#pragma region SHAPE_INPUT

	if (input.getKey(SPACE)) {
		shape->setColor(1, 0, 0);
	}
	if (input.getKey(RIGHT)) {
		xShape += speed * time.deltaTime();
		shape->setPosition(xShape, yShape, zShape);
	}
	if (input.getKey(LEFT)) {
		xShape -= speed * time.deltaTime();
		shape->setPosition(xShape, yShape, zShape);
	}
	if (input.getKey(UP)) {
		yShape += speed * time.deltaTime();
		shape->setPosition(xShape, yShape, zShape);
	}
	if (input.getKey(DOWN)) {
		yShape -= speed * time.deltaTime();
		shape->setPosition(xShape, yShape, zShape);
	}
#pragma endregion

	if (collisionmanager->CheckCollision2D(sprite2, shape,
		sprite2->transform.scale + glm::vec3(sprite2->transform.scale.x, sprite2->transform.scale.y, sprite2->transform.scale.z),
		shape->transform.scale + glm::vec3(shape->transform.scale.x, shape->transform.scale.y, shape->transform.scale.z))) {
		std::cout << "Colisiono!" << std::endl;
	}
	else {
		std::cout << "no Colisiono!" << std::endl;
	}
}

void Game::unloadGame() {
	if (sprite1 != NULL) {
		delete sprite1;
	}
	if (sprite2 != NULL) {
		delete sprite2;
	}
	if (sprite3 != NULL) {
		delete sprite3;
	}
	if (idle != NULL) {
		delete idle;
	}
}