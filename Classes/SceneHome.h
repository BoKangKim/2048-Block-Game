#ifndef __SCENE_HOME_H__
#define __SCENE_HOME_H__

#include "stdafx.h"

class SceneHome : public Scene {
public:
	Button* btnStart;
	Button* btnQuit;

	static SceneHome* create();
	virtual bool init() override;
};

#endif