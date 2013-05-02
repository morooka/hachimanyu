#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxSyphon.h"
#include "ofxKinect.h"

#define NUM_BILLBOARDS 1000

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void drawDual();
    void cfDraw();
    void vboDraw();
    
    bool            LearnBakground,bGrayImage,bfeedback,bImage;
    
    ofxCvColorImage     colorImg,colorImg2;
	ofxCvGrayscaleImage grayImage,grayImage2; // grayscale depth image
	ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
	ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
	ofxCvGrayscaleImage graydiff,grayBg,graydiff2,grayBg2;
    
	ofxCvContourFinder contourFinder,contourFinder2;
    ofVideoGrabber      vidGrabber,vidGrabber2;
    
    int                       threshold,threshold2;
    bool				bLearnBakground,bDrawDual,bVboDraw;
    
    std::vector<ofxCvBlob>::iterator blob;
    std::vector<ofxCvBlob>::iterator blob2;
    
    int centroidX1,centroidY1,centroidX2,centroidY2,centroidX3,centroidY3,centroidX4,centroidY4,
        centroidX12,centroidY12,centroidX22,centroidY22;
    
    unsigned char * 	videoInverted;
    ofTexture			videoTexture;
    int 				camWidth;
    int 				camHeight;
    
  ofxSyphonServer mainOutputSyphonServer;
    
    ofxKinect kinect;
    
    bool bThreshWithOpenCV;
	bool bDrawPointCloud;
    bool bReversePoints;
	
	int nearThreshold;
	int farThreshold;
    
    int angle;
    
    ofImage hachimanyuImage,videoImage;
    
    bool bcFdraw,bsoundOn;

    
ofTexture imageTex,videoTex;
ofxSyphonServer individualTextureSyphonServer;
        
    ofEasyCam cam;
    float zoom;
    float zoomTarget;
    ofVbo billboardVbo;
    ofVec3f billboardVerts[NUM_BILLBOARDS];
    ofFloatColor billboardColor[NUM_BILLBOARDS];
    ofVec3f billboardVels[NUM_BILLBOARDS];


/*
 individualTextureSyphonServer.setName("Texture Output");

int width = 360;
int height = 480;
tex.allocate(width, height, GL_RGBA); 

 mainOutputSyphonServer.publishScreen();
 individualTextureSyphonServer.publishTexture(&tex);
*/
    
};
