#pragma once

#include "ofMain.h"
#include "ofxScene.h"
#include "ofxSosoRenderer.h"
#include "ofxTextObject.h"
#include "ofxGridSystem.h"
#include "ofxCircleObject.h"
#include "ofxArcObject.h"
#include "ofxLineSegmentObject.h"
#include "ofxPolygonObject.h"
#include "ofxQuadStripObject.h"
#include "ofxLineStripObject.h"
#include "ofxDynamicPolygonObject.h"
#include "ofxVideoPlayerObject.h"
#include "ofxFboObject.h"
#include "ofxImageObject.h"
#include "ofxRectangleObject.h"
#include "ofxRoundedArcObject.h"
#include "ofxStateMachine.h"
#include "ofxAnimation.h"
#include "ofxScroller.h"
#include "ofQTKitPlayer.h"
#include "ofxLetterTextObject.h"

//DEV_JC: memory usage testing: http://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process
#include<mach/mach.h>

class emptyApp : public ofBaseApp{
  
public:
  
  void setup();
  void update();
  void draw();
  
  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y );
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);
  
  
public:

  //DEV_JC: memory usage testing
  struct task_basic_info t_info;
  mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;
  
  ofxScene                  *scene;
  
  ofxSosoTrueTypeFont				*font16;
  ofxTextObject             *counterDisplay;
  vector<ofxVideoPlayerObject *>  videoPlayerCollection;
  vector<ofxImageObject *>  imageCollection;
  
  // For deletion timer.
  float                     deletionInterval;
  float                     timeElapsedSinceVideoCreation;
  float                     timeStartedVideoCreation;
  float                     timePreviousForVideo;
  bool                      videosCreated;
  float                     timeElapsedSinceImageCreation;
  float                     timeStartedImageCreation;
  float                     timePreviousForImage;
  bool                      imagesCreated;
  
  int                       numObjectsToCreate;
  int                       numVideosToCreate;

  // counters for each type of object we wish to test destructor for.
  int                       numCreatedTextObjects;
  int                       numCreatedGridSystems;
  int                       numCreatedCircleObjects;
  int                       numCreatedArcObjects;
  int                       numCreatedLineSegments;
  int                       numCreatedPolygonObjects;
  int                       numCreatedQuadStripObjects;
  int                       numCreatedLineStripObjects;
  int                       numCreatedDynPolygonObjects;
  int                       numCreatedVideoPlayerObjects;
  int                       numCreatedFboObjects;
  int                       numCreatedImageObjects;
  int                       numCreatedRectangleObjects;
  int                       numCreatedRoundedArcObjects;
  int                       numCreatedSceneObjects;
  int                       numCreatedRendererObjects;
  int                       numCreatedFonts;
  int                       numCreatedStateMachines;
  int                       numCreatedAnimations;
  int                       numCreatedScrollers;
  int                       numCreatedLetterTextObjects;
  
  // Testing obviousJim's video obj.
  ofQTKitPlayer jimMovie;
  vector<ofQTKitPlayer *>  jimVideoPlayerCollection;
};

