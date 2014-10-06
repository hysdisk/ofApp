#include "ofApp.h"
int deg_loop;
int part_count;



ofColor kurveColor[8];
ofEasyCam cam;

//--------------------------------------------------------------
void ofApp::setup(){
    
    kurveColor[0] = ofColor(33,34,39);
    kurveColor[1] = ofColor(48,45,72);
    kurveColor[2] = ofColor(46,41,61);
    kurveColor[3] = ofColor(61,44,78);
    kurveColor[4] = ofColor(127,49,39);
    kurveColor[5] = ofColor(142,49,34);
    kurveColor[6] = ofColor(165,61,36);
    kurveColor[7] = ofColor(193,106,63);
    
    ofSetFrameRate(60);
    ofSetCircleResolution(32);
    ofBackground(0,0,0);
    
    deg_loop = 36;
    part_count = 180;
    
    

}

//--------------------------------------------------------------
void ofApp::update(){
}

void draw_kurve_2(){
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    ofVec3f trans_in;
    ofVec3f trans_out;
    
    ofVec3f pos_in;
    ofVec3f pos_out;
    
    int k_rad;
    int k_width;
    bool isTrans = false;
    
    k_rad = 100;
    k_width = 30;
    
    for (int ik = 0; ik <= 7; ik++) {
        
        for (int ir = 0; ir <= 360 / 5; ir++) {
            
            if (ir <= 180 / 5) {
                pos_in.set((k_rad + (k_width * ik)) * cos(ofDegToRad(ir*5)),
                           (k_rad + (k_width * ik)) * sin(ofDegToRad(ir*5)));
                
                ofSetColor(kurveColor[ik]);
                ofCircle(pos_in, 15);
            }
            else {
                trans_out.set((k_rad + (k_width * 8)) * cos(ofDegToRad(180)),
                              (k_rad + (k_width * 8)) * sin(ofDegToRad(180)));
                ofPushMatrix();
                ofTranslate(trans_out);
                pos_in.set((k_rad + (k_width * ik)) * cos(ofDegToRad(ir*5)),
                           (k_rad + (k_width * ik)) * sin(ofDegToRad(ir*5)));
                
                ofSetColor(kurveColor[ik]);
                ofCircle(pos_in, 15);
                ofPopMatrix();
            }
            
            
        }
        
        
    }
    
    
    
    
    
}




void draw_kurve_1(){
    ofMesh mesh;
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    //    mesh.setMode(OF_PRIMITIVE_POINTS);
    
    float cosX,sinY;
    int kurve_radius;
    int kurve_width;
    
    ofVec3f pos;
    
    kurve_width= 30;
    kurve_radius = 100;
    
    for (int ilayer = 0; ilayer <= 7; ilayer++) {
        
        kurve_radius = 50 + ilayer * kurve_width;
        
        for (int i = 0; i <= deg_loop; i++) {
            
            cosX = cos(ofDegToRad(i*5));
            sinY = sin(ofDegToRad(i*5));
            mesh.addColor(kurveColor[ilayer]);
            mesh.addVertex(ofVec3f(kurve_radius * cosX,
                                   kurve_radius * sinY,0));
            mesh.addColor(kurveColor[ilayer]);
            mesh.addVertex(ofVec3f((kurve_radius+kurve_width) * cosX,
                                   (kurve_radius+kurve_width) * sinY,0));
            
        }
        
        mesh.draw();
        mesh.clear();
        
        ofPushMatrix();
        
        ofTranslate(kurve_radius+80 + (7 - ilayer) * kurve_width,0);
        
        kurve_radius = 50 + (7-ilayer) * kurve_width;
        
        for (int i = deg_loop; i <= deg_loop + 36; i++) {

            cosX = cos(ofDegToRad(i*5));
            sinY = sin(ofDegToRad(i*5));
            
            mesh.addColor(kurveColor[ilayer]);
            mesh.addVertex(ofVec3f(kurve_radius * cosX,
                                   kurve_radius * sinY,0));

            mesh.addColor(kurveColor[ilayer]);
            mesh.addVertex(ofVec3f((kurve_radius+kurve_width) * cosX,
                                   (kurve_radius+kurve_width) * sinY,0));

        
        
        }
        mesh.draw();
        mesh.clear();
        
        ofPopMatrix();
    }

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofTranslate(ofGetWidth() / 2, ofGetHeight()/2);
    cam.begin();
    draw_kurve_1();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == OF_KEY_UP) {
        deg_loop++;
        part_count++;
    }

    if (key == OF_KEY_DOWN) {
        deg_loop--;
        part_count--;
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
