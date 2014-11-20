#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(0);
    ofSetFrameRate(60);

    glPointSize(1);

    w = 1024;
    h = 768;

    font.loadFont("Ricty-Regular.ttf",32,true,true,true);
    text = "Welcome to Perfume world";

    ring = new ConsoleRing(ofPoint(w/2,h/2));
    ring->set_ring();

}

//--------------------------------------------------------------
void ofApp::update(){
    ring->update();

}

//--------------------------------------------------------------
void ofApp::draw(){

    ring->draw();



    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()),10,10);
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

//==============================================================================

void ofApp::setup_particle(){

    int cntX = 50;
    int cntY = 50;

    ofPoint pos,home;
    int radius = 5;

    for (int iy = 0; iy < cntY; iy++) {
        for (int ix = 0; ix < cntX; ix++) {
            Particle *p = new Particle(ofPoint(ofMap(ix,0,cntX,0,w),
                ofMap(iy,0,cntY,0,h),
                0));
            parts.push_back(p);
        }
    }

    for (int i = 0; i < parts.size(); i++) {
        parts[i]->p_num     = (int)ofRandom(3,32);
        parts[i]->radius    = ofRandom(10,30);
        parts[i]->deg_speed = ofRandom(-5,5);
        //parts[i]->velocity.set(ofRandom(-5,5),ofRandom(-5,5),0);
        parts[i]->desire.set(parts[((parts.size()-1)-i)]->pos);
    }
}

void ofApp::update_particle(){
    ofPoint p1,p2;

    for (int i = 0; i < parts.size(); i++) {

        //parts[i]->update_deg(mouseX,mouseY);
        parts[i]->update_pos();
    }
}

void ofApp::draw_particle(){
    ofPoint p1,p2;

    for (int i = 0; i < parts.size(); i++) {
        parts[i]->draw();

        //p1 = parts[i]->pos;
        //if (i+1!=parts.size()){p2 = parts[i+1]->pos;}
        //ofLine(p1,p2);        
    }
}
