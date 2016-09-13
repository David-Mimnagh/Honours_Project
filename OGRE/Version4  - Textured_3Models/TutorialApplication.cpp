/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
___                 __    __ _ _    _
/___\__ _ _ __ ___  / / /\ \ (_) | _(_)
//  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
|___/
Tutorial Framework (for Ogre 1.9)
http://www.ogre3d.org/wiki/
-----------------------------------------------------------------------------
*/

#include "TutorialApplication.h"

//---------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void) : mInfoLabel(0)
{
	loadModel1 = false, loadModel2 = false, loadModel3 = false;
}
//---------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

void TutorialApplication::createScene(void)
{
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5)); // Set ambient lighting

	model1 = mSceneMgr->createEntity("jacket.MESH");//insert the first mesh
	model2 = mSceneMgr->createEntity("TShirt_Hanging_Red.MESH");//insert the second mesh
	model3 = mSceneMgr->createEntity("Trainers_Black.MESH");//insert the third mesh

	ogreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(); // Creating scene node to show entity
	ogreNode->scale(Ogre::Vector3(15, 15, 15));
	ogreNode->attachObject(model1); //Attach entity to scene node
	currentModel = model1;
	light = mSceneMgr->createLight("MainLight"); // create the main light
	light->setPosition(20, 80, 50); // Set the light position

}
//---------------------------------------------------------------------------
void TutorialApplication::createFrameListener()
{
	BaseApplication::createFrameListener();
	mInfoLabel = mTrayMgr->createLabel(OgreBites::TL_TOP, "ModelInfo", "", 350);
}
bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
	bool ret = BaseApplication::frameRenderingQueued(fe);
	if (!processUnbufferedInput(fe))
		return false;
	mTrayMgr->moveWidgetToTray(mInfoLabel, OgreBites::TL_TOP, 0);
	mInfoLabel->show();

	return ret;
}
bool TutorialApplication::processUnbufferedInput(const Ogre::FrameEvent& fe)
{
	if (mKeyboard->isKeyDown(OIS::KC_1))
	{
		loadModel1 = true;
		loadModel2 = false;
		loadModel3 = false;
	}
	if (mKeyboard->isKeyDown(OIS::KC_2))
	{
		loadModel1 = false;
		loadModel2 = true;
		loadModel3 = false;
	}
	if (mKeyboard->isKeyDown(OIS::KC_3))
	{
		loadModel1 = false;
		loadModel2 = false;
		loadModel3 = true;
	}
	
	if (loadModel1 == true)
	{
		ogreNode->detachObject(currentModel);
		ogreNode->attachObject(model1); //Attach entity to scene node
		currentModel = model1;
		mInfoLabel->setCaption("Loading Model 1");
	}
	else if (loadModel2 == true)
	{
		ogreNode->detachObject(currentModel);
		ogreNode->attachObject(model2); //Attach entity to scene node
		currentModel = model2;
		mInfoLabel->setCaption("Loading Model 2");
	}
	else if (loadModel3 == true)
	{
		ogreNode->detachObject(currentModel);
		ogreNode->attachObject(model3); //Attach entity to scene node
		currentModel = model3;
		mInfoLabel->setCaption("Loading Model 3");
	}

	return true;
}


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
	int main(int argc, char *argv[])
#endif
	{
		// Create application object
		TutorialApplication app;

		try {
			app.go();
		}
		catch (Ogre::Exception& e)  {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
			std::cerr << "An exception has occurred: " <<
				e.getFullDescription().c_str() << std::endl;
#endif

		}

		return 0;
	}

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------
