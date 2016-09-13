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
	values[0] = 11.0f;
	values[1] = 1154.0f;
	values[2] = 151.0f;
	values[3] = 154141.0f;
	values[4] = 212.0f;
	values[5] = 122.0f;
	values[6] = 221.0f;
	values[7] = 2112.0f;
	values[8] = 12232.0f;
	fileName = "Testing/HIGHPOLYGONCOUNT5.csv";
	L_model1 = "STC_mining_boot.MESH"; L_model2 = "boar-fbx.MESH"; L_model3 = "basketball.MESH";  L_model4 = "zune_120.MESH"; L_model5 = "MagmaElemental.MESH";
	M_model1 = "PS4.MESH"; M_model2 = "SC Private 001.MESH"; M_model3 = "sed.MESH"; M_model4 = "Motorola V3.MESH"; M_model5 = "nokia-5700-highres.MESH";
	H_model1 = "anturium.MESH"; H_model2 = "Technosphere.MESH"; H_model3 = "ArmChair.MESH"; H_model4 = "ship steering double wheel.MESH"; H_model5 = "Nokia_5310.MESH";
	nextFrame = 0;
	currentTimer = 0.0f;
	currentFrame = 0.0f;
	refreshTimer = 0.5f;
	timeTaken = 0.0f;


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
	file << "Current Model: " << current + 3 << "\n";
	file << values[9] << "," << values[10] << "," << values[11] << "\n";
	file << "Current Model: " << current + 4 << "\n";
	file << values[12] << "," << values[13] << "," << values[14] << "\n";
	file.close();
}
void TutorialApplication::FPS(const Ogre::FrameEvent& fe)
{
	if (currentTimer < refreshTimer)
	{
		currentTimer += fe.timeSinceLastFrame;
		nextFrame++;
	}
	else
	{
		//This code will break if you set your refreshTimer to 0, which makes no sense.
		currentFrame = (float)nextFrame / currentTimer;
		nextFrame = 0;
		currentTimer = 0.0f;
	}

}
//---------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5)); // Set ambient lighting
	//TShirt_Hanging_Red.MESH, Trainers_Black.MESH, jacket.MESH ---- Model 3, Model 2, Model 1
	if (POLYGON_LEVEL == 1)
	{
		model1 = mSceneMgr->createEntity(L_model1);//insert the first mesh
		model2 = mSceneMgr->createEntity(L_model2);
		model3 = mSceneMgr->createEntity(L_model3);
		model4 = mSceneMgr->createEntity(L_model4);
		model5 = mSceneMgr->createEntity(L_model5);
	}
	else if (POLYGON_LEVEL == 2)
	{
		model1 = mSceneMgr->createEntity(M_model1);//insert the first mesh
		model2 = mSceneMgr->createEntity(M_model2);
		model3 = mSceneMgr->createEntity(M_model3);
		model4 = mSceneMgr->createEntity(M_model4);
		model5 = mSceneMgr->createEntity(M_model5);
	}
	else if (POLYGON_LEVEL == 3)
	{
		model1 = mSceneMgr->createEntity(H_model1);//insert the first mesh
		model2 = mSceneMgr->createEntity(H_model2);
		model3 = mSceneMgr->createEntity(H_model3);
		model4 = mSceneMgr->createEntity(H_model4);
		model5 = mSceneMgr->createEntity(H_model5);
	}
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
	FPS(fe);
	
	if (mKeyboard->isKeyDown(OIS::KC_1))
	{
		loadModel1 = true;
		loadModel2 = false;
		loadModel3 = false;
		loadModel4 = false;
		loadModel5 = false;
		values[0] = currentFrame;
	}
	if (mKeyboard->isKeyDown(OIS::KC_2))
	{
		loadModel1 = false;
		loadModel2 = true;
		loadModel3 = false;
		loadModel4 = false;
		loadModel5 = false;
		values[3] = currentFrame;
	}
	if (mKeyboard->isKeyDown(OIS::KC_3))
	{
		loadModel1 = false;
		loadModel2 = false;
		loadModel3 = true;
		loadModel4 = false;
		loadModel5 = false;
		values[6] = currentFrame;
	}
	if (mKeyboard->isKeyDown(OIS::KC_4))
	{
		loadModel1 = false;
		loadModel2 = false;
		loadModel3 = false;
		loadModel4 = true;
		loadModel5 = false;
		values[9] = currentFrame;
	}
	if (mKeyboard->isKeyDown(OIS::KC_5))
	{
		loadModel1 = false;
		loadModel2 = false;
		loadModel3 = false;
		loadModel4 = false;
		loadModel5 = true;
		values[12] = currentFrame;
	}
	if (mKeyboard->isKeyDown(OIS::KC_6))
	{
		writeToFile = true;
		loadModel1 = false;
		loadModel2 = false;
		loadModel3 = false;
		loadModel4 = false;
		loadModel5 = false;
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
		timeTaken += fe.timeSinceLastEvent;
		ogreNode->attachObject(model1); //Attach entity to scene node
		currentModel = model1;
		values[2] = timeTaken;
		timeTaken = 0.0f;
		values[1] = 1;
		mInfoLabel->setCaption("Loading Model 1");
	}
	else if (loadModel2 == true)
	{
		ogreNode->detachObject(currentModel);
		timeTaken += fe.timeSinceLastEvent;
		ogreNode->attachObject(model2); //Attach entity to scene node
		currentModel = model2;
		values[5] = timeTaken;
		timeTaken = 0.0f;
		values[4] = 2;
		mInfoLabel->setCaption("Loading Model 2");
	}
	else if (loadModel3 == true)
	{
		ogreNode->detachObject(currentModel);
		timeTaken += fe.timeSinceLastEvent;
		ogreNode->attachObject(model3); //Attach entity to scene node
		currentModel = model3;
		values[8] = timeTaken;
		timeTaken = 0.0f;
		values[7] = 3;
		mInfoLabel->setCaption("Loading Model 3");
	}
	else if (loadModel4 == true)
	{
		ogreNode->detachObject(currentModel);
		timeTaken += fe.timeSinceLastEvent;
		ogreNode->attachObject(model4); //Attach entity to scene node
		currentModel = model4;
		values[11] = timeTaken;
		timeTaken = 0.0f;
		values[10] = 4;
		mInfoLabel->setCaption("Loading Model 4");
	}
	else if (loadModel5 == true)
	{
		ogreNode->detachObject(currentModel);
		timeTaken += fe.timeSinceLastEvent;
		ogreNode->attachObject(model5); //Attach entity to scene node
		currentModel = model5;
		values[14] = timeTaken;
		timeTaken = 0.0f;
		values[13] = 5;
		mInfoLabel->setCaption("Loading Model 5");
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
