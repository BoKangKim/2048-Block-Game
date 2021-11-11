
#include "stdafx.h"
#include "Environment.h"

Global* instance = nullptr;

Global* Global::getInstance()
{
    if (instance == nullptr) instance = new Global();
    return instance;
}

void Global::playBackgroundMusic()
{
   this->backgroundMusicId = AudioEngine::play2d("res/titlemusic.mp3",true,0.5);
}

void Global::stopBackgroundMusic()
{
    if (backgroundMusicId == -1) return;
    AudioEngine::stop(this->backgroundMusicId);
}
