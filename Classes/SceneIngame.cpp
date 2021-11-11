#include "stdafx.h"
#include "SceneIngame.h"
#include "Environment.h"
#include <string>
#include "SceneHome.h"
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
	int count = 1;
	blockTypeSpr[0] = Sprite::create("res/mainblock.png");
	blockTypeSpr[0]->setScale(1.3);
	addChild(blockTypeSpr[0]);

	blockTypeSpr[1] = Sprite::create("res/2.png");
	blockTypeSpr[1]->setScale(0.98);
	addChild(blockTypeSpr[1]);

	blockTypeSpr[2] = Sprite::create("res/4.png");
	blockTypeSpr[2]->setScale(0.98);
	addChild(blockTypeSpr[2]);

	blockTypeSpr[3] = Sprite::create("res/8.png");
	blockTypeSpr[3]->setScale(0.98);
	addChild(blockTypeSpr[3]);

	blockTypeSpr[4] = Sprite::create("res/16.png");
	blockTypeSpr[4]->setScale(0.98);
	addChild(blockTypeSpr[4]);

	blockTypeSpr[5] = Sprite::create("res/32.png");
	blockTypeSpr[5]->setScale(0.98);
	addChild(blockTypeSpr[5]);

	blockTypeSpr[6] = Sprite::create("res/64.png");
	blockTypeSpr[6]->setScale(0.98);
	addChild(blockTypeSpr[6]);

	blockTypeSpr[7] = Sprite::create("res/128.png");
	blockTypeSpr[7]->setScale(0.98);
	addChild(blockTypeSpr[7]);

	blockTypeSpr[8] = Sprite::create("res/256.png");
	blockTypeSpr[8]->setScale(0.98);
	addChild(blockTypeSpr[8]);

	blockTypeSpr[9] = Sprite::create("res/512.png");
	blockTypeSpr[9]->setScale(0.98);
	addChild(blockTypeSpr[9]);

	blockTypeSpr[10] = Sprite::create("res/1024.png");
	blockTypeSpr[10]->setScale(0.98);
	addChild(blockTypeSpr[10]);

	blockTypeSpr[11] = Sprite::create("res/2048.png");
	blockTypeSpr[11]->setScale(0.98);
	addChild(blockTypeSpr[11]);

	setBlockData(x, y, type);
	setBlockSprite(x, y, blockTypeSpr[type]);
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
	blockSprite[y][x] = nullptr;
	blockData[y][x] = 0;
}

void SceneIngame::setStartRandomNum()
{
	randX1 = rand() % ((BLOCK_HORIZONTAL - 2)) + 1;
	randY1 = rand() % (BLOCK_VERTICAL - 2) + 1;
	randX2 = rand() % ((BLOCK_HORIZONTAL - 2)) + 1;
	randY2 = rand() % (BLOCK_VERTICAL - 2) + 1;

	while ((randX1 == randX2 || randY1 == randY2)) {
		randX2 = rand() % ((BLOCK_HORIZONTAL - 2)) + 1;
		randY2 = rand() % (BLOCK_VERTICAL - 2) + 1;
		randX1 = rand() % ((BLOCK_HORIZONTAL - 2)) + 1;
		randY1 = rand() % (BLOCK_VERTICAL - 2) + 1;
	}
	
	
}

