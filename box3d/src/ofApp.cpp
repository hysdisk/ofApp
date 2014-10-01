#include "ofApp.h"

ofEasyCam cam;

int deg;
//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

    deg++ % 360;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofMesh box;
    ofMesh sphere;
    
    float x;
    float y;
    float z;

    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);

    box = ofMesh::box(30, 30, 30,1,1,1);

    cam.begin();
    
    for (int i = 0; i < 36; i++) {
        x = 300 * cos(ofDegToRad(i*10));
        y = 0;
        z = 300 * sin(ofDegToRad(i*10));
        
        ofPushMatrix();
        ofTranslate(x,y,z);
        box.drawWireframe();
        ofPopMatrix();
        
    }
        ofRotateY(deg);
    

    
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
