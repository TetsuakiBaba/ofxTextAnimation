#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//    ofEnableSmoothing();
    ofEnableAntiAliasing();
    
    text_animation[0].setAnimate(OFX_TEXT_ANIMATION_TYPE_FADE, 2000, 1000, 2000);
    text_animation[1].setAnimate(OFX_TEXT_ANIMATION_TYPE_OUTLINE, 2000, 1000, 2000);
    text_animation[2].setAnimate(OFX_TEXT_ANIMATION_TYPE_TYPING, 2000, 1000, 2000);
    for( int i = 0; i < 3; i++ ){
        text_animation[i].loadFont(ofToDataPath("DIN Alternate Bold.ttf"), 24);
        text_animation[i].setText("Hello ofxTextAnimation");
        text_animation[i].setLoop(true);
        text_animation[i].play();
    }

}

//--------------------------------------------------------------
void ofApp::update(){
//    cout << text_animation.getTimeMillis() << endl;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(50);
    for( int i = 0; i < 3; i++ ){
        text_animation[i].draw(ofGetWidth()/2, ofGetHeight()/2 + 50*i);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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