void SceneIngame::movedBlocks()
{
	int loseCount = 0;
	for (int i = 0; i < BLOCK_HORIZONTAL; i++) {
		for (int j = 0; j < BLOCK_VERTICAL; j++) {
			if (getBlockData(i, j) != 0) {
				loseCount++;
			}
		}
	}
	CCLOG("%d lose",loseCount);
	if (loseCount == 36) {
		loseGame();
	}
	if (mousemove == MouseMove::RIGHT && state == GameState::PLAYING)
	{
		int equal_x = 0;
		int not_mainBlock_x = 0;
		for (int i = BLOCK_HORIZONTAL - 1; i >= 0 ; i--)
		{
			for(int j = 0; j < BLOCK_VERTICAL; j++)
			{	
				if(blockData[j][i] != 0)
				{
					equal_x = findEqualTypeBlockXIndex(i,j);
					not_mainBlock_x = findNotMainBlockXIndex(i,j);

					//CCLOG("%d, %d index", equal_x, not_mainBlock_x);
					
					if (equal_x != -1 && not_mainBlock_x != -1)
					{
						blockSprite[j][equal_x]->runAction(Sequence::create(
							RemoveSelf::create(),
							nullptr
						));

						blockSprite[j][i]->runAction(Sequence::create(
							RemoveSelf::create(),
							nullptr
						));

						createBlock(i, j, (getBlockData(i, j) + 1));
						auto s = getBlockSprite(i, j);
						if (s != nullptr) s->setPosition(convertBlockCoordToGameCoord(Vec2(i, j)));

						blockSprite[j][i]->runAction(MoveTo::create(0.2, convertBlockCoordToGameCoord(Vec2(equal_x, j))));
						if (getBlockData(i, j) == 11)
						{
							winGame();
						}
						
						setBlockData(equal_x, j, getBlockData(i,j));
						setBlockSprite(equal_x, j, blockTypeSpr[getBlockData(i, j)]);
						
						
						if (i != BLOCK_HORIZONTAL - 1)
						{
							numBlockTomainBlock(i, j);
						}
						
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
						
						blockSprite[j][i]->runAction(MoveTo::create(0.2, convertBlockCoordToGameCoord(Vec2(5, j))));
						
						int a = getBlockData(i, j);
						int b = getBlockData(BLOCK_HORIZONTAL -1, j);
						SWAP(int, a, b);
						setBlockData(i, j, a);
						setBlockData(BLOCK_HORIZONTAL - 1, j, b);

						Sprite* sa = getBlockSprite(i, j);
						Sprite* sb = getBlockSprite(BLOCK_HORIZONTAL-1, j);
						SWAP(Sprite*, sa, sb);
						setBlockSprite(i, j, sa);
						setBlockSprite(BLOCK_HORIZONTAL - 1, j, sb);

						if(i != BLOCK_HORIZONTAL - 1)
						{
							numBlockTomainBlock(i, j);
						}
						
					}
					else if(equal_x == -1 && not_mainBlock_x != -1)
					{
						if (getBlockData(not_mainBlock_x - 1, j) != getBlockData(i, j)) {

							blockSprite[j][not_mainBlock_x - 1]->runAction(Sequence::create(
								RemoveSelf::create(),
								nullptr
							));
							blockSprite[j][i]->runAction(MoveTo::create(0.2, convertBlockCoordToGameCoord(Vec2(not_mainBlock_x - 1, j))));
							
							int a = getBlockData(i, j);
							int b = getBlockData(not_mainBlock_x - 1, j);
							SWAP(int, a, b);
							setBlockData(i, j, a);
							setBlockData(not_mainBlock_x - 1, j, b);

							Sprite* sa = getBlockSprite(i, j);
							Sprite* sb = getBlockSprite(not_mainBlock_x - 1, j);
							SWAP(Sprite*, sa, sb);
							setBlockSprite(i, j, sa);
							setBlockSprite(not_mainBlock_x - 1, j, sb);
							
							
								if (i != BLOCK_HORIZONTAL - 1)
								{
									numBlockTomainBlock(i, j);
								}
						}
						
					}
				}
			}
		}
		setRandTwoBlockXY();
		
	}

	else if (mousemove == MouseMove::LEFT && state == GameState::PLAYING)
	{
		
		int equal_x = 0;
		int not_mainBlock_x = 0;

		for (int i = 0; i < BLOCK_HORIZONTAL; i++)
		{
			for (int j = 0; j < BLOCK_VERTICAL; j++)
			{

				if (blockData[j][i] != 0)
				{
					equal_x = findEqualTypeBlockXIndex(i, j);
					not_mainBlock_x = findNotMainBlockXIndex(i, j);

					

					if (equal_x != -1 && not_mainBlock_x != -1)
					{
						blockSprite[j][equal_x]->runAction(Sequence::create(
							RemoveSelf::create(),
							nullptr
						));

						blockSprite[j][i]->runAction(Sequence::create(
							RemoveSelf::create(),
							nullptr
						));

						createBlock(i, j, (getBlockData(i, j) + 1));
						auto s = getBlockSprite(i, j);
						if (s != nullptr) s->setPosition(convertBlockCoordToGameCoord(Vec2(i, j)));
						blockSprite[j][i]->runAction(MoveTo::create(0.2, convertBlockCoordToGameCoord(Vec2(equal_x, j))));
						if (getBlockData(i, j) == 11)
						{
							winGame();
						}

						setBlockData(equal_x, j, getBlockData(i, j));
						setBlockSprite(equal_x, j, blockTypeSpr[getBlockData(i, j)]);
						//createBlock(equal_x, j, getBlockData(i, j));

						//createBlock(i, j, 0);

						if (i != 0)
						{
							numBlockTomainBlock(i, j);
						}

					}
					else if (equal_x == -1 && not_mainBlock_x == -1)
					{
						if (getBlockData(0, j) == 0)
						{

							blockSprite[j][0]->runAction(Sequence::create(
								RemoveSelf::create(),
								nullptr
							));
						}

						blockSprite[j][i]->runAction(MoveTo::create(0.2, convertBlockCoordToGameCoord(Vec2(0, j))));
						int a = getBlockData(i, j);
						int b = getBlockData(0, j);
						SWAP(int, a, b);
						setBlockData(i, j, a);
						setBlockData(0, j, b);

						Sprite* sa = getBlockSprite(i, j);
						Sprite* sb = getBlockSprite(0, j);
						SWAP(Sprite*, sa, sb);
						setBlockSprite(i, j, sa);
						setBlockSprite(0, j, sb);
						//createBlock(0, j, getBlockData(i, j));

						if (i != 0)
						{
							numBlockTomainBlock(i, j);
						}

					}
					else if (equal_x == -1 && not_mainBlock_x != -1)
					{
						if (getBlockData(not_mainBlock_x + 1 , j) != getBlockData(i, j)) {

							blockSprite[j][not_mainBlock_x + 1]->runAction(Sequence::create(
								RemoveSelf::create(),
								nullptr
							));
							blockSprite[j][i]->runAction(MoveTo::create(0.2, convertBlockCoordToGameCoord(Vec2(not_mainBlock_x+1, j))));
							int a = getBlockData(i, j);
							int b = getBlockData(not_mainBlock_x + 1, j);
							SWAP(int, a, b);
							setBlockData(i, j, a);
							setBlockData(not_mainBlock_x + 1, j, b);

							Sprite* sa = getBlockSprite(i, j);
							Sprite* sb = getBlockSprite(not_mainBlock_x + 1, j);
							SWAP(Sprite*, sa, sb);
							setBlockSprite(i, j, sa);
							setBlockSprite(not_mainBlock_x + 1, j, sb);
							if (i != 0)
							{
								numBlockTomainBlock(i, j);
							}
						}

					}
				}
			}
		}
		setRandTwoBlockXY();

	}

	else if (mousemove == MouseMove::BOTTOM && state == GameState::PLAYING)
	{

	int equal_y = 0;
	int not_mainBlock_y = 0;

	for (int i = 0; i < BLOCK_VERTICAL; i++)
	{
		for (int j = 0; j < BLOCK_HORIZONTAL; j++)
		{

			if (blockData[i][j] != 0)
			{
				equal_y = findEqualTypeBlockYIndex(j, i);
				not_mainBlock_y = findNotMainBlockYIndex(j, i);
				

				if (equal_y != -1 && not_mainBlock_y != -1)
				{
					blockSprite[equal_y][j]->runAction(Sequence::create(
						RemoveSelf::create(),
						nullptr
					));

					blockSprite[i][j]->runAction(Sequence::create(
						RemoveSelf::create(),
						nullptr
					));

					createBlock(j, i, (getBlockData(j, i) + 1));
					auto s = getBlockSprite(j, i);
					if (s != nullptr) s->setPosition(convertBlockCoordToGameCoord(Vec2(j, i)));
					blockSprite[i][j]->runAction(MoveTo::create(0.2, convertBlockCoordToGameCoord(Vec2(j, equal_y))));
					if (getBlockData(j, i) == 11)
					{
						winGame();
					}

					setBlockData(j, equal_y, getBlockData(j, i));
					setBlockSprite(j, equal_y, blockTypeSpr[getBlockData(j, i)]);
					//createBlock(equal_x, j, getBlockData(i, j));

					//createBlock(i, j, 0);

					if (i != 0)
					{
						numBlockTomainBlock(j, i);
					}

				}
				else if (equal_y == -1 && not_mainBlock_y == -1)
				{
					if (getBlockData(j, 0) == 0)
					{

						blockSprite[0][j]->runAction(Sequence::create(
							RemoveSelf::create(),
							nullptr
						));
					}

					blockSprite[i][j]->runAction(MoveTo::create(0.2, convertBlockCoordToGameCoord(Vec2(j, 0))));

					int a = getBlockData(j, i);
					int b = getBlockData(j, 0);
					SWAP(int, a, b);
					setBlockData(j, i, a);
					setBlockData(j, 0, b);

					Sprite* sa = getBlockSprite(j, i);
					Sprite* sb = getBlockSprite(j, i);
					SWAP(Sprite*, sa, sb);
					setBlockSprite(j, i, sa);
					setBlockSprite(j, 0, sb);
					//createBlock(0, j, getBlockData(i, j));

					if (i != 0)
					{
						numBlockTomainBlock(j, i);
					}

				}
				else if (equal_y == -1 && not_mainBlock_y != -1)
				{
					if (getBlockData(j, not_mainBlock_y + 1) != getBlockData(j, i)) {

						blockSprite[not_mainBlock_y + 1][j]->runAction(Sequence::create(
							RemoveSelf::create(),
							nullptr
						));
						blockSprite[i][j]->runAction(MoveTo::create(0.2, convertBlockCoordToGameCoord(Vec2(j, not_mainBlock_y + 1))));
						int a = getBlockData(j, i);
						int b = getBlockData(j, not_mainBlock_y + 1);
						SWAP(int, a, b);
						setBlockData(j, i, a);
						setBlockData(j, not_mainBlock_y + 1, b);

						Sprite* sa = getBlockSprite(j, i);
						Sprite* sb = getBlockSprite(j, not_mainBlock_y + 1);
						SWAP(Sprite*, sa, sb);
						setBlockSprite(j, i, sa);
						setBlockSprite(j, not_mainBlock_y + 1, sb);
						if (i != 0)
						{
							numBlockTomainBlock(j, i);
						}
					}

				}
			}
		}
	}
	setRandTwoBlockXY();

	}

	else if (mousemove == MouseMove::TOP && state == GameState::PLAYING)
	{
		int equal_y = 0;
		int not_mainBlock_y = 0;
		for (int i = BLOCK_VERTICAL - 2; i >= 0; i--)
		{
			for (int j = 0; j < BLOCK_HORIZONTAL; j++)
			{
				if (blockData[i][j] != 0)
				{
					equal_y = findEqualTypeBlockYIndex(j, i);
					not_mainBlock_y = findNotMainBlockYIndex(j, i);
					
					if (equal_y != -1 && not_mainBlock_y != -1)
					{
						
						blockSprite[equal_y][j]->runAction(Sequence::create(
							RemoveSelf::create(),
							nullptr
						));

						blockSprite[i][j]->runAction(Sequence::create(
							RemoveSelf::create(),
							nullptr
						));

						createBlock(j, i, (getBlockData(j, i) + 1));
						auto s = getBlockSprite(j, i);
						if (s != nullptr) s->setPosition(convertBlockCoordToGameCoord(Vec2(j, i)));

						blockSprite[i][j]->runAction(MoveTo::create(0.2, convertBlockCoordToGameCoord(Vec2(j, equal_y))));
						if (getBlockData(j, i) == 11)
						{
							winGame();
						}

						setBlockData(j, equal_y, getBlockData(j, i));
						setBlockSprite(j, equal_y, blockTypeSpr[getBlockData(j, i)]);

						if (i != BLOCK_HORIZONTAL - 1)
						{
							numBlockTomainBlock(j, i);
						}

					}
					else if (equal_y == -1 && not_mainBlock_y == -1)
					{
						if (getBlockData(j, BLOCK_VERTICAL - 1) == 0)
						{
							blockSprite[BLOCK_VERTICAL - 1][j]->runAction(Sequence::create(
								RemoveSelf::create(),
								nullptr
							));
						}
						
						blockSprite[i][j]->runAction(MoveTo::create(0.2, convertBlockCoordToGameCoord(Vec2(j, BLOCK_VERTICAL-1))));

						int a = getBlockData(j, i);
						int b = getBlockData(j, BLOCK_VERTICAL-1);
						SWAP(int, a, b);
						setBlockData(j, i, a);
						setBlockData(j, BLOCK_VERTICAL - 1, b);

						Sprite* sa = getBlockSprite(j, i);
						Sprite* sb = getBlockSprite(j, BLOCK_VERTICAL - 1);
						SWAP(Sprite*, sa, sb);
						setBlockSprite(j, i, sa);
						setBlockSprite(j, BLOCK_VERTICAL - 1, sb);

						if (i != BLOCK_VERTICAL - 1)
						{
							numBlockTomainBlock(j, i);
						}

					}
					else if (equal_y == -1 && not_mainBlock_y != -1)
					{
						if (getBlockData(j, not_mainBlock_y - 1) != getBlockData(j, i)) {

							blockSprite[not_mainBlock_y - 1][j]->runAction(Sequence::create(
								RemoveSelf::create(),
								nullptr
							));
							blockSprite[i][j]->runAction(MoveTo::create(0.2, convertBlockCoordToGameCoord(Vec2(j, not_mainBlock_y - 1))));

							int a = getBlockData(j, i);
							int b = getBlockData(j, not_mainBlock_y - 1);
							SWAP(int, a, b);
							setBlockData(j, i, a);
							setBlockData(j, not_mainBlock_y - 1, b);

							Sprite* sa = getBlockSprite(j, i);
							Sprite* sb = getBlockSprite(j, not_mainBlock_y - 1);
							SWAP(Sprite*, sa, sb);
							setBlockSprite(j, i, sa);
							setBlockSprite(j, not_mainBlock_y - 1, sb);


							if (i != BLOCK_VERTICAL - 1)
							{
								numBlockTomainBlock(j, i);
							}
						}

					}
				}
			}
		}
		setRandTwoBlockXY();

	}
}

