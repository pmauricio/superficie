#include "Swarm.h"

// This 'swarm' object demonstrates a simple particle system
//  with 'simple harmonic motion'

swarm::swarm(){
	light.setAmbientColor(ofColor(0, 0, 0));
}

float _positionDispersion;

void swarm::init(int nParticles, float positionDispersion, float velocityDispersion){

    
    image.load("/users/mauro/Documents/leandro.jpg");
    _positionDispersion = (positionDispersion);
    
    parameters.add(color.set("color",ofColor(127,127,127,127),ofColor(0,0),ofColor(255)));
    parameters.add(randomColor);
    
    parameters.add(xSlider.set("x ",50,1,200));
    parameters.add(ySlider.set("y ",10,1,200));
    
	// Check if we've already initialised
	if(particles.size() != 0){
		// clear out old data
		ofLogWarning("swarm") <<  "Swarm: Already initialised";

		particles.clear();
	}

	ofSeedRandom();
	//
	ofVec3f position, velocity;
    
    ofPixels & pixels = image.getPixels();
    
	for(int i = 0; i < nParticles; i++){
//		position.x = (ofRandom(1.0f) - 0.5f)  * positionDispersion;
//		position.y = (ofRandom(1.0f) - 0.5f)  * positionDispersion;
//		position.z = (ofRandom(1.0f) - 0.5f)  * positionDispersion;
 
        position.x = (((i) % 100)* positionDispersion)+ofRandom(-positionDispersion,positionDispersion) ;
        position.z = (((i)/100 )* positionDispersion)+ofRandom(-positionDispersion,positionDispersion) ;
//        position.y = (ofNoise(position.x * 0.001, position.y * 0.001 ) * positionDispersion)  ;
                position.y = (0)  ;

        
		velocity.x = (ofRandom(1.0f) - 0.5f)  * velocityDispersion;
		velocity.y = (ofRandom(1.0f) - 0.5f)  * velocityDispersion;
		velocity.z = (ofRandom(1.0f) - 0.5f)  * velocityDispersion;

        ofColor color;
		color.r = ofRandom(255.0f);
		color.g = ofRandom(255.0f);
		color.b = 150.0f;
		color.a = 255.0f;

		particle newParticle;
		newParticle.position = position;
		newParticle.velocity = velocity;
		
        
        int yImg = (i%100)*image.getWidth()/100;
        int xImg = i/100*image.getHeight()/100;
        int bytesPerPixel = 3;
       
        
    
//        mesh.getColors().resize(pixels.getWidth()*pixels.getHeight());
//        for(auto line: pixels.getLines()){
//            for(auto pixel: line.getPixels()){
//                mesh.getColors()[i].set(pixel[0],pixel[1],pixel[2])
//                i++;
//            }
//        }
        int imgIndex = xImg+yImg*image.getWidth();
        newParticle.color.set(pixels.getLine(xImg).getPixel(yImg)[0],
                              pixels.getLine(xImg).getPixel(yImg)[1]
                              ,pixels.getLine(xImg).getPixel(yImg)[2]);
        
        
        
//        newParticle.color.r = image.getPixels()[xImg+yImg*image.getWidth()];
//        newParticle.color.g = image.getPixels()[xImg+yImg*image.getWidth()+image.getWidth()*image.getHeight()];
//        newParticle.color.b = image.getPixels()[xImg+yImg*image.getWidth()+image.getWidth()*image.getHeight()*2];

//        newParticle.color = color;
        
		// add our new particle to the vector
		particles.push_back(newParticle);
	}

    gui.setup(); // most of the time you don't need a name
    
    //    gui.add(filled.setup("fill", true));
    

    
    //    parameters.add(xSlider.set(" x " ,50,1,100));
    //
    //
    
    gui.setup(parameters);
    sync.setup((ofParameterGroup&)gui.getParameter(),6666,"localhost",6667);
    ofSetVerticalSync(true);
    //    bHide = false;
    
}

