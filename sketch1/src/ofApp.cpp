#include "ofApp.h"

class MyObj
{
public:

    MyObj(){
        kurveColor[1] = ofColor(33,34,39);
        kurveColor[2] = ofColor(48,45,72);
        kurveColor[3] = ofColor(46,41,61);
        kurveColor[4] = ofColor(61,44,78);
        kurveColor[5] = ofColor(127,49,39);
        kurveColor[6] = ofColor(142,49,34);
        kurveColor[7] = ofColor(165,61,36);
        kurveColor[8] = ofColor(193,106,63);

        pos.set(0,0,0);
        deg = 0;
        color.set(255,255,255);
        isFill = false;
        mode = 3;

        kurve_width = 10;
        kurve_deg = 0;
        kurve_base_point = 3;
        kurve_color_mode = 0;

        size = kurve_width * 10;
    }
    ~MyObj(){}

    void draw(){
        switch (mode)
        {
        case RECT:
            draw_rect();
            break;
        case TRIANGLE:
            draw_triangle();
            break;
        case CIRCLE:
            draw_triangle();
            break;
        case KURVE:
            draw_kurve();
            break;
        default:
            break;
        }
    }

    void set_pos(ofVec3f pos_){

        int x,y;
        x = (size / 2)+(int)(pos_.x / size) * size;
        y = (size / 2)+(int)(pos_.y / size) * size;
        pos = ofVec3f(x,y,0);
    }

    void set_size(float size_){size = size_;}
    void set_color(ofColor color_){color = color_;}
    void set_mode(int mode_){mode = mode_;}

    void set_kurve_color_mode(int kurve_color_mode_){kurve_color_mode = kurve_color_mode_;}
    void set_kurve_base_point(int kurve_base_point_){kurve_base_point = kurve_base_point_;}
    void set_kurve_deg(int kurve_deg_){kurve_deg = kurve_deg_;}
    void set_kurve_width(float kurve_width_){kurve_width = kurve_width_;}

    int get_kurve_color_mode(){return kurve_color_mode;}
    int get_kurve_base_point(){return kurve_base_point;}



private:
    ofColor kurveColor[9];
    float kurve_deg;
    int kurve_base_point;
    float kurve_width;
    int kurve_color_mode;

    ofVec3f pos;
    float size;
    float deg;
    ofColor color;
    bool isFill;
    ofVec3f vpos3[3];
    int mode;
    enum {RECT,TRIANGLE,CIRCLE,KURVE};
    enum {LU,RU,RD,LD};

    void draw_rect(){

        if (isFill){
            ofFill();
        }
        else {
            ofNoFill();
        }

        ofSetColor(color);
        glLineWidth(2);
        ofRect(pos,size,size);
    }

    void draw_triangle(){

        vpos3[0].set(pos.x - (size / 2),pos.y - (size / 2),0);
        vpos3[1].set(pos.x - (size / 2),pos.y + (size / 2),0);
        vpos3[2].set(pos.x + (size / 2),pos.y + (size / 2),0);

        ofSetColor(color);
        ofTriangle(vpos3[0],vpos3[1],vpos3[2]);
    }

