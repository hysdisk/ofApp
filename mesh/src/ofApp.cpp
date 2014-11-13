#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(60);
    ofBackground(0);
    ofSetCircleResolution(16);
    ofSetRectMode(OF_RECTMODE_CENTER);
    glPointSize(2);

    //glBlendFunc(GL_ONE, GL_ZERO);

    int space = 10;
    for (int iy = 0; iy < 50; iy++)
    {
        for (int ix = 0; ix < 100; ix++)
        {
            Particle *p = new Particle();
            p->setup(ix*space,iy*space,0);
            //p->set_velocity(ofRandom(-1,1),ofRandom(-1,1),0);
            parts.push_back(p);
        }
    }

}

//--------------------------------------------------------------
void ofApp::update(){
    for (int icnt = 0; icnt < parts.size(); icnt++)
    {
        parts[icnt]->set_velocity_dest();
        parts[icnt]->update();
    }

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
    cam.begin();
    for (int icnt = 0; icnt < parts.size(); icnt++)
    {
        parts[icnt]->draw();
    }

    cam.end();

    ofSetColor((ofColor::white),128);
    ofDrawBitmapString(ofToString(ofGetFrameRate()),10,10);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key=='1'){alignment_circle();}
    if (key=='2'){
        alignment_box(0,100,300);
        alignment_box(1000,300,300);
        alignment_box(2000,500,300);
        alignment_box(3000,700,300);
        alignment_box(4000,900,300);
    }

    if (key==' '){cam.reset();}
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
    //for (int icnt = 0; icnt < parts.size(); icnt++)
    //{
    //    parts[icnt]->set_dest(x,y,0);
    //    parts[icnt]->set_velocity_dest();
    //}
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

void ofApp::alignment_circle(){

    int circle_diameter = 600;
    int space = 1;
    //int radius_on_part = (circle_diameter * PI) / (space / 10);
    int radius_on_part = 1000;
    float dx,dy,dz;

    for (int icircle = 0; icircle < radius_on_part; icircle++)
    {
        dx = (circle_diameter / 2) * cos(ofMap(icircle,0,radius_on_part,0,PI*2));
        dy = (circle_diameter / 2) * sin(ofMap(icircle,0,radius_on_part,0,PI*2));
        dz = 0;

        //dx += ofGetWidth() / 2;
        //dy += ofGetHeight() / 2;

        parts[icircle]->set_dest(dx,dy,dz);
    }

}

void ofApp::alignment_box(int start_cnt_,float x_,float y_){
    int cnt = start_cnt_;
    for (int iz = 0; iz < 10; iz++)
    {
        for (int iy = 0; iy < 10; iy++)
        {
            for (int ix = 0; ix < 10; ix++)
            {
                parts[cnt]->set_dest((ix*10)+x_,(iy*10)+y_,iz*10);
                cnt++;
            }
        }
    }
}