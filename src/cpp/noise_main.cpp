#include "noise.h"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    // Default parameters
    int width = 512;
    int height = 512;
    int featureSize = 64;
    int octaves = 6;
    double persistence = 0.5;
    std::string output_path = "perlin_terrain.ppm";
    bool colored = true;
    
    // Parse command line arguments
    if (argc > 1) width = atoi(argv[1]);
    if (argc > 2) height = atoi(argv[2]);
    if (argc > 3) featureSize = atoi(argv[3]);
    if (argc > 4) octaves = atoi(argv[4]);
    if (argc > 5) persistence = atof(argv[5]);
    if (argc > 6) output_path = argv[6];
    if (argc > 7) colored = (atoi(argv[7]) != 0);
    
    std::cout << "Generating Perlin noise with parameters:" << std::endl;
    std::cout << "  Width: " << width << std::endl;
    std::cout << "  Height: " << height << std::endl;
    std::cout << "  Feature size: " << featureSize << std::endl;
    std::cout << "  Octaves: " << octaves << std::endl;
    std::cout << "  Persistence: " << persistence << std::endl;
    std::cout << "  Output path: " << output_path << std::endl;
    std::cout << "  Colored: " << (colored ? "yes" : "no") << std::endl;
    
    // Create the noise generator
    noise noiseGen(width, height);
    
    // Generate and export noise
    auto result = noiseGen.generateAndExportOctavesPPM(featureSize, octaves, persistence, output_path, colored);
    
    if (result) {
        std::cout << "Noise generation successful. Output saved to " << output_path << std::endl;
    } else {
        std::cerr << "Error: Failed to generate or save noise map." << std::endl;
        return 1;
    }
    
    return 0;
}