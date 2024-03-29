#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include "stdafx.h"

enum class GameState {
	PLAYING,
	PAUSED,
	WIN,
	LOSE,
	BLOCK_MOVING
};

enum class MouseMove {
	LEFT,
	RIGHT,
	TOP,
	BOTTOM,
	STOP
};

#define SWAP(TYPE, A, B){TYPE t = A; A = B; B = t;}
#define FONT_NAME "fonts/SDSamliphopangcheTTFBasic.ttf"
// 블록의 기본 설정들
#define BLOCK_HORIZONTAL 6
#define BLOCK_VERTICAL 6
#define BLOCK_OFFSET Vec2(720/2, 1280/2)
#define BLOCK_WIDTH 100
#define BLOCK_HEIGHT 100

class Global {
private:
	Global() {}
	int backgroundMusicId = -1;
public:
	static Global* getInstance();
	void playBackgroundMusic();
	void stopBackgroundMusic();
};

#endif // !__ENVIRONMENT_H__

