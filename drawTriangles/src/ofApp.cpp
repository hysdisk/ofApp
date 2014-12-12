#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(60);
    ofBackground(0);

    ofEnableDepthTest();
    ofSetSmoothLighting(true);

    w = ofGetWidth();
    h = ofGetHeight();

    light.enable();
    light.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    light.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));

    material.setShininess( 120 );
    material.setSpecularColor(ofColor(255, 255, 255, 255));

    //d2t.setup(ofVec3f(w/2,h/2,0),50);
    //restest.setup(300,2,ofVec3f(w/2,h/2,0));
    //restest.mode=resTest::MODE::BOX;

    icotri.setup(ofVec3f(w/2,h/2,0),300,1);

}

//--------------------------------------------------------------
void ofApp::update(){

    //d2t.update();
    icotri.update();

}

//--------------------------------------------------------------
void ofApp::draw(){

    //d2t.draw();

    icotri.draw();


    ofDrawBitmapString(ofToString(ofGetFrameRate()),10,10);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if(key=='1'){restest.decl_res();}
    if(key=='2'){restest.incl_res();}

    if(key=='q'){ restest.mode = resTest::MODE::BOX;}
    if(key=='w'){ restest.mode = resTest::MODE::SPHERE;}
    if(key=='e'){ restest.mode = resTest::MODE::ICO;}
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
