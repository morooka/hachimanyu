#include "testApp.h"
#include "ofxUGen.h"

int synthX1 = 0;
int synthY1 = 0;
int synthX2 = 0;
int synthY2 = 0;
int synthX3 = 0;
int synthY3 = 0;
int synthX4 = 0;
int synthY4 = 0;
int synthX5 = 0;
int synthY5 = 0;

float amp1 = 0;
float amp2 = 0;
float amp3 = 0;

class MySynth : public ofxUGen::SynthDef
{
public:
	
	ofVec2f pos;
	
	UGen envgen;
	UGen amp;
    
	MySynth()
	{
		pos.x = synthX1;
		pos.y = synthY1;
		
		float freq = ofMap(pos.x, 0, ofGetHeight(), 0, 500);
		float pan = ofMap(pos.y, 0, ofGetWidth(), -1, 1);
        
		Env env = Env::perc(0.3, 0.3, 0.1, EnvCurve::Sine);
		envgen = EnvGen::AR(env);
		envgen.addDoneActionReceiver(this);
		
		amp = SinOsc::AR(ofRandom(4.0), 0, 0.5, 0.5) * envgen;
        amp1 = amp.getValue();
        Out(
            Pan2::AR(SinOsc::AR(freq) * amp, pan)
            );
    }
	
	void draw()
	{
		ofNoFill();
        ofSetColor(255,130,110,100);
        ofCircle(pos.x, pos.y, 10+ofRandom(0,80));
    }
	
	bool isAlive()
	{
		return !Out().isNull();
	}
};

class MySynth2 : public ofxUGen::SynthDef
{
public:
	
	ofVec2f pos;
	
	UGen envgen;
	UGen amp;
       
	MySynth2()
	{
		pos.x = synthX2;
		pos.y = synthY2;
		
		float freq = ofMap(pos.x, 0, ofGetHeight(), 0, 1000);
		float pan = ofMap(pos.y, 0, ofGetWidth(), -1, 1);
        
		Env env = Env::perc(0.3, 0.6, 0.1, EnvCurve::Linear);
		envgen = EnvGen::AR(env);
		envgen.addDoneActionReceiver(this);
		
		amp = SinOsc::AR(ofRandom(10.0), 0, 0.5, 0.5) * envgen;
        amp2 = amp.getValue();
		
		Out(
			Pan2::AR(SinOsc::AR(freq) * amp, pan)
            );
	}
	
	void draw()
	{
        ofNoFill();
        ofSetColor(100,100,255,100);
        ofCircle(pos.x, pos.y,10+ofRandom(0,80));
	}
	
	bool isAlive()
	{
		return !Out().isNull();
	}
};

class MySynth3 : public ofxUGen::SynthDef
{
public:
	
	ofVec2f pos;
	
	UGen envgen;
	UGen amp;
    
	MySynth3()
	{
		pos.x = synthX3;
		pos.y = synthY3;
		
		float freq = ofMap(pos.x, 0, ofGetHeight(), 0, 10000);
		float pan = ofMap(pos.y, 0, ofGetWidth(), -1, 1);
        
		Env env = Env::perc(0.8, 1.0, 0.2, EnvCurve::Welch);
		envgen = EnvGen::AR(env);
		envgen.addDoneActionReceiver(this);
		
		amp = SinOsc::AR(ofRandom(5.0), 0, 0.1, 0.1) * envgen;
        amp3 = amp.getValue();
		
		Out(
			Pan2::AR(SinOsc::AR(freq) * amp, pan)
            );
	}
	
	void draw()
	{
        ofNoFill();
        ofSetColor(50,255,87,150);
        ofCircle(pos.x, pos.y, 30+ofRandom(0,20));
    }
	
	bool isAlive()
	{
		return !Out().isNull();
	}
};

class MySynth4 : public ofxUGen::SynthDef
{
public:
	
	ofVec2f pos;
	
	UGen envgen;
	UGen amp;
    
	MySynth4()
	{
		pos.x = synthX5;
		pos.y = synthY5;
		
		float freq = ofMap(pos.x, 0, ofGetHeight(), 0, 8000);
		float pan = ofMap(pos.y, 0, ofGetWidth(), -1, 1);
        
		Env env = Env::perc(0.8, 1.0, 0.2, EnvCurve::Welch);
		envgen = EnvGen::AR(env);
		envgen.addDoneActionReceiver(this);
		
		amp = SinOsc::AR(ofRandom(5.0), 0, 0.1, 0.1) * envgen;
        
        amp3 = amp.getValue();
		
		Out(
			Pan2::AR(SinOsc::AR(freq) * amp, pan)
            );
	}
	
	void draw()
	{
        ofNoFill();
        ofSetColor(210,150,220,150);
        ofCircle(pos.x, pos.y, 30+ofRandom(0,20));
    }
	