void SceneIngame::numBlockTomainBlock(int x, int y)
{
	//destroyBlock(x, y);
	createBlock(x, y, 0);
	auto s = getBlockSprite(x, y);
	if (s != nullptr) s->setPosition(convertBlockCoordToGameCoord(Vec2(x, y)));
}

void SceneIngame::setRandTwoBlockXY()
{
	int randX3 = rand() % ((BLOCK_HORIZONTAL));
	int randY3 = rand() % (BLOCK_VERTICAL);
	int randX4 = rand() % ((BLOCK_HORIZONTAL));
	int randY4 = rand() % (BLOCK_VERTICAL);

	while (
		getBlockData(randX3, randY3) != 0 
		) {
		randX3 = rand() % ((BLOCK_HORIZONTAL));
		randY3 = rand() % (BLOCK_VERTICAL);
	}

	while ((randX3 == randX4 && randX4 == randY4)
		|| getBlockData(randX4, randY4) != 0
		) {
		randX4 = rand() % ((BLOCK_HORIZONTAL));
		randY4 = rand() % (BLOCK_VERTICAL);

		CCLOG("%d %d ", randX3, randY3);
	}

	if (blockSprite[randY3][randX3] != nullptr) {
		blockSprite[randY3][randX3]->runAction(Sequence::create(
			RemoveSelf::create(),
			nullptr
		));
		//destroyBlock(randX3, randY3);
		createBlock(randX3, randY3, 1);
		auto s = getBlockSprite(randX3, randY3);
		if (s != nullptr) s->setPosition(convertBlockCoordToGameCoord(Vec2(randX3, randY3)));
		blockSprite[randY3][randX3]->runAction(Sequence::create(
			FadeOut::create(0.125f),
			FadeIn::create(0.125f),
			FadeOut::create(0.125f),
			FadeIn::create(0.125f),
			nullptr
		));
	}

	if (blockSprite[randY4][randX4] != nullptr) {

		blockSprite[randY4][randX4]->runAction(Sequence::create(
			RemoveSelf::create(),
			nullptr
		));
		//destroyBlock(randX4, randY4);
		createBlock(randX4, randY4, 1);
		auto s2 = getBlockSprite(randX4, randY4);
		if (s2 != nullptr) s2->setPosition(convertBlockCoordToGameCoord(Vec2(randX4, randY4)));
		blockSprite[randY4][randX4]->runAction(Sequence::create(
			FadeOut::create(0.125f),
			FadeIn::create(0.125f),
			FadeOut::create(0.125f),
			FadeIn::create(0.125f),
			nullptr
		));
	}
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
	int stopNotMainBlock = findNotMainBlockXIndex(x, y);
	if (mousemove == MouseMove::RIGHT) {
		for (int i = x + 1; i <= stopNotMainBlock; i++)
		{
			//CCLOG("%d %d find", getBlockData(x, y), getBlockData(i, y));
			if ((getBlockData(x,y) == getBlockData(i,y)))
			{
				return i;
				
			}
		}
	}
	else if (mousemove == MouseMove::LEFT) {
		for (int i = x - 1 ; i >= stopNotMainBlock; i--)
		{
			
			if ((getBlockData(x, y) == getBlockData(i, y)))
			{
				return i;
				
			}
		}
	}

	return -1;
}

