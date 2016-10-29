#include "ofApp.h"

//--------------------------------------------------------------
//
//
// ADVANCED 3D EXAMPLE
//		ofNode3d, ofCamera, ofEasyCam
//
//
//--------------------------------------------------------------

//
// SUGGESTED EXERCISES
//
// 0. Run and understand the example
//
// 1. Change number of particles in the swarm.
// 2. Change the dynamic properties of the swarm (speed, orbit radius)
// 3. Change the near and far clipping planes of camEasyCam
//
// 4. Add another camera to the existing 4.
//		Have all parts of the example working with all 5 cameras.
//
// 6. Create your own custom node class and add an instance of it
//		to the scene.
//
// 7. Understand how the 'frustrum preview' works
//



//--------------------------------------------------------------
void ofApp::setup(){
//
	ofSetVerticalSync(true);
	ofBackground(70, 70, 70);
//    ofSetBackgroundAuto(false);
//    ofBackground(255,255,255);
    ofEnableAlphaBlending();
    
	ofEnableSmoothing();
	ofEnableDepthTest();
//
//    
  
    ofVec3f v1;
//        cam.setPosition(v1);
//
//    cam.position.y = 1072.74
//    
//    cam.position.z = 2461.54;
    ofSetCircleResolution(64);
    bShowHelp = true;


	//--
	// Setup cameras

	iMainCamera = 0;
	bCamParent = false;

	// user camera
	camEasyCam.setTarget(nodeSwarm);
	camEasyCam.setDistance(100);
	cameras[0] = &camEasyCam;


	// front
	camFront.scale = 20;
	cameras[1] = &camFront;

	// top
	camTop.scale = 20;
	camTop.tilt(-90);
	cameras[2] = &camTop;

	// left
	camLeft.scale = 20;
	camLeft.pan(-90);
	cameras[3] = &camLeft;

	//
	//--



	//--
	// Define viewports

	setupViewports();

	//
	//--




	//--
	// Setup swarm

	// swarm is a custom ofNode in this example (see Swarm.h / Swarm.cpp)
	nodeSwarm.init(10000, 50, 10);
    // this sets the camera's distance from the object
    cam.setDistance(100);
    cam.setTarget(nodeSwarm.particles[nodeSwarm.particles.size()/2].position);
	//
	//--
//    gui.setup("contorls");
//    gui.add(xSlider.setup("xasdasdasda", 1,0 , 500));
//
//  gui.add(ySlider.setup("asdasdax", 1,0 , 500));
//    gui.add(xSlider.setup("x", 1,0 , 5));

    
    
    // we add this listener before setting up so the initial circle resolution is correct
//    circleResolution.addListener(this, &ofApp::circleResolutionChanged);
//    ringButton.addListener(this, &ofApp::ringButtonPressed);
//    
    
    // setup a server with default options on port 9092
    // - pass in true after port to set up with SSL
    //bSetup = server.setup( 9093 );
    
    
    //WEBSOCKET
    ofxLibwebsockets::ServerOptions options = ofxLibwebsockets::defaultServerOptions();
    options.port = 9092;
    options.bUseSSL = false; // you'll have to manually accept this self-signed cert if 'true'!
    bSetup = server.setup( options );
    
    // this adds your app as a listener for the server
    server.addListener(this);
    //WEBSOCKET
}


//--------------------------------------------------------------
void ofApp::setupViewports(){
	//call here whenever we resize the window


	//--
	// Define viewports

	float xOffset = ofGetWidth() / 3;
	float yOffset = ofGetHeight() / N_CAMERAS;

	viewMain.x = xOffset;
	viewMain.y = 0;
	viewMain.width = xOffset * 2;
	viewMain.height = ofGetHeight();

	for(int i = 0; i < N_CAMERAS; i++){

		viewGrid[i].x = 0;
		viewGrid[i].y = yOffset * i;
		viewGrid[i].width = xOffset;
		viewGrid[i].height = yOffset;
	}

	//
	//--
}

//--------------------------------------------------------------
void ofApp::update(){

}


