#include "ofApp.h"

int end_deg;

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(ofColor::black);
    end_deg = 180;


}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofTranslate(ofGetWidth()/2 ,ofGetHeight()/2);

    ofMesh mesh;

    ofVec3f pos_in;
    ofVec3f pos_out;
    ofVec3f r_pos;

    float posx,posy;

    int r_width;
    int r_radius;
    int r_count;
    int r_deg;
    int _rad;

    r_count = 1;
    r_width = 20;
    r_radius = 20;

    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    //mesh.setMode(OF_PRIMITIVE_POINTS);

    mesh.addVertex(ofVec3f(0,0,0));

    glPointSize(3.0);

    for (int icount = 1; icount <= 7; icount++)
    {
        for (int ir = 0; ir <= end_deg; ir++)
        {
            _rad = r_radius + (r_width * icount);
            posx = _rad * cos(ofDegToRad(ir));
            posy = _rad * sin(ofDegToRad(ir));

            pos_in.set(posx,posy,0);
            mesh.addVertex(pos_in);

            _rad+=r_width;
            posx = _rad * cos(ofDegToRad(ir));
            posy = _rad * sin(ofDegToRad(ir));

            pos_out.set(posx,posy,0);
            mesh.addVertex(pos_out);

            r_deg = ir;

        }
        mesh.draw();
        mesh.clear();

        _rad = (r_radius + r_width * 10);
        posx = _rad * cos(ofDegToRad(r_deg));
        posy = _rad * sin(ofDegToRad(r_deg));
        r_pos.set(posx,posy);

        mesh.addVertex(ofVec3f(0,0,0));
        for (int ir = r_deg-180; ir >= (r_deg * -1); ir--)
        {
            _rad = r_radius + ((icount - 8)* -1) * r_width;
            posx = _rad * cos(ofDegToRad(ir));
            posy = _rad * sin(ofDegToRad(ir));

            pos_in.set(posx,posy,0);
            mesh.addVertex(pos_in);

            _rad+=r_width;
            posx = _rad * cos(ofDegToRad(ir));
            posy = _rad * sin(ofDegToRad(ir));

            pos_out.set(posx,posy,0);
            mesh.addVertex(pos_out);
        }

        ofPushMatrix();
        ofTranslate(r_pos);
        mesh.draw();
        mesh.clear();
        ofPopMatrix();
    }



}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key==OF_KEY_RIGHT)
    {
        end_deg++;
    }

    if (key==OF_KEY_LEFT)
    {
        end_deg--;
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
