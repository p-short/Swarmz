#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxMaxim.h"
#include "Agent.hpp"

class ofApp : public ofBaseApp{
    
public:
    void setup() override;
    void update() override;
    void draw() override;
    
    void keyPressed(int key) override;
    void keyReleased(int key) override;
    void mouseMoved(int x, int y ) override;
    void mouseDragged(int x, int y, int button) override;
    void mousePressed(int x, int y, int button) override;
    void mouseReleased(int x, int y, int button) override;
    void mouseEntered(int x, int y) override;
    void mouseExited(int x, int y) override;
    void windowResized(int w, int h) override;
    void dragEvent(ofDragInfo dragInfo) override;
    void gotMessage(ofMessage msg) override;
    
    //initalise ofSoudStream object so I can output sound
    ofSoundStream mySoundStream;
    void audioOut(ofSoundBuffer& output) override;
    
    //maxi sound objects
    maxiOsc sine0, sine1, sine2, sine3;
    maxiFilter filt0, filt1, filt2, filt3;
    
    //of gui objects
    ofxPanel gui;
    ofxFloatSlider noiseRadiusSlider;
    ofxFloatSlider ball0_speed_Slider;
    ofxFloatSlider ball1_speed_Slider;
    ofxFloatSlider ball2_speed_Slider;
    ofxFloatSlider ball3_speed_Slider;
    ofxFloatSlider pitchModSlider;
    ofxFloatSlider cuttoffSlider;
    ofxFloatSlider resoSlider;
    
    float t { 0 };
    
    //initalise agents!
    Agent b1;
    Agent b2;
    Agent b3;
    Agent b4;
};
