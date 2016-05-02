#include "ofApp.h"

int i = 0;
int _i = 0;
int alpha;
float vidSpeed;

// resolution of live video
int vidX = 320;
int vidY = 240;
// setup blob pointer
int pointerX = 0;
int pointerY = 0;

ofVideoPlayer mov1;

ofImage img1;
ofImage img2;
ofImage img3;
ofImage img4;
ofImage img5;
ofImage img6;
ofImage img7;
ofImage img8;
ofImage img9;
ofImage img10;
ofImage img11;
ofImage img12;
ofImage img13;

//--------------------------------------------------------------
void ofApp::setup(){
//-------------------------
    
    int num = 1500;
    p.assign(num, demoParticle());
    currentMode = PARTICLE_MODE_NEAREST_POINTS;
    
    resetParticles();
    
    ofBackground(100, 100, 100);
    
    vidGrabber.setVerbose(true);
    vidGrabber.setup(vidX,vidY);  // setup live video grabbing
    colorImg.allocate(vidX,vidY);  // color image display
    grayImage.allocate(vidX,vidY); // grayscale display
    grayBg.allocate(vidX,vidY);	   // contour image
    grayDiff.allocate(vidX,vidY);  // b/w differencing image
    bLearnBakground = true;
    threshold = 80;
    
    ofSetVerticalSync(true);
    bSendSerialMessage = false;
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    int baud = 9600;
    serial.setup("/dev/cu.usbmodem1411", baud);
    
    nTimesRead = 0;
    nBytesRead = 0;
    readTime = 0;
    
    memset(bytesReadString, 0, 4);
    
    font.load("NADISN__.TTF", 12);
    font2.load("NADISN__.TTF", 24);
    _i = ofClamp(i, 0, 14);
    
    mov1.load("hel-0world.mp4");
    mov1.setLoopState(OF_LOOP_NORMAL);
    mov1.play();
    
    music1.load("1.wav");
    music2.load("2.wav");
    music3.load("3.wav");
    music4.load("4.wav");
    music5.load("5.wav");
    music6.load("6.wav");
    music7.load("7.wav");
    music8.load("8.wav");
    music9.load("9.wav");
    music10.load("10.wav");
    music11.load("11.wav");
    music12.load("12.wav");
    music13.load("11.wav");
    music14.load("12.wav");
    music15.load("13.wav");
    
    music1.play();
    music2.play();
    music3.play();
    music4.play();
    music5.play();
    music6.play();
    music7.play();
    music8.play();
    music9.play();
    music10.play();
    music11.play();
    music12.play();
    music13.play();
    music14.play();
    music15.play();
    
    music1.setPaused(true);
    music2.setPaused(true);
    music3.setPaused(true);
    music4.setPaused(true);
    music5.setPaused(true);
    music6.setPaused(true);
    music7.setPaused(true);
    music8.setPaused(true);
    music9.setPaused(true);
    music10.setPaused(true);
    music11.setPaused(true);
    music12.setPaused(true);
    music13.setPaused(true);
    music14.setPaused(true);
    music15.setPaused(true);
    
    img1.load("01.png");
    img2.load("02.png");
    img3.load("03.png");
    img4.load("04.png");
    img5.load("05.png");
    img6.load("06.png");
    img7.load("07.png");
    img8.load("08.png");
    img9.load("09.png");
    img10.load("10.png");
    img11.load("11.png");
    img12.load("12.png");
    img13.load("13.png");
    
}

//--------------------------------------------------------------
void ofApp::resetParticles(){
//-------------------------
    
    //these are the attraction points used in the forth demo
    attractPoints.clear();
    for(int i = 0; i < 4; i++){
        attractPoints.push_back( ofPoint( ofMap(i, 0, 4, 100, ofGetWidth()-100) , ofRandom(100, ofGetHeight()-100) ) );
    }
    
    attractPointsWithMovement = attractPoints;
    
    for(unsigned int i = 0; i < p.size(); i++){
        p[i].setMode(currentMode);
        p[i].setAttractPoints(&attractPointsWithMovement);;
        p[i].reset();
    }	
}

