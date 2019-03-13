#include "ApeTexasEEGPlugin.h"

Ape::ApeTexasEEGPlugin::ApeTexasEEGPlugin()
{
	APE_LOG_FUNC_ENTER();
	mpEventManager = Ape::IEventManager::getSingletonPtr();
	mpEventManager->connectEvent(Ape::Event::Group::NODE, std::bind(&ApeTexasEEGPlugin::eventCallBack, this, std::placeholders::_1));
	mpSceneManager = Ape::ISceneManager::getSingletonPtr();
	mpSystemConfig = Ape::ISystemConfig::getSingletonPtr();
	mScore = 0;
	mpApeUserInputMacro = Ape::UserInputMacro::getSingletonPtr();
	mUserInputMacroPose = Ape::UserInputMacro::Pose();
	APE_LOG_FUNC_LEAVE();
}

Ape::ApeTexasEEGPlugin::~ApeTexasEEGPlugin()
{
	APE_LOG_FUNC_ENTER();
	mpEventManager->disconnectEvent(Ape::Event::Group::NODE, std::bind(&ApeTexasEEGPlugin::eventCallBack, this, std::placeholders::_1));
	if (mBubbleManager)
	{
		delete mBubbleManager;
		mBubbleManager = NULL;
	}
	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeTexasEEGPlugin::eventCallBack(const Ape::Event& event)
{

}

void Ape::ApeTexasEEGPlugin::Init()
{
	APE_LOG_FUNC_ENTER();
	mGameManager = new TexasEEG::GameManager(mpApeUserInputMacro->getUserNode());
	mGameManager->Start();

	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeTexasEEGPlugin::Run()
{
	APE_LOG_FUNC_ENTER();
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeTexasEEGPlugin::Step()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeTexasEEGPlugin::Stop()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeTexasEEGPlugin::Suspend()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeTexasEEGPlugin::Restart()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}
