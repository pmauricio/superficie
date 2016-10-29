#pragma once

//--------------------------------------------------------------
//
//
// ADVANCED 3D EXAMPLE
//		ofNode3d, ofCamera, ofEasyCam
//
//
//--------------------------------------------------------------


#include "ofMain.h"

// Custom objects for this example
#include "Swarm.h"
#include "Grid.h"
#include "OrthoCamera.h"
#include "ofxGui.h"
#include "ofxOscParameterSync.h"

#include "ofxLibwebsockets.h"




#define N_CAMERAS 4

class ofApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();

		void setupViewports();
		void drawScene(int iCameraDraw);
		void updateMouseRay();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
    


		//cameras (all these inherit from ofCamera)
		ofEasyCam camEasyCam;
		orthoCamera camFront;
		orthoCamera camTop;
		orthoCamera camLeft;

		 
    //cameras have parent?
		bool bCamParent;

		//camera pointers
		ofCamera * cameras[N_CAMERAS];
		int iMainCamera;

		//viewports
		ofRectangle viewMain;
		ofRectangle viewGrid[N_CAMERAS];

		//my custom node
		swarm nodeSwarm;
		grid nodeGrid;

		//ray drawn under mouse cursor [start,end]
		ofVec3f ray[2];
    
        ofEasyCam cam; // add mouse controls for camera movement
    
    void drawInteractionArea();
    bool bShowHelp;
    double alfa;
    double beta;
    double gama;
    
    
    //WEBSOCKET
    void gotMessage(ofMessage msg);
    ofxLibwebsockets::Server server;
    bool bSetup;
    //queue of rec'd messages
    vector<string> messages;
    //string to send to clients
    string toSend;
    // websocket methods
    void onConnect( ofxLibwebsockets::Event& args );
    void onOpen( ofxLibwebsockets::Event& args );
    void onClose( ofxLibwebsockets::Event& args );
    void onIdle( ofxLibwebsockets::Event& args );
    void onMessage( ofxLibwebsockets::Event& args );
    void onBroadcast( ofxLibwebsockets::Event& args );
    //END WEBSOKET
    
 };