//--------------------------------------------------------------
void ofApp::draw(){
//
    
    if ( bSetup ){
        ofDrawBitmapString("WebSocket server setup at "+ofToString( server.getPort() ) + ( server.usingSSL() ? " with SSL" : " without SSL"), 20, 20);
    }
    
    
    ofEnableDepthTest();

    cam.begin();
  
    drawScene(1);
    
    
    
    
    cam.end();
    
    ofSetColor(70,255,0,125*alfa);
    
    
    ofFill();

    ofDisableDepthTest();
    
    nodeSwarm.drawGUI();
    ofRectangle(ofGetWidth()/2,ofGetHeight()/2,ofGetWidth(),ofGetHeight());
//
//    string msg = string("Using mouse inputs to navigate (press 'c' to toggle): ") + (cam.getMouseInputEnabled() ? "YES" : "NO");
//    msg += string("\nShowing help (press 'h' to toggle): ")+ (bShowHelp ? "YES" : "NO");
//    if (bShowHelp) {
//        msg += "\n\nLEFT MOUSE BUTTON DRAG:\nStart dragging INSIDE the yellow circle -> camera XY rotation .\nStart dragging OUTSIDE the yellow circle -> camera Z rotation (roll).\n\n";
//        msg += "LEFT MOUSE BUTTON DRAG + TRANSLATION KEY (" + ofToString(cam.getTranslationKey()) + ") PRESSED\n";
//        msg += "OR MIDDLE MOUSE BUTTON (if available):\n";
//        msg += "move over XY axes (truck and boom).\n\n";
//        msg += "RIGHT MOUSE BUTTON:\n";
//        msg += "move over Z axis (dolly)";
//        
//    }
//    msg += "\n\nfps: " + ofToString(ofGetFrameRate(), 2);
//    msg += "\n " +ofToString( cam.getPosition().x )+
//    " " +ofToString(cam.getPosition().y )+" "+ofToString(cam.getPosition().z);
//    ofDrawBitmapStringHighlight(msg, 10, 20);
//
    if ( bSetup ){
        ofDrawBitmapString("WebSocket server setup at "+ofToString( server.getPort() ) + ( server.usingSSL() ? " with SSL" : " without SSL"), 20, 20);
        
        ofSetColor(150);
        ofDrawBitmapString("Click anywhere to open up client example", 20, 40);
        
        
        ofDrawBitmapString("alfa "+ to_string(alfa)+" beta "+to_string(beta)+" gama "+ to_string(gama),20,30);
    } else {
        ofDrawBitmapString("WebSocket setup failed :(", 20,20);
    }
	// restore the GL depth function
	glDepthFunc(GL_LESS);
	ofPopStyle();

	//
	//--
}

void ofApp::drawScene(int iCameraDraw){

    nodeSwarm.light.setPosition(cam.getPosition());

    nodeSwarm.draw();
    
//	nodeGrid.draw();

//	//--
//	// Draw frustum preview for ofEasyCam camera
//
//	// This code draws our camera in
//	//	the scene (reddy/pink lines)
//	//
//	// The pyramid-like shape defined
//	//	by the cameras view is called
//	//	a 'frustum'.
//	//
//	// Often we refer to the volume
//	//	which can be seen by the
//	//	camera as 'the view frustum'.
//
//
	// First check if we're already drawing the view through the easycam
	// If so, don't draw the frustum preview.
	if(iCameraDraw != 0){

		ofPushStyle();
		ofPushMatrix();

		//--
		// Create transform for box->frustum

		// In 'camera space' the bounds of
		//  the view are defined by a box
		//  with bounds -1->1 in each axis
		//
		// To convert from camera to world
		//  space, we multiply by the inverse
		//  camera matrix of the camera, i.e
		//  inverse of the ViewProjection
		//  matrix.
		//
		// By applying this transformation
		//  our box in camera space is
		//  transformed into a frustum in
		//  world space.
		//

		// The camera's matricies are dependant on
		//  the aspect ratio of the viewport.
		//  (Which is why we use the viewport as
		//  an argument when we begin the camera.
		//
		// If this camera is fullscreen we'll use
		//   viewMain, else we'll use viewGrid[0]
		ofRectangle boundsToUse;
		if(iMainCamera == 0){
			boundsToUse = viewMain;
		}
		else{
			boundsToUse = viewGrid[0];
		}

		// Now lets get the inverse ViewProjection
		//  for the camera
		ofMatrix4x4 inverseCameraMatrix;
		inverseCameraMatrix.makeInvertOf(camEasyCam.getModelViewProjectionMatrix(boundsToUse));

		// By default, we can say
		//	'we are drawing in world space'
		//
		// The camera matrix performs
		//	world->camera
		//
		// The inverse camera matrix performs
		//	camera->world
		//
		// Our box is in camera space, if we
		//	want to draw that into world space
		//	we have to apply the camera->world
		//	transformation.
		//

		// This syntax is a little messy.
		// What it's saying is, send the data
		//  from the inverseCameraMatrix object
		//  to OpenGL, and apply that matrix to
		//  the current OpenGL transform
		ofMultMatrix( inverseCameraMatrix );

		//
		//--


		//--
		// Draw box in camera space
		// (i.e. frustum in world space)

		ofNoFill();
		// i.e. a box -1, -1, -1 to +1, +1, +1
		ofDrawBox(0, 0, 0, 2.0f);
		//
		//--

		ofPopStyle();
		ofPopMatrix();
	}

	//
	//--



	//--
	// Draw mouse ray

	// Draw the ray if ofEasyCam is in main view,
	//  and we're not currently drawing in that view
	if(iMainCamera == 0 && iCameraDraw != 0){
		ofPushStyle();
		ofSetColor(100, 100, 255);
		ofDrawLine(ray[0], ray[1]);
		ofPopStyle();
	}

	//
	//--
}

