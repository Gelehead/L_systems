#ifndef NOISE_H
#define NOISE_H

#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <functional>
#include <fstream>
#include <iostream>
#include <string>

class noise {
public:
    int width, length;
    
    // Constructor
    noise(int w, int l);
    
    // Perlin noise generation functions
    std::vector<std::vector<double>> perlin(int featureSize);
    std::vector<std::vector<int>> perlinInt(int featureSize, int minVal = 0, int maxVal = 255);
    std::vector<std::vector<double>> perlinOctaves(int baseFeatureSize, int octaves, double persistence = 0.5);
    
    // PPM export functions
    bool exportToPPM(const std::vector<std::vector<double>>& noiseGrid, const std::string& filename);
    bool exportToColoredPPM(const std::vector<std::vector<double>>& noiseGrid, const std::string& filename);
    bool generateAndExportPPM(int featureSize, const std::string& filename, bool colored = false);
    bool generateAndExportOctavesPPM(int baseFeatureSize, int octaves, 
                                   double persistence, const std::string& filename, 
                                   bool colored = false);
                                   
private:
    // Helper methods
    std::vector<std::vector<std::vector<double>>> generateGradients(int gridWidth, int gridLength);
    double dotProduct(const std::vector<double>& g, const std::vector<double>& d);
    double fade(double t);
    double lerp(double a, double b, double t);
};

#endif // NOISE_H