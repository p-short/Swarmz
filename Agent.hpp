//
//  Agent.hpp
//  swarmz_courseworkOne
//
//  Created by Iansyst Loan on 07/03/2022.
//

#ifndef Agent_hpp
#define Agent_hpp

#include <stdio.h>
#include "ofMain.h"


//agent class
class Agent {
public:
    //public class methods
    void setNoiseIndex(float noiseIndexX, float noiseIndexY);
    void updateAgent(float speed, float diameter);
    void showAgent();
    float getXUniPolar();
    float getYUniPolar();
    float getXBiPolar();
    float getYBiPolar();
    
private:
    //private member variables
    float xInc;
    float yInc;
    float x;
    float y;
    float r;
    float agentR { 5 };
    float magVecA;
};


//Helper functions
struct Coord
{
    float x, y;
};
//helper functions explained in Agent.cpp
Coord returnCoord(float x_, float y_);
Coord returnVector(Coord v0, Coord v1);
float clampIt(float value, float min, float max);
float magnitude(Coord v);
float setRange(float val, float a, float b, float c, float d);
double* pan(double input, double x);

#endif /* Agent_hpp */
