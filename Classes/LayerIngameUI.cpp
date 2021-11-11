#include "stdafx.h"
#include "LayerIngameUI.h"

LayerIngameUI* LayerIngameUI::create()
{
	auto ret = new LayerIngameUI();
	if (ret && ret->init()) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool LayerIngameUI::init()
{
	if (!Node::init()) return false;

	addChild(btnPause = Button::create("res/pause.png", "res/pause_pressed.png", "res/pause_pressed.png"));
	btnPause->setPosition(Vec2(720 - 70, 1280 - 200));

	const Size PANEL_SIZE(600, 400);
	const float SPACING = 200;
	const float BUTTON_BOTTOM_SPACING = 100;

	addChild(dnCurtain = DrawNode::create());
	dnCurtain->drawSolidRect(Vec2::ZERO, Vec2(720,1280), Color4F(0,0,0,0.8));

	addChild(pausePanel = Scale9Sprite::create("res/panel.png"));
	pausePanel->setPosition(Vec2(720 / 2, 1280 / 2));
	pausePanel->setScale9Enabled(true);
	pausePanel->setContentSize(PANEL_SIZE);

	addChild(winPanel = Scale9Sprite::create("res/panel.png"));
	winPanel->setPosition(Vec2(720 / 2, 1280 / 2));
	winPanel->setScale9Enabled(true);
	winPanel->setContentSize(PANEL_SIZE);

	addChild(losePanel = Scale9Sprite::create("res/panel.png"));
	losePanel->setPosition(Vec2(720 / 2, 1280 / 2));
	losePanel->setScale9Enabled(true);
	losePanel->setContentSize(PANEL_SIZE);

	pausePanel->addChild(btnRestart = Button::create("res/return_pressed.png","res/return.png","res/return.png"));
	pausePanel->addChild(btnHome = Button::create("res/home_pressed.png", "res/home.png", "res/home.png"));
	pausePanel->addChild(btnResume = Button::create("res/right_pressed.png", "res/right.png", "res/right.png"));

	winPanel->addChild(btnWinRestart = Button::create("res/return_pressed.png", "res/return.png", "res/return.png"));
	winPanel->addChild(btnWinHome = Button::create("res/home_pressed.png", "res/home.png", "res/home.png"));

	losePanel->addChild(btnLoseRestart = Button::create("res/return_pressed.png", "res/return.png", "res/return.png"));
	losePanel->addChild(btnLoseHome = Button::create("res/home_pressed.png", "res/home.png", "res/home.png"));

	btnResume->setPosition(Vec2(PANEL_SIZE.width / 2, BUTTON_BOTTOM_SPACING));
	btnHome->setPosition(Vec2(PANEL_SIZE.width / 2 - SPACING, BUTTON_BOTTOM_SPACING));
	btnRestart->setPosition(Vec2(PANEL_SIZE.width / 2 + SPACING, BUTTON_BOTTOM_SPACING));

	btnWinHome->setPosition(Vec2((PANEL_SIZE.width / 2 - SPACING) + 100, BUTTON_BOTTOM_SPACING));
	btnWinRestart->setPosition(Vec2((PANEL_SIZE.width / 2 + SPACING) - 100, BUTTON_BOTTOM_SPACING));

	btnLoseHome->setPosition(Vec2((PANEL_SIZE.width / 2 - SPACING) + 100, BUTTON_BOTTOM_SPACING));
	btnLoseRestart->setPosition(Vec2((PANEL_SIZE.width / 2 + SPACING) - 100, BUTTON_BOTTOM_SPACING));
	
	Label* lbPause = Label::createWithTTF("PAUSED!!!", FONT_NAME, 64.0f);
	Label* lbWin = Label::createWithTTF("CLEAR!!!", FONT_NAME, 64.0f);
	Label* lbLose = Label::createWithTTF("FAILED....", FONT_NAME, 64.0f);

	pausePanel->addChild(lbPause);
	winPanel->addChild(lbWin);
	losePanel->addChild(lbLose);

	lbPause->setColor(Color3B(0, 0, 0));
	lbPause->setPosition(Vec2(PANEL_SIZE.width / 2, 300));

	lbWin->setColor(Color3B(0, 0, 0));
	lbWin->setPosition(Vec2(PANEL_SIZE.width / 2, 300));

	lbLose->setColor(Color3B(0, 0, 0));
	lbLose->setPosition(Vec2(PANEL_SIZE.width / 2, 300));

	hidePausePanel();
	hideWinPanel();
	hideLosePanel();

	return true;
}

void LayerIngameUI::showPausePanel()
{
	pausePanel->setVisible(true);
	dnCurtain->setVisible(true);

	dnCurtain->setOpacity(0);
	dnCurtain->runAction(FadeIn::create(0.125f));

	auto pos = pausePanel->getPosition();
	pausePanel->setPosition(pos - Vec2(0, 1000));
	pausePanel->runAction(EaseExponentialInOut::create(MoveTo::create(0.125f, pos)));
}

void LayerIngameUI::hidePausePanel()
{

	auto pos = pausePanel->getPosition();
	pausePanel->runAction(Sequence::create(
		EaseExponentialOut::create(MoveTo::create(0.25f, pos - Vec2(0,1000))),
		CallFunc::create([=]() {
			pausePanel->setPosition(pos);
			pausePanel->setVisible(false);
			dnCurtain->setVisible(false);
			}),
		nullptr
	));
	
}

void LayerIngameUI::showWinPanel()
{
	winPanel->setVisible(true);
	dnCurtain->setVisible(true);

	dnCurtain->setOpacity(0);
	dnCurtain->runAction(FadeIn::create(0.125f));

	auto pos = winPanel->getPosition();
	winPanel->setPosition(pos - Vec2(0, 1000));
	winPanel->runAction(EaseExponentialInOut::create(MoveTo::create(0.125f, pos)));
}

void LayerIngameUI::hideWinPanel()
{
	auto pos = winPanel->getPosition();
	winPanel->runAction(Sequence::create(
		EaseExponentialOut::create(MoveTo::create(0.25f, pos - Vec2(0, 1000))),
		CallFunc::create([=]() {
			winPanel->setPosition(pos);
			winPanel->setVisible(false);
			dnCurtain->setVisible(false);
			}),
		nullptr
				));
}

void LayerIngameUI::showLosePanel()
{
	losePanel->setVisible(true);
	dnCurtain->setVisible(true);

	dnCurtain->setOpacity(0);
	dnCurtain->runAction(FadeIn::create(0.125f));

	auto pos = losePanel->getPosition();
	losePanel->setPosition(pos - Vec2(0, 1000));
	losePanel->runAction(EaseExponentialInOut::create(MoveTo::create(0.125f, pos)));
}

void LayerIngameUI::hideLosePanel()
{
	auto pos = losePanel->getPosition();
	losePanel->runAction(Sequence::create(
		EaseExponentialOut::create(MoveTo::create(0.25f, pos - Vec2(0, 1000))),
		CallFunc::create([=]() {
			losePanel->setPosition(pos);
			losePanel->setVisible(false);
			dnCurtain->setVisible(false);
			}),
		nullptr
				));
}

