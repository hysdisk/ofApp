#pragma once

#include "ofMain.h"

class d2Triangle : public ofBaseApp{

public:
    ofVec3f pos;
    ofMesh mesh;
    ofVboMesh vbomesh;

    float base_radius;
    float radius[3];
    ofVec3f p[3];
    ofColor color;

    d2Triangle(){}
    ~d2Triangle(){}

    void setup(){}

    void setup(ofVec3f pos_,float base_radius_){
        pos = pos_;
        base_radius = base_radius_;

        color.set(ofColor::fromHsb(ofRandom(0,255),255,255));
        init_mesh();

    }

    void draw(){
        ofPushMatrix();{
            ofTranslate(pos);
            //ofRotate(ofGetElapsedTimef() * 30,1,1,1);
            mesh.draw();

        }ofPopMatrix();
    }
    void update(){

        float px,py;
        float noise;

        for (int ipoint = 0; ipoint < 3; ipoint++) {

            noise = ofMap(ofNoise((1000 * ipoint) + ofGetElapsedTimef()),0,1,base_radius * 0.3,base_radius * 3);
            px = noise * cos(ofDegToRad(ipoint * 120));

            noise = ofMap(ofNoise((5000 * ipoint) + ofGetElapsedTimef()),0,1,base_radius * 0.3,base_radius * 3);
            py = noise * sin(ofDegToRad(ipoint * 120));

            p[ipoint].set(px,py,0);
            mesh.setVertex(ipoint,p[ipoint]);
        }
    }

    void init_mesh(){

        mesh.clear();

        float px,py;
        float r;

        for (int ipoint = 0; ipoint < 3; ipoint++)
        {
            r = ofRandom(base_radius / 2,base_radius * 2);
            px = r * cos(ofDegToRad(ipoint * 120));
            py = r * sin(ofDegToRad(ipoint * 120));

            p[ipoint].set(px,py,0);
            mesh.addColor(color);
            mesh.addVertex(p[ipoint]);
        }

    }
};

class resTest : public ofBaseApp{

public:

    ofIcoSpherePrimitive icosphere;
    ofSpherePrimitive sphere;
    ofBoxPrimitive box;

    int res;
    int size;
    int mode;
    ofVec3f pos;
    enum MODE{BOX,SPHERE,ICO};

    resTest(){}
    ~resTest(){}

    void setup(int size_,int res_,ofVec3f pos_){

        size = size_;
        res = res_;
        pos = pos_;

        icosphere.set(size,res);
        sphere.set(size,res);
        box.set(size,size,size,res,res,res);
    }

    void draw(){
        ofPushMatrix();{
            ofTranslate(pos);
            switch (mode)
            {
            case BOX:
                box.drawWireframe();
                for (int i = 0; i < box.getMesh().getNumVertices(); i++)
                {
                    ofDrawBitmapString(ofToString(i),box.getMesh().getVertex(i));
                }
                break;
            case SPHERE:
                sphere.drawWireframe();
                break;
            case ICO:
                icosphere.drawWireframe();
                break;
            default:
                break;
            }
        }ofPopMatrix();

    }

    void set_res(){

        switch (mode)
        {
        case BOX:
            box.set(size,size,size,res,res,res);
            break;
        case SPHERE:
            sphere.set(size,res);
            break;
        case ICO:
            icosphere.set(size,res);
            break;
        default:
            break;
        }
    }

    void incl_res(){
        res++;
        set_res();
    }

    void decl_res(){
        res--;
        set_res();
    }

};

class icoTriangle : public ofBaseApp{

public:

    ofIcoSpherePrimitive ico1;
    ofIcoSpherePrimitive ico2;

    vector<ofMeshFace> triangles1;
    vector<ofMeshFace> triangles2;

    ofMesh mesh1;
    ofMesh mesh2;
    ofMesh meshmix;

    ofVec3f pos;
    int size;
    int res;

    //==================================================================================

    icoTriangle(){}
    ~icoTriangle(){}

    //==================================================================================

    void setup(ofVec3f pos_,int size_,int res_){
        pos = pos_;
        size = size_;
        res = res_;

        init_mesh();    
    }

    void draw(){
        ofPushMatrix();{
            ofTranslate(pos);
            ofRotateY(ofGetElapsedTimef() * 20);
            meshmix.drawWireframe();


        }ofPopMatrix();
    }

    void update(){
    }

    //==================================================================================

private:

    void init_mesh(){

        mesh1.clear();
        mesh2.clear();

        ico1.set(size,res);
        ico2.set(size * 0.9,res);

        triangles1 = ico1.getMesh().getUniqueFaces();
        triangles2 = ico2.getMesh().getUniqueFaces();

        resize_triangles(triangles1,0.3);
        resize_triangles(triangles2,0.3);

        mesh1.setFromTriangles(triangles1);
        mesh2.setFromTriangles(triangles2);

        make_meshmix();
    }

    void resize_triangles(vector<ofMeshFace> &ptri,float multi){

        ofVec3f p[3];
        ofVec3f center_p;
        ofVec3f dest;

        for (int isize = 0; isize < ptri.size(); isize++){
            //中心点算出
            for (int ip = 0; ip < 3; ip++){
                p[ip] = ptri[isize].getVertex(ip);
            }
            center_p.average(p,3);

            //中心点に向かって移動
            for (int ip = 0; ip < 3; ip++) {
                dest = p[ip] - center_p;
                ptri[isize].setVertex(ip,p[ip] - (dest * multi));
            }
        }
    }

    void make_meshmix(){
        ofVec3f p1[3],p2[3];

        meshmix.clear();
        meshmix.setMode(OF_PRIMITIVE_TRIANGLES);

        for (int isize = 0; isize < triangles1.size(); isize++){

            for (int ip = 0; ip < 3; ip++) {
                p1[ip] = (triangles1[isize].getVertex(ip));
                p2[ip] = (triangles2[isize].getVertex(ip));
            }

            for (int ip = 0; ip < 3; ip++) {
                meshmix.addVertex(p1[ip]);
            }

            for (int ip = 0; ip < 3; ip++) {
                meshmix.addVertex(p2[ip]);
            }

            for (int ip = 0; ip < 3; ip++) {
                meshmix.addVertex(p1[ip]);
                meshmix.addVertex(p1[(ip+1)%3]);
                meshmix.addVertex(p2[ip]);

                meshmix.addVertex(p2[ip]);
                meshmix.addVertex(p2[(ip+1)%3]);
                meshmix.addVertex(p1[ip]);
            }
        }
    }


};

class ofApp : public ofBaseApp{

public:

    int w,h;
    d2Triangle d2t;
    resTest restest;
    icoTriangle icotri;

    ofLight light;
    ofMaterial material;
    ofEasyCam cam;

    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

};