int SceneIngame::findEqualTypeBlockYIndex(int x, int y)
{
	int stopNotMainBlock = findNotMainBlockYIndex(x, y);
	if (mousemove == MouseMove::BOTTOM) {
		for (int i = y - 1 ; i >= stopNotMainBlock; i--)
		{
			//CCLOG("%d %d find", getBlockData(x, y), getBlockData(i, y));
			if ((getBlockData(x, y) == getBlockData(x, i)))
			{
				return i;

			}
		}
	}
	else if (mousemove == MouseMove::TOP) {
		for (int i = y + 1; i <= stopNotMainBlock; i++)
		{
			//CCLOG("%d %d find", getBlockData(x, y), getBlockData(i, y));
			if ((getBlockData(x, y) == getBlockData(x, i)))
			{
				return i;

			}
		}
	}

	return -1;
}

int SceneIngame::findNotMainBlockXIndex(int x, int y)
{
	if (mousemove == MouseMove::RIGHT)
	{
		for (int i = x + 1; i < BLOCK_HORIZONTAL; i++)
		{
			if (getBlockData(i, y) != 0)
			{
				return i;
			}
		}
	}
	else if (mousemove == MouseMove::LEFT)
	{
		for (int i = x - 1; i >= 0; i--)
		{
			if (getBlockData(i, y) != 0)
			{	
				return i;
			}
		}

	}

	return -1;
}

