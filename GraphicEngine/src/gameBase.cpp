#include "GL/glew.h"
#include "gameBase.h"
#include <stdlib.h>
#include <iostream>
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"


GameBase::GameBase() {
	window = new Window();
	renderer = new Renderer();
	shape = new Shape(GL_QUADS, renderer);
	sprite1 = new Sprite(renderer, false, false);
	sprite2 = new Sprite(renderer, true, true);
	sprite3 = new Sprite(renderer, false, true);
	input = new Input();
	idle = new Animation();
}
GameBase::~GameBase() {
	if (window != NULL)
		delete window;
	if (renderer != NULL)
		delete renderer;
	if (shape != NULL)
		delete shape;
	if (sprite1 != NULL)
		delete sprite1;
	if (sprite2 != NULL)
		delete sprite2;
	if (sprite3 != NULL)
		delete sprite3;
	if (idle != NULL)
		delete idle;
}

int GameBase::init() {
	GLFWwindow* newWindow;

	window->StartWindow(800, 600, "Graphics Engine", newWindow);
	if (!newWindow)
	{
		glfwTerminate();
		return -1;
	}
	input->setInputWindow(newWindow);

	// Make the window's context current /
	glfwMakeContextCurrent(newWindow);
	glViewport(0, 0, 800, 600);
	glewExperimental = GL_TRUE;

	glewInit();
	if (glewInit() != GLEW_OK) {
		std::cout << "Error in Glew Init" << std::endl;
		return 0;
	}
	//shape->setColor(0.5f, 1.0f, 0.7f);
	//shape->init();
	renderer->setDefaultProjection();
	renderer->setDefaultView();
	glGetIntegerv(GL_CONTEXT_COMPATIBILITY_PROFILE_BIT, nullptr);
	std::cout << glGetString(GL_VERSION) << std::endl;
	unsigned int textureShader = renderer->createTextureProgram();
	//unsigned int colorShader = renderer->createColorProgram();
	sprite1->setTexture("res/raw/meme.jpg");
	sprite2->setTexture("res/raw/spriteSheet.png");
	sprite3->setTexture("res/raw/Sun.png");
	idle->addFrame(0,0,(525/7),75,525,75,1);
	idle->addFrame(0,0,(525/6),75,525,75,1);
	idle->addFrame(0,0,(525/5),75,525,75,1);
	idle->addFrame(0,0,(525/4),75,525,75,1);
	idle->addFrame(0,0,(525/3),75,525,75,1);
	idle->addFrame(0,0,(525/2),75,525,75,1);
	idle->addFrame(0,0,(525/1),75,525,75,1);
	idle->addAnimation();
	sprite2->setAnimation(idle);
	sprite2->SetCurrentAnimationIndex(0);
	sprite1->setColor(1, 1, 1);
	sprite2->setColor(1, 1, 1);
	sprite3->setColor(1, 1, 1);
	sprite1->setPosition(0, 0, -1.0f);
	sprite1->setScale(0.5f, 0.5f, 0.5f);
	sprite2->setPosition(0.5f, 0, -1.0f);
	sprite2->setScale(1, 0.2f, 0.5f);
	sprite3->setPosition(0, 0.75f, -1.0f);
	sprite3->setScale(0.25f, 0.25f, 0.5f);
	//renderer->setSpriteAttrib(textureShader);

	float rotate = 0;
	float x1 = 0; float y1 = 0; float z1 = -1;
	float x2 = 0; float y2 = 0; float z2 = -1;
	float timer = 0; int seconds = 0;
	while (!glfwWindowShouldClose(newWindow))
	{
		time.tick();
		glClearColor(0.1f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//shape->draw(colorShader, shape->getTRS());
		sprite1->draw(textureShader, sprite1->getTRS());
		sprite2->updateAnimation(getTime());
		sprite2->draw(textureShader, sprite2->getTRS());
		sprite3->draw(textureShader, sprite3->getTRS());
		// Swap front and back buffers /
		glfwSwapBuffers(newWindow);
		if (input->getKey(D)) {
			x1 += 0.004f;
			sprite1->setPosition(x1, y1, z1);
		}
		if (input->getKey(RIGHT)) {
			x2 += 0.004f;
			sprite2->setPosition(x2, y2, z2);
		}
		if (input->getKey(A)) {
			x1 -= 0.004f;
			sprite1->setPosition(x1, y1, z1);
		}
		if (input->getKey(LEFT)) {
			x2 -= 0.004f;
			sprite2->setPosition(x2, y2, z2);
		}
		if (input->getKey(W)) {
			y1 += 0.004f;
			sprite1->setPosition(x1, y1, z1);
		}
		if (input->getKey(UP)) {
			y2 += 0.004f;
			sprite2->setPosition(x2, y2, z2);
		}
		if (input->getKey(S)) {
			y1 -= 0.004f;
			sprite1->setPosition(x1, y1, z1);
		}
		if (input->getKey(DOWN)) {
			y2 -= 0.004f;
			sprite2->setPosition(x2, y2, z2);
		}
		if (input->getKey(E)) {
			rotate -= 2 * time.deltaTime();
		}
		if (input->getKey(Q)) {
			rotate += 2 * time.deltaTime();
		}
		if (input->getKey(SPACE)) {
			sprite2->setColor(0.5f, 0.5f, 1.0f);
		}
		if (input->getKey(C)) {
			sprite2->setColor(1, 0, 0);
		}
		timer += time.deltaTime();
		sprite1->setRotZ(rotate);
		glfwPollEvents();
	}
	glDeleteProgram(textureShader);
	glfwTerminate();
	return 0;
}

void GameBase::update() {

}
void GameBase::unload() {

}
Time& GameBase::getTime() {
	return time;
}