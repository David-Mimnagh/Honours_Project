/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.h
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

#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include "BaseApplication.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <time.h>
//---------------------------------------------------------------------------
#define POLYGON_LEVEL 3
class TutorialApplication : public BaseApplication
{
	Ogre::Entity* model1; Ogre::Entity* model2; Ogre::Entity* model3; Ogre::Entity* model4; Ogre::Entity* model5; Ogre::Entity* currentModel;
	Ogre::SceneNode* ogreNode;
	Ogre::Light* light;
	Ogre::RenderWindow* window;
	OgreBites::Label* mInfoLabel;
	std::string L_model1, L_model2, L_model3, L_model4, L_model5;
	std::string M_model1, M_model2, M_model3, M_model4, M_model5;
	std::string H_model1, H_model2, H_model3, H_model4, H_model5;
	std::ofstream file;
	std::string fileName;
	float values[15];
	bool writeToFile;
	float timeTaken;
	int nextFrame;
	float currentTimer;
	float currentFrame;
	float refreshTimer;
	bool loadModel1, loadModel2, loadModel3, loadModel4, loadModel5;
	bool processUnbufferedInput(const Ogre::FrameEvent& fe);

	void WriteInformation(std::string filename, int current, float values[]);
public:
	TutorialApplication(void);
	virtual ~TutorialApplication(void);

	void FPS(const Ogre::FrameEvent& fe);

protected:
	virtual void createScene(void);
	virtual void createFrameListener();
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);

};

//---------------------------------------------------------------------------

#endif // #ifndef __TutorialApplication_h_

//---------------------------------------------------------------------------