int SceneIngame::findNotMainBlockYIndex(int x, int y)
{
	if (mousemove == MouseMove::BOTTOM)
	{
		for (int i = y - 1; i >= 0; i--)
		{
			
			if (getBlockData(x, i) != 0)
			{
				return i;
			}
		}
	}
	else if (mousemove == MouseMove::TOP)
	{
		for (int i = y + 1; i < BLOCK_VERTICAL; i++)
		{
			if (getBlockData(x, i) != 0)
			{
				return i;
			}
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
	state = GameState::PLAYING;

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
	this->startGame();
}

void SceneIngame::initUI()
{
	addChild(ui = LayerIngameUI::create());
	ui->setLocalZOrder(1);

	ui->btnPause->addClickEventListener([=](Ref* r) {
		if (state == GameState::PLAYING) {
			ui->showPausePanel();
			state = GameState::PAUSED;
		}
		});
	ui->btnResume->addClickEventListener([=](Ref* r) {
		if (state == GameState::PAUSED) {
			ui->hidePausePanel();
			state = GameState::PLAYING;
			}
		});
	ui->btnRestart->addClickEventListener([=](Ref* r) {
		if (state == GameState::PAUSED) {
			Global::getInstance()->stopBackgroundMusic();
			ui->hidePausePanel();
			this->destroyGame();
			this->initGame();
			this->startGame();
			state = GameState::PLAYING;
		}
		});
	ui->btnHome->addClickEventListener([=](Ref* r) {
		if (state == GameState::PAUSED) {
			auto scene = SceneHome::create();
			auto transit = TransitionSlideInL::create(0.125f, scene);
			Director::getInstance()->replaceScene(transit);
		}
		});

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
	state = GameState::PLAYING;
	this->alignBlockSprite();
}

void SceneIngame::destroyUI()
{
}

void SceneIngame::destroyGame()
{
	for (int i = 0; i < BLOCK_HORIZONTAL; i++)
	{
		for (int k = 0; k < BLOCK_VERTICAL; k++)
		{
			setBlockData(i, k, 0);
			getBlockSprite(i, k)->removeFromParent();
			setBlockSprite(i, k, nullptr);
		}
	}
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
	SceneIngame::movedBlocks();
	
	//CCLOG("%f %f end", p.x, p.y);
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

void SceneIngame::startGame()
{
	Global::getInstance()->playBackgroundMusic();
}

void SceneIngame::pauseGame()
{
}

void SceneIngame::winGame()
{	
	//addChild(ui = LayerIngameUI::create());
	ui->showWinPanel();
	ui->setLocalZOrder(1);
	state = GameState::WIN;

	ui->btnWinRestart->addClickEventListener([=](Ref* r) {
		if (state == GameState::WIN) {
			Global::getInstance()->stopBackgroundMusic();
			ui->hideWinPanel();
			this->destroyGame();
			this->initGame();
			this->startGame();
			state = GameState::PLAYING;
		}
		});
	ui->btnWinHome->addClickEventListener([=](Ref* r) {
		if (state == GameState::WIN) {
			auto scene = SceneHome::create();
			auto transit = TransitionSlideInL::create(0.125f, scene);
			Director::getInstance()->replaceScene(transit);
		}
		});
}

void SceneIngame::loseGame()
{
	//addChild(ui = LayerIngameUI::create());
	ui->showLosePanel();
	ui->setLocalZOrder(1);
	state = GameState::LOSE;
	ui->btnLoseRestart->addClickEventListener([=](Ref* r) {
		if (state == GameState::LOSE) {
			Global::getInstance()->stopBackgroundMusic();
			ui->hideLosePanel();
			this->destroyGame();
			this->initGame();
			this->startGame();
			state = GameState::PLAYING;
		}
		});

	ui->btnLoseHome->addClickEventListener([=](Ref* r) {
		if (state == GameState::LOSE) {
			auto scene = SceneHome::create();
			auto transit = TransitionSlideInL::create(0.125f, scene);
			Director::getInstance()->replaceScene(transit);
		}
		});
}
