#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    w = ofGetWidth();
    h = ofGetHeight();

    //ofSetCoordHandedness(OF_RIGHT_HANDED);
    ofScale(1,-1,1);
    ofSetFrameRate(60);

    ofBackground(ofColor::white);

    //lighting 
    light.enable();
    light.setPosition(1000, 1000, 2000);

    /*
    light.setSpotlight();
    light.setAmbientColor(ofFloatColor(0.5,0.5,0.5));   
    light.setDiffuseColor(ofFloatColor(1,1,1,1));    
    */

    //gui用リスナー定義
    camFov.addListener(this, &ofApp::lsn_camFov);
    camDist.addListener(this, &ofApp::lsn_camDist);

    //gui設定
    gui.setup();
    gui.add(camFov.setup("camera fov",80.0,0.0,180.0));
    gui.add(camDist.setup("camera dist",500.0,0.0,1000.0));
    gui.add(camPos.setup("camera pos",ofVec3f(0,0,0),ofVec3f(-w/2,-h/2,-500),ofVec3f(w/2,h/2,500)));
    isGui = true;

    //easycam設定
    cam.setFov(80);
    cam.setDistance(500);
    isCam = true;

    //SandBox SetUp

}

void ofApp::lsn_camFov(float & camFov){cam.setFov(camFov);}
void ofApp::lsn_camDist(float & camDist){cam.setDistance(camDist);}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){

    if(isCam){cam.begin();}

    ofPushMatrix();{

        ofTranslate(w/2,h/2);

        ofSetColor(0);
        ofTriangle(ofVec3f(0,100,0),ofVec3f(100,-100,0),ofVec3f(-100,-100,0));
        ofDrawAxis(100);
        //ofDrawGrid(100);

    }ofPopMatrix();

    if(isCam){cam.end();}

    if(isGui){
        ofDisableDepthTest();
        gui.draw();
        ofEnableDepthTest();
    }

    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key=='s') {   
        myimage.grabScreen(0,0,ofGetWidth(),ofGetHeight());
        myimage.saveImage("myimage.png",OF_IMAGE_QUALITY_BEST);
    }

    if (key=='r'){cam.reset();}

    if (key=='p'){cam.setPosition(camPos);}

    if (key=='g'){isGui = !isGui;}
    if (key=='c'){isCam = !isCam;}

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

