#include "ApeLinkageDesignerVRPlugin.h"

Ape::ApeLinkageDesignerVRPlugin::ApeLinkageDesignerVRPlugin()
{
	APE_LOG_FUNC_ENTER();
	mpSystemConfig = Ape::ISystemConfig::getSingletonPtr();
	mpEventManager = Ape::IEventManager::getSingletonPtr();
	mpEventManager->connectEvent(Ape::Event::Group::CAMERA, std::bind(&ApeLinkageDesignerVRPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(Ape::Event::Group::NODE, std::bind(&ApeLinkageDesignerVRPlugin::eventCallBack, this, std::placeholders::_1));
	mpSceneManager = Ape::ISceneManager::getSingletonPtr();
	mInterpolators = std::vector<std::unique_ptr<Ape::Interpolator>>();
	mSwitchNodeVisibilityToggleIndex = 0;
	/*mSwitchNodeVisibilityNames = std::vector<std::string>();
	mSwitchNodeVisibilityNames.push_back("WeldingFixture@base1Switch");
	mSwitchNodeVisibilityNames.push_back("WeldingFixture@base2Switch");
	mSwitchNodeVisibilityNames.push_back("WeldingFixture@base3Switch");
	mSwitchNodeVisibilityNames.push_back("WeldingFixture@base4Switch");*/
	/*mSwitchNodeVisibilityNames.push_back("WeldingFixture@p1Switch");
	mSwitchNodeVisibilityNames.push_back("WeldingFixture@p2Switch");
	mSwitchNodeVisibilityNames.push_back("WeldingFixture@p3Switch");
	mSwitchNodeVisibilityNames.push_back("WeldingFixture@p4Switch");*/
	//mSwitchNodeVisibilityNames.push_back("WeldingFixture@fixture_1Switch");
	mSwitchNodeVisibilityNames.push_back("WeldingFixture@wp_1Switch");
	mSwitchNodeVisibilityNames.push_back("WeldingFixture@wp_2Switch");
	mSwitchNodeVisibilityNames.push_back("WeldingFixture@wp_3Switch");
	mSwitchNodeVisibilityNames.push_back("WeldingFixture@wp_4Switch");
	mSwitchNodeVisibilityNames.push_back("WeldingFixture@wp_5Switch");
	mSwitchNodeVisibilityNames.push_back("WeldingFixture@wp_6Switch");
	mSwitchNodeVisibilityNames.push_back("WeldingFixture@wp_7Switch");
	mSwitchNodeVisibilityNames.push_back("WeldingFixture@wp_8Switch");
	//mSwitchNodeVisibilityNames.push_back("WeldingFixture@WorkbenchSwitch");
	/*mSwitchNodeVisibilityNames.push_back("Bounding@BoxSwitch");*/
	mSwitchNodes = std::vector<Ape::NodeWeakPtr>();
	APE_LOG_FUNC_LEAVE();
}

Ape::ApeLinkageDesignerVRPlugin::~ApeLinkageDesignerVRPlugin()
{
	APE_LOG_FUNC_ENTER();
	mpEventManager->disconnectEvent(Ape::Event::Group::CAMERA, std::bind(&ApeLinkageDesignerVRPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->disconnectEvent(Ape::Event::Group::NODE, std::bind(&ApeLinkageDesignerVRPlugin::eventCallBack, this, std::placeholders::_1));
	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeLinkageDesignerVRPlugin::eventCallBack(const Ape::Event& event)
{
	if (event.type == Ape::Event::Type::NODE_CREATE)
	{
		if (auto node = mpSceneManager->getNode(event.subjectName).lock())
		{
			for (auto switchNodeName : mSwitchNodeVisibilityNames)
			{
				std::size_t found = node->getName().find(switchNodeName);
				if (found != std::string::npos)
					mSwitchNodes.push_back(node);
			}
		}
	}
}

void Ape::ApeLinkageDesignerVRPlugin::Init()
{
	APE_LOG_FUNC_ENTER();

	if (auto skyBoxMaterial = std::static_pointer_cast<Ape::IFileMaterial>(mpSceneManager->createEntity("skyBox", Ape::Entity::MATERIAL_FILE).lock()))
	{
		skyBoxMaterial->setFileName("skyBox.material");
		skyBoxMaterial->setAsSkyBox();
	}
	if (auto light = std::static_pointer_cast<Ape::ILight>(mpSceneManager->createEntity("light", Ape::Entity::LIGHT).lock()))
	{
		light->setLightType(Ape::Light::Type::DIRECTIONAL);
		light->setLightDirection(Ape::Vector3(1, -1, 0));
		light->setDiffuseColor(Ape::Color(0.6f, 0.6f, 0.6f));
		light->setSpecularColor(Ape::Color(0.6f, 0.6f, 0.6f));
	}
	if (auto light = std::static_pointer_cast<Ape::ILight>(mpSceneManager->createEntity("light2", Ape::Entity::LIGHT).lock()))
	{
		light->setLightType(Ape::Light::Type::DIRECTIONAL);
		light->setLightDirection(Ape::Vector3(0, -1, 1));
		light->setDiffuseColor(Ape::Color(0.6f, 0.6f, 0.6f));
		light->setSpecularColor(Ape::Color(0.6f, 0.6f, 0.6f));
	}

	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeLinkageDesignerVRPlugin::toggleSwitchNodesVisibility()
{
	APE_LOG_FUNC_ENTER();
	if (mSwitchNodes.size() > 0)
	{
		if (auto switchNode = mSwitchNodes[mSwitchNodeVisibilityToggleIndex].lock())
		{
			if (!switchNode->getChildrenVisibility())
				switchNode->setChildrenVisibility(true);
			else
				switchNode->setChildrenVisibility(false);
		}
		mSwitchNodeVisibilityToggleIndex++;
		if (mSwitchNodes.size() == mSwitchNodeVisibilityToggleIndex)
			mSwitchNodeVisibilityToggleIndex = 0;
	}
	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeLinkageDesignerVRPlugin::Run()
{
	APE_LOG_FUNC_ENTER();
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeLinkageDesignerVRPlugin::Step()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeLinkageDesignerVRPlugin::Stop()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeLinkageDesignerVRPlugin::Suspend()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeLinkageDesignerVRPlugin::Restart()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}
