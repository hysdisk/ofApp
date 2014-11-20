#pragma once
#include "ofMain.h"

class Particle{

public:

    ofPoint pos;
    ofPoint velocity;
    ofPoint direction;
    ofPoint desire;
    ofMesh  mesh;
    ofColor color;

    int p_num;
    int radius;
    float deg;
    float deg_speed;
    float force;
    bool isDead;

    enum draw_mode{POINT,TRIANGLE,RECT};

    //--------------------------------------------------------------
    Particle(ofPoint pos_){
        pos       = pos_;
        desire    = pos;
        p_num     = 4;
        radius    = 10;
        deg       = 45;
        deg_speed = 0;
        force     = 3.0;
        isDead    = false;
        velocity.set(0,0,0);
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
    void update_deg(int x_,int y_){

        float dist;

        dist = x_ - pos.x;
        deg_speed = ofMap(dist,-(ofGetWidth()/2),(ofGetWidth()/2),-10,10);
        deg+=deg_speed;
    }

    //--------------------------------------------------------------
    void update_direction(){

        ofPoint diff;

        diff = desire - pos;
        direction = diff.normalized();
        if (diff.length() <= 1){direction.set(0,0,0);}
    }

    //--------------------------------------------------------------
    void update_force(){

    }

    //--------------------------------------------------------------
    void update_velocity(){
        velocity = direction * force;
    }
    
    //--------------------------------------------------------------
    void update_pos(){
        update_force();
        update_direction();
        update_velocity();

        pos += velocity;
        check_pos_bounds();
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

    //--------------------------------------------------------------
    void check_pos_bounds(){
        if (pos.x > ofGetWidth()){velocity.x*=-1;}
        if (pos.x < 0){velocity.x*=-1;}
        if (pos.y > ofGetHeight()){velocity.y*=-1;}
        if (pos.y < 0){velocity.y*=-1;}
    }

};