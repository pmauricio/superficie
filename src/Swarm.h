#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOscParameterSync.h"

#define SPRING_CONSTANT 0.1f
#define MAX_VELOCITY 30.0f

// This 'swarm' object demonstrates a simple particle system
//  with 'simple harmonic motion'
class swarm : public ofNode {
	struct particle {
		ofVec3f position;
		ofVec3f velocity;
        ofColor color;
      
	};

	public:
		swarm();
		void init(int nParticles, float positionDispersion, float velocityDispersion);
		void customDraw();
		ofLight light;

        void drawGUI();
    ofxPanel gui;
    	vector<particle>particles;
    
    ofParameter<int> number;
    ofParameter<bool> check;
        ofParameter<bool> randomColor;
    ofParameter<float> xSlider;
    ofParameter<float> ySlider;
    ofParameterGroup parameters;
    ofParameter<ofColor> color;
    ofParameter<int> meshMode;
    ofxOscParameterSync sync;
    ofImage image;
	protected:
		// we call this update function ourselves
		//  at the beginning of customDraw
		void update();

		// objects
	
    ofPrimitiveMode meshModes[7]; 
};