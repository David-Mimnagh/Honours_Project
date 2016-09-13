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
//---------------------------------------------------------------------------

class TutorialApplication : public BaseApplication
{
	Ogre::Entity* model1; Ogre::Entity* model2; Ogre::Entity* model3; Ogre::Entity* currentModel;
	Ogre::SceneNode* ogreNode;
	Ogre::Light* light;
	Ogre::RenderWindow* window;
	OgreBites::Label* mInfoLabel;


	bool loadModel1;
	bool loadModel2;
	bool loadModel3;


	bool processUnbufferedInput(const Ogre::FrameEvent& fe);
	void WriteInformation(std::string filename, int current, float values[]);
public:
	TutorialApplication(void);
	virtual ~TutorialApplication(void);
	

protected:
	virtual void createScene(void);
	virtual void createFrameListener();
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);

};

//---------------------------------------------------------------------------

#endif // #ifndef __TutorialApplication_h_

//---------------------------------------------------------------------------