    void draw_kurve(){

        ofMesh mesh[9];
        ofVec3f draw_pos,base_pos;
        float wx,wy;

        switch (kurve_base_point) {
        case LU:
            base_pos.x = pos.x - (size / 2);
            base_pos.y = pos.y - (size / 2);
            break;
        case RU:
            base_pos.x = pos.x + (size / 2);
            base_pos.y = pos.y - (size / 2);
            break;
        case RD:
            base_pos.x = pos.x + (size / 2);
            base_pos.y = pos.y + (size / 2);
            break;
        case LD:
            base_pos.x = pos.x - (size / 2);
            base_pos.y = pos.y + (size / 2);
            break;
        default:
            break;
        }


        for (int ideg = kurve_deg; ideg <= kurve_deg+90; ideg+=3)
        {
            wx = kurve_width * cos(ofDegToRad(ideg-90));
            wy = kurve_width * sin(ofDegToRad(ideg-90));

            draw_pos = base_pos;
            draw_pos += ofVec3f(wx,wy,0);

            if (kurve_color_mode==0){
                for (int ipart = 1; ipart <= 8; ipart++)
                {
                    mesh[ipart].addColor(kurveColor[ipart]);
                    mesh[ipart].addVertex(draw_pos);

                    draw_pos += ofVec3f(wx,wy,0);
                    mesh[ipart].addColor(kurveColor[ipart]);
                    mesh[ipart].addVertex(draw_pos);
                }
            }
            if (kurve_color_mode==1){
                for (int ipart = 1; ipart <= 8; ipart++)
                {
                    mesh[ipart].addColor(kurveColor[-(ipart-9)]);
                    mesh[ipart].addVertex(draw_pos);

                    draw_pos += ofVec3f(wx,wy,0);
                    mesh[ipart].addColor(kurveColor[-(ipart-9)]);
                    mesh[ipart].addVertex(draw_pos);
                }
            }
        }

        for (int ipart = 1; ipart <= 8; ipart++)
        {
            mesh[ipart].setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
            mesh[ipart].draw();
        }
    }

};


MyObj myobj;
vector<MyObj *> myobjs;

float size;
float kurve_width;

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(0);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetCircleResolution(32);

    kurve_width = 10;
    size = kurve_width * 10;

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){


    myobj.set_pos(ofVec3f(mouseX,mouseY,0));
    myobj.set_size(size);
    myobj.draw();

    if (myobjs.size() > 0){
        for (int it = 0; it < myobjs.size(); it++)
        {
            myobjs[it]->draw();
        }
    }

    //   draw_grid(3);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    int kurvemode = myobj.get_kurve_base_point();

    switch (key){

    case 'q':
        kurvemode++;
        if (kurvemode == 4){kurvemode = 0;}
        break;
    case 'w':
        kurvemode--;
        if (kurvemode == -1){kurvemode = 3;}
        break;
    case 'a':
        myobj.set_kurve_color_mode(0);
        break;
    case 's':
        myobj.set_kurve_color_mode(1);
        break;

    case OF_KEY_UP:
        kurve_width++;
        myobj.set_kurve_width(kurve_width);
        size = kurve_width * 10;
        break;
    case OF_KEY_DOWN:
        kurve_width--;
        myobj.set_kurve_width(kurve_width);
        size = kurve_width * 10;
        break;
    default:
        break;
    }

    if (kurvemode == 0)    {
        myobj.set_kurve_base_point(0);
        myobj.set_kurve_deg(90);
    }
    if (kurvemode == 1)    {
        myobj.set_kurve_base_point(1);
        myobj.set_kurve_deg(180);
    }
    if (kurvemode == 2)    {
        myobj.set_kurve_base_point(2);
        myobj.set_kurve_deg(-90);
    }
    if (kurvemode == 3)    {
        myobj.set_kurve_base_point(3);
        myobj.set_kurve_deg(0);
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

    int it;

    myobjs.push_back(new MyObj());
    it = myobjs.size();
    *myobjs[it -1] = myobj;
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

//--------------------------------------------------------------
void ofApp::draw_grid(int mode){

    int gridX,gridY;
    int x,y;

    gridX = (ofGetWidth() / size) + 1;
    gridY = (ofGetHeight() / size) + 1;

    glLineWidth(0.5);


    for (int ix = 0; ix <= gridX; ix++)
    {
        ofLine(ix * size,0,ix * size,ofGetHeight());
    }
    for (int iy = 0; iy <= gridY; iy++)
    {
        ofLine(0,iy * size, ofGetWidth(),iy * size);
    }


    for (int iy = 0; iy < gridY; iy++)
    {
        for (int ix = 0; ix < gridX; ix++)
        {
            x = (size / 2)+ix * size;
            y = (size / 2)+iy * size;
            ofDrawBitmapString(ofToString(ix + (iy * gridX)),x,y);
        }
    }
}
