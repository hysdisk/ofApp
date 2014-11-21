#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(0);
    ofSetFrameRate(60);
    ofSetRectMode(OF_RECTMODE_CENTER);

    glPointSize(1);

    w = ofGetWidth();
    h = ofGetHeight();

    setup_particle();
}

//--------------------------------------------------------------
void ofApp::update(){

    update_particle();

}

//--------------------------------------------------------------
void ofApp::draw(){

    draw_particle();

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


    enum {RIGHT,DOWN,LEFT,UP};

    ofPoint pos;

    int addX,addY;
    int draw_cnt   = 1;
    int draw_allow = RIGHT;
    int turn_cnt   = 0;

    int side       = 10;
    int p_width    = 50;
    int space      = 2;

    pos.x = (w/2) + ((p_width + space) * (int)(1-(side /2)));
    pos.y = (h/2) + ((p_width + space) * (int)(1-(side /2)));
    pos.x -=(p_width + space);

    int p_num = (side * 2) + ((side - 2) * 2);
    //int p_num = (side * side) - 1;

    for (int icnt = 0; icnt < p_num; icnt++)
    {
        switch (draw_allow)
        {
        case RIGHT:
            addX = p_width + space;
            addY = 0;
            break;
        case DOWN:
            addX = 0;
            addY = p_width + space;
            break;
        case LEFT:
            addX = -(p_width + space);
            addY = 0;
            break;
        case UP:
            addX = 0;
            addY = -(p_width + space);
            break;
        default:
            break;
        }

        pos.x+=addX;
        pos.y+=addY;

        draw_cnt++;
        if (draw_cnt == (side)) {
            draw_allow++;
            draw_cnt = 1;
        }

        Particle *p = new Particle(pos);
        parts.push_back(p);
    }

    for (int i = 0; i < parts.size(); i++) {
        parts[i]->number    = i;
        parts[i]->p_num     = 4;
        parts[i]->radius    = p_width / 2;
        parts[i]->deg_speed = ofRandom(-5,5);
        parts[i]->desire.set(parts[(i+1)%parts.size()]->pos);
    }
}

void ofApp::update_particle(){

    //for (int i = 0; i < parts.size(); i++) {
    //    parts[i]->update_deg();
    //    parts[i]->update_pos();
    //    if (parts[i]->isMove == false){
    //        parts[i]->desire.set(parts[(i+1)%parts.size()]->pos);
    //    }
    //}
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
