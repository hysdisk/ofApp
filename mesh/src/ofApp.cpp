#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(60);
    ofBackground(0);
    ofSetCircleResolution(16);

    glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);


    for (int iy = 0; iy < 50; iy++)
    {
        for (int ix = 0; ix < 50; ix++)
        {
            Particle *p = new Particle();
            p->setup(ix*10,iy*10,0);
            p->set_velocity(ofRandom(-1,1),ofRandom(-1,1),0);
            parts.push_back(p);
        }
    }

}

//--------------------------------------------------------------
void ofApp::update(){
    for (int icnt = 0; icnt < parts.size(); icnt++)
    {
        parts[icnt]->update();
    }

}

//--------------------------------------------------------------
void ofApp::draw(){

    for (int icnt = 0; icnt < parts.size(); icnt++)
    {
        parts[icnt]->draw();
    }

    ofDrawBitmapString(ofToString(ofGetFrameRate()),10,10);

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
    for (int icnt = 0; icnt < parts.size(); icnt++)
    {
        parts[icnt]->set_dest(x,y,0);
        parts[icnt]->set_velocity_dest();
    }
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
