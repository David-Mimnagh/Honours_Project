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
	Ogre::Entity* model1;
	Ogre::SceneNode* ogreNode;
	Ogre::Light* light;
	Ogre::RenderWindow* window;

public:
	TutorialApplication(void);
	virtual ~TutorialApplication(void);
	

protected:
	virtual void createScene(void);
};

//---------------------------------------------------------------------------

#endif // #ifndef __TutorialApplication_h_

//---------------------------------------------------------------------------
