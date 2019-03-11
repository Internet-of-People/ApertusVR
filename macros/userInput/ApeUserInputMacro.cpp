#include <iostream>
#include "ApeUserInputMacro.h"

Ape::UserInputMacro::UserInputMacro()
{
	APE_LOG_FUNC_ENTER();
	mpSystemConfig = Ape::ISystemConfig::getSingletonPtr();
	mpEventManager = Ape::IEventManager::getSingletonPtr();
	mpEventManager->connectEvent(Ape::Event::Group::NODE, std::bind(&UserInputMacro::eventCallBack, this, std::placeholders::_1));
	mpSceneManager = Ape::ISceneManager::getSingletonPtr();
	mCameras = std::map<std::string, Ape::CameraWeakPtr>();
	std::string uniqueUserNamePrefix = mpSystemConfig->getSceneSessionConfig().uniqueUserNamePrefix;
	std::string delimiter = "-";
	auto tp = std::chrono::system_clock::now();
	auto dur = tp.time_since_epoch();
	auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
	mUniqueUserNodeName =  uniqueUserNamePrefix + delimiter + std::to_string(nanoseconds);
	if (auto userNode = mpSceneManager->createNode(mUniqueUserNodeName).lock())
	{
		if (auto headNode = mpSceneManager->createNode(mUniqueUserNodeName + "_HeadNode").lock())
		{
			headNode->setParentNode(userNode);
			if (auto userMaterial = std::static_pointer_cast<Ape::IManualMaterial>(mpSceneManager->createEntity(mUniqueUserNodeName + "_Material", Ape::Entity::MATERIAL_MANUAL).lock()))
			{
				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_real_distribution<double> distDouble(0.0, 1.0);
				std::vector<double> randomColors;
				for (int i = 0; i < 3; i++)
					randomColors.push_back(distDouble(gen));
				userMaterial->setDiffuseColor(Ape::Color(randomColors[0], randomColors[1], randomColors[2]));
				userMaterial->setSpecularColor(Ape::Color(randomColors[0], randomColors[1], randomColors[2]));
				mUserMaterial = userMaterial;
			}
			mHeadNode = headNode;
		}
		mUserNode = userNode;
	}
	mOverlayText = Ape::TextGeometryWeakPtr();
	APE_LOG_FUNC_LEAVE();
}

Ape::UserInputMacro::~UserInputMacro()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}

void Ape::UserInputMacro::eventCallBack(const Ape::Event& event)
{
}

void Ape::UserInputMacro::updateViewPose(Pose pose)
{
	if (auto userNode = mUserNode.lock())
	{
		userNode->setPosition(pose.userPosition);
		userNode->setOrientation(pose.userOrientation);
	}
	if (auto headNode = mHeadNode.lock())
	{
		headNode->setPosition(pose.headPosition);
		headNode->setOrientation(pose.headOrientation);
	}
}

void Ape::UserInputMacro::interpolateViewPose(Pose pose, unsigned int milliseconds)
{
	if (auto userNode = mUserNode.lock())
	{
		auto moveInterpolator = std::make_unique<Ape::Interpolator>(false);
		moveInterpolator->addSection(
			userNode->getPosition(),
			pose.userPosition,
			milliseconds * 1000,
			[&](Ape::Vector3 pos) { userNode->setPosition(pos); }
		);
		auto rotateInterpolator = std::make_unique<Ape::Interpolator>(false);
		rotateInterpolator->addSection(
			userNode->getOrientation(),
			pose.userOrientation,
			milliseconds * 1000,
			[&](Ape::Quaternion ori) { userNode->setOrientation(ori); }
		);
		while (!moveInterpolator->isQueueEmpty() && !rotateInterpolator->isQueueEmpty())
		{
			if (!moveInterpolator->isQueueEmpty())
				moveInterpolator->iterateTopSection();
			if (!rotateInterpolator->isQueueEmpty())
				rotateInterpolator->iterateTopSection();
		}
	}
}

Ape::NodeWeakPtr Ape::UserInputMacro::getUserNode()
{
	return mUserNode;
}

Ape::NodeWeakPtr Ape::UserInputMacro::getHeadNode()
{
	return mHeadNode;
}

Ape::CameraWeakPtr Ape::UserInputMacro::createCamera(std::string name)
{
	std::string uniqueName = mUniqueUserNodeName + name;
	if (auto camera = std::static_pointer_cast<Ape::ICamera>(mpSceneManager->createEntity(name, Ape::Entity::Type::CAMERA).lock()))
	{
		if (auto cameraNode = mpSceneManager->createNode(uniqueName + "_Node").lock())
		{
			cameraNode->setParentNode(mHeadNode);
			if (auto cameraConeNode = mpSceneManager->createNode(uniqueName + "_ConeNode").lock())
			{
				cameraConeNode->setParentNode(cameraNode);
				cameraConeNode->rotate(Ape::Degree(90.0f).toRadian(), Ape::Vector3(1, 0, 0), Ape::Node::TransformationSpace::WORLD);
				if (auto cameraCone = std::static_pointer_cast<Ape::IConeGeometry>(mpSceneManager->createEntity(uniqueName + "_ConeGeometry", Ape::Entity::GEOMETRY_CONE).lock()))
				{
					cameraCone->setParameters(10.0f, 30.0f, 1.0f, Ape::Vector2(1, 1));
					cameraCone->setParentNode(cameraConeNode);
					cameraCone->setMaterial(mUserMaterial);
				}
			}
			if (auto userNameTextNode = mpSceneManager->createNode(uniqueName + "_TextNode").lock())
			{
				userNameTextNode->setParentNode(cameraNode);
				userNameTextNode->setPosition(Ape::Vector3(0.0f, 10.0f, 0.0f));
				if (auto userNameText = std::static_pointer_cast<Ape::ITextGeometry>(mpSceneManager->createEntity(uniqueName + "_TextGeometry", Ape::Entity::GEOMETRY_TEXT).lock()))
				{
					userNameText->setCaption(uniqueName);
					userNameText->setParentNode(userNameTextNode);
				}
			}
			camera->setParentNode(cameraNode);
		}
		mCameras[uniqueName] = camera;
		return camera;
	}
}

void Ape::UserInputMacro::updateOverLayText(std::string caption)
{
	if (auto overlayText = mOverlayText.lock())
	{
		overlayText->setCaption(caption);
	}
}

void Ape::UserInputMacro::createOverLayText(std::string caption)
{
	if (mOverlayText.lock())
	{

	}
	else
	{
		if (auto userNode = mUserNode.lock())
		{
			if (auto overLayTextNode = mpSceneManager->createNode("overLayTextNode").lock())
			{
				overLayTextNode->setParentNode(mUserNode);
				overLayTextNode->setPosition(Ape::Vector3(0, 17, -50));
				if (auto overlayText = std::static_pointer_cast<Ape::ITextGeometry>(mpSceneManager->createEntity("overLayText", Ape::Entity::GEOMETRY_TEXT).lock()))
				{
					overlayText->setCaption(caption);
					overlayText->showOnTop(true);
					overlayText->setParentNode(overLayTextNode);
					mOverlayText = overlayText;
				}
			}
		}
	}
}

