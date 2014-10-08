#include "ofApp.h"



class Kurve {

public:

    Kurve(){
        kurveColor[1] = ofColor(33,34,39);
        kurveColor[2] = ofColor(48,45,72);
        kurveColor[3] = ofColor(46,41,61);
        kurveColor[4] = ofColor(61,44,78);
        kurveColor[5] = ofColor(127,49,39);
        kurveColor[6] = ofColor(142,49,34);
        kurveColor[7] = ofColor(165,61,36);
        kurveColor[8] = ofColor(193,106,63);

        for (int i = 1; i <= 8; i++)
        {
            kurveMesh[i].setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
            //kurveMesh[i].setMode(OF_PRIMITIVE_POINTS);
        }

        kurveWidth = 30;
        position.set(ofGetWidth()/2,ofGetHeight()/2,0);
    }

    ~Kurve(){
    }

    ofColor kurveColor[9];
    ofMesh  kurveMesh[9];
    ofVec3f position;
    int   kurveDeg;

    int kurveWidth;

    enum Arrow{UP,RIGHT,DOWN,LEFT};

    void draw_Straight(int step_,int distance_,int arrow_){

        ofVec3f location_;

        location_.set(0,0,0);

        for (int idist = 0; idist <= distance_ / step_; idist++)
        {
            for (int ipart = 1; ipart < 8; ipart++)
            {
                //TODO : 進行方向判定

                location_.set(ipart * kurveWidth,idist * step_,0);
                kurveMesh[ipart].addColor(kurveColor[ipart]);
                kurveMesh[ipart].addVertex(location_);

                location_.set(ipart * kurveWidth + kurveWidth,idist * step_,0);
                kurveMesh[ipart].addColor(kurveColor[ipart]);
                kurveMesh[ipart].addVertex(location_);
            }            
        }

        for (int i = 1 ; i < 8; i++)
        {
            kurveMesh[i].draw();
            kurveMesh[i].clear();

        }


    }

    void draw_u(int step_,int startdeg_, int enddeg_){

        ofVec3f location_;

        //TODO : 回転方向判断

        for (int ideg = startdeg_ / step_; ideg <= enddeg_ / step_; ideg++)
        {
            for (int ipart = 1; ipart < 8; ipart++)
            {

                //内径位置セット
                location_.set(
                    ipart * kurveWidth * cos(ofDegToRad(ideg * step_)),
                    ipart * kurveWidth * sin(ofDegToRad(ideg * step_)),0);

                kurveMesh[ipart].addColor(kurveColor[ipart]);
                kurveMesh[ipart].addVertex(location_);

                //外径位置セット
                location_.set(
                    (kurveWidth + (ipart * kurveWidth)) * cos(ofDegToRad(ideg * step_)),
                    (kurveWidth + (ipart * kurveWidth)) * sin(ofDegToRad(ideg * step_)),0);
                kurveMesh[ipart].addColor(kurveColor[ipart]);
                kurveMesh[ipart].addVertex(location_);
            }            
        }

        for (int i = 1 ; i < 8; i++)
        {
            kurveMesh[i].draw();
            kurveMesh[i].clear();

        }

    }

    void draw_n(int step_,int startdeg_, int enddeg_){

        ofVec3f location_;

        // 0 to -180を想定
        for (int ideg = startdeg_ / step_; ideg >= enddeg_ / step_; ideg--)
        {
            for (int ipart = 1; ipart < 8; ipart++)
            {

                //内径位置セット
                location_.set(
                    ipart * kurveWidth * cos(ofDegToRad(ideg * step_)),
                    ipart * kurveWidth * sin(ofDegToRad(ideg * step_)),0);

                kurveMesh[ipart].addColor(kurveColor[-(ipart-8)]);
                kurveMesh[ipart].addVertex(location_);

                //外径位置セット
                location_.set(
                    (kurveWidth + (ipart * kurveWidth)) * cos(ofDegToRad(ideg * step_)),
                    (kurveWidth + (ipart * kurveWidth)) * sin(ofDegToRad(ideg * step_)),0);
                kurveMesh[ipart].addColor(kurveColor[-(ipart-8)]);
                kurveMesh[ipart].addVertex(location_);
            }            
        }

        for (int i = 1 ; i < 8; i++)
        {
            kurveMesh[i].draw();
            kurveMesh[i].clear();

        }

    }

};

Kurve *kurve;
ofEasyCam cam;


//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(ofColor::black);
    glPointSize(3.0);

    kurve = new Kurve;



}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    //cam.begin();

    ofPushMatrix();

    ofTranslate(700,80,0);
    kurve->draw_Straight(5,100,2);

    ofTranslate(0,100,0);
    kurve->draw_u(5,0,180);

    ofTranslate(-270,0,0);
    kurve->draw_n(5,0,-180);

    ofTranslate(-270,0,0);
    kurve->draw_Straight(5,500,2);

    ofPopMatrix();

    //cam.end();

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
