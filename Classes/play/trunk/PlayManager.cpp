//
//  PlayManager.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-8-25.
//
//

#include "PlayManager.h"
#include "PlayShared.h"
#include "GameSceneMgr.h"
#include "DBLevelNotes.h"
#include "DBJigLevel.h"

PlayManager::PlayManager()
{

}

PlayManager::~PlayManager()
{
    
}

void PlayManager::onStateChanged(GameState gs)
{
//    if (gs==gs_dead && GameStateMgr::inst().lastState()!=gs_pause)
//    {
//        playshared.play_scene->alert( PauseLayer::create() );
//    }
}

void PlayManager::enterGame(const PlayInitMsg& msg)
{
    GameStateMgr::inst().setKeyListener(this);

    playshared.resetAll();
    
    playshared.m_config = msg;
    playshared.cur_level = 0;
    CCASSERT(playshared.cur_level<playshared.config().max_level(), "");
    
    restart();
}

void PlayManager::exitGame()
{
    playshared.resetAll();
    GameStateMgr::inst().clearListener();
    GameStateMgr::inst().change(gs_none);

    GameSceneMgr::inst().replace(kStartScene);
}

void PlayManager::restart()
{
    playshared.resetNewlevel();

    reloadResource();

    GameSceneMgr::inst().replace(kPlayScene);
    GameStateMgr::inst().change(gs_prepare);
}

void PlayManager::startNextLevel()
{
    assert( playshared.cur_level+1 != playshared.config().max_level() );
    ++playshared.cur_level;

    restart();
}

//void PlayManager::saveState()
//{
//}

//void PlayManager::clearState()
//{
//    GameStateMgr::inst().clearListener();
//    GameStateMgr::inst().change(gs_none);
//}

bool PlayManager::finishAllState()
{
    return playshared.cur_level==playshared.config().max_level()-1;
}

void PlayManager::reloadResource()
{
    addSpriteFrameByFile( playshared.getJigsaw() );

    DBJigLevel data;
    DBJigLevel::readby_level(data, playshared.cur_level);
    playshared.rows = data.rows;
    playshared.cols = data.cols;
}

//int PlayManager::getstar()
//{
//    float percent = lefttime() / (float) playconfig().max_time();
//    if (percent>=0 && percent<0.4)
//    {
//        return 1;
//    }
//    else if (percent<=0.7)
//    {
//        return 2;
//    }
//    else
//    {
//        return 3;
//    }
//}

//int PlayManager::lefttime()
//{
//    return playconfig().max_time()-playshared.esptime;
//}

