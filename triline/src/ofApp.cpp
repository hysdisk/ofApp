#include "ofApp.h"

int diff_r;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofRectMode(OF_RECTMODE_CENTER);
    ofSetCircleResolution(64);

    diff_r=0;

}

//--------------------------------------------------------------
void ofApp::update(){

    diff_r = ofGetElapsedTimef() * 10;
    diff_r%=200;
}
void draw_bow_triange(){

    ofVec2f vp0;
    ofVec2f vp1,vp2,vp3;
    ofVec2f vp1s,vp1e;
    ofVec2f vp2s,vp2e;
    ofVec2f vp3s,vp3e;
    ofVec2f vpn12,vpn23,vpn31;
    ofVec2f vpmid12,vpmid23,vpmid31;
    int     dist12,dist23,dist31;
    float   deg12,deg23,deg31;
    int r_tri;
    float deg_tri;
    float x,y;

    ofVec2f vp[4];
    ofVec2f vps[4],vpe[4];
    ofVec2f vpn[4],vpmid[4];
    float dist[4],deg[4];

    float deg_;

    vp0.set(0,0);
    r_tri   = 100;
    deg_tri = -90;

    //各頂点(基準点)計算
    x = r_tri * cos(ofDegToRad(deg_tri));
    y = r_tri * sin(ofDegToRad(deg_tri));
    vp1.set(x,y);

    x = r_tri * cos(ofDegToRad(deg_tri+120));
    y = r_tri * sin(ofDegToRad(deg_tri+120));
    vp2.set(x,y);

    x = r_tri * cos(ofDegToRad(deg_tri-120));
    y = r_tri * sin(ofDegToRad(deg_tri-120));
    vp3.set(x,y);

    //２点間距離
    dist12 = vp1.distance(vp2);
    dist23 = vp2.distance(vp3);
    dist31 = vp3.distance(vp1);

    //２点間中間点
    vpmid12 = vp1.getMiddle(vp2);
    vpmid23 = vp2.getMiddle(vp3);
    vpmid31 = vp3.getMiddle(vp1);

    //２点間角度
    deg12 = ofRadToDeg(atan2(vp2.y - vp1.y,vp2.x - vp1.x));
    deg23 = ofRadToDeg(atan2(vp3.y - vp2.y,vp3.x - vp2.x));
    deg31 = ofRadToDeg(atan2(vp1.y - vp3.y,vp1.x - vp3.x));

    //２点間ベクトル算出
    x = cos(ofDegToRad(deg12));
    y = sin(ofDegToRad(deg12));
    vpn12.set(x,y);

    x = cos(ofDegToRad(deg23));
    y = sin(ofDegToRad(deg23));
    vpn23.set(x,y);

    x = cos(ofDegToRad(deg31));
    y = sin(ofDegToRad(deg31));
    vpn31.set(x,y);

    vp1s = vpmid12 - (vpn12 * diff_r);
    vp1e = vpmid12 + (vpn12 * diff_r);
    vp2s = vpmid23 - (vpn23 * diff_r);
    vp2e = vpmid23 + (vpn23 * diff_r);
    vp3s = vpmid31 - (vpn31 * diff_r);
    vp3e = vpmid31 + (vpn31 * diff_r);

    ofDrawBitmapString("vp1s",vp1s);
    ofDrawBitmapString("vp1e",vp1e);
    ofDrawBitmapString("vp2s",vp2s);
    ofDrawBitmapString("vp2e",vp2e);
    ofDrawBitmapString("vp3s",vp3s);
    ofDrawBitmapString("vp3e",vp3e);

    ofNoFill();
    ofCircle(vp0,10);
    ofCircle(vp0,r_tri);

    ofLine(vp1s,vp1e);
    ofLine(vp2s,vp2e);
    ofLine(vp3s,vp3e);

}

void draw_bow_polygon(int poly){

#define POLY_MAX 13

    float x,y;
    ofVec2f vp[POLY_MAX];
    ofVec2f vps[POLY_MAX],vpe[POLY_MAX];
    ofVec2f vpnormal[POLY_MAX],vpmiddle[POLY_MAX];
    float deg[POLY_MAX],dist[POLY_MAX];
    float r_poly;
    int deg_split;

    r_poly = 100;
    vp[0].set(0,0);

    deg_split = 360 / poly;

    for (int ipoly = 1; ipoly <= poly; ipoly++)
    {
        //基準頂点算出
        x = r_poly * cos(ofDegToRad((ipoly -1) * deg_split));
        y = r_poly * sin(ofDegToRad((ipoly -1) * deg_split));
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

    for (int i = 1; i <= poly; i++)
    {
        vps[i] = vp[i];
        vpe[i] = vp[i] + (vpnormal[i] * 300);
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

    draw_bow_polygon(8);

    ofPopMatrix();


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