//--------------------------------------------------------------
void ofApp::updateMouseRay(){
	// Define ray in screen space
	ray[0] = ofVec3f(ofGetMouseX(), ofGetMouseY(), -1);
	ray[1] = ofVec3f(ofGetMouseX(), ofGetMouseY(), 1);

	// Transform ray into world space
	ray[0] = cameras[iMainCamera]->screenToWorld(ray[0], viewMain);
	ray[1] = cameras[iMainCamera]->screenToWorld(ray[1], viewMain);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    cout << " key "+ ofToString(key);
	if(key >= '1' && key <= '4'){
		iMainCamera = key - '1';
	}

	if(key == 'f'){
		ofToggleFullscreen();
	}

	if(key == 'p'){
		if(bCamParent){
			camFront.clearParent();
			camTop.clearParent();
			camLeft.clearParent();

			bCamParent = false;
		}
		else{
			camFront.setParent(nodeSwarm.light);
			camTop.setParent(nodeSwarm.light);
			camLeft.setParent(nodeSwarm.light);

			bCamParent = true;
		}
	}
    
    // do some typing!
    if ( key != OF_KEY_RETURN ){
        if ( key == OF_KEY_BACKSPACE ){
            if ( toSend.length() > 0 ){
                toSend.erase(toSend.end()-1);
            }
        } else {
            toSend += key;
        }
    } else {
        // send to all clients
        server.send( toSend );
        messages.push_back("Sent: '" + toSend + "' to "+ ofToString(server.getConnections().size())+" websockets" );
        toSend = "";
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    string url = "http";
    if ( server.usingSSL() ){
        url += "s";
    }
    url += "://localhost:" + ofToString( server.getPort() );
   // ofLaunchBrowser(url);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	setupViewports();
}



//--------------------------------------------------------------
void ofApp::onConnect( ofxLibwebsockets::Event& args ){
    cout<<"on connected"<<endl;
}

//--------------------------------------------------------------
void ofApp::onOpen( ofxLibwebsockets::Event& args ){
    cout<<"new connection open"<<endl;
    messages.push_back("New connection from " + args.conn.getClientIP() + ", " + args.conn.getClientName() );
}

//--------------------------------------------------------------
void ofApp::onClose( ofxLibwebsockets::Event& args ){
    cout<<"on close"<<endl;
    messages.push_back("Connection closed");
}

//--------------------------------------------------------------
void ofApp::onIdle( ofxLibwebsockets::Event& args ){
    cout<<"on idle"<<endl;
}
void ofApp::gotMessage(ofMessage msg){
    
}
//--------------------------------------------------------------
void ofApp::onMessage( ofxLibwebsockets::Event& args ){
//    cout<<"got message "<<args.message<<endl;
    
    // trace out string messages or JSON messages!
    if ( !args.json.isNull() ){
        messages.push_back("New message: " + args.json.toStyledString() + " from " + args.conn.getClientName() );
    } else {
        messages.push_back("New message: " + args.message + " from " + args.conn.getClientName() );
    }
    
    // echo server = send message right back!
    args.conn.send("blz "+ args.message );
    if(args.message!="" && args.message.find(";") != std::string::npos){
      
        vector<string> strings;
        istringstream f(args.message);
        string s;
        while (getline(f, s, ';')) {
            strings.push_back(s);
        }
        //ofVec3f orientation;
        //orientation.set(::atof(strings[1].c_str()),::atof(strings[2].c_str()),::atof(strings[3].c_str()));
        alfa = atof(strings[0].c_str());
        beta = atof(strings[1].c_str());
        gama = atof(strings[2].c_str());
       
        
    }
}

//--------------------------------------------------------------
void ofApp::onBroadcast( ofxLibwebsockets::Event& args ){
    cout<<"got broadcast "<<args.message<<endl;
}

//--------------------------------------------------------------



