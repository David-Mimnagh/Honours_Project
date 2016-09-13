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
	loadModel1 = false, loadModel2 = false, loadModel3 = false, end = false, writeToFile = false;
	values[0] = 11.0f;
	values[1] = 1154.0f;
	values[2] = 151.0f;
	values[3] = 154141.0f;
	values[4] = 22.0f;
	fileName = "info.csv";
	FPS = 0;

}
//---------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}
void TutorialApplication::WriteInformation(std::string filename, int current, float values[])
{
	file.open(fileName);
	file << "Current Model: " << current << "\n";
	file << values[0] << "," << values[1] << "," << values[2] << "\n";
	file << "Current Model: " << current + 1 << "\n";
	file << values[3] << "," << values[4] << "," << values[5] << "\n";
	file << "Current Model: " << current + 2 << "\n";
	file << values[6] << "," << values[7] << "," << values[8] << "\n";
	file.close();
}
//---------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5)); // Set ambient lighting
	//TShirt_Hanging_Red.MESH, Trainers_Black.MESH, jacket.MESH ---- Model 3, Model 2, Model 1
	model1 = mSceneMgr->createEntity("model1.MESH");//insert the first mesh
	model2 = mSceneMgr->createEntity("model2.MESH");//insert the mesh
	model3 = mSceneMgr->createEntity("model3.MESH");//insert the mesh

	ogreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(); // Creating scene node to show entity
	ogreNode->attachObject(model1); //Attach entity to scene node
	ogreNode->scale(Ogre::Vector3(15, 15, 15));
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
	if (mKeyboard->isKeyDown(OIS::KC_4))
	{
		writeToFile = true;
		loadModel1 = false;
		loadModel2 = false;
		loadModel3 = false;
	}
	if (writeToFile == true)
	{
		mInfoLabel->setCaption("Writing to file...");
		WriteInformation(fileName, 1, values);
		mInfoLabel->setCaption("Done");
		writeToFile = false;
	}
	if (loadModel1 == true)
	{
		ogreNode->detachObject(currentModel);
		ogreNode->attachObject(model1); //Attach entity to scene node
		currentModel = model1;
		values[0] = 1; values[1] = 11; values[2] = 111;
		mInfoLabel->setCaption("Loading Model 1");
	}
	else if (loadModel2 == true)
	{
		ogreNode->detachObject(currentModel);
		ogreNode->attachObject(model2); //Attach entity to scene node
		currentModel = model2;
		values[3] = 2; values[4] = 22; values[5] = 222;
		mInfoLabel->setCaption("Loading Model 2");
	}
	else if (loadModel3 == true)
	{
		ogreNode->detachObject(currentModel);
		ogreNode->attachObject(model3); //Attach entity to scene node
		currentModel = model3;
		values[6] = 3; values[7] = 33; values[8] = 333;
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
