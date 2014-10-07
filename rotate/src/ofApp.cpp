#include "ofApp.h"

int end_deg;
int circle_steps;
ofColor kurveColor[9];

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(ofColor::black);
    end_deg = 180;
    kurveColor[1] = ofColor(33,34,39);
    kurveColor[2] = ofColor(48,45,72);
    kurveColor[3] = ofColor(46,41,61);
    kurveColor[4] = ofColor(61,44,78);
    kurveColor[5] = ofColor(127,49,39);
    kurveColor[6] = ofColor(142,49,34);
    kurveColor[7] = ofColor(165,61,36);
    kurveColor[8] = ofColor(193,106,63);

    circle_steps = 3;

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

    for (int icount = 1; icount <= 8; icount++)
    {
        for (int ir = 0; ir <= end_deg / circle_steps; ir++)
        {
            _rad = r_radius + (r_width * icount);
            posx = _rad * cos(ofDegToRad(ir*circle_steps));
            posy = _rad * sin(ofDegToRad(ir*circle_steps));

            pos_in.set(posx,posy,0);
            mesh.addColor(kurveColor[icount]);
            mesh.addVertex(pos_in);

            _rad+=r_width;
            posx = _rad * cos(ofDegToRad(ir*circle_steps));
            posy = _rad * sin(ofDegToRad(ir*circle_steps));

            pos_out.set(posx,posy,0);
            mesh.addColor(kurveColor[icount]);
            mesh.addVertex(pos_out);

            r_deg = ir*circle_steps;

        }
        mesh.draw();
        mesh.clear();

        _rad = (r_radius + r_width * 11);
        posx = _rad * cos(ofDegToRad(r_deg));
        posy = _rad * sin(ofDegToRad(r_deg));
        r_pos.set(posx,posy);

        for (int ir = r_deg-180; ir >= -r_deg; ir--)
        {
            //
            _rad = r_radius + (-(icount - 9)) * r_width;
            posx = _rad * cos(ofDegToRad(ir));
            posy = _rad * sin(ofDegToRad(ir));

            pos_in.set(posx,posy,0);
            mesh.addColor(kurveColor[icount]);
            mesh.addVertex(pos_in);

            _rad+=r_width;
            posx = _rad * cos(ofDegToRad(ir));
            posy = _rad * sin(ofDegToRad(ir));

            pos_out.set(posx,posy,0);
            mesh.addColor(kurveColor[icount]);
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
