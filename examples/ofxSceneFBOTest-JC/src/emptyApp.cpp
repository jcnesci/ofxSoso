#include "emptyApp.h"


//--------------------------------------------------------------
void emptyApp::setup(){
  
  //Replace the default ofGLRenderer with ofxSosoRenderer which has overriden setupScreen() and setupScreenPerspective().
	//This lets us set up the scene graph how we want to.
	//Warning: Up is up and down is down in this world.
  ofSetCurrentRenderer(ofPtr<ofBaseRenderer>(new ofxSosoRenderer(false)));
  
  // DEV - testing creating an FBO in a scene.
  scene = new tempScene(ofGetWidth(), ofGetHeight());
	scene->setBackgroundColor(10, 10, 10);
  
// ORIG ---
//  vidUniverse = new videoUniverse(1024, 768);
//  vidUniverse->setTrans(-1024/2, -768/2, 5);
  vidUniverse = new videoUniverse(100, 100);
  vidUniverse->setTrans(0, 0, 5);
  
  ofxRectangleObject *r = new ofxRectangleObject(40,40);
  r->setColor(255., 255., 0., 255.);
  r->isCentered = true;
  r->setTrans(0, 0, 10);
  vidUniverse->addToRoot(r);
//  scene->getRoot()->addChild(r);      //test

  scene->getRoot()->addChild(vidUniverse);

}

//--------------------------------------------------------------
void emptyApp::update(){
  
	//Update the scene with the current time. This call propagates the idle() call to all objects as well.
	//Note: If you are capturing frames to create a movie, simply replace ofGetElapsedTimef() with a float variable that you increment by a fixed time interval each frame.
  scene->update(ofGetElapsedTimef());
}

//--------------------------------------------------------------
void emptyApp::draw(){
  
	// Orig
  scene->draw();
  
  // New
  vidUniverse->drawFBOScene();

}

//--------------------------------------------------------------
void emptyApp::keyPressed  (int key){
  
}

//--------------------------------------------------------------
void emptyApp::keyReleased(int key){
  
}

//--------------------------------------------------------------
void emptyApp::mouseMoved(int x, int y ){
  
}

//--------------------------------------------------------------
void emptyApp::mouseDragged(int x, int y, int button){
  
  
}

//--------------------------------------------------------------
void emptyApp::mousePressed(int x, int y, int button){
  
}

//--------------------------------------------------------------
void emptyApp::mouseReleased(int x, int y, int button){
  
  
}


//--------------------------------------------------------------
void emptyApp::windowResized(int w, int h){
  
}

//--------------------------------------------------------------
void emptyApp::gotMessage(ofMessage msg){
  
}

//--------------------------------------------------------------
void emptyApp::dragEvent(ofDragInfo dragInfo){ 
  
}

