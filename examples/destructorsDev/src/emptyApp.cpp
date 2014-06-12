#include "emptyApp.h"


//--------------------------------------------------------------
void emptyApp::setup(){
  
  // Disable the of setupScreen because now each scene has a custom renderer.
  ofDisableSetupScreen();
  
  //Create a scene.
	//The scene is a scene graph that renders objects added to its root and their children and their children's children and so on.
	//When the render mode of the scene is set to RENDER_ALPHA_DEPTH_SORTED, it handles sorting of both transparent and opaque objects in the z-axis.
  scene = new ofxScene(ofGetWidth(), ofGetHeight());
	scene->setBackgroundColor(10, 10, 10);
  
  // Create object counter that shows the number of created objects for Destructor testing.
  font16 = new ofxSosoTrueTypeFont();
  font16->loadFont("Arial.ttf", 16, true,  true, false, true);
	font16->setKerningPair('T', 'y', -2);
  counterDisplay = new ofxTextObject(font16, "# of objects: 0");
  counterDisplay->setColor(0, 255, 255);
  counterDisplay->setPointSize(16);     //DEV: why doesnt work?
  counterDisplay->setLeading(19);
  counterDisplay->setColumnWidth(360);
  counterDisplay->setTrans(0, 0, 5.0);
  scene->getRoot()->addChild(counterDisplay);
  
  // For deletion timer
  deletionInterval = 60.0;    // in ms, dictates the time between each video deletion.
  videosCreated = false;
  imagesCreated = false;

  // Init counters for each destructor test.
  numObjectsToCreate = 1000;
  numVideosToCreate = 120;
  numCreatedTextObjects = 0;
  numCreatedGridSystems = 0;
  numCreatedCircleObjects = 0;
  numCreatedArcObjects = 0;
  numCreatedLineSegments = 0;
  numCreatedPolygonObjects = 0;
  numCreatedQuadStripObjects = 0;
  numCreatedLineStripObjects = 0;
  numCreatedDynPolygonObjects = 0;
  numCreatedVideoPlayerObjects = 0;
  numCreatedFboObjects = 0;
  numCreatedImageObjects = 0;
  numCreatedRectangleObjects = 0;
  numCreatedRoundedArcObjects = 0;
  numCreatedSceneObjects = 0;
  numCreatedRendererObjects = 0;
  numCreatedFonts = 0;
  numCreatedStateMachines = 0;
  numCreatedAnimations = 0;
  numCreatedScrollers = 0;
  numCreatedLetterTextObjects = 0;
  
  ofLogToFile("logs_destructorTests.txt", true);    // OPTION : log console msgs to file.
  ofLog()<<"----------------------------------------------------------------------------------------------------";
  ofLog()<<"DESTRUCTOR TEST - START @ "<< ofGetTimestampString("%H:%M:%S %A - %w %d/%B/%Y");
  ofLog()<<"----------------------------------------------------------------------------------------------------";
}

