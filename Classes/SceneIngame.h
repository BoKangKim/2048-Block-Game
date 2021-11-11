#ifndef __SCENEINGAME_H__
#define __SCENEINGAME_H__

#include "stdafx.h"
#include "Environment.h"
#include <string>
#include "LayerIngameUI.h"

class SceneIngame : public Scene {
private:
	GameState state;
	MouseMove mousemove;
	int blockData[BLOCK_VERTICAL][BLOCK_HORIZONTAL];
	Sprite* blockSprite[BLOCK_VERTICAL][BLOCK_HORIZONTAL];
	Vec2 mouseTouch;

	Sprite* blockSpr = nullptr; // 메인 블록
	Sprite* twoblockSpr = nullptr; // 2블록
	Vec2 judgeStack[128];
	int judgeStackCount = 0;
	int judgeData[BLOCK_VERTICAL][BLOCK_HORIZONTAL];

	Sprite* blockTypeSpr[12];
	int blockNumType[11]; // 블록 타입 11개
	int randX1;
	int randY1;
	int randX2;
	int randY2; 


	Vec2 convertGameCoordToBlockCoord(const Vec2& gameCoord); 
	Vec2 convertBlockCoordToGameCoord(const Vec2& blockCoord);

	void createBlock(int x,int y, int type);
	int getBlockData(int x,int y);
	void setBlockData(int x,int y, int type);
	Sprite* getBlockSprite(int x,int y);
	void setBlockSprite(int x, int y, Sprite* s);
	void destroyBlock(int x,int y);
	void setStartRandomNum(); //시작할 때 랜덤한 곳에 생성되는 2 두개 위치 초기화
	void movedBlocks(); // 드래그로 블록 이동
	void numBlockTomainBlock(int x,int y); // 이동시킨 후 원래 2가 있던 위치를 메인 블록으로 바꾸는 함수
	void setRandTwoBlockXY();
	bool MousePosition(Vec2 p); //마우스 이동 체크
	int findEqualTypeBlockXIndex(int x,int y);
	int findEqualTypeBlockYIndex(int x,int y);
	int findNotMainBlockXIndex(int x,int y);
	int findNotMainBlockYIndex(int x, int y);
	Vec2 checkNoneMainBlock();

	void stackPush(const Vec2& value);
	const Vec2& stackPop();
	void stackEmpty();
	bool stackFind(const Vec2& value);
	
	LayerIngameUI* ui;
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
	bool onTouchEnded(Touch* t, Event* e);

	void alignBlockSprite();

	void startGame();
	void pauseGame();
	void winGame();
	void loseGame();
};

#endif // !__SCENEINGAME_H__
