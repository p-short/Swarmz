//
//  Agent.cpp
//  swarmz_courseworkOne
//
//  Created by Iansyst Loan on 07/03/2022.
//

#include "Agent.hpp"

//pass floating point numbers to initialise member variables
void Agent::setNoiseIndex(float noiseIndexX, float noiseIndexY)
{
    xInc = noiseIndexX;
    yInc = noiseIndexY;
}

//pass the speed and radius of the agents movments & initialise member variables
void Agent::updateAgent(float speed, float radius)
{
    r = radius;
    x = ofMap(ofNoise(xInc), 0, 1, -1, 1) * r;
    y = ofMap(ofNoise(yInc), 0, 1, -1, 1) * r;
    xInc += speed;
    yInc += speed;
}

//draw agent to the screen
void Agent::showAgent()
{
    //coord object that holds the position of the centre
    Coord centerPoint = returnCoord(0, 0);
    //coord object that holds the position of the agent
    Coord agentPosition = returnCoord(x, y);
    //works out the vector inbetween these two points
    Coord vecA = returnVector(agentPosition, centerPoint);
    //clamp the vectors magnitude so it cannot exceed a radius
    magVecA = clampIt(magnitude(vecA), 0, r / 2 - agentR);
    //use polar coordinates to draw the agent as an ellipse
    ofDrawEllipse(magVecA * cos(atan2(y, x)),
                  magVecA * sin(atan2(y, x)), agentR * 2, agentR * 2);
}

//return nomalized x values
float Agent::getXUniPolar()
{
    return setRange(magVecA * cos(atan2(y, x)), -200, 200, 0, 1);
}

//return nomalized y values
float Agent::getYUniPolar()
{
    return setRange(magVecA * sin(atan2(y, x)), -200, 200, 0, 1);
}

//returns x values inbetween the range of -1 and 1
float Agent::getXBiPolar()
{
    return setRange(magVecA * cos(atan2(y, x)), -200, 200, -1, 1);
}

//returns x values inbetween the range of -1 and 1
float Agent::getYBiPolar()
{
    return setRange(magVecA * sin(atan2(y, x)), -200, 200, -1, 1);
}

//---helper functions decleration---\\

//this function returns an object with an x and y position
Coord returnCoord(float x_, float y_)
{
    Coord coord_instance;
    coord_instance.x = x_;
    coord_instance.y = y_;
    return coord_instance;
}

//this function returns the vector between two Coord objects
Coord returnVector(Coord v0, Coord v1)
{
    Coord coord_instance;
    coord_instance.x = v1.x - v0.x;
    coord_instance.y = v1.y - v0.y;
    return coord_instance;
}

//helper function to clamp values between a range
float clampIt(float value, float min, float max)
{
    return std::min(std::max(value, min), max);
}

//function to get the magnitude of a vector
float magnitude(Coord v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

//this function takes an input and a range a to b then maps it to range c to d
float setRange(float value, float a, float b, float c, float d)
{
    value = (value - a) / (b - a);
    return c + value * (d - c);
}

//this function is for stereo panning, implemented by Benjamin Whateley
double* pan(double input, double x)
{
    double* chan;
    chan = new double[2];
    x *=  PI / 2;
    
    chan[0] = sin(x) * input;
    chan[1] = cos(x) * input;
    return chan;
};