void swarm::customDraw(){

    
    // We run the update ourselves manually. ofNode does
	//  not do this for us.
	update();

    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    int height=100;
    int width=100;
//   
//        for (int x = 0; x<particles.size(); x++){
//            mesh.addVertex(particles[x].position); // make a new vertex
//            mesh.addColor(particles[x].color);  // add a color at that vertex
//        }
    mesh.sphere(100);
    for (int y = 0; y < height; y++){
        for (int x = 0; x<width; x++){
//            cout << y*1000+x << " y "<< y <<" x "<<x<< " size " << particles.size();
//            cout <<"\n";
//
//            cout <<  particles[y*100+x].position;
//            cout <<"\n";
            mesh.addVertex(particles[y*100+x].position); // make a new vertex
            if(randomColor){
                particles[y*100+x].color.a = color.get().a;
                mesh.addColor(particles[y*100+x].color);
            }else{
            // add a color at that vertex
                mesh.addColor(color.get());
            }
        }
    }
    // now it's important to make sure that each vertex is correctly connected with the
    // other vertices around it. This is done using indices, which you can set up like so:
    for (int y = 0; y<height-1; y++){
        for (int x=0; x<width-1; x++){
            mesh.addIndex(x+y*width);               // 0
            mesh.addIndex((x+1)+y*width);           // 1
            mesh.addIndex(x+(y+1)*width);           // 10
            
            mesh.addIndex((x+1)+y*width);           // 1
            mesh.addIndex((x+1)+(y+1)*width);       // 11
            mesh.addIndex(x+(y+1)*width);           // 10
        }
    }

    
    for (int w = 0 ;w++; w<3){
//        mesh.draw();
//    ofTranslate(0, 10);
    }
    mesh.draw();
    mesh.drawWireframe();

    
    
    //
//    mesh.drawWireframe();
    //--
	// Draw particles

	// We use the position of the first
	//  particle as the position of the
	//  light.
	ofPushStyle();
	light.enable();
	light.setPosition(0,0,0);
 
//	for(unsigned int i = 0; i < particles.size(); i++){
//		ofPushStyle();
//		ofSetColor(particles[i].color);
//
////		ofDrawSphere(particles[i].position, 5.0);
////        ofDrawIcoSphere(particles[i].position,10);
//		ofDrawBox(particles[i].position,10);
//        ofPopStyle();
//	}

	light.disable();
	ofDisableLighting();

	//
	//--
//    image.draw(0,1000, 1000);

	// Render light as white sphere
	ofSetColor(255, 255, 255);
	ofDrawSphere(light.getPosition(), 1.0);
	ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL);
	ofDrawBitmapString(" light", light.getPosition());
	ofPopStyle();


    
}

void swarm::drawGUI(){
    gui.draw();
    
}


float t = 0;
void swarm::update(){
//    sync.update();
 	// Calculate time past per frame
	float dt = ofGetLastFrameTime();

    int width = 100;
    int height = 100;
    for(int y = 0 ; y<height ; y++){
        for(int x = 0 ; x<width ; x++){
       
            t = (t + dt/10000);
particles[x+y*width].position.y = ( ofNoise(((float)x)/xSlider+t,((float)y)/(10+ySlider))* _positionDispersion*7);
    //        particles[x+y*width].color.a= particles[x+y*width].position.y ;
        }
    
	// Update positions, velocities
//	for(unsigned int i = 0; i < particles.size(); i++){
//
//		// -----------
//		//
//		//	MOTION MATHS
//		//
//		//		'Simple Harmonic Motion' + a little extra
//		// ----
//		//
//
//		// [1] apply velocity to postion
//		//  (i.e. integrate velocity)
//		//
//		//  v = dx / dt (*)
//		//  x = x + dx [every frame]
//		//
//		// therefore
//		//  x = x + v * dt (*)
//		//
//
//		// (velcotity is taken from previous frame)
////		particles[i].position += particles[i].velocity * dt;
//        t = (t + dt/100000);
////        particles[i].position.y = ofNoise(i+t,i+t)* _positionDispersion*7;
//        
//		// [2] apply spring force to velocity
//		//  (i.e. integrate acceleration)
//		//
//		//  a = -k * x (this is the shm restoring force, aka spring force)
//		//  a = dv / dt
//		//
//		// therefore from (*)s above
//		//  (v = v + dv)
//		//
//		//  v = v + (dt * a)
//		//  v = v + (dt * -k * x)
//		//
////		particles[i].velocity += -SPRING_CONSTANT * particles[i].position * dt;
////
////
////		// [3] to get a super simple kind of 'flocking' behaviour
////		//  we add a second spring force to velocity relative
////		//  to the position of the light
////		// NOTICE: THIS ISN'T REAL FLOCKING!
//////		particles[i].velocity += -SPRING_CONSTANT * (particles[i].position - light.getPosition()) * dt;
////
////
////		// [4] Force a maximum velocity
////		if(particles[i].velocity.length() > MAX_VELOCITY){
////			particles[i].velocity /= particles[i].velocity.length() * MAX_VELOCITY;
////		}
//
//		//
//		// -----------
//
	}
}
