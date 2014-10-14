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
//            kurveMesh[i].setMode(OF_PRIMITIVE_POINTS);
        }

        kurveWidth = 20;
        
        baseDeg = 0;
        basePosition.set(0,0,0);
        basePosition_out.set(0,0,0);
    }

    ~Kurve(){
    }

    // ---------------------------------------------------

    ofColor kurveColor[9];
    ofMesh  kurveMesh[9];
    int   kurveDeg;
    
    ofVec3f basePosition;
    ofVec3f basePosition_out;
    int baseDeg;

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
                //内径位置算出
                kurveMesh[ipart].addColor(kurveColor[ipart]);
                kurveMesh[ipart].addVertex(drawPosition);

                //外径位置算出
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
        float dx,dy;
        
        dx = 10 * kurveWidth * cos(ofDegToRad(enddeg_));
        dy = 10 * kurveWidth * sin(ofDegToRad(enddeg_));
       
        *basePosition+=ofVec3f(dx,dy,0);

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

        *basePosition+=ofVec3f(dx,dy,0);

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
        ofCircle(*basePosition, 5);
    }
    
    // -----------------------------------------------------------------------------
    //
    // -----------------------------------------------------------------------------
    void add_vertex(int step_,int deg_){
        
        ofVec3f drawPosition;
        ofVec3f tempPosition;
        
        int drawDeg;
        float sx,sy;
        float wx,wy;
        float outx,outy;
        
        drawDeg = baseDeg+deg_;

        //幅分ベクトル計算 進行方向に対して基準点から左方向(-90)に展開
        wx = kurveWidth * cos(ofDegToRad(drawDeg-90));
        wy = kurveWidth * sin(ofDegToRad(drawDeg-90));
        
        //最外径ベクトル計算
        outx = 10 * kurveWidth * cos(ofDegToRad(drawDeg-90));
        outy = 10 * kurveWidth * sin(ofDegToRad(drawDeg-90));
        
        //直進時 ----------------------------------------------------------
        if (drawDeg == baseDeg) {
        
            //直進速度分のベクトル計算
            sx = step_ * cos(ofDegToRad(drawDeg));
            sy = step_ * sin(ofDegToRad(drawDeg));
            
            //基準ポイント更新
            basePosition+=ofVec3f(sx,sy,0);
            
            //最外径ポイント更新
            basePosition_out = basePosition + ofVec3f(outx,outy,0);
        }
        
        //右回り時 ----------------------------------------------------------
        if (drawDeg > baseDeg) {
        
            //最外径ポイント更新
            basePosition_out = basePosition + ofVec3f(outx,outy,0);
  
            //基準角度更新
            baseDeg = drawDeg;
        }
        
        //左回り時 ----------------------------------------------------------
        if (drawDeg < baseDeg) {
        
            //最外径ポイントから左回り用基準点を算出
            outx = 10 * kurveWidth * cos(ofDegToRad(drawDeg+90));
            outy = 10 * kurveWidth * sin(ofDegToRad(drawDeg+90));
            basePosition = basePosition_out + ofVec3f(outx,outy,0);
            
            baseDeg = drawDeg;
            
            //幅分ベクトル計算 進行方向に対して右方向(+90)に展開
            wx = kurveWidth * cos(ofDegToRad(drawDeg+90));
            wy = kurveWidth * sin(ofDegToRad(drawDeg+90));
            
            //最外径から減算するために符号反転
            wx = -wx;
            wy = -wy;
        }
        
        //描画位置に基準ポイントをセット
        drawPosition = basePosition;
        
        //最内径分ずらす
        drawPosition+=ofVec3f(wx,wy,0);
        
        for (int ipart = 1; ipart <= 8; ipart++)
        {
            //内径位置セット
            kurveMesh[ipart].addColor(kurveColor[ipart]);
            kurveMesh[ipart].addVertex(drawPosition);
            
            //外径位置セット
            drawPosition+=ofVec3f(wx,wy,0);
            kurveMesh[ipart].addColor(kurveColor[ipart]);
            kurveMesh[ipart].addVertex(drawPosition);
        }
    
    }
    
    void draw(){
        
        ofSetColor(ofColor::white);
        ofCircle(basePosition, 2);
        ofSetColor(ofColor::red);
        ofCircle(basePosition_out, 2);
        
        kurveMesh[1].draw();
        kurveMesh[2].draw();
        kurveMesh[3].draw();
        kurveMesh[4].draw();
        kurveMesh[5].draw();
        kurveMesh[6].draw();
        kurveMesh[7].draw();
        kurveMesh[8].draw();
        
        ofDrawBitmapString(ofToString(baseDeg), 0,0);

    }
    
    void clear(){
        for (int i = 1; i <= 8; i++) {
            kurveMesh[i].clear();
        }
    }

};

Kurve *kurve;
ofEasyCam cam;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(ofColor(61,44,78));
    glPointSize(10.0);

    kurve = new Kurve;

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushMatrix();
    ofTranslate(mouseX,mouseY);
    kurve->draw();
    ofPopMatrix();



}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key==OF_KEY_UP) {
        kurve->add_vertex(5, 0);
    }
    if (key==OF_KEY_RIGHT) {
        kurve->add_vertex(5, 5);
    }
    if (key==OF_KEY_LEFT) {
        kurve->add_vertex(5, -5);
    }
    if (key=='c'){
        kurve->clear();
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
