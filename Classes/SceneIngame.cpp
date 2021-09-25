#include "stdafx.h"
#include "SceneIngame.h"
#include "Environment.h"

Vec2 SceneIngame::convertGameCoordToBlockCoord(const Vec2& gameCoord)
{
	Vec2 blockOrigin = BLOCK_OFFSET
	- Vec2((BLOCK_HORIZONTAL*BLOCK_WIDTH)/2,(BLOCK_VERTICAL * BLOCK_HEIGHT)/2)
	+ Vec2(BLOCK_WIDTH,BLOCK_HEIGHT)/2;

	Vec2 delta = gameCoord - blockOrigin;
	Vec2 pos = Vec2((int)(delta.x/ BLOCK_WIDTH + 0.5),(int)(delta.y / BLOCK_HEIGHT + 0.5));
	
	return pos;
}

Vec2 SceneIngame::convertBlockCoordToGameCoord(const Vec2& blockCoord)
{
	Vec2 blockOrigin = BLOCK_OFFSET
		- Vec2((BLOCK_HORIZONTAL * BLOCK_WIDTH) / 2, (BLOCK_VERTICAL * BLOCK_HEIGHT) / 2)
		+ Vec2(BLOCK_WIDTH, BLOCK_HEIGHT) / 2;

	return blockOrigin + Vec2(BLOCK_WIDTH * blockCoord.x, BLOCK_HEIGHT * blockCoord.y);
}

void SceneIngame::createBlock(int x, int y, int type)
{
	//auto cache = Director::getInstance()->getTextureCache();
//	auto spr = Sprite::createWithTexture(
	//	cache->getTextureForKey("res/mainblock.jpg")
	//	,Rect(300,240,40,40)
	//);
	
	blockSpr = Sprite::create("res/mainblock.jpg");
	blockSpr->setScale(1.6);
	blockSpr->setPosition(720/2, 1280/2);
	addChild(blockSpr);
	setBlockData(x,y,type);
	setBlockSprite(x,y,blockSpr);
}

int SceneIngame::getBlockData(int x, int y)
{
	return blockData[y][x];
}

void SceneIngame::setBlockData(int x, int y, int type)
{
	blockData[y][x] = type;
}

Sprite* SceneIngame::getBlockSprite(int x, int y)
{
	return blockSprite[y][x];
}

void SceneIngame::setBlockSprite(int x, int y, Sprite* s)
{
	blockSprite[y][x] = s;
}

void SceneIngame::destroyBlock(int x, int y)
{
	if (blockData[y][x] != 0)
	{

	}
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
	for (int i = 0; i < BLOCK_HORIZONTAL; i++)
	{
		for (int k = 0; k < BLOCK_VERTICAL; k++)
		{
			createBlock(i,k,0);
		}
	}
	this->alignBlockSprite();
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

void SceneIngame::alignBlockSprite()
{
	for (int i = 0; i < BLOCK_HORIZONTAL; i++)
	{
		for (int k = 0; k < BLOCK_VERTICAL; k++)
		{
			auto s = getBlockSprite(i,k);
			if(s != nullptr) s->setPosition(convertBlockCoordToGameCoord(Vec2(i,k)));
		}
	}
}
