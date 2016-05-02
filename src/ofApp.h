#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "demoParticle.h"

#define _USE_LIVE_VIDEO		// uncomment this to use a live camera

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void resetParticles();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofTrueTypeFont font;
        ofTrueTypeFont font2;
    
        ofSoundPlayer music1;
        ofSoundPlayer music2;
        ofSoundPlayer music3;
        ofSoundPlayer music4;
        ofSoundPlayer music5;
        ofSoundPlayer music6;
        ofSoundPlayer music7;
        ofSoundPlayer music8;
        ofSoundPlayer music9;
        ofSoundPlayer music10;
        ofSoundPlayer music11;
        ofSoundPlayer music12;
        ofSoundPlayer music13;
        ofSoundPlayer music14;
        ofSoundPlayer music15;
    
        ofPolyline line;
    
        bool bSendSerialMessage;
        // a flag for sending serial
        char bytesRead[3];
        // data from serial, we will be trying to read 3
        char bytesReadString[4];
        // a string needs a null terminator, so we need 3 + 1 bytes
        int nBytesRead;
        // how much did we read?
        int nTimesRead;
        // how many times did we read?
        float readTime;
        // when did we last read?
        
        ofSerial serial;
    
        #ifdef _USE_LIVE_VIDEO
            ofVideoGrabber vidGrabber;
        #else
            ofVideoPlayer vidPlayer;
        #endif
            
        ofxCvColorImage	colorImg;
        ofxCvGrayscaleImage grayImage;
        ofxCvGrayscaleImage grayBg;
        ofxCvGrayscaleImage grayDiff;
        ofxCvContourFinder contourFinder;
        int threshold;
        bool bLearnBakground;
    
        particleMode currentMode;
        string currentModeStr;
        
        vector <demoParticle> p;
        vector <ofPoint> attractPoints;
        vector <ofPoint> attractPointsWithMovement;

};