void emptyApp::update(){
  
  scene->update(ofGetElapsedTimef());
  
  // --------------------------------------------------------------------------------
  // TIMER for deleting videos/images objects over a long period of time.
  
  // VIDEO DELETION: We want to see if the memory will clear itself if we delete items over a longer period of time.
  if (videosCreated){
    if(videoPlayerCollection.size() > 0){
      
      timeElapsedSinceVideoCreation = ofxObject::curTime - timeStartedVideoCreation;
//      cout<<"-- timeElapsedSinceVideoCreation = "<< timeElapsedSinceVideoCreation <<endl;
//      cout<<"--- timePreviousForVideo = "<< timePreviousForVideo <<endl;
      
      if (timeElapsedSinceVideoCreation >= (timePreviousForVideo + deletionInterval)){
        ofLog()<<"----------------------------------------------------------------------------------------------------";
        
        // Delete a video.
        videoPlayerCollection.pop_back();

        // Log deletion progress.
        ofLog()<<"DELETING 1 VIDEO. Videos remaining: "<< videoPlayerCollection.size();
        ofLog()<<"Time passed = "<< timeElapsedSinceVideoCreation <<" seconds";
        //        cout<<"* * * * * * * * * * It's been "<< deletionInterval <<" secs!"<<endl;
        //        cout<<"* * * * * * * * * * videos left: "<< videoPlayerCollection.size() <<endl;

        // DEV_JC: Log memory usage.
        //COMMENT-OUT IF UNNECESSARY.
        if (KERN_SUCCESS != task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&t_info, &t_info_count)){ return -1; }
        ofLog()<<"MEMORY STATS:";
        ofLog()<<"t_info.resident_size = "<< t_info.resident_size;
        ofLog()<<"t_info.virtual_size = "<< t_info.virtual_size;

        // Update timer.
        timePreviousForVideo = timeElapsedSinceVideoCreation;
      }
    }
  }
  
  // IMAGE DELETION
  if (imagesCreated){
    if(imageCollection.size() > 0){
      
      timeElapsedSinceImageCreation = ofxObject::curTime - timeStartedImageCreation;
      //      cout<<"-- timeElapsedSinceImageCreation = "<< timeElapsedSinceImageCreation <<endl;
      //      cout<<"--- timePreviousForImage = "<< timePreviousForImage <<endl;
      
      if (timeElapsedSinceImageCreation >= (timePreviousForImage + deletionInterval)){
        ofLog()<<"----------------------------------------------------------------------------------------------------";
        
        // Delete a video.
        imageCollection.pop_back();
        
        // Log deletion progress.
        ofLog()<<"DELETING 1 IMAGE. Images remaining: "<< imageCollection.size();
        ofLog()<<"Time passed = "<< timeElapsedSinceImageCreation <<" seconds";
        //        cout<<"* * * * * * * * * * It's been "<< deletionInterval <<" secs!"<<endl;
        //        cout<<"* * * * * * * * * * images left: "<< imageCollection.size() <<endl;
        
        // DEV_JC: Log memory usage.
        //COMMENT-OUT IF UNNECESSARY.
        if (KERN_SUCCESS != task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&t_info, &t_info_count)){ return -1; }
        ofLog()<<"MEMORY STATS:";
        ofLog()<<"t_info.resident_size = "<< t_info.resident_size;
        ofLog()<<"t_info.virtual_size = "<< t_info.virtual_size;
        
        // Update timer.
        timePreviousForImage = timeElapsedSinceImageCreation;
      }
    }
    
  }
  
}

void emptyApp::draw(){
  
	//Call draw on scene, which initiates the drawing of the root object.
  scene->draw();
}

