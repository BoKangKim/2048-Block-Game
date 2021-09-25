#ifndef __SCENEINGAME_H__
#define __SCENEINGAME_H__

#include "stdafx.h"
#include "Environment.h"
#include <String.h>

class SceneIngame : public Scene {
private:
	GameState state;
	int blockData[BLOCK_VERTICAL][BLOCK_HORIZONTAL];
	Sprite* blockSprite[BLOCK_VERTICAL][BLOCK_HORIZONTAL];

	Sprite* blockSpr = nullptr;

	Vec2 convertGameCoordToBlockCoord(const Vec2& gameCoord);
	Vec2 convertBlockCoordToGameCoord(const Vec2& blockCoord);

	void createBlock(int x,int y, int type);
	int getBlockData(int x,int y);
	void setBlockData(int x,int y, int type);
	Sprite* getBlockSprite(int x,int y);
	void setBlockSprite(int x, int y, Sprite* s);
	void destroyBlock(int x,int y);
	
	//char blockType[12] = {"blue.png","dagray.png","gray.png", "green.png"
	//,"lightblue.png","orange.png","pink.png","purple.png","red.png","red2.png","white.png"};

public:
	static SceneIngame* create();
	virtual bool init() override;
	virtual void onEnter() override;

	void initUI();
	void initGame();
	void destroyUI();
	void destroyGame();

	bool onTouchBegan(Touch* t, Event* e);
	void onTouchMoved(Touch* t, Event* e);
	void onTouchEnded(Touch* t, Event* e);

	void alignBlockSprite();
};

#endif // !__SCENEINGAME_H__
