#pragma once
#include "ofMain.h"

class Particle
{
public:
    ofVec3f pos;
    ofVec3f force;
    ofVec3f velocity;
    ofVec3f dest;
    ofColor color;
    ofVboMesh mesh;
    float radius;
    float speed;

    Particle(){
        velocity.set(0,0,0);
        force.set(0,0,0);
        radius = 1;
        speed = 2;
        color.set(255,255,255,255);
    }

    ~Particle(){}

    void setup(ofVec3f pos_){
        set_pos(pos_);
    }

    void setup(float posX_,float posY_,float posZ_){
        set_pos(posX_,posY_,posZ_);
    }

    void set_pos(ofVec3f pos_){
        pos = pos_;
    }
    void set_pos(float posX_,float posY_,float posZ_){
        pos.x = posX_;
        pos.y = posY_;
        pos.z = posZ_;
    }

    void set_velocity(ofVec3f velocity_){
        velocity = velocity_;
    }
    void set_velocity(float velX_,float velY_,float velZ_){
        velocity.x = velX_;
        velocity.y = velY_;
        velocity.z = velZ_;
    }

    void set_dest(ofVec3f dest_){
        dest = dest_;
    }

    void set_dest(float destX_,float destY_,float destZ_){
        dest.x = destX_;
        dest.y = destY_;
        dest.z = destZ_;
    }

    void set_velocity_dest(){
        ofVec3f diff;

        if (dest.length() != 0)
        {
            diff = dest - pos;
            velocity = diff.normalized() * speed;
            if (diff.length() < 1){velocity.set(0,0,0);}
        }

    }


    void add_force(ofVec3f force_){
    }

    void add_force(float forceX_,float forceY_,float forceZ_){
    }

    void update_pos(){
        pos += velocity + force;
    }

    void update_force(){
    }

    void reset_force(){
    }


    void update(){
        update_pos();
    }

    void draw(){
                
        ofRotateY(5);

        //ofSetColor(color);
        //ofCircle(pos,radius);

        ofNoFill();
        ofRect(pos,10,10);
        ofFill();
    }
    
private:
    
};

