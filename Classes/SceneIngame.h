#ifndef __SCENEINGAME_H__
#define __SCENEINGAME_H__

#include "stdafx.h"
#include "Environment.h"
#include <String.h>

class SceneIngame : public Scene {
private:
	GameState state;
	MouseMove mousemove;
	int blockData[BLOCK_VERTICAL][BLOCK_HORIZONTAL];
	Sprite* blockSprite[BLOCK_VERTICAL][BLOCK_HORIZONTAL];
	Vec2 mouseTouch;

	Sprite* blockSpr = nullptr; // ���� ���
	Sprite* twoblockSpr = nullptr; // 2���

	void toDo();
	int blockNumType[11]; // ��� Ÿ�� 11��
	int randX1; // ���� �� �� ù��° 2�� x ��ǥ
	int randY1; // ���� �� �� ù��° 2�� y ��ǥ
	int randX2; // ���� �� �� �ι�° 2�� x ��ǥ
	int randY2; // ���� �� �� �ι�° 2�� y ��ǥ

	Vec2 convertGameCoordToBlockCoord(const Vec2& gameCoord); 
	Vec2 convertBlockCoordToGameCoord(const Vec2& blockCoord);

	void createBlock(int x,int y, int type);
	int getBlockData(int x,int y);
	void setBlockData(int x,int y, int type);
	Sprite* getBlockSprite(int x,int y);
	void setBlockSprite(int x, int y, Sprite* s);
	void destroyBlock(int x,int y);
	void setStartRandomNum(); //������ �� ������ ���� �����Ǵ� 2 �ΰ� ��ġ �ʱ�ȭ
	void movedBlocks(); // �巡�׷� ��� �̵�
	void numBlockTomainBlock(int x,int y); // �̵���Ų �� ���� 2�� �ִ� ��ġ�� ���� ������� �ٲٴ� �Լ�
	bool MousePosition(Vec2 p); //���콺 �̵� üũ
	int findEqualTypeBlockXIndex(int x,int y);
	int findEqualTypeBlockYIndex(int x,int y);
	Vec2 checkNoneMainBlock();

public:
	static SceneIngame* create();
	virtual bool init() override;
	virtual void onEnter() override;

	void initUI();
	void initGame();
	void destroyUI();
	void destroyGame();

	bool onTouchBegan(Touch* t, Event* e);
	bool onTouchMoved(Touch* t, Event* e);
	void onTouchEnded(Touch* t, Event* e);

	void alignBlockSprite();
};

#endif // !__SCENEINGAME_H__
