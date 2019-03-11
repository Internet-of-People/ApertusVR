/*MIT License

Copyright (c) 2018 MTA SZTAKI

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#ifndef APE_USERINPUTMACRO_H
#define APE_USERINPUTMACRO_H

#ifdef _WIN32
#ifdef BUILDING_APE_USERINPUTMACRO_DLL
#define APE_USERINPUTMACRO_DLL_EXPORT __declspec(dllexport)
#else
#define APE_USERINPUTMACRO_DLL_EXPORT __declspec(dllimport)
#endif
#else
#define APE_USERINPUTMACRO_DLL_EXPORT 
#endif

#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <memory>
#include "plugin/ApePluginAPI.h"
#include "managers/ApeIEventManager.h"
#include "managers/ApeILogManager.h"
#include "managers/ApeISceneManager.h"
#include "sceneelements/ApeINode.h"
#include "sceneelements/ApeILight.h"
#include "sceneelements/ApeITextGeometry.h"
#include "sceneelements/ApeIFileGeometry.h"
#include "sceneelements/ApeIConeGeometry.h"
#include "sceneelements/ApeIFileMaterial.h"
#include "sceneelements/ApeIManualMaterial.h"
#include "sceneelements/ApeICamera.h"
#include "managers/ApeISystemConfig.h"
#include "utils/ApeInterpolator.h"
#include "utils/ApeSingleton.h"

namespace Ape
{
    class APE_USERINPUTMACRO_DLL_EXPORT UserInputMacro : public Singleton<UserInputMacro>
    {
	public: 
		struct Pose
		{
			Ape::Vector3 userPosition;

			Ape::Quaternion userOrientation;

			Ape::Vector3 headPosition;

			Ape::Quaternion headOrientation;

			Pose() {}

			Pose(Ape::Vector3 userPosition, Ape::Quaternion userOrientation, Ape::Vector3 headPosition, Ape::Quaternion headOrientation)
			{
				this->userPosition = userPosition;
				this->userOrientation = userOrientation;
				this->headPosition = headPosition;
				this->headOrientation = headOrientation;
			}
		};

	private:
		Ape::IEventManager* mpEventManager;

		Ape::ISceneManager* mpSceneManager;

		Ape::ISystemConfig* mpSystemConfig;

		Ape::NodeWeakPtr mUserNode;

		std::string mUniqueUserNodeName;

		Ape::NodeWeakPtr mHeadNode;

		Ape::TextGeometryWeakPtr mOverlayText;

		std::map<std::string, Ape::CameraWeakPtr> mCameras;

		Ape::ManualMaterialWeakPtr mUserMaterial;

		void eventCallBack(const Ape::Event& event);

	public:
		UserInputMacro();

		~UserInputMacro();

		void updateViewPose(Pose pose);

		void interpolateViewPose(Pose pose, unsigned int milliseconds);

		Ape::NodeWeakPtr getUserNode();

		Ape::NodeWeakPtr getHeadNode();

		Ape::CameraWeakPtr createCamera(std::string name);

		void createOverLayText(std::string caption);

		void updateOverLayText(std::string caption);
    };
}

#endif
