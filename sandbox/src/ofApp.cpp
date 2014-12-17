#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    w = ofGetWidth();
    h = ofGetHeight();

    ofSetCoordHandedness(OF_RIGHT_HANDED);
    ofScale(1,-1,1);
    ofTranslate(w/2,h/2);

    ofSetFrameRate(60);
    ofEnableDepthTest();

    ofBackground(ofColor::white);

    light.enable();
    light.setPosition(1000, 1000, 2000);
    /*
    light.setSpotlight();
    light.setAmbientColor(ofFloatColor(1,1,1,1));
    light.setDiffuseColor(ofFloatColor(1,1,1,1));

    */
    mesh = ofMesh::icosphere(300,3);
    mesh.mergeDuplicateVertices();

    for (int i = 0; i < mesh.getNumVertices(); i++)
    {
        vpos.push_back(mesh.getVertex(i));
    }

    mesh = ofMesh::sphere(25,2);
 
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    cam.begin();{

        for (int i = 0; i < vpos.size(); i++)
        {
            ofPushMatrix();{

                ofTranslate(vpos[i]);

                ofSetColor(ofColor::fromHsb(ofMap(i,0,vpos.size(),0,255),255,255,255));
                //mesh.draw();

                //ofSetColor(255);
                ////glLineWidth(3);
                //mesh.drawWireframe();

                ofCircle(0,0,0,30);

            }ofPopMatrix();
        }

        ofDrawAxis(100);
    }cam.end();

    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key=='s') {   
        myimage.grabScreen(0,0,ofGetWidth(),ofGetHeight());
        myimage.saveImage("myimage.png",OF_IMAGE_QUALITY_BEST);
    }

    if (key=='r'){cam.reset();}
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
