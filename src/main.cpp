#include "ofMain.h"
#include "ofApp.h"
#include "ofAppSecond.h"

shared_ptr<ofAppBaseWindow> *SECOND_WINDOW = 0;

//========================================================================
int main( ){

	/*ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());*/

	ofGLFWWindowSettings settings;

	settings.setSize(1024, 768);
	settings.setPosition(ofVec2f(0, 0));
	settings.resizable = true;
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

	settings.setSize(1000, 580);
	settings.setPosition(ofVec2f(1920, 0));
	settings.resizable = true;
	shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);
	SECOND_WINDOW = &guiWindow;

	shared_ptr<AppSecond> guiApp(new AppSecond);	//create it first, because mainApp will call set_screen()
	shared_ptr<ofApp> mainApp(new ofApp);

	ofRunApp(mainWindow, mainApp);
	ofRunApp(guiWindow, guiApp);
	ofRunMainLoop();

}
