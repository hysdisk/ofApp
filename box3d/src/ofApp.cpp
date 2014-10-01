#include "ofApp.h"

ofEasyCam cam;
ofLight light;

int deg;
int rr;
//--------------------------------------------------------------
void ofApp::setup(){
    // 画面設定
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(31);
    // 照明とカメラ
    ofEnableLighting();
    light.setPosition(200, 300, 50);
    light.enable();
    cam.setOrientation(ofPoint(-20, 0, 0));
    // GL設定
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    deg = 0;
    rr = 300;
}

//--------------------------------------------------------------
void ofApp::update(){

    deg = (deg + 1) % 360;
//    rr = 200 * abs(cos(ofDegToRad(deg))) + 150;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofMesh box;
    ofMesh sphere;
    
    float x;
    float y;
    float z;

    ofSetColor(ofColor::white);
    ofDrawBitmapString(ofToString(deg), 10,10);
    ofDrawBitmapString(ofToString(rr), 10,20);
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);

    box = ofMesh::box(10, 10, 10,1,1,1);
    sphere = ofMesh::sphere(100);

    cam.begin();

    sphere.draw();

    ofRotateY(deg);
    
    
    for (int i = 0; i < 72; i++) {
        ofPushMatrix();
        ofTranslate(rr * cos(ofDegToRad(i*5)),0,rr * sin(ofDegToRad(i*5)));
        box.drawWireframe();
        ofPopMatrix();
    }

    ofRotateX(deg);
    for (int i = 0; i < 72; i++) {
        ofPushMatrix();
        ofTranslate(0,rr * cos(ofDegToRad(i*5)),rr * sin(ofDegToRad(i*5)));
        box.drawWireframe();
        ofPopMatrix();
    }

    ofRotateZ(deg);
    for (int i = 0; i < 72; i++) {
        ofPushMatrix();
        ofTranslate(rr * cos(ofDegToRad(i*5)),rr * sin(ofDegToRad(i*5)),0);
        box.drawWireframe();
        ofPopMatrix();
    }

    cam.end();
    

    

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
