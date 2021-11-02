#include "stdafx.h"
#include "SceneIngame.h"
#include "Environment.h"

/*
	같은 블록, 다른 블록 충돌 처리
	Finish Game 구현
*/

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
		int equal_x = 0;
		int not_mainBlock_x = 0;
		for (int i = 0 ; i < BLOCK_HORIZONTAL; i++)
		{
			for(int j = 0; j <BLOCK_VERTICAL; j++)
			{
				if(getBlockData(i,j) != 0)
				{

					equal_x = findEqualTypeBlockXIndex(i, j);
					not_mainBlock_x = findNotMainBlockXIndex(i,j);
					if (equal_x != -1)
					{

					}
					else if(equal_x == -1 && not_mainBlock_x == -1)
					{
						if (getBlockData(BLOCK_HORIZONTAL - 1, j) == 0)
						{
							blockSprite[j][BLOCK_HORIZONTAL - 1]->runAction(Sequence::create(
								RemoveSelf::create(),
								nullptr
							));
							
						}

						blockSprite[j][i] ->runAction(MoveTo::create(0, convertBlockCoordToGameCoord(Vec2(BLOCK_HORIZONTAL -1 ,j))));
						setBlockData(BLOCK_HORIZONTAL - 1, j,0);
						setBlockSprite(BLOCK_HORIZONTAL - 1, j, twoblockSpr);

						if(i != BLOCK_HORIZONTAL - 1)
						{
							blockSprite[j][i] = nullptr;
							blockData[j][i] = 0;
							createBlock(i, j, 0);
							auto s = getBlockSprite(i, j);
							if (s != nullptr) s->setPosition(convertBlockCoordToGameCoord(Vec2(i, j)));
						}
						
						
					}
					else if(equal_x == -1 && not_mainBlock_x != -1)
					{

					}
				}
			}
		}
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
	else if(mouseTouch.y > p.y)
		mousemove = MouseMove::BOTTOM;
	else
		mousemove = MouseMove::STOP;

	return true;
}

int SceneIngame::findEqualTypeBlockXIndex(int x, int y)
{
	for (int i = x + 1; i < BLOCK_HORIZONTAL; i++) 
	{
		if (getBlockData(x,y) == getBlockData(i,y))
		{
			return i;
		}
	}

	return -1;
}

int SceneIngame::findEqualTypeBlockYIndex(int x, int y)
{
	return 0;
}

int SceneIngame::findNotMainBlockXIndex(int x, int y)
{
	for (int i = x + 1; i < BLOCK_HORIZONTAL; i++)
	{
		if (getBlockData(i, y) != 0)
		{
			return i;
		}
	}

	return -1;
}

Vec2 SceneIngame::checkNoneMainBlock()
{
	
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

void SceneIngame::onTouchMoved(Touch* t, Event* e)
{
}

bool SceneIngame::onTouchEnded(Touch* t, Event* e)
{
	Vec2 p = convertGameCoordToBlockCoord(t->getLocation());
	SceneIngame::MousePosition(p);
	CCLOG("%d position",mousemove);
	SceneIngame::movedBlocks();
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
