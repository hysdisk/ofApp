#include "ofApp.h"


class ConsoleRing
{
public:
    ConsoleRing(){

        pos.set(0,0,0);
        radius = 100;
        width = 10;
        deg_start = 0;
        deg_end = 300;
        rotate_speed = 3;
        rotate_deg = 0;
        is_clockwork = true;
        color.set(255,255,255);
    }
    ~ConsoleRing(){}

    void make_ring(){

        float x,y;

        mesh.clear();
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

        for (int ideg = deg_start; ideg  < deg_end; ideg +=9)
        {
            x = radius * cos(ofDegToRad(ideg));
            y = radius * sin(ofDegToRad(ideg));

            mesh.addColor(color);
            mesh.addVertex(ofVec3f(x,y,0));

            x = (radius + width) * cos(ofDegToRad(ideg));
            y = (radius + width) * sin(ofDegToRad(ideg));

            mesh.addColor(color);
            mesh.addVertex(ofVec3f(x,y,0));
        }
    }

    void draw(){

        ofPushMatrix();
        ofTranslate(pos);
        if (is_clockwork == 0) {
            rotate_deg += rotate_speed;
        } else {
            rotate_deg -= rotate_speed;
        }
        ofRotate(rotate_deg);
        mesh.draw();
        ofPopMatrix();

        update();
    }

    //----------------------------------------
    void set_pos(ofVec3f pos_){pos = pos_;}
    void set_radius(float radius_){radius = radius_;}
    void set_width(float width_){width = width_;}
    void set_rotate_speed(float rotate_speed_){rotate_speed = rotate_speed_;}
    void set_deg_start(int deg_start_){deg_start = deg_start_;}
    void set_deg_end(int deg_end_){deg_end = deg_end_;}

    //----------------------------------------
    float get_radius(){return radius;}
    float get_width(){return width;}
    float get_rotate_speed(){return rotate_speed;}
    float get_rotate_deg(){return rotate_deg;}

    void update(){
        if (ofRandom(0,1) > 0.99){is_clockwork = 1 - is_clockwork;}
    }

private:

    ofMesh mesh;        //ringメッシュ

    ofVec3f pos;        //中心座標
    float radius;       //半径
    float width;        //リング幅
    int deg_start;      //リング開始角度
    int deg_end;        //リング終了角度
    float rotate_speed; //回転速度
    float rotate_deg;   //リング回転角度
    int is_clockwork;   //時計回り？(0:true 1:false)

    ofColor color;

};

#define MAX_RING_COUNT 30

ConsoleRing rings[MAX_RING_COUNT];
int ring_count;

//-----------------------------------------------------------
// リング初期化
//-----------------------------------------------------------
void init_ring(ofVec3f pos_){

    float t_width;

    float t_radius = 50;
    int min_width = 1;
    int max_width = 10;
    float min_speed = 0;
    float max_speed = 3;

    for (int i = 0; i < ring_count; i++)
    {
        rings[i].set_pos(ofVec3f(pos_));
        t_width = ofRandom(min_width,max_width);
        rings[i].set_width(t_width);
        rings[i].set_radius(t_radius);
        t_radius += t_width + 1;
        rings[i].set_rotate_speed(ofRandom(min_speed,max_speed));
        rings[i].set_deg_end(ofRandom(180,360));
        rings[i].make_ring();
    }
}

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(0);

    ring_count = 10;

    init_ring(ofVec3f(ofGetWidth() / 2 ,ofGetHeight() / 2,0));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    for (int i = 0; i < ring_count; i++)
    {
        rings[i].draw();

        ofDrawBitmapString(ofToString(rings[i].get_radius(),1),10,i * 15);
        ofDrawBitmapString(ofToString(rings[i].get_width(),1),100,i * 15);
        ofDrawBitmapString(ofToString(rings[i].get_rotate_deg(),1),200,i * 15);
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key==OF_KEY_UP){ ring_count++;}
    if (key==OF_KEY_DOWN){ ring_count--;}

    ring_count = ofClamp(ring_count,1,MAX_RING_COUNT - 1);
    init_ring(ofVec3f(mouseX,mouseY,0));
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
