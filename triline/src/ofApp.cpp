#include "ofApp.h"

int g_count;
float g_scale_start;
float g_scale_end;
float g_r_poly;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofRectMode(OF_RECTMODE_CENTER);
    ofSetCircleResolution(64);
    glLineWidth(3.0);
    
    g_count       = 8;
    g_r_poly      = 100;
    g_scale_start = 0;
    g_scale_end   = 1;

}

//--------------------------------------------------------------
void ofApp::update(){

}

void draw_burr_polygon(int poly,float r_poly,float s_scale,float e_scale){

#define POLY_MAX 37

    float x,y;
    ofVec2f vp[POLY_MAX];
    ofVec2f vps[POLY_MAX],vpe[POLY_MAX];
    ofVec2f vpnormal[POLY_MAX],vpmiddle[POLY_MAX];
    float deg[POLY_MAX],dist[POLY_MAX];
    int deg_split;

    r_poly = 100;
    vp[0].set(0,0);

    deg_split = 360 / poly;

    for (int ipoly = 1; ipoly <= poly; ipoly++)
    {
        //基準頂点算出
        x = r_poly * cos(ofDegToRad( (ipoly -1) * deg_split ));
        y = r_poly * sin(ofDegToRad( (ipoly -1) * deg_split ));
        vp[ipoly].set(x,y);
    }

    for (int i = 1; i <= poly; i++)
    {
        //次点との角度算出
        deg[i] = ofRadToDeg(atan2(vp[(i%poly)+1].y - vp[i].y,
                                  vp[(i%poly)+1].x - vp[i].x));

        //次点までの距離算出
        dist[i]     = vp[i].distance(vp[(i%poly)+1]);

        //次点間の中間点算出
        vpmiddle[i] = vp[i].getMiddle(vp[(i%poly)+1]);

        //次点までのベクトル算出
        x = cos(ofDegToRad(deg[i]));
        y = sin(ofDegToRad(deg[i]));
        vpnormal[i].set(x,y);
    }

    //始点、終点距離の倍率を引数で指定
    for (int i = 1; i <= poly; i++)
    {
        vps[i] = vp[i] + (vpnormal[i] * (dist[i]*s_scale));
        vpe[i] = vp[i] + (vpnormal[i] * (dist[i]*e_scale));
    }

    for (int i = 1; i <= poly; i++)
    {
        ofLine(vps[i],vpe[i]);
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofPushMatrix();
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2);

    //draw_burr_polygon(g_count,g_scale_start,g_scale_end);
    draw_burr_polygon(g_count,0.1,0.9);

    ofPopMatrix();    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key==OF_KEY_UP)
    {
        g_count++;
    }
    if (key==OF_KEY_DOWN)
    {
        g_count--;
    }
    if (key==OF_KEY_RIGHT)
    {
        g_scale_end+=0.1;
    }
    if (key==OF_KEY_LEFT)
    {
        g_scale_end-=0.1;
    }

    g_count = ofClamp(g_count,3,36);


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