	bool isAlive()
	{
		return !Out().isNull();
	}
};


vector<MySynth *> synths;
vector<MySynth2*>synths2;
vector<MySynth3*>synths3;
vector<MySynth4*>synths4;

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofSetCircleResolution(60);
   
    vidGrabber.listDevices();
    vidGrabber.setDeviceID(1);
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(640, 480);
    
    colorImg.allocate(kinect.width, kinect.height);
    grayImage.allocate(kinect.width, kinect.height);
    grayBg.allocate(kinect.width, kinect.height);
    graydiff.allocate(kinect.width, kinect.height);
    
    // enable depth->video image calibration
    kinect.setRegistration(true);
    kinect.init(true,false,true);
    kinect.open();
       
    threshold = 255;
    threshold2 = 255;
    bLearnBakground = true;
       
    centroidX1 = 0;
    centroidY1 = 0;
    centroidX2 = 0;
    centroidY2 = 0;
    centroidX3 = 0;
    centroidY3 = 0;
    centroidX4 = 0;
    centroidY4 = 0;
       
    colorImg2.allocate(kinect.width, kinect.height);
    grayImage2.allocate(kinect.width, kinect.height);
    grayBg2.allocate(kinect.width, kinect.height);
    graydiff2.allocate(kinect.width, kinect.height);
    
    grayThreshNear.allocate(kinect.width, kinect.height);
    grayThreshFar.allocate(kinect.width, kinect.height);

    ofxUGen::instance().setup();
    
    mainOutputSyphonServer.setName("Main Output");
    
    nearThreshold = 227;
    farThreshold =197;
    bThreshWithOpenCV = true;
   
    // zero the tilt on startup
	angle = 1;
	kinect.setCameraTiltAngle(angle);
    
    hachimanyuImage.loadImage("hachimanyu.jpg");
    
    bGrayImage = false;
    bDrawDual = false;
    bcFdraw = false;
    bVboDraw = false;
    bsoundOn = false;
    
    zoomTarget = zoom = 20;
    cam.setDistance(zoom);
     for (int i=0; i<NUM_BILLBOARDS; i++) {
         billboardVels[i].set(ofRandomf(), -1.0, ofRandomf());
         billboardVerts[i].set(ofRandom(-500, 500), ofRandom(-500, 500), ofRandom(-500, 500));
         billboardColor[i].set(1, 1, 1, 0.7);
     }
    billboardVbo.setVertexData(billboardVerts, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
    billboardVbo.setColorData(billboardColor, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
   
    ofDisableArbTex();
}

//--------------------------------------------------------------
void testApp::update(){
        
    kinect.update();
    vidGrabber.update();
    
    if(kinect.isFrameNew()) {
        
        grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
        colorImg.setFromPixels(vidGrabber.getPixels(),kinect.width,kinect.height);
        
        //contourFinder2!!!!!!
        grayImage2=colorImg;
        if(bLearnBakground==true){
            grayBg2=grayImage2;
            bLearnBakground=false;
        }
        graydiff2.absDiff(grayBg2,grayImage2);
        graydiff2.threshold(threshold);
        contourFinder2.findContours(graydiff2, 10, (kinect.width*kinect.height)/3, 5, false);
		
		if(bThreshWithOpenCV) {
			grayThreshNear = grayImage;
			grayThreshFar = grayImage;
			grayThreshNear.threshold(nearThreshold, true);
			grayThreshFar.threshold(farThreshold);
			cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
            
		} else {
			// or we do it ourselves - show people how they can work with the pixels
			unsigned char * pix = grayImage.getPixels();
			int numPixels = grayImage.getWidth() * grayImage.getHeight();
			for(int i = 0; i < numPixels; i++) {
				if(pix[i] < nearThreshold && pix[i] > farThreshold) {
					pix[i] = 255;
				} else {
					pix[i] = 0;
				}
			}
		}
        // update the cv images
		grayImage.flagImageChanged();
		
		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
        
        contourFinder.findContours(grayImage, 2, (kinect.width*kinect.height)/3, 5, false);
    }
    
    for (blob=contourFinder.blobs.begin(); blob!= contourFinder.blobs.end(); blob++) {
        centroidX1 = contourFinder.blobs[0].centroid.x;
        centroidY1 = contourFinder.blobs[0].centroid.y;
        centroidX2 = contourFinder.blobs[1].centroid.x;
        centroidY2 = contourFinder.blobs[1].centroid.y;
        centroidX3 = contourFinder.blobs[2].centroid.x;
        centroidY3 = contourFinder.blobs[2].centroid.y;
        centroidX4 = contourFinder.blobs[3].centroid.x;
        centroidY4 = contourFinder.blobs[3].centroid.y;
        synthX1 = centroidX1;
        synthY1 = centroidY1+480;
        synthX2 = centroidX2;
        synthY2 = centroidY2+480;
        synthX4 = centroidX3;
        synthY4 = centroidY3+480;
    }
    
    for (blob2=contourFinder2.blobs.begin(); blob2!= contourFinder2.blobs.end(); blob2++) {
        centroidX12 = contourFinder2.blobs[0].centroid.x;
        centroidY12 = contourFinder2.blobs[0].centroid.y;
        synthX5 = centroidX22 = contourFinder2.blobs[1].centroid.x;
        synthY5 = centroidY22 = contourFinder2.blobs[1].centroid.y;
        synthX3 = centroidX12;
        synthY3 = centroidY12;
    }
    
    ofDisableArbTex();
    if (vidGrabber.isFrameNew()) {
        videoImage.setFromPixels(vidGrabber.getPixels(),640,480, OF_IMAGE_COLOR);
    }
    
    float t   = (ofGetElapsedTimef()) * 0.9f;
    float div = 250.0;
  
    for (int i=0; i<contourFinder2.blobs.size(); i++) {
        for (int j = 0; j < contourFinder2.blobs[i].nPts; j++) {
        ofVec3f vec(contourFinder2.blobs[i].pts[j].x,contourFinder2.blobs[i].pts[j].y,ofRandom(-200,200));
            vec *= 1.0f;
            billboardVels[i] += vec;
            billboardVerts[i] += billboardVels[i];
            billboardVels[i]  *= 0.94f;
        }
    }

    billboardVbo.setVertexData(billboardVerts, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
    billboardVbo.setColorData(billboardColor, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
    zoom += (zoomTarget - zoom) * 0.03;
    
    if (bVboDraw == true) {
        float movementSpeed = 0.9f;
        float t = ofGetElapsedTimef()*movementSpeed ;
        float cloudSize = ofGetWidth() / 2;
        ofVec3f pos(
                    ofSignedNoise(t, 0, 0),
                    ofSignedNoise(0, t, 0),
                    ofSignedNoise(0, 0, t));
        t = t*1000;
        pos *= cloudSize;
        ofTranslate(pos*t);
        ofRotateX(pos.x*t*1000);
        ofRotateY(pos.y*t*1000);
        ofRotateZ(pos.z*t*1000);
    }
    cam.setDistance(zoom);
}

//--------------------------------------------------------------
void testApp::draw(){
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    ofSetLineWidth(1);
    ofTranslate(0, 640);
    ofRotateZ(-90);
    ofEnableAlphaBlending();
    
    ofBackground(0);
    ofSetColor(255);
  
    if (bGrayImage == false) {
        hachimanyuImage.draw(synthX1-100,synthY1-150,202,300);
        hachimanyuImage.draw(synthX2-100,synthY2-150,202,300);
        if (contourFinder.nBlobs > 2) {
            hachimanyuImage.draw(synthX4-100,synthY4-150,202,300);
        }
        glBlendFunc(GL_DST_COLOR, GL_ZERO);
        grayImage.draw(0,480,640,480);
    }
    
    if (bsoundOn == true) {
        if (contourFinder.nBlobs > 0) {
            vector<MySynth*>::iterator it = synths.begin();
            while (it != synths.end())
            {
                MySynth *s = *it;
                s->draw();
                if (!s->isAlive())
                {
                    it = synths.erase(it);
                    delete s;
                }
                else
                    it++;
            }
            for (int i = 0; i < synths.size()/100; i++)
                synths[i]->release();
            
            synths.push_back(new MySynth);
            synths.back()->play();
        }
    }
    if (contourFinder.nBlobs > 1) {
        ofSetColor(100, 200, 200,200);
        ofSetLineWidth(2);
        ofLine(synthX1, synthY1,synthX2,synthY2);
        
        if (bsoundOn  == true) {
        vector<MySynth2*>::iterator it2 = synths2.begin();
        while (it2 != synths2.end())
        {
            MySynth2 *s = *it2;
            s->draw();
            
            if (!s->isAlive())
            {
                it2 = synths2.erase(it2);
                delete s;
            }
            else
                it2++;
        }
            for (int i = 0; i < synths2.size()/100; i++)
                synths2[i]->release();
            
            synths2.push_back(new MySynth2);
            synths2.back()->play();
        }
    }
    
    if (bsoundOn == true) {
        if (contourFinder2.nBlobs > 0) {
            vector<MySynth3*>::iterator it3 = synths3.begin();
            while (it3 != synths3.end())
            {
                MySynth3 *s = *it3;
                s->draw();
                
                if (!s->isAlive())
                {
                    it3 = synths3.erase(it3);
                    delete s;
                }
                else
                    it3++;
            }
            for (int i = 0; i < synths3.size()/100; i++)
                synths3[i]->release();
            synths3.push_back(new MySynth3);
            synths3.back()->play();
        }
    
    if (contourFinder2.nBlobs > 1) {
        vector<MySynth4*>::iterator it3 = synths4.begin();
        while (it3 != synths4.end())
        {
            MySynth4 *s = *it3;
            s->draw();
            
            if (!s->isAlive())
            {
                it3 = synths4.erase(it3);
                delete s;
            }
            else
                it3++;
        }
        for (int i = 0; i < synths4.size()/100; i++)
            synths4[i]->release();
        
        synths4.push_back(new MySynth4);
        synths4.back()->play();
    }
    } // bsoundOn
    
    if (bDrawDual == true) {
        drawDual();
    }
    if (bcFdraw == true) {
        cfDraw();
    }
    if (bVboDraw == true) {
        vboDraw();
    }
    
    ofEnableArbTex();
    mainOutputSyphonServer.publishScreen();
       
    
    ofSetHexColor(0xffffff);
	stringstream reportStr;
	reportStr 
    << "threshold " << threshold << endl
     << "nearThreshold:" << nearThreshold << endl
    <<"farThreshold:"<< farThreshold << endl
    << "cF1 " << contourFinder.nBlobs << endl
    << "cF2 " << contourFinder2.nBlobs << endl
    <<"fps: " << ofGetFrameRate();
	ofDrawBitmapString(reportStr.str(), 40, 20);
}

//--------------------------------------------------------------
void testApp::drawDual(){
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255,100);
    vidGrabber.draw(0,0,640,480);
    
    if(contourFinder2.nBlobs == 1){
        glEnable(GL_BLEND);
        ofSetColor(255*ofRandom(1.0),255*ofRandom(1.0),255*ofRandom(1.0),100);
        ofFill();
        ofTriangle(synthX1, synthY1, synthX2, synthY2, centroidX12, centroidY12);
        ofSetColor(255, 100, 100);
        ofLine(centroidX12, centroidY12, synthX1, synthY1);
        ofLine(centroidX12, centroidY12, synthX2, synthY2);
    }
    if(contourFinder2.nBlobs > 1){
        glEnable(GL_BLEND);
        ofSetColor(255*ofRandom(1.0),255*ofRandom(1.0),255*ofRandom(1.0),100);
        ofFill();
        glBegin(GL_POLYGON);
        glVertex2i(centroidX22, centroidY22);
        glVertex2i(centroidX12, centroidY12);
        glVertex2i(synthX1, synthY1);
        glVertex2i(synthX2, synthY2);
        glEnd();
    }
}
//--------------------------------------------------------------
void testApp::cfDraw(){
    contourFinder2.draw(0,0,640,480);
}
//--------------------------------------------------------------
void testApp::vboDraw(){
    cam.begin();
    glDepthMask(GL_FALSE);
    ofEnablePointSprites();
    videoImage.getTextureReference().bind();
    static GLfloat distance[] = { 0.0, 0.0, 1.0 };
    glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, distance);
    glPointSize(10000);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    billboardVbo.draw(GL_POINTS, ofRandom(-20,100), NUM_BILLBOARDS);
    videoImage.getTextureReference().unbind();
    ofDisablePointSprites();
    glDepthMask(GL_TRUE);
    cam.end();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    switch (key){
		case ' ':
			bLearnBakground = true;
			break;
            
		case '+':
        case ';':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
        case 't':
			bThreshWithOpenCV = !bThreshWithOpenCV;
			break;
            
        case '>':
		case '.':
			farThreshold ++;
			if (farThreshold > 255) farThreshold = 255;
			break;
            
		case '<':
		case ',':
			farThreshold --;
			if (farThreshold < 0) farThreshold = 0;
			break;
        case '/':
			nearThreshold ++;
			if (nearThreshold > 255) nearThreshold = 255;
			break;
        case '_':
			nearThreshold --;
			if (nearThreshold < 0) nearThreshold = 0;
			break;
        case 'g':
            bGrayImage = !bGrayImage;
            break;
        case 'd':
            bDrawDual = !bDrawDual;
            break;
        case OF_KEY_UP:
			angle++;
			if(angle>30) angle=30;
			kinect.setCameraTiltAngle(angle);
			break;
		case OF_KEY_DOWN:
			angle--;
			if(angle<-30) angle=-30;
			kinect.setCameraTiltAngle(angle);
			break;
        case 'c':
            bcFdraw = !bcFdraw;
            break;
        case 'v':
            bVboDraw = !bVboDraw;
            break;
        case 's':
            bsoundOn = !bsoundOn;
            break;
	}
    if (key == OF_KEY_RIGHT)
        zoomTarget -= 10;
    if (key == OF_KEY_LEFT)
        zoomTarget += 10;
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}