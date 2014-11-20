#pragma once
#include "ofMain.h"

class ConsoleRing{

public:

    ofPoint pos;
    float radius;
    float deg_start;
    float deg_end;
    ofColor color;
    float rotate_speed;
    float rotate_deg;
    float line_width;
    ofMesh mesh;

    ConsoleRing(ofPoint pos_){
        pos = pos_;
        radius = 100;
        line_width = 30;
        deg_start = 0;
        deg_end = 300;
        rotate_speed = 1.0;
        rotate_deg = 0;
        color.set(ofColor::green);

    }

    ~ConsoleRing(){}

    void setup(){
    }

    void  set_ring(){

        float x,y;
        mesh.clear();
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        for (int ideg = deg_start; ideg < deg_end; ideg +=9)
        {
            x = radius * cos(ofDegToRad(ideg));
            y = radius * sin(ofDegToRad(ideg));
            mesh.addColor(color);
            mesh.addVertex(ofPoint(x,y,0));
            x = (radius + line_width) * cos(ofDegToRad(ideg));
            y = (radius + line_width) * sin(ofDegToRad(ideg));
            mesh.addColor(color);
            mesh.addVertex(ofPoint(x,y,0));
        }

    }

    void update(){
        rotate_deg+=rotate_speed;
    }

    void draw(){
        ofPushMatrix();{
            ofTranslate(pos);
            ofSetColor(color);
            ofRotate(rotate_deg);
            mesh.draw();
        }ofPopMatrix();
    }




};