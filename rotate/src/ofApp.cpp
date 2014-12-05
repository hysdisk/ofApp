#include "ofApp.h"
ofVboMesh mesh;
int px;
int py;
int pz;
int spacex;
int spacey;
int spacez;
int face_no;

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

}

void set_mesh_Sphere(){

    float mx,my,mz;
    float radx;
    float rz;

    mesh.clear();
    mesh.setMode(OF_PRIMITIVE_POINTS);
    glPointSize(3);

    //グリッド点作成
    for (int iz = 0; iz < pz; iz++) {
        for (int iy = 0; iy < py; iy++) {
            for (int ix = 0; ix < px; ix++) {

                radx = ofDegToRad(ofMap(ix,0,px,0,360));
                rz = sin(ofDegToRad(ofMap(iz,0,pz-1,0,180)));

                mx = ((rz) * ((iy+1) * 20)) * cos(radx);
                my = ((rz) * ((iy+1) * 20)) * sin(radx);

                mesh.addVertex(ofVec3f(mx,my, iz * 40));
            }
        }
    }




}

void set_mesh_Sphere_from_class(){

    mesh.clear();
    mesh.setMode(OF_PRIMITIVE_LINES);

    int size = 8;
    int point = 4;

    ofMesh mesh_ = ofMesh::sphere(300,size);

    for (int i = 0; i < mesh_.getNumVertices(); i++) {
        mesh.addVertex(mesh_.getVertex(i));
    }
    for (int i = point + ((size*2) * point); i < (point + ((size*2) * point)) + (size*2); i++) {
        mesh.addIndex(i);
        mesh.addIndex(i+1);
    }

}

void set_mesh_index_grid(){

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

void set_mesh_index_outline(){

    //mesh.clearIndices();

    int iP1[4] = {0,0,0,0};
    int iP2[4] = {0,0,0,0};
    int baseP[4];

    //         　  ０１２３
    //          　---------
    // １：0,0  ０|１□□２
    // ２：0,3　１|□□□□　　　　
    // ３：3,0　２|□□□□
    // ４：3,3　３|３□□４

    //x方向yz面
    //yz = (iy * py) + (iz * (py * pz)) 

    iP1[1] = py - 1;
    iP1[3] = py - 1;
    iP2[2] = pz - 1;
    iP2[3] = pz - 1;

    for (int i = 0; i < 4; i++){
        //baseP[i] = (iP1[i] * py) + (iP2[i] * (py * pz));
        baseP[i] = (iP1[i] * px) + (iP2[i] * (px * py));

        for (int ix = 0; ix < px - 1; ix++) {
            mesh.addIndex(baseP[i] + ix);
            mesh.addIndex(baseP[i] + (ix + 1));
        }
    }


    //y方向xz面
    //xz = ix + (iz * px * pz)
    iP1[1] = px - 1;
    iP1[3] = px - 1;
    iP2[2] = pz - 1;
    iP2[3] = pz - 1;

    for (int i = 0; i < 4; i++){
        baseP[i] = iP1[i] + (iP2[i] * px * py);

        for (int iy = 0; iy < py - 1; iy++) {
            mesh.addIndex(baseP[i] + (iy * px));
            mesh.addIndex(baseP[i] + px + (iy * px));
        }
    }

    //z方向xy面
    //xy = ix + (iy * px)
    iP1[1] = px - 1;
    iP1[3] = px - 1;
    iP2[2] = py - 1;
    iP2[3] = py - 1;

    for (int i = 0; i < 4; i++){
        baseP[i] = iP1[i] + (iP2[i] * px);

        for (int iz = 0; iz < pz - 1; iz++) {
            mesh.addIndex(baseP[i] + (iz * px * py));
            mesh.addIndex(baseP[i] + (px * py) + (iz * px * py));
        }
    }


}

void set_mesh_index_Zface(int face_no){

    int iPX[16];
    int iPY[16];

    //x方向
    for (int iy = 0; iy  < py; iy ++){
        iPY[iy] = (iy * px) + (face_no * px * py);

        for (int ix = 0; ix < px - 1; ix++) {
            mesh.addIndex(iPY[iy] + ix);
            mesh.addIndex(iPY[iy] + (ix + 1));
        }
    }

    //y方向
    for (int ix = 0; ix < px; ix++) {
        iPX[ix] =  ix + (face_no * px * py);

        for (int iy = 0; iy < py - 1; iy++) {
            mesh.addIndex(iPX[ix] + (iy * px));
            mesh.addIndex(iPX[ix] + px + (iy * px));
        }
    }
    set_mesh_index_outline(); 
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

    px = 4;
    py = 4;
    pz = 4;
    spacex = 20;
    spacey = 20;
    spacez = 20;

    face_no = 0;

    //set_mesh_grid_3d();
    //set_mesh_index_grid();

    //set_mesh_Sphere();
    set_mesh_Sphere_from_class();
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

        for (int i = 0; i < mesh.getNumVertices(); i++)
        {
            ofDrawBitmapString(ofToString(i), mesh.getVertex(i));
        }

    }ofPopMatrix();

    cam.end();

    ofDrawBitmapStringHighlight(ofToString(ofGetElapsedTimef()),10,10);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key=='p')
    {
        glPointSize(3);
        mesh.setMode(OF_PRIMITIVE_POINTS);
    }
    if (key=='l'){mesh.setMode(OF_PRIMITIVE_LINES); }
    if (key=='1'){
        mesh.clearIndices();
        set_mesh_index_grid(); 
    }
    if (key=='2'){
        mesh.clearIndices();
        set_mesh_index_outline(); 
    }
    if (key=='3'){
        face_no++;
        face_no%=pz;
        mesh.clearIndices();
        set_mesh_index_Zface(face_no); 
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
