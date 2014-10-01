#include "ofApp.h"

//=============================================================================
class Donuts{

public:

    Donuts()
    {
        enddeg = 0;
    }

    ~Donuts(){
        cout << "erase donuts" << endl;

    }

    void setup(ofPoint pos_,float startdeg_,float enddeg_,float r_outcircle_,float r_donuts_)
    {
        pos = pos_;
        r_outcircle = r_outcircle_;
        r_donuts    = r_donuts_;
        startdeg    = startdeg_;
        enddeg      = enddeg_;
    }


    void draw(){

        ofPath pathDonuts; 

        pathDonuts.setCircleResolution(64);

        pathDonuts.setStrokeWidth(0);  
        pathDonuts.setStrokeColor(ofColor(0,0,0,255));  
        pathDonuts.setFilled(true);  

        ofPushMatrix();
        ofTranslate(pos.x,pos.y);

        pathDonuts.arc(0,0,0,r_outcircle,r_outcircle,startdeg-90,enddeg-90);
        pathDonuts.close();

        pathDonuts.arc(0,0,0,r_donuts,r_donuts,startdeg-90,enddeg-90);
        pathDonuts.close();

        //pathDonuts.circle(0,0,r_donuts);
        //pathDonuts.close();

        pathDonuts.draw();
        //pathDonuts.clear();

        ofPopMatrix();

    }

    void update_pos(ofPoint pos_){
        pos = pos_;
    }

    void update_deg(float startdeg_,float degstep_){
        startdeg = startdeg_;
        enddeg += degstep_;
    }

    float get_deg(){
        return enddeg;
    }

private:

    ofPoint pos;
    float   startdeg;
    float   enddeg;
    float   r_outcircle;
    float   r_donuts;
};

//=============================================================================

vector <Donuts *> donuties;
float degstep;

//=============================================================================

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);
    ofSetFrameRate(60);

    degstep = 1;   

}

//--------------------------------------------------------------
void ofApp::update(){

    int donuts_size = donuties.size();

    for (int i = 0; i < donuts_size; i++)
    {
        donuties[i]->update_deg(0,degstep);

        if (donuties[i]->get_deg() >= 360)
        {
            delete donuties[i];
            donuts_size--;
            donuties.erase(donuties.begin()+i);

        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    for (int i = 0; i < donuties.size(); i++)
    {
        donuties[i]->draw();
    }

    ofDrawBitmapString(ofToString(donuties.size()),20,20);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == OF_KEY_RIGHT)
    {
        degstep++;
    }
    if (key == OF_KEY_LEFT)
    {
        degstep--;
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

    Donuts *donuts = new Donuts;
    ofPoint pos_(x,y);
    donuts->setup(pos_,0,0,50,40);
    donuties.push_back(donuts);  
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    Donuts *donuts = new Donuts;
    ofPoint pos_(x,y);
    donuts->setup(pos_,0,0,50,40);
    donuties.push_back(donuts);    
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