//--------------------------------------------------------------
void ofApp::update(){
//-------------------------
    
    bool bNewFrame = false;
    vidGrabber.update();
    bNewFrame = vidGrabber.isFrameNew();
    if (bNewFrame){  // if we have a new frame
        colorImg.setFromPixels(vidGrabber.getPixels());
        grayImage = colorImg;
        if (bLearnBakground == true){  // if we hit space, this grabs a "control" image
            grayBg = grayImage;		// copys the pixels from grayImage into grayBg
            bLearnBakground = false;
        }
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(threshold);
        // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
        // find max 10 blobs with no holes in them
        contourFinder.findContours(grayDiff, 20, (vidX*vidY)/3, 10, false);	// false == dont find holes in our blobs
    }
    
    if (bSendSerialMessage){
        serial.writeByte('a');
        nTimesRead = 0;
        nBytesRead = 0;
        int nRead;
        
        unsigned char bytesReturned[3];
        
        memset(bytesReadString, 0, 4);
        memset(bytesReturned, 0, 3);
        
        while( (nRead = serial.readBytes( bytesReturned, 3)) > 0){
            nTimesRead++;
            nBytesRead = nRead;
        };
        
        memcpy(bytesReadString, bytesReturned, 3);
        
        bSendSerialMessage = false;
        readTime = ofGetElapsedTimef();
    }
    
    mov1.update();
    
    for(unsigned int i = 0; i < p.size(); i++){
        p[i].setMode(currentMode);
        p[i].update();
    }
    for(unsigned int i = 0; i < attractPointsWithMovement.size(); i++){
        attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
        attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
//-------------------------
    
    int  limit = contourFinder.nBlobs;
    int maxArea = 0;
    int elementNum = -1;
    ofColor yellow(255, 255, 171);
    ofColor white(255, 1);
    
//-------------------------
    
    // loop pages, back and forth
    if (_i < 0) {
        _i = 14;
    }
    if (_i > 14){
        _i = 0;
    }
    
    switch (_i) {
    
        case 0: // blink eyes - ellipse, fill black when clicked DONE
            img1.draw(30, 60);
            ofSetColor(255, 180, 0, alpha);
            ofDrawCircle(265, 225, 45);
            ofDrawCircle(440, 230, 45);
            if (ofGetMousePressed() == true){
                alpha = 0;
            } else {
                alpha = 255;
            }
            music1.setPaused(false);
            ofSetColor(255);
            font.drawString("Omphalotus wasnt like all the other mushrooms.", 40, 40);
            font.drawString("He had eyes. ...and could walk.", 40, 55);
            break;
            
        case 1: // cap sensor DONE
            img2.draw(30, 60);
            music2.setPaused(false);
            bSendSerialMessage = true;
            if (nBytesRead != 1){
                ofSetColor(220);
            } else {
                ofSetColor(0);
            }
            font.drawString("...and talk. He glowed in the dark too.", 40, 40);
            break;
            
        case 2: // earth video speed, mouse move DONE
            bSendSerialMessage = false;
            ofClearAlpha();
            img3.draw(30, 60);
            mov1.draw(215, 480);
            mov1.setSpeed(vidSpeed);
            music3.setPaused(false);
            font.drawString("He didnt know what to do with the days, he felt lost and lonely.", 40, 40);
            font.drawString("Like the world was too big, and he was too small.", 40, 55);
            break;
            
        case 3: // ketchup DONE
            ofEnableAlphaBlending();
            bSendSerialMessage = false;
            img4.draw(30, 60);
            music4.setPaused(false);
            font.drawString("He thought of turning himself in to the omelet factory,", 40, 40);
            font.drawString("but even then, theyd turn him away because he is too poisonous.", 40, 55);
            ofSetColor(250, 58, 20);
            line.draw();
            ofSetColor(255);
            break;
            
        case 4:
            bSendSerialMessage = false;
            ofClearAlpha();
            img5.draw(30, 60);
            music5.setPaused(false);
            font.drawString("It was late one evening he squished sadly past a slime mold on a rock.", 40, 40);
            break;
            
        case 5: // stars in eyes
            bSendSerialMessage = false;
            ofClearAlpha();
            img6.draw(30, 60);
            music6.setPaused(false);
            font.drawString("Hello, what a lovely evening!", 40, 40);
            font.drawString("...squeaked the slime mold.", 40, 55);
            break;
            
        case 6: // drops in eyes
            bSendSerialMessage = false;
            ofClearAlpha();
            img8.draw(30, 60);
            music7.setPaused(false);
            font.drawString("Hello.", 40, 40);
            font.drawString("...replied Omphalotus gloomily.", 40, 55);
            break;
            
        case 7: // more stars
            bSendSerialMessage = false;
            ofClearAlpha();
            img9.draw(30, 60);
            music8.setPaused(false);
            font.drawString("Come, sit upon this rock with me, the lunar eclipse is coming!", 40, 40);
            font.drawString("...the slime mold squeaked.", 40, 55);
            break;
            
        case 8:
            bSendSerialMessage = false;
            img7.draw(30, 60);
            ofClearAlpha();
            music9.setPaused(false);
            font.drawString("Omphalotus did not know what the slime mold was talking about ", 40, 40);
            font.drawString("but he slowly glided over to the rock and joined his new companion.", 40, 55);
            break;
            
        case 9: // throw sum leds DONE
                // touch cap sensor to alternate functions?
            bSendSerialMessage = true;
            ofClearAlpha();
            img10.draw(30, 60);
            music10.setPaused(false);
            font.drawString("They waited in silence, staring at the full moon glowing in the night sky.", 40, 40);
            font.drawString("A snake slithered past in the grass. Three crickets chirped an evening chorus, and a group of fireflies danced.", 40, 55);
            break;
            
        case 10: // moon ellipse, covered by black ellipse with openCV DONE
            bSendSerialMessage = false;
            img11.draw(30, 60);
            
            for (int i = 0; i < limit; i++) {
                if (contourFinder.blobs[i].area > maxArea){
                    maxArea = contourFinder.blobs[i].area;
                    elementNum = i;
                }
            }
            if (elementNum >= 0) {
                pointerX = ofMap(contourFinder.blobs[elementNum].boundingRect.x, vidX, 0, 0, ofGetWidth(), true);
                ofSetColor(255);
                ofDrawCircle(ofGetWidth()/2, 400, 160);
                ofSetColor(0);
                ofDrawCircle(pointerX/2 + 200, 400, 150);
            }
            ofSetColor(255, 255, 255, 150);
            music11.setPaused(false);
            font.drawString("Soon the world grew quiet all around and Omphalotus gazed into the sky.", 40, 40);
            font.drawString("He watched in wonder as the once luminous moon was covered in a veil of magic shadow.", 40, 55);
            break;
            
        case 11: // 'glowing' eclipse
            bSendSerialMessage = false;
            ofClearAlpha();
            img12.draw(30, 60);
            music12.setPaused(false);
            font.drawString("A small smile crept onto his cap, a satisfying chill rushed up his stalk.", 40, 40);
            font.drawString("He had never seen something so spectacular, so unequivocally beautiful.", 40, 55);
            ofSetColor(255);
            ofDrawCircle(300, 300, 110);
            ofSetColor(0);
            ofDrawCircle(300, 300, 100);
            ofSetColor(255, 150);
            break;
            
        case 12: // particle eyes
            bSendSerialMessage = false;
            img13.draw(30, 60);
            music13.setPaused(false);
            
            for(unsigned int i = 0; i < p.size(); i++){
                p[i].draw();
            }
            currentMode == PARTICLE_MODE_ATTRACT;
            
            ofSetColor(255);
            font.drawString("For the first time he was filled with wonder, and he no longer felt so small.", 40, 40);
            
            break;
            
        case 13: // radial gradient fills screen
            ofSetColor(255);
            ofBackgroundGradient(yellow, white, OF_GRADIENT_CIRCULAR);
            bSendSerialMessage = false;
            music14.setPaused(false);
            font.drawString("He started glowing brighter than the moon.", 250, ofGetHeight()/1.3);
            break;
            
        case 14:
            bSendSerialMessage = false;
            music15.setPaused(false);
            ofSetColor(255);
            font2.drawString("After the Eclipse", 40, 300);
            font.drawString("story by: Amber Glassman", 40, 80);
            font.drawString("illustrated by: Jessica Herzog", 40, 100);
            break;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
        if (key == OF_KEY_RIGHT){
            _i++;
        }
        if (key == OF_KEY_LEFT){
            _i--;
        }
    
        switch (key){
            case ' ':
                bLearnBakground = true;
                break;
        }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    if (mouseY >= ofGetHeight()/2) {
        vidSpeed++;
    } else if (mouseY < ofGetHeight()/2) {
        vidSpeed--;
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    ofPoint pt;
    pt.set(x,y);
    line.addVertex(pt);
    
    
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    alpha = 0;
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
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
}
