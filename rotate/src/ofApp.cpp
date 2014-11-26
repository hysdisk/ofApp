#include "ofApp.h"
ofVboMesh mesh;
int px;
int py;
int pz;
int spacex;
int spacey;
int spacez;
//--------------------------------------------------------------

void set_mesh_grid(){

    mesh.clear();
    mesh.setMode(OF_PRIMITIVE_POINTS);

    //グリッド点作成
    for (int iy = 0; iy < py; iy++) {
        for (int ix = 0; ix < px; ix++) {
            mesh.addVertex(ofVec3f(ix * spacex,iy * spacey, 0));   
        }
    }

    //グリッド線作成
    for (int iy = 0; iy < py; iy++) {
        for (int ix = 0; ix < px; ix++) {

            //横線
            if (ix < px -1) {
                mesh.addIndex(((iy*px) + ix));   
                mesh.addIndex(((iy*px) + ix) + 1);   
            }

            //縦線
            if (iy < py -1) {
                mesh.addIndex(((iy*px) + ix));   
                mesh.addIndex(((iy*px) + ix) + px);   
            }
        }
    }
}
void set_mesh_grid_3d(){

    mesh.clear();
    mesh.setMode(OF_PRIMITIVE_LINES);

    //グリッド点作成
    for (int iz = 0; iz < pz; iz++) {
        for (int iy = 0; iy < py; iy++) {
            for (int ix = 0; ix < px; ix++) {
                mesh.addVertex(ofVec3f(ix * spacex,iy * spacey, iz * spacez));   
            }
        }
    }

    //グリッド線作成
    for (int iz = 0; iz < pz; iz++) {
        for (int iy = 0; iy < py; iy++) {
            for (int ix = 0; ix < px; ix++) {
                //横線
                if (ix < px -1) {
                    mesh.addIndex(((iy * px) + ((px * py) * iz) + ix));   
                    mesh.addIndex(((iy * px) + ((px * py) * iz) + ix) + 1);   
                }

                //縦線
                if (iy < py -1) {
                    mesh.addIndex(((iy * px) + ((px * py) * iz) + ix));   
                    mesh.addIndex(((iy * px) + ((px * py) * iz) + ix) + px);   
                }
                //奥線
                if (iz < pz -1) {
                    mesh.addIndex(((iy * px) + ((px * py) * iz) + ix));   
                    mesh.addIndex(((iy * px) + ((px * py) * iz) + ix) + (px * py));   
                }
            }
        }
    }

    //x用yz面
    //yz = (iy * py) + (iz * (py * pz)) 

    //y用xz面
    //xz = ix + (iz * px * pz)

    //z用xy面
    //xy = ix + (iy * px)


}

void update_mesh_grid_index_3d(){

    mesh.clearIndices();

    //グリッド線作成
    for (int iz = 0; iz < pz; iz++) {
        for (int iy = 0; iy < py; iy++) {
            for (int ix = 0; ix < px; ix++) {
                //横線
                if (ix < px -1) {
                    mesh.addIndex(((iy * px) + ((px * py) * iz) + ix));   
                    mesh.addIndex(((iy * px) + ((px * py) * iz) + ix) + 1);   
                }

                //縦線
                if (iy < py -1) {
                    mesh.addIndex(((iy * px) + ((px * py) * iz) + ix));   
                    mesh.addIndex(((iy * px) + ((px * py) * iz) + ix) + px);   
                }
                //奥線
                if (iz < pz -1) {
                    mesh.addIndex(((iy * px) + ((px * py) * iz) + ix));   
                    mesh.addIndex(((iy * px) + ((px * py) * iz) + ix) + (px * py));   
                }
            }
        }
    }
}


void update_mesh_grid(float wave_deg){

    ofPoint pos;

    //グリッド点更新
    for (int iy = 0; iy < py; iy++) {
        for (int ix = 0; ix < px; ix++) {
            pos.x = ix * spacex;
            pos.y = iy * spacey;
            pos.z = 30 * sin(ofDegToRad(ofMap(ix+iy,0,px+py,0,360)+wave_deg));

            mesh.setVertex((iy*px) + ix,pos);
        }
    }
}
//--------------------------------------------------------------
void ofApp::setup(){

    ofSetRectMode(OF_RECTMODE_CENTER);

    ofBackground(ofColor::black);

    w = ofGetWidth();
    h = ofGetHeight();
    cw = w / 2;
    ch = h / 2;

    sine_deg = 0;

    px = 10;
    py = 10;
    pz = 10;
    spacex = 50;
    spacey = 50;
    spacez = 50;

    set_mesh_grid_3d();

}

//--------------------------------------------------------------
void ofApp::update(){
    //update_mesh_grid(ofGetElapsedTimef()*100);
}

void draw_sine_wave(float start_deg,float wave_deg){

    int wave_length = 300;
    int wave_height = 50;

    ofPoint dpos;

    for (int ideg = 0; ideg <= 360; ideg+=9)
    {
        dpos.x = ofMap(ideg,0,360,10,wave_length);
        dpos.y = 0;
        dpos.z = wave_height * sin(start_deg + (ofDegToRad(ideg)));

        //dpos.rotate(wave_deg,ofVec3f(0, 0, 1));

        ofNoFill();
        //ofCircle(dpos,3);
        ofRect(dpos,5,5);
    }

}



//--------------------------------------------------------------
void ofApp::draw(){

    cam.begin();
    ofPushMatrix();{
        //ofTranslate(cw,ch,0);
        //ofRotateY(ofGetElapsedTimef() * 10 );
        //for (int i = 0; i <= 360; i+=5){
        //    ofRotateZ(i);
        //    draw_sine_wave(ofGetElapsedTimef(),i);
        //}
        mesh.draw();
    }ofPopMatrix();

    cam.end();

    ofDrawBitmapStringHighlight(ofToString(ofGetElapsedTimef()),10,10);

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