void emptyApp::keyPressed  (int key){
  
  if(key == 'a'){
    
    // Create the objects.
    for(int i=0; i < numObjectsToCreate; i++) {
      ofxTextObject* text = new ofxTextObject(font16, "Life is thickly sown with thorns, and I know no other remedy than to pass quickly through them. The longer we dwell on our misfortunes, the greater is their power to harm us. -Voltaire");
      delete text;
    }
    
    // Update counter to display # of created objs.
    numCreatedTextObjects += numObjectsToCreate;
    counterDisplay->setString("# of ofxTextObjects: "+ ofToString(numCreatedTextObjects));

  } else if(key == 'b'){
   
    for(int i=0; i < numObjectsToCreate; i++) {
      ofxGridSystem* grid = new ofxGridSystem(1080, 1920,
                    5, 14,
                    108, 28,     // left = menu + gutter; right = gutter
                    108, 108,    // top = bottom = left
                    2);
      delete grid;
    }
    numCreatedGridSystems += numObjectsToCreate;
    counterDisplay->setString("# of ofxGridSystems: "+ ofToString(numCreatedGridSystems));
  } else if(key == 'c'){
    
    for(int i=0; i < numObjectsToCreate; i++) {
      ofxCircleObject* circle = new ofxCircleObject(120, 100.0);
      delete circle;
    }
    numCreatedCircleObjects += numObjectsToCreate;
    counterDisplay->setString("# of ofxCircleObjects: "+ ofToString(numCreatedCircleObjects));
  } else if(key == 'd'){
    
    for(int i=0; i < numObjectsToCreate; i++) {
      ofxArcObject* arc = new ofxArcObject(100,80,90,270);
      delete arc;
    }
    numCreatedArcObjects += numObjectsToCreate;
    counterDisplay->setString("# of ofxArcObjects: "+ ofToString(numCreatedArcObjects));
  } else if(key == 'e'){
    
    for(int i=0; i < numObjectsToCreate; i++) {
      ofxLineSegmentObject* lineSegment = new ofxLineSegmentObject(1000);
      delete lineSegment;
    }
    numCreatedLineSegments += numObjectsToCreate;
    counterDisplay->setString("# of ofxLineSegmentObjects: "+ ofToString(numCreatedLineSegments));
  } else if(key == 'f'){
    // Testing ofxObject & ofxMessage destructors.
    ofxTextObject *testText = new ofxTextObject(font16, "Testing ofxObject and ofxMessage.");
    testText->setColor(0, 255, 255);
    testText->doMessage3f(OF_TRANSLATE, 0, 1, OF_LINEAR, 0, 100, 200);
    testText->doMessage3f(OF_ROTATE, 0, 1, OF_LINEAR, 0, 100, 200);
    testText->doMessage1f(OF_SCALE, 0, 1, OF_LINEAR, 200);
    testText->doMessage3f(OF_SCALE3, 0, 1, OF_LINEAR, 100, 200, 200);
    testText->doMessage3f(OF_SETCOLOR, 0, 1, OF_LINEAR, 150, 10, 200);
    testText->doMessage1f(OF_SETALPHA, 0, 1, OF_LINEAR, 0.5);
    scene->getRoot()->addChild(testText);
    testText->addChild( new ofxTextObject(font16, "") );                //test destruction of children.
    testText->addChild( new ofxTextObject(font16, "") );
    delete testText;
  } else if(key == 'g'){
    
    for(int i=0; i < numObjectsToCreate; i++) {
      ofxPolygonObject* polygon = new ofxPolygonObject(8);
      delete polygon;
    }
    numCreatedPolygonObjects += numObjectsToCreate;
    counterDisplay->setString("# of ofxPolygonObjects: "+ ofToString(numCreatedPolygonObjects));
  } else if(key == 'h'){
    
    for(int i=0; i < numObjectsToCreate; i++) {
      ofxQuadStripObject* quadStrip = new ofxQuadStripObject(4);
      delete quadStrip;
    }
    numCreatedQuadStripObjects += numObjectsToCreate;
    counterDisplay->setString("# of ofxQuadStripObjects: "+ ofToString(numCreatedQuadStripObjects));
  } else if(key == 'i'){
    
    for(int i=0; i < numObjectsToCreate; i++) {
      ofxLineStripObject* lineStrip = new ofxLineStripObject(4);
      delete lineStrip;
    }
    numCreatedLineStripObjects += numObjectsToCreate;
    counterDisplay->setString("# of ofxLinetripObjects: "+ ofToString(numCreatedLineStripObjects));
  } else if(key == 'j'){
    
    for(int i=0; i < numObjectsToCreate; i++) {
      ofxDynamicPolygonObject* dynPoly = new ofxDynamicPolygonObject(8);
      delete dynPoly;
    }
    numCreatedDynPolygonObjects += numObjectsToCreate;
    counterDisplay->setString("# of ofxDynamicPolygonObjects: "+ ofToString(numCreatedDynPolygonObjects));
  } else if(key == 'k'){
    timeStartedVideoCreation = ofGetElapsedTimef();
    timeElapsedSinceVideoCreation = 0.0;
    timePreviousForVideo = 0.0;
    videosCreated = true;       // Starts the timer to begin timed video deletion.
    string videoFile = "fingers.mov";     //RF1308-Superbowl_Closing-Ver02.mp4
    
    ofLog()<<"----------------------------------------------------------------------------------------------------";
    ofLog()<< numVideosToCreate <<" VIDEOS CREATED @ "<< timeStartedVideoCreation <<" seconds since program started.";
    ofLog()<<"Now starting deletion of 1 video every minute.";
    ofLog()<<"Video file is: "<< videoFile;
    // DEV_JC: Log memory usage.
    //COMMENT-OUT IF UNNECESSARY.
    if (KERN_SUCCESS != task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&t_info, &t_info_count)){ return -1; }
    ofLog()<<"MEMORY STATS:";
    ofLog()<<"t_info.resident_size = "<< t_info.resident_size;
    ofLog()<<"t_info.virtual_size = "<< t_info.virtual_size;
    ofLog()<<"----------------------------------------------------------------------------------------------------";
    
    // SOSO's video obj.
    for(int i=0; i < numVideosToCreate; i++) {
      ofxVideoPlayerObject* videoPlayer = new ofxVideoPlayerObject(videoFile);
      videoPlayer->start();
      videoPlayerCollection.push_back(videoPlayer);
    }

    // ObviousJim's video obj.
//    for(int i=0; i < numVideosToCreate; i++) {
//      ofQTKitPlayer* jimMovie = new ofQTKitPlayer();
//      jimMovie->loadMovie(videoFile);
//      jimMovie->play();
//      jimVideoPlayerCollection.push_back(jimMovie);
//    }
    
    numCreatedVideoPlayerObjects += numVideosToCreate;
    counterDisplay->setString("# of ofxVideoPlayerObjects CREATED: "+ ofToString(numCreatedVideoPlayerObjects));
  }
  
  // REMOVING for now since we're deleting with timer now.
  else if(key == 'K'){
    //Deletes all videos.
    
    //SOSO video obj.
    for(auto videoPlayer : videoPlayerCollection) {
      delete videoPlayer;
    }
    videoPlayerCollection.clear();
    numCreatedVideoPlayerObjects = videoPlayerCollection.size();
    counterDisplay->setString("# of ofxVideoPlayerObjects DELETED: "+ ofToString(numCreatedVideoPlayerObjects));
    
    // obviousJim video obj.
//    for(auto videoPlayer : jimVideoPlayerCollection) {
//      videoPlayer->close();
////      delete videoPlayer;
//    }
//    jimVideoPlayerCollection.clear();
//    numCreatedVideoPlayerObjects = jimVideoPlayerCollection.size();
//    counterDisplay->setString("# of ofxVideoPlayerObjects DELETED: "+ ofToString(numCreatedVideoPlayerObjects));
  }
  
   else if(key == 'l'){
    
    for(int i=0; i < numObjectsToCreate; i++) {
      ofxFboObject* fbo = new ofxFboObject(400, 400);
      delete fbo;
    }
    numCreatedFboObjects += numObjectsToCreate;
    counterDisplay->setString("# of ofxFboObjects: "+ ofToString(numCreatedFboObjects));
  } else if(key == 'm'){
    timeStartedImageCreation = ofGetElapsedTimef();
    timeElapsedSinceImageCreation = 0.0;
    timePreviousForImage = 0.0;
    imagesCreated = true;       // Starts the timer to begin timed image deletion.
    string imageFile = "plasticman.jpg";
    
    ofLog()<<"----------------------------------------------------------------------------------------------------";
    ofLog()<< numObjectsToCreate <<" IMAGES CREATED @ "<< timeStartedImageCreation <<" seconds since program started.";
    ofLog()<<"Now starting deletion of 1 image every minute.";
    ofLog()<<"Image file is: "<< imageFile;
    // DEV_JC: Log memory usage.
    //COMMENT-OUT IF UNNECESSARY.
    if (KERN_SUCCESS != task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&t_info, &t_info_count)){ return -1; }
    ofLog()<<"MEMORY STATS:";
    ofLog()<<"t_info.resident_size = "<< t_info.resident_size;
    ofLog()<<"t_info.virtual_size = "<< t_info.virtual_size;
    ofLog()<<"----------------------------------------------------------------------------------------------------";
    
    // Using ofxImageObject.
    for(int i=0; i < numObjectsToCreate; i++) {
      ofxImageObject* image = new ofxImageObject(imageFile);
      imageCollection.push_back(image);
//      delete image;     //REMOVE for now since we are deleting with timer now.
    }
    // Instead using ofImage to see if it also doesn't clear system memory. It doesn't either, just like ofxImageObject.
