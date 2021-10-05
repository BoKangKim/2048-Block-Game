#include "stdafx.h"
#include "SceneIngame.h"
#include "Environment.h"


void SceneIngame::toDo()
{
	//마우스 위치 판단 후 블록 움직이기
	//MoveTo 에러 잡기
	//같은 블록 다른 블록 충돌 판단
}

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
		stackPush(Vec2(x,y));
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
		DelayTime::create(0.625f),
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

void SceneIngame::movedBlocks()
{
//	Vec2 chVec = Vec2(0,0);

	if (mousemove == MouseMove::RIGHT)
	{
		mousemove = MouseMove::STOP;
		
	}
}

void SceneIngame::numBlockTomainBlock(int x, int y)
{
	blockSprite[y][x] = nullptr;
	createBlock(x, y , 0);
}

bool SceneIngame::MousePosition(Vec2 p)
{
	if(mouseTouch.x < p.x)
		mousemove = MouseMove::RIGHT;
	else if(mouseTouch.x > p.x)
		mousemove = MouseMove::LEFT;
	else if(mouseTouch.y < p.y)
		mousemove = MouseMove::TOP;
	else if(mouseTouch.y < p.y)
		mousemove = MouseMove::BOTTOM;
	else
	{
		mousemove = MouseMove::STOP;
		return false;
	}

	return true;
}

int SceneIngame::findEqualTypeBlockXIndex(int x, int y)
{
	
	return 0;
}

int SceneIngame::findEqualTypeBlockYIndex(int x, int y)
{
	return 0;
}

Vec2 SceneIngame::checkNoneMainBlock()
{
	//Vec2 retVec = Vec2(0,0);
	
	

	//return Vec2(-1,-1);
	
	return Vec2();
}

void SceneIngame::stackPush(const Vec2& value)
{
	if(judgeData[(int)value.y][(int)value.x] != 0) return;
	judgeStack[judgeStackCount++] = value;
	judgeData[(int)value.y][(int)value.x] = 1;
}

const Vec2& SceneIngame::stackPop()
{
	auto ret = judgeStack[--judgeStackCount];
	judgeData[(int)ret.y][(int)ret.x] = 0;
	return ret;
}

void SceneIngame::stackEmpty()
{
	judgeStackCount = 0;
	for (int i = 0; i < BLOCK_HORIZONTAL; i++)
	{
		for (int k = 0; k < BLOCK_VERTICAL; k++)
		{
			judgeData[k][i] = 0;
		}
	}
}

bool SceneIngame::stackFind(const Vec2& value)
{
	return judgeData[(int)value.y][(int)value.x] == 1;
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
	mousemove = MouseMove::STOP;

	auto touch = EventListenerTouchOneByOne::create();

	for (int i = 0; i < 11; i++)
	{
		count = count * 2;
		blockNumType[i] = count;
	}

	touch->onTouchBegan = std::bind(&SceneIngame::onTouchBegan,this,std::placeholders::_1,std::placeholders::_2);
	touch->onTouchMoved = std::bind(&SceneIngame::onTouchMoved,this,std::placeholders::_1,std::placeholders::_2);
	touch->onTouchEnded = std::bind(&SceneIngame::onTouchEnded, this, std::placeholders::_1, std::placeholders::_2);

	getEventDispatcher()->addEventListenerWithSceneGraphPriority(touch, this);

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
	Vec2 p = convertGameCoordToBlockCoord(t->getLocation());

	mouseTouch.x = p.x;
	mouseTouch.y = p.y;

	CCLOG("%f %f touch", p.x, p.y);
	
	return true;
}

bool SceneIngame::onTouchMoved(Touch* t, Event* e)
{
	bool check = false;
	Vec2 p = convertGameCoordToBlockCoord(t->getLocation());
	
	CCLOG("%f %f move", p.x, p.y);
	return false; 

	
	//SceneIngame::movedBlocks(); return true;
	
	
}

bool SceneIngame::onTouchEnded(Touch* t, Event* e)
{
	Vec2 p = convertGameCoordToBlockCoord(t->getLocation());
	CCLOG("%f %f end", p.x, p.y);
	return true;
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
