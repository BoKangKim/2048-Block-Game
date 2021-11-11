#ifndef __LAYER_INGAME_UI_H__
#define __LAYER_INGAME_UI_H__

#include "stdafx.h"
#include "Environment.h"

class LayerIngameUI: public Node {
private:

public:
	Button* btnPause;
	Scale9Sprite* pausePanel;
	Scale9Sprite* winPanel;
	Scale9Sprite* losePanel;
	Button* btnWinRestart;
	Button* btnWinHome;
	Button* btnLoseRestart;
	Button* btnLoseHome;
	Button* btnResume;
	Button* btnRestart;
	Button* btnHome;
	DrawNode* dnCurtain;

	static LayerIngameUI* create();
	virtual bool init() override;

	void showPausePanel();
	void hidePausePanel();

	void showWinPanel();
	void hideWinPanel();

	void showLosePanel();
	void hideLosePanel();

};

#endif // !__LAYER_INGAME_UI_H__
