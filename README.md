# Swarmz

Interactive audio-visual piece written in c++ using oFx and Maximilian libraries, Four agents are drawn to the screen each agent has an equivalent
sawtooth wave oscillating at 440 Hz "A4", their positions are randomly seeded and are determined by the oFx Perlin noise algorithm.
As they move around the center of the screen their position on the x axis affect the pan and filter cutoff, while their position on the y axis
affects the pitch modulation and resonance of a low pass filter.

The piece is interactive, you can use the gui sliders to change each agents speed and the overall radius of their trajectory, you can also change
the the frequency of filter cutoff and resonance and increase / decrease the level of pitch modulation. 

As the agents move round each over they creates interesting variable dissonant drones.


