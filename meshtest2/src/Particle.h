#pragma once
#include "ofMain.h"

class Particle{

public:

    ofPoint pos;
    ofPoint accel;
    ofMesh mesh;
    ofColor color;

    int p_num;
    int radius;
    float deg;
    float deg_speed;

    enum draw_mode{POINT,TRIANGLE,RECT};

    //--------------------------------------------------------------
    Particle(ofPoint pos_){
        pos       = pos_;
        p_num     = 6;
        radius    = 10;
        deg       = 0;
        deg_speed = 0;
        accel.set(0,0,0);
        color.set(255,255,255,64);
    }
    //--------------------------------------------------------------
    ~Particle(){}

    //--------------------------------------------------------------
    void set_mesh(){

        ofPoint pmesh;
        int inc2,inc3,phase;
        vector<ofPoint> vp;
        float p_deg;

        mesh.clear();

        for (int i = 0; i < p_num; i++) {

            p_deg = ofDegToRad((deg + (i * (360 / p_num))));

            pmesh.x = radius * cos(p_deg);
            pmesh.y = radius * sin(p_deg);
            pmesh.z = 0;
            pmesh += pos;
            vp.push_back(pmesh);
            mesh.addVertex(pmesh);
        }

        for (int i = 0; i < vp.size(); i++) {
            phase = i / p_num;

            inc2 = ((i + 1) % p_num) + (phase * p_num);
            inc3 = ((i + 2) % p_num) + (phase * p_num);

            mesh.addIndex(i);
            mesh.addIndex(inc2);
            mesh.addIndex(inc3);
        }
    }

    //--------------------------------------------------------------
    void update_mesh(){
        float p_deg;
        ofPoint pmesh;

        for (int i = 0; i < p_num; i++) {

            p_deg = ofDegToRad((deg + (i * (360 / p_num))));

            pmesh.x = radius * cos(p_deg);
            pmesh.y = radius * sin(p_deg);
            pmesh.z = 0;
            pmesh += pos;
            mesh.setVertex(i,pmesh);
        }
    }

    //--------------------------------------------------------------
    void update_deg(){

        deg+=deg_speed;
    }

    //--------------------------------------------------------------
    void update_pos(){
        pos += accel;

        if (pos.x > ofGetWidth()){accel.x*=-1;}
        if (pos.x < 0){accel.x*=-1;}
        if (pos.y > ofGetHeight()){accel.y*=-1;}
        if (pos.y < 0){accel.y*=-1;}

    }

    //--------------------------------------------------------------
    void draw(){
        //mesh.drawWireframe();
        //path.draw();

        ofPushMatrix();{
            ofTranslate(pos);
            ofSetCircleResolution(p_num);
            ofRotate(deg);
            //ofNoFill();
            ofSetColor(color);
            ofCircle(0,0,0,radius);
            ofFill();
        }ofPopMatrix();
    }
};