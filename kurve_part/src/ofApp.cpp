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

        kurveWidth = 10;
    }

    ~Kurve(){
    }

    // ---------------------------------------------------

    ofColor kurveColor[9];
    ofMesh  kurveMesh[9];
    int   kurveDeg;

    int kurveWidth;

    enum Arrow{UP,RIGHT,DOWN,LEFT};

    // -----------------------------------------------------------------------------
    //  直線パーツ描画
    //------------------------------------------------------------------------------
    void draw_Straight(ofVec3f *basePosition,int step_,int distance_,int arrow_){

        ofVec3f drawPosition;
        float sx,sy;
        float wx,wy;

        for (int idist = 0; idist <= distance_ / step_; idist++)
        {
            //step単位の移動量計算
            sx = step_ * cos(ofDegToRad(arrow_));
            sy = step_ * sin(ofDegToRad(arrow_));

            //幅単位の移動量計算
            wx = kurveWidth * cos(ofDegToRad(arrow_-90));
            wy = kurveWidth * sin(ofDegToRad(arrow_-90));

            //描画ポイントに基準ポイントをセット + 1幅分ずらしとく
            drawPosition = *basePosition + ofVec3f(wx,wy,0);

            *basePosition+=ofVec3f(sx,sy,0);
            ofCircle(*basePosition,1);

            for (int ipart = 1; ipart <= 8; ipart++)
            {                
                //内径位置算出
                kurveMesh[ipart].addColor(kurveColor[ipart]);
                kurveMesh[ipart].addVertex(drawPosition);

                //外径位置算出
                drawPosition+=ofVec3f(wx,wy,0);
                kurveMesh[ipart].addColor(kurveColor[ipart]);
                kurveMesh[ipart].addVertex(drawPosition);
            }            
        }
        *basePosition-=ofVec3f(sx,sy,0);

        for (int i = 1 ; i <= 8; i++)
        {
            kurveMesh[i].draw();
            kurveMesh[i].clear();
        }
    }

    // -----------------------------------------------------------------------------
    //  曲線パーツ(右回り-->)描画
    //------------------------------------------------------------------------------
    void draw_rt(ofVec3f *basePosition,int step_,int startdeg_, int enddeg_){

        ofVec3f drawPosition;
        float x,y;

        for (int ideg = startdeg_ / step_; ideg <= enddeg_ / step_; ideg++)
        {
            x = kurveWidth * cos(ofDegToRad(ideg * step_));
            y = kurveWidth * sin(ofDegToRad(ideg * step_));

            drawPosition = *basePosition + ofVec3f(x,y,0);

            for (int ipart = 1; ipart <= 8; ipart++)
            {
                //内径位置セット
                kurveMesh[ipart].addColor(kurveColor[ipart]);
                kurveMesh[ipart].addVertex(drawPosition);

                //外径位置セット
                drawPosition+=ofVec3f(x,y,0);    
                kurveMesh[ipart].addColor(kurveColor[ipart]);
                kurveMesh[ipart].addVertex(drawPosition);
            }
        }

        kurveMesh[1].draw();
        kurveMesh[2].draw();
        kurveMesh[3].draw();
        kurveMesh[4].draw();
        kurveMesh[5].draw();
        kurveMesh[6].draw();
        kurveMesh[7].draw();
        kurveMesh[8].draw();

        for (int i = 1 ; i <= 8; i++)
        {
            kurveMesh[i].clear();
        }       
    }

    // -----------------------------------------------------------------------------
    //  曲線パーツ(左回り<--)描画
    //------------------------------------------------------------------------------
    void draw_lt(ofVec3f *basePosition,int step_,int startdeg_, int enddeg_){

        ofVec3f drawPosition;
        float x,y;

        for (int ideg = startdeg_ / step_; ideg >= enddeg_ / step_; ideg--)
        {
            x = kurveWidth * cos(ofDegToRad(ideg * step_));
            y = kurveWidth * sin(ofDegToRad(ideg * step_));

            drawPosition = *basePosition + ofVec3f(x,y,0);

            for (int ipart = 1; ipart <= 8; ipart++)
            {
                //内径位置セット
                kurveMesh[ipart].addColor(kurveColor[-(ipart-9)]);
                kurveMesh[ipart].addVertex(drawPosition);

                //外径位置セット
                drawPosition+=ofVec3f(x,y,0);    
                kurveMesh[ipart].addColor(kurveColor[-(ipart-9)]);
                kurveMesh[ipart].addVertex(drawPosition);
            }
        }

        kurveMesh[1].draw();
        kurveMesh[2].draw();
        kurveMesh[3].draw();
        kurveMesh[4].draw();
        kurveMesh[5].draw();
        kurveMesh[6].draw();
        kurveMesh[7].draw();
        kurveMesh[8].draw();

        for (int i = 1 ; i <= 8; i++)
        {
            kurveMesh[i].clear();

        }
    }

};

Kurve *kurve;
ofEasyCam cam;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(ofColor(61,44,78));
    glPointSize(3.0);

    kurve = new Kurve;

}

//--------------------------------------------------------------
void ofApp::update(){

}
void drawtest(){
    float x,y;
    float dx,dy;
    int deg;
    int width = 10;
    int step;

    ofVec3f gBasePotison,drawPosition1,drawPosition2;

    deg = 36;
    step = 10;
    int sec = ofGetElapsedTimef() * 10;
    sec %= 360;

    ofCircle(0,0,5);

    gBasePotison.set(0,0,0);


    for (int i = 0; i < 100; i+=step)
    {
        x = step * cos(ofDegToRad(deg));
        y = step * sin(ofDegToRad(deg));

        gBasePotison  += ofVec3f(x,y,0);
        drawPosition1 = gBasePotison;

        for (int j = 1; j <= 8; j++)
        {
            dx = width * cos(ofDegToRad(deg-90));
            dy = width * sin(ofDegToRad(deg-90));

            drawPosition1 += ofVec3f(dx,dy,0);
            drawPosition2 = drawPosition1 + ofVec3f(dx,dy,0);
            ofLine(drawPosition1,drawPosition2);                        
        }
    }
}
//--------------------------------------------------------------
void ofApp::draw(){

    ofVec3f basePositin;

    basePositin.set(0,0,0);

    ofPushMatrix();
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2);

    kurve->draw_rt(&basePositin,5,90,270);
    kurve->draw_Straight(&basePositin,5,100,0);
    kurve->draw_lt(&basePositin,5,90,-90);

    //kurve->draw_u(&basePositin,5,0,180);
    //kurve->draw_Straight(&basePositin,5,100,270);


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
