#include "ofApp.h"

int start_deg;
int dist_deg;
int step_circle;
ofPoint pos;

int r_outer;
int r_inner;
//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(60);

    start_deg = -90;
    dist_deg = 45;
    step_circle = 2;

    pos.set(ofGetWidth()/2,ofGetHeight()/2);
    r_outer = 100;
    r_inner = 90;
}

//--------------------------------------------------------------
void ofApp::update(){

}

void draw_poly(){

    ofPolyline poly;

    for (int i = 1; i < 18; i++)
    {
        poly.addVertex(100*cos(ofDegToRad(i*10)),100*sin(ofDegToRad(i*10)));
    }

    poly.close();
    poly.draw();
}

void draw_mesh_roll(int start_deg_,int dist_deg_){

    ofMesh mesh;

    ofPushMatrix();
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2);

    int it;

    mesh.setMode(OF_PRIMITIVE_LINE_LOOP);

    //時計回り

    ////外周点作成
    for (int i = start_deg_/step_circle; i <= (start_deg_ + dist_deg_)/step_circle; i++)
    {
        mesh.addVertex(ofVec3f(300*cos(ofDegToRad(i*step_circle)),300*sin(ofDegToRad(i*step_circle)),0));

        it = i;
    }
    ofDrawBitmapString(ofToString(it),0,10);

    //内周点作成
    for (int i = (start_deg_ + dist_deg_)/step_circle; i >= start_deg_/step_circle; i--)
    {
        mesh.addVertex(ofVec3f(200*cos(ofDegToRad(i*step_circle)),200*sin(ofDegToRad(i*step_circle)),0));        
        it = i;
    }
    ofDrawBitmapString(ofToString(it),0,20);

    mesh.draw();

    ofDrawBitmapString(ofToString(mesh.getNumVertices()),0,0);

    ofPopMatrix();

}
void draw_mesh_roll_fill(ofPoint pos_,int start_deg_,int dist_deg_,int r_outer_,int r_innner_){

    ofMesh mesh;

    ofPushMatrix();
    ofTranslate(pos_);

    int it;

    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

    for (int i = start_deg_/step_circle; i <= (start_deg_ + dist_deg_)/step_circle; i++)
    {
        mesh.addVertex(ofVec3f(r_outer_*cos(ofDegToRad(i*step_circle)),r_outer_*sin(ofDegToRad(i*step_circle)),0));
        mesh.addColor(ofColor::orange);
        mesh.addVertex(ofVec3f(r_innner_*cos(ofDegToRad(i*step_circle)),r_innner_*sin(ofDegToRad(i*step_circle)),0));
        mesh.addColor(ofColor::orangeRed);
        it = i;
    }
    ofDrawBitmapString(ofToString(it),0,10);

    mesh.draw();
    ofDrawBitmapString(ofToString(mesh.getNumVertices()),0,0);
    ofPopMatrix();

}
//--------------------------------------------------------------
void ofApp::draw(){

    //draw_poly();

    draw_mesh_roll_fill(pos,start_deg,dist_deg,r_outer,r_inner);

    string msg;

    msg = "start_deg: " + ofToString(start_deg) + " dist_deg: " + ofToString(dist_deg);
    ofDrawBitmapString(msg,10,10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == OF_KEY_RIGHT)
    {
        dist_deg++;
    }
    if (key == OF_KEY_LEFT)
    {
        dist_deg--;
    }


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
    pos.set(x,y);
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
