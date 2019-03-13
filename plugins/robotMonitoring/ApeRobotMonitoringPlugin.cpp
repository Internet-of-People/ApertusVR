#include "ApeRobotMonitoringPlugin.h"

Ape::ApeRobotMonitoringPlugin::ApeRobotMonitoringPlugin()
{
	APE_LOG_FUNC_ENTER();
	mpSystemConfig = Ape::ISystemConfig::getSingletonPtr();
	mpEventManager = Ape::IEventManager::getSingletonPtr();
	mpEventManager->connectEvent(Ape::Event::Group::CAMERA, std::bind(&ApeRobotMonitoringPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(Ape::Event::Group::NODE, std::bind(&ApeRobotMonitoringPlugin::eventCallBack, this, std::placeholders::_1));
	mpSceneManager = Ape::ISceneManager::getSingletonPtr();
	APE_LOG_FUNC_LEAVE();
}

Ape::ApeRobotMonitoringPlugin::~ApeRobotMonitoringPlugin()
{
	APE_LOG_FUNC_ENTER();
	mpEventManager->disconnectEvent(Ape::Event::Group::CAMERA, std::bind(&ApeRobotMonitoringPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->disconnectEvent(Ape::Event::Group::NODE, std::bind(&ApeRobotMonitoringPlugin::eventCallBack, this, std::placeholders::_1));
	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeRobotMonitoringPlugin::eventCallBack(const Ape::Event& event)
{

}

void Ape::ApeRobotMonitoringPlugin::Init()
{
	APE_LOG_FUNC_ENTER();
	Ape::Color lightColor(0.4f, 0.4f, 0.44f);
	Ape::ManualMaterialSharedPtr glassMaterial = std::static_pointer_cast<Ape::IManualMaterial>(mpSceneManager->createEntity("glassMaterial", Ape::Entity::MATERIAL_MANUAL).lock());
	if (glassMaterial)
	{
		float opacity = 0.6f;
		glassMaterial->setDiffuseColor(Ape::Color(0.2, 0.2, 0.2, opacity));
		glassMaterial->setAmbientColor(Ape::Color(0.2, 0.2, 0.2));
		glassMaterial->setSpecularColor(Ape::Color(0.2, 0.2, 0.2, opacity));
		glassMaterial->setEmissiveColor(Ape::Color(0.2, 0.2, 0.2));
		glassMaterial->setSceneBlending(Ape::Pass::SceneBlendingType::TRANSPARENT_ALPHA);
		glassMaterial->setCullingMode(Ape::Material::CullingMode::NONE_CM);
	}
	if (auto light = std::static_pointer_cast<Ape::ILight>(mpSceneManager->createEntity("light", Ape::Entity::LIGHT).lock()))
	{
		light->setLightType(Ape::Light::Type::DIRECTIONAL);
		light->setLightDirection(Ape::Vector3(-1, 0, 0));
		light->setDiffuseColor(lightColor);
		light->setSpecularColor(lightColor);
	}
	/*if (auto light = std::static_pointer_cast<Ape::ILight>(mpSceneManager->createEntity("light2", Ape::Entity::LIGHT).lock()))
	{
		light->setLightType(Ape::Light::Type::DIRECTIONAL);
		light->setLightDirection(Ape::Vector3(0, -1, -1));
		light->setDiffuseColor(lightColor);
		light->setSpecularColor(lightColor);
	}
	if (auto light = std::static_pointer_cast<Ape::ILight>(mpSceneManager->createEntity("light3", Ape::Entity::LIGHT).lock()))
	{
		light->setLightType(Ape::Light::Type::DIRECTIONAL);
		light->setLightDirection(Ape::Vector3(0, 1, 1));
		light->setDiffuseColor(lightColor);
		light->setSpecularColor(lightColor);
	}*/
	/*if (auto lightNode = mpSceneManager->createNode("lightNode2").lock())
	{
		lightNode->setPosition(Ape::Vector3(0, 2500, -500));
		if (auto light = std::static_pointer_cast<Ape::ILight>(mpSceneManager->createEntity("light2", Ape::Entity::LIGHT).lock()))
		{
			light->setLightType(Ape::Light::Type::SPOT);
			light->setLightDirection(Ape::Vector3(0, -1, 0));
			light->setLightSpotRange(Ape::LightSpotRange(Ape::Degree(10), Ape::Degree(70), 2));
			light->setLightAttenuation(Ape::LightAttenuation(4000, 1, 0, 0));
			light->setDiffuseColor(lightColor);
			light->setSpecularColor(lightColor);
			light->setParentNode(lightNode);
		}
	}
	if (auto lightNode = mpSceneManager->createNode("lightNode3").lock())
	{
		lightNode->setPosition(Ape::Vector3(-1000, 2500, -500));
		if (auto light = std::static_pointer_cast<Ape::ILight>(mpSceneManager->createEntity("light3", Ape::Entity::LIGHT).lock()))
		{
			light->setLightType(Ape::Light::Type::SPOT);
			light->setLightDirection(Ape::Vector3(0, -1, 0));
			light->setLightSpotRange(Ape::LightSpotRange(Ape::Degree(10), Ape::Degree(70), 2));
			light->setLightAttenuation(Ape::LightAttenuation(4000, 1, 0, 0));
			light->setDiffuseColor(lightColor);
			light->setSpecularColor(lightColor);
			light->setParentNode(lightNode);
		}
	}*/
	if (auto lightNode = mpSceneManager->createNode("lightNode4").lock())
	{
		lightNode->setPosition(Ape::Vector3(-303.136, 250.268, -500.706));
		if (auto light = std::static_pointer_cast<Ape::ILight>(mpSceneManager->createEntity("light4", Ape::Entity::LIGHT).lock()))
		{
			light->setLightType(Ape::Light::Type::POINT);
			light->setDiffuseColor(lightColor);
			light->setSpecularColor(lightColor);
			light->setParentNode(lightNode);
		}
	}
	if (auto environmentNode = mpSceneManager->createNode("environmentNode").lock())
	{
		environmentNode->setPosition(Ape::Vector3(0, 0, -100));
		environmentNode->setScale(Ape::Vector3(-100, 100, 100));
		Ape::Quaternion rot1(0, 0, 1, 0);
		Ape::Degree angle(8);
		Ape::Vector3 axis(0, 0, 1);
		Ape::Quaternion rot2;
		rot2.FromAngleAxis(Ape::Radian(angle.toRadian()), axis);
		Ape::Quaternion rot3;
		rot3 = rot1 * rot2;
		environmentNode->setOrientation(rot3);
		if (auto environmentMeshFile = std::static_pointer_cast<Ape::IFileGeometry>(mpSceneManager->createEntity("sphere.mesh", Ape::Entity::GEOMETRY_FILE).lock()))
		{
			environmentMeshFile->setFileName("sphere.mesh");
			environmentMeshFile->setParentNode(environmentNode);
		}
	}
	if (auto glassWallNode = mpSceneManager->createNode("glassWallNode").lock())
	{
		glassWallNode->setPosition(Ape::Vector3(0, 0, 195));
		Ape::Degree angle(90);
		Ape::Vector3 axis(1, 0, 0);
		Ape::Quaternion orientation;
		orientation.FromAngleAxis(Ape::Radian(angle.toRadian()), axis);
		glassWallNode->setOrientation(orientation);
		if (auto glassWallGeometry = std::static_pointer_cast<Ape::IPlaneGeometry>(mpSceneManager->createEntity("glassWallGeometry", Ape::Entity::GEOMETRY_PLANE).lock()))
		{
			glassWallGeometry->setParameters(Ape::Vector2(1, 1), Ape::Vector2(5000, 5000), Ape::Vector2(1, 1));
			glassWallGeometry->setMaterial(glassMaterial);
			glassWallGeometry->setParentNode(glassWallNode);
		}
	}
	if (auto environmentNode = mpSceneManager->createNode("environmentNode_3").lock())
	{
		environmentNode->setPosition(Ape::Vector3(0, 0, 100));
		environmentNode->setScale(Ape::Vector3(-100, 100, 100));
		Ape::Quaternion rot1(0, 0, 1, 0);
		environmentNode->setOrientation(rot1);
		if (auto environmentMeshFile = std::static_pointer_cast<Ape::IFileGeometry>(mpSceneManager->createEntity("sphere_3.mesh", Ape::Entity::GEOMETRY_FILE).lock()))
		{
			environmentMeshFile->setFileName("sphere_3.mesh");
			environmentMeshFile->setParentNode(environmentNode);
		}
	}
	if (auto glassWallNode = mpSceneManager->createNode("glassWallNode3").lock())
	{
		glassWallNode->setPosition(Ape::Vector3(0, 0, -1320));
		Ape::Radian angle(1.57f);
		Ape::Vector3 axis(1, 0, 0);
		Ape::Quaternion orientation;
		orientation.FromAngleAxis(angle, axis);
		glassWallNode->setOrientation(orientation);
		if (auto glassWallGeometry = std::static_pointer_cast<Ape::IPlaneGeometry>(mpSceneManager->createEntity("glassWallGeometry3", Ape::Entity::GEOMETRY_PLANE).lock()))
		{
			glassWallGeometry->setParameters(Ape::Vector2(1, 1), Ape::Vector2(5000, 5000), Ape::Vector2(1, 1));
			glassWallGeometry->setMaterial(glassMaterial);
			glassWallGeometry->setParentNode(glassWallNode);
		}
	}
	if (auto entranceWallNode = mpSceneManager->createNode("entranceWallNode").lock())
	{
		entranceWallNode->setPosition(Ape::Vector3(410, 0, -500));
		Ape::Quaternion orientation(0.707, 0.707, 0, 0);
		Ape::Quaternion orientation2(0.707, 0, 0, 0.707);
		Ape::Quaternion orientation3;
		orientation3 = orientation * orientation2;
		entranceWallNode->setOrientation(orientation3);
		if (auto entranceWallGeometry = std::static_pointer_cast<Ape::IPlaneGeometry>(mpSceneManager->createEntity("entranceWallGeometry", Ape::Entity::GEOMETRY_PLANE).lock()))
		{
			entranceWallGeometry->setParameters(Ape::Vector2(1, 1), Ape::Vector2(1000, 1000), Ape::Vector2(1, 1));
			entranceWallGeometry->setParentNode(entranceWallNode);
		}
	}
	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeRobotMonitoringPlugin::Run()
{
	APE_LOG_FUNC_ENTER();
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeRobotMonitoringPlugin::Step()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeRobotMonitoringPlugin::Stop()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeRobotMonitoringPlugin::Suspend()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeRobotMonitoringPlugin::Restart()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}
