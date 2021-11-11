#include "stdafx.h"
#include "SceneHome.h"
#include "SceneIngame.h"

SceneHome* SceneHome::create()
{
	auto ret = new SceneHome();
	if (ret && ret->init()) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool SceneHome::init()
{
	if (!Scene::init()) return false;

	Sprite* img = Sprite::create("res/title.png");
	addChild(img);
	//img->setOpacity(0);

	img->setPosition(Vec2(720 / 2, 650));

	addChild(btnStart = Button::create("res/buttonStart.png", "res/buttonStart_pressed.png", "res/buttonStart_pressed.png"));
	
	addChild(btnQuit = Button::create("res/exit.png", "res/exit_pressed.png", "res/exit_pressed.png"));
	btnQuit->setPosition(Vec2(720 - 70, 1280 - 200));

	btnStart->setPosition(Vec2(720 / 2, 200));
	btnStart->setScale(1.5);

	btnStart->addClickEventListener([=](Ref* r) {
		auto scene = SceneIngame::create();
		auto transit = TransitionSlideInR::create(0.125f, scene);
		Director::getInstance()->replaceScene(transit);
		});

	btnQuit->addClickEventListener([=](Ref* r) {
		Director::getInstance()->end();
		});

	Global::getInstance()->stopBackgroundMusic();

	return true;
}
