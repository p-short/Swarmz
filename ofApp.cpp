#include "ofApp.h"
#include <iostream>

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    //set up gui objects
    gui.setup();
    //adding and setting up gui elements
    gui.add(noiseRadiusSlider.setup("Noise Radius", 25, 25, 400));
    //ball speed sliders
    gui.add(ball0_speed_Slider.setup("Ball One Speed", 0.01, 0, 0.05));
    gui.add(ball1_speed_Slider.setup("Ball Two Speed", 0.01, 0, 0.05));
    gui.add(ball2_speed_Slider.setup("Ball Three Speed", 0.01, 0, 0.05));
    gui.add(ball3_speed_Slider.setup("Ball Four Speed", 0.01, 0, 0.05));
    //param sliders
    gui.add(pitchModSlider.setup("Pitch modulation", 2, 0, 100));
    gui.add(cuttoffSlider.setup("Filter cutoff", 600, 100, 2000));
    gui.add(resoSlider.setup("Filter resonance", 0.5, 0, 9.9));
    
    //randomly seeding the noise function inside the Agent class
    //this is so each agent is seeded with a unique seed value and dosent follow the same trajectory
    b1.setNoiseIndex(ofRandom(0, 5), ofRandom(0, 5));
    b2.setNoiseIndex(ofRandom(0, 5), ofRandom(0, 5));
    b3.setNoiseIndex(ofRandom(0, 5), ofRandom(0, 5));
    b4.setNoiseIndex(ofRandom(0, 5), ofRandom(0, 5));
    
    //sound set up
    int sampleRate = 44100;
    int bufferSize = 512;
    
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = bufferSize;
    mySoundStream.setup(settings);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //updating speed and noise radius by passing the slider values to the updateAgent function
    b1.updateAgent(ball0_speed_Slider, noiseRadiusSlider);
    b2.updateAgent(ball1_speed_Slider, noiseRadiusSlider);
    b3.updateAgent(ball2_speed_Slider, noiseRadiusSlider);
    b4.updateAgent(ball3_speed_Slider, noiseRadiusSlider);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //translate to middle of canvas
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    
    //draw Agent class instances
    ofFill();
    ofSetColor(255, 255, 255, 155);
    b1.showAgent();
    b2.showAgent();
    b3.showAgent();
    b4.showAgent();
    
    //drawing border circle
    ofNoFill();
    ofSetColor(255, 255, 255, 90);
    ofDrawEllipse(0, 0, noiseRadiusSlider, noiseRadiusSlider);
    
    //translate back to 0,0 to draw gui and write text
    ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2);
    gui.draw();
    ofSetColor(255);
    ofDrawBitmapString(" .d8888b.                                                        \nd88P  Y88b                                                       \nY88b.                                                            \n .Y888b.   888  888  888  8888b.  888d888 88888b.d88b.  88888888 \n    .Y88b. 888  888  888     .88b 888P.   888 .888 .88b    d88P   \nY88b  d88P Y88b 888 d88P 888  888 888     888  888  888  d88P    \n .Y8888P.   .Y8888888P.  .Y888888 888     888  888  888 88888888 \n\nEach Agent is an oscillator\nagent position on x axis = pan & filter cutoff\nagent position on y axis = pitch modulation & filter resonance", ofGetWidth() / 2 - 60, 30);
}

//audioOut function to handle outputed sound
void ofApp::audioOut(ofSoundBuffer& output)
{
    //loop through each sample and write into buffer
    std::size_t outChans = output.getNumChannels();
    for (int i = 0; i < output.getNumFrames(); ++i)
    {
        std::size_t currentIndex = i * outChans;
        
        //X axis = pan & filter cutoff
        //Y axis = pitch modulation & filter resonance
        
        /*
        4 saw wave oscillators all at the note of 'A' when an agent moves on the x axis it effects the pan and filter cutoff of that particular note, the agents position on the y axis also controlls pitch modulation and the filter resonance.
        */
        
        float inOne = 0.25 * filt0.lores(sine0.saw(440 + pitchModSlider * b1.getYUniPolar()), cuttoffSlider * b1.getXUniPolar(), resoSlider * b1.getYUniPolar());
        
        float inTwo = 0.25 * filt1.lores(sine1.saw(440 + pitchModSlider * b2.getYUniPolar()), cuttoffSlider * b2.getXUniPolar(), resoSlider * b2.getYUniPolar());
        
        float inThree = 0.25 * filt2.lores(sine2.saw(440 + pitchModSlider * b3.getYUniPolar()), cuttoffSlider * b3.getXUniPolar(), resoSlider * b3.getYUniPolar());
        
        float inFour = 0.25 * filt3.lores(sine3.saw(440 + pitchModSlider * b4.getYUniPolar()), cuttoffSlider * b4.getXUniPolar(), resoSlider * b4.getYUniPolar());
        
        /*
         the four floating point values representing the signal are then passed in to the panning function, the x position of each agent is then used to affect the pan
         */
         
        double* newOut1 = pan(inOne, b1.getXUniPolar());
        double* newOut2 = pan(inTwo, b2.getXUniPolar());
        double* newOut3 = pan(inThree, b3.getXUniPolar());
        double* newOut4 = pan(inFour, b4.getXUniPolar());
       
        //sum the output to each channel
        output[currentIndex] = newOut1[0] + newOut2[0] +
                               newOut3[0] + newOut4[0];
        
        output[currentIndex + 1] = newOut1[1] + newOut2[1] +
                                   newOut3[1] + newOut4[1];
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
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
