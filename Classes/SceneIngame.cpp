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
	
	blockSpr = Sprite::create("res/mainblock.png");
	blockSpr->setScale(1.3);
	//blockSpr->setPosition(720/2, 1280/2);
	addChild(blockSpr);

	twoblockSpr = Sprite::create("res/2.png");
	twoblockSpr->setScale(0.98);
	//twoblockSpr->setTexture("2");
	addChild(twoblockSpr);

	if (type == 0)
	{
		setBlockData(x, y, type);
		setBlockSprite(x, y, blockSpr);
	}
	else
	{
		setBlockData(x,y,type);
		setBlockSprite(x,y,twoblockSpr);
	}
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
		blockSprite[y][x]->runAction(
			Sequence::create(
				FadeOut::create(0.125f),
				RemoveSelf::create(),
				nullptr
			)
		);
	}
	
	this->runAction(Sequence::create(
		CallFunc::create([=](){numBlockTomainBlock(x, y);}),
		nullptr
	));
	
}

void SceneIngame::setStartRandomNum()
{
	randX1 = rand() % BLOCK_HORIZONTAL;
	randY1 = rand() % BLOCK_VERTICAL;
	randX2 = rand() % BLOCK_HORIZONTAL;
	randY2 = rand() % BLOCK_VERTICAL;

	if (randX1 == randX2 && randY1 == randY2)
	{
		while (true)
		{
			randX2 = rand() % BLOCK_HORIZONTAL;
			randY2 = rand() % BLOCK_VERTICAL;
			if (randX1 != randX2 || randY1 != randY2)
				break;
		}
	}
}

void SceneIngame::movedBlocks(int x, int y)
{

}

void SceneIngame::numBlockTomainBlock(int x, int y)
{
	blockSprite[y][x] = nullptr;
	setBlockData(x, y, 0);
	setBlockSprite(x,y,blockSpr);
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

	srand(time(0));
	int count = 1;

	for (int i = 0; i < 11; i++)
	{
		count = count * 2;
		blockNumType[i] = count;
	}

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
	setStartRandomNum();

	for (int i = 0; i < BLOCK_HORIZONTAL; i++)
	{
		for (int k = 0; k < BLOCK_VERTICAL; k++)
		{
			if (i == randX1 && k == randY1)
			{
				createBlock(i, k, 1);
			}
			else if (i == randX2 && k == randY2)
			{
				createBlock(i, k, 1);
			}
			else
			{
				createBlock(i, k, 0);
			}
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

bool SceneIngame::onTouchMoved(Touch* t, Event* e)
{
	Vec2 p = convertGameCoordToBlockCoord(t->getLocation());
	
	return false;
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
