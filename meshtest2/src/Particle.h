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

    int number;
    int p_num;
    int radius;
    float deg;
    float deg_speed;
    float direction_speed;
    float force;
    bool isDead;
    bool isMove;

    int d_mode;
    int m_mode;

    enum draw_mode{POINT,CIRCLE,RECT,MESH};
    enum move_mode{LINEAR,ATTRACT,DISTRACT };

    //--------------------------------------------------------------
    Particle(ofPoint pos_){
        pos       = pos_;
        desire    = pos;
        p_num     = 4;
        radius    = 10;
        deg       = 45;
        deg_speed = 0;
        direction_speed = 1.0;
        force     = 0.95;
        isDead    = false;
        isMove    = false;
        d_mode = CIRCLE;
        m_mode = ATTRACT;
        velocity.set(0,0,0);
        color.set(255,255,255,255);
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
        direction *= direction_speed;
    }

    //--------------------------------------------------------------
    void update_force(){

    }

    //--------------------------------------------------------------
    void update_velocity(){

        switch (m_mode)
        {
        case Particle::LINEAR:
            velocity *= force;
            break;
        case Particle::ATTRACT:
            update_force();
            update_direction();
            velocity = direction * force;
            break;
        case Particle::DISTRACT:
            update_force();
            update_direction();
            velocity = -(direction * force);
            break;
        default:
            break;
        }

        isMove = (velocity.length()==0) ? false : true;
    }

    //--------------------------------------------------------------
    void update_pos(){

        update_velocity();
        pos += velocity;
        check_pos_bounds();
    }

    //--------------------------------------------------------------
    void draw(){

        ofPushMatrix();{
            ofTranslate(pos);


            switch (d_mode)
            {
            case Particle::POINT:
                ofSetCircleResolution(3);
                ofFill();
                ofSetColor(color);
                ofCircle(0,0,0,1);
            case Particle::CIRCLE:
                ofSetCircleResolution(p_num);
                ofRotate(deg);
                ofNoFill();
                ofSetColor(color);
                ofCircle(0,0,0,radius);
                ofFill();
                ofDrawBitmapString(ofToString(number),0,0);
                break;
            case Particle::RECT:
                ofRotate(deg);
                ofNoFill();
                ofSetColor(color);
                ofRect(0,0,0,radius);
                ofFill();
                break;
            case Particle::MESH:
                mesh.draw();
                break;
            default:
                break;
            }

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