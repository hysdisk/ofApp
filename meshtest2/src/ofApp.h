#pragma once
#include "ofMain.h"
#include "Particle.h"
#include "ConsoleRing.h"

class ofApp : public ofBaseApp{

public:
    ofMesh mesh;
    int w,h;
    ofEasyCam cam;

    void setup();
    void update();
    void draw();

    vector<Particle *> parts;
    void setup_particle();
    void update_particle();
    void draw_particle();

    ofTrueTypeFont font;
    string text;
    void setup_font();
    void update_font();
    void draw_font();

    ConsoleRing *ring;


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
