#include "stdafx.h"
#include "SceneIngame.h"

void SceneIngame::createBlock(int x, int y, int type)
{
	Sprite* spr;
	spr->create("res/white.png");
	spr->setScale(2);
	spr->setPosition(720/2, 1280/2);
	addChild(spr);
}

int SceneIngame::getBlockData(int x, int y)
{
	return 0;
}

void SceneIngame::setBlockData(int x, int y, int type)
{
}

Sprite* SceneIngame::getBlockSprite(int x, int y)
{
	return nullptr;
}

void SceneIngame::setBlockSprite(int x, int y, Sprite* s)
{
}

void SceneIngame::destroyBlock(int x, int y)
{
}

SceneIngame* SceneIngame::create()
{
	auto ret = new SceneIngame();
	if(ret && ret->init()) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool SceneIngame::init()
{
	if(!Scene::init()) return false;

	return true;
}

void SceneIngame::onEnter()
{
	Scene::onEnter();

	this->initUI();
	this->initGame();
	
}

void SceneIngame::initUI()
{
}

void SceneIngame::initGame()
{
}

void SceneIngame::destroyUI()
{
}

void SceneIngame::destroyGame()
{
}

bool SceneIngame::onTouchBegan(Touch* t, Event* e)
{
	return false;
}

void SceneIngame::onTouchMoved(Touch* t, Event* e)
{
}

void SceneIngame::onTouchEnded(Touch* t, Event* e)
{
}