//    for(int i=0; i < numObjectsToCreate; i++) {
//      ofImage* image = new ofImage("plasticman.jpg");
//      delete image;
//    }
    
    numCreatedImageObjects += numObjectsToCreate;
    counterDisplay->setString("# of ofxImageObjects: "+ ofToString(numCreatedImageObjects));
  } else if(key == 'n'){
    
    for(int i=0; i < numObjectsToCreate; i++) {
      ofxRectangleObject* rect = new ofxRectangleObject(1000, 800);
      delete rect;
    }
    numCreatedRectangleObjects += numObjectsToCreate;
    counterDisplay->setString("# of ofxRectangleObjects: "+ ofToString(numCreatedRectangleObjects));
  } else if(key == 'o'){
    
    for(int i=0; i < numObjectsToCreate; i++) {
      ofxRoundedArcObject* rArc = new ofxRoundedArcObject(100,80,90,270);
      delete rArc;
    }
    numCreatedRoundedArcObjects += numObjectsToCreate;
    counterDisplay->setString("# of ofxRoundedArcObjects: "+ ofToString(numCreatedRoundedArcObjects));
  } else if(key == 'p'){
    
    for(int i=0; i < numObjectsToCreate; i++) {
      ofxScene* scene = new ofxScene(ofGetWidth(), ofGetHeight());
      delete scene;
    }
    numCreatedSceneObjects += numObjectsToCreate;
    counterDisplay->setString("# of ofxSceneObjects: "+ ofToString(numCreatedSceneObjects));
  } else if(key == 'q'){
    
    for(int i=0; i < numObjectsToCreate; i++) {
      ofxSosoRenderer* renderer = new ofxSosoRenderer(ofGetWidth(), ofGetHeight());
      delete renderer;
    }
    numCreatedRendererObjects += numObjectsToCreate;
    counterDisplay->setString("# of ofxSosoRenderer: "+ ofToString(numCreatedRendererObjects));
  } else if(key == 'r'){
    
    for(int i=0; i < numObjectsToCreate; i++) {
      ofxSosoTrueTypeFont* font = new ofxSosoTrueTypeFont();
      font->loadFont("Arial.ttf", 16, true,  true, false, true);
      delete font;
    }
    numCreatedFonts += numObjectsToCreate;
    counterDisplay->setString("# of ofxSosoTrueTypeFont: "+ ofToString(numCreatedFonts));
  } else if(key == 's'){
    
    for(int i=0; i < numObjectsToCreate; i++) {
      ofxStateMachine* state = new ofxStateMachine();
      state->setVerbose(true);
      state->enableTransitionBlocking(true);
      state->addTransition("MAP", "INTRO", 2.01);
      state->addTransition("INTRO", "MAP", 2.01);
      state->addTransition("INTRO", "LIST", 2.01);
      state->addTransition("LIST", "MAP", 2.01);
      
      delete state;
    }
    numCreatedStateMachines += numObjectsToCreate;
    counterDisplay->setString("# of ofxStateMachine: "+ ofToString(numCreatedStateMachines));
  } else if(key == 't'){
    
    for(int i=0; i < numObjectsToCreate; i++) {
      ofxAnimation* animation = new ofxAnimation();
      ofxCircleObject *circle = new ofxCircleObject(120, 100.0);
      scene->getRoot()->addChild(circle);
      animation->tween(circle, OF_SCALE, 0, 1, OF_EASE_OUT, OF_RELATIVE_VAL, 0.5);
      
      delete circle;
      delete animation;
    }
    numCreatedAnimations += numObjectsToCreate;
    counterDisplay->setString("# of ofxAnimation: "+ ofToString(numCreatedAnimations));
  } else if(key == 'u'){
    
    for(int i=0; i < numObjectsToCreate; i++) {
      ofxScroller* scroller = new ofxScroller(1000.0);
      scroller->addSnapPoint(500.0);
      delete scroller;
    }
    numCreatedScrollers += numObjectsToCreate;
    counterDisplay->setString("# of ofxScroller: "+ ofToString(numCreatedScrollers));
  } else if(key == 'v'){
    
    for(int i=0; i < numObjectsToCreate; i++) {
      ofxLetterTextObject* lto = new ofxLetterTextObject(font16, "testing");
      delete lto;
    }
    numCreatedLetterTextObjects += numObjectsToCreate;
    counterDisplay->setString("# of ofxLetterTextObjects: "+ ofToString(numCreatedLetterTextObjects));
  }
  
  
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


