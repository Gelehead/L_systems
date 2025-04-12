#include "noise.h"
#include <cmath>
#include <random>
#include <algorithm>
#include <fstream>
#include <iostream>

// Constructor
noise::noise(int w, int l) : width(w), length(l) {}

// Generates a 2D Perlin noise map
std::vector<std::vector<double>> noise::perlin(int featureSize) {
    // Get grid dimension depending on feature size
    int grid_width = (width / featureSize) + 1;  // +1 to handle edge cases
    int grid_length = (length / featureSize) + 1;

    // Initialize final noise grid with doubles (better for noise values)
    std::vector<std::vector<double>> noise_grid(length, std::vector<double>(width, 0.0));

    // Generate random gradient vectors
    auto gradients = generateGradients(grid_width, grid_length);
    
    // For each pixel in the output
    for (int y = 0; y < length; ++y) {
        for (int x = 0; x < width; ++x) {
            // Determine grid cell coordinates
            int grid_x = x / featureSize;
            int grid_y = y / featureSize;
            
            // Calculate position within the grid cell (0.0 to 1.0)
            double cell_x = (double)(x % featureSize) / featureSize;
            double cell_y = (double)(y % featureSize) / featureSize;
            
            // Get the four corners of the grid cell
            std::vector<double> p00 = {gradients[0][grid_y][grid_x], gradients[1][grid_y][grid_x]};
            std::vector<double> p10 = {gradients[0][grid_y][grid_x + 1], gradients[1][grid_y][grid_x + 1]};
            std::vector<double> p01 = {gradients[0][grid_y + 1][grid_x], gradients[1][grid_y + 1][grid_x]};
            std::vector<double> p11 = {gradients[0][grid_y + 1][grid_x + 1], gradients[1][grid_y + 1][grid_x + 1]};
            
            // Calculate dot products between gradients and distance vectors
            double v00 = dotProduct(p00, {cell_x, cell_y});
            double v10 = dotProduct(p10, {cell_x - 1.0, cell_y});
            double v01 = dotProduct(p01, {cell_x, cell_y - 1.0});
            double v11 = dotProduct(p11, {cell_x - 1.0, cell_y - 1.0});
            
            // Apply smooth interpolation (using fade function)
            double fx = fade(cell_x);
            double fy = fade(cell_y);
            
            // Bilinear interpolation
            double top = lerp(v00, v10, fx);
            double bottom = lerp(v01, v11, fx);
            double value = lerp(top, bottom, fy);
            
            // Scale to [0, 1] range and store
            noise_grid[y][x] = (value + 1.0) * 0.5;
        }
    }
    
    return noise_grid;
}

// Overloaded function to return integer values if needed
std::vector<std::vector<int>> noise::perlinInt(int featureSize, int minVal, int maxVal) {
    auto doubleGrid = perlin(featureSize);
    std::vector<std::vector<int>> intGrid(length, std::vector<int>(width));
    
    for (int y = 0; y < length; ++y) {
        for (int x = 0; x < width; ++x) {
            intGrid[y][x] = static_cast<int>(doubleGrid[y][x] * (maxVal - minVal) + minVal);
        }
    }
    
    return intGrid;
}

// Generate multi-octave Perlin noise for more natural-looking results
std::vector<std::vector<double>> noise::perlinOctaves(int baseFeatureSize, int octaves, double persistence) {
    std::vector<std::vector<double>> result(length, std::vector<double>(width, 0.0));
    
    double amplitude = 1.0;
    double totalAmplitude = 0.0;
    
    // Sum multiple noise layers with decreasing amplitude
    for (int o = 0; o < octaves; ++o) {
        // Feature size decreases with each octave (higher frequency)
        int featureSize = baseFeatureSize / std::pow(2, o);
        if (featureSize < 1) featureSize = 1;
        
        auto octaveNoise = perlin(featureSize);
        
        for (int y = 0; y < length; ++y) {
            for (int x = 0; x < width; ++x) {
                result[y][x] += octaveNoise[y][x] * amplitude;
            }
        }
        
        totalAmplitude += amplitude;
        amplitude *= persistence;
    }
    
    // Normalize result
    for (int y = 0; y < length; ++y) {
        for (int x = 0; x < width; ++x) {
            result[y][x] /= totalAmplitude;
        }
    }
    
    return result;
}

// Function to export noise as a grayscale PPM file
bool noise::exportToPPM(const std::vector<std::vector<double>>& noiseGrid, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return false;
    }
    
    // PPM header (P3 format - ASCII RGB)
    file << "P3\n";
    // Add comment with generation info
    file << "# Perlin noise generated image\n";
    // Width and height
    file << width << " " << length << "\n";
    // Maximum color value
    file << "255\n";
    
    // Write pixel data
    for (int y = 0; y < length; ++y) {
        for (int x = 0; x < width; ++x) {
            // Convert noise value [0,1] to grayscale [0,255]
            int pixelValue = static_cast<int>(std::clamp(noiseGrid[y][x] * 255.0, 0.0, 255.0));
            // Write as RGB (same value for grayscale)
            file << pixelValue << " " << pixelValue << " " << pixelValue << " ";
        }
        file << "\n"; // End of row
    }
    
    file.close();
    return true;
}

// Function to export noise as a colored height map PPM
bool noise::exportToColoredPPM(const std::vector<std::vector<double>>& noiseGrid, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return false;
    }
    
    // PPM header
    file << "P3\n";
    file << "# Perlin noise colored height map\n";
    file << width << " " << length << "\n";
    file << "255\n";
    
    // Define height map colors (from deep blue to white)
    struct Color { int r, g, b; };
    std::vector<Color> colorMap = {
        {0, 0, 128},    // Deep water (deep blue)
        {0, 0, 255},    // Water (blue)
        {0, 128, 255},  // Shallow water (light blue)
        {240, 240, 64}, // Sand (yellow)
        {32, 160, 0},   // Grass (green)
        {224, 224, 0},  // Hills (yellow-green)
        {128, 128, 128},// Mountain (gray)
        {255, 255, 255} // Snow peaks (white)
    };
    
    // Write pixel data with color mapping
    for (int y = 0; y < length; ++y) {
        for (int x = 0; x < width; ++x) {
            double value = noiseGrid[y][x];
            
            // Map the noise value to a color
            int colorIndex = static_cast<int>(value * (colorMap.size() - 1));
            
            // Ensure index is in bounds
            colorIndex = std::clamp(colorIndex, 0, static_cast<int>(colorMap.size()) - 2);
            
            // Interpolate between two adjacent colors for smoother transitions
            double t = (value * (colorMap.size() - 1)) - colorIndex;
            
            Color c1 = colorMap[colorIndex];
            Color c2 = colorMap[colorIndex + 1];
            
            int r = static_cast<int>((1.0 - t) * c1.r + t * c2.r);
            int g = static_cast<int>((1.0 - t) * c1.g + t * c2.g);
            int b = static_cast<int>((1.0 - t) * c1.b + t * c2.b);
            
            // Write the color values
            file << r << " " << g << " " << b << " ";
        }
        file << "\n"; // End of row
    }
    
    file.close();
    return true;
}

// A function to generate and directly export noise to a PPM file
bool noise::generateAndExportPPM(int featureSize, const std::string& filename, bool colored) {
    auto noiseGrid = perlin(featureSize);
    
    if (colored) {
        return exportToColoredPPM(noiseGrid, filename);
    } else {
        return exportToPPM(noiseGrid, filename);
    }
}

// Generate and export multi-octave noise
bool noise::generateAndExportOctavesPPM(int baseFeatureSize, int octaves, 
                                       double persistence, const std::string& filename, 
                                       bool colored) {
    auto noiseGrid = perlinOctaves(baseFeatureSize, octaves, persistence);
    
    if (colored) {
        return exportToColoredPPM(noiseGrid, filename);
    } else {
        return exportToPPM(noiseGrid, filename);
    }
}

// Generate random gradient vectors for the grid
std::vector<std::vector<std::vector<double>>> noise::generateGradients(int gridWidth, int gridLength) {
    // Create a 3D vector: [2][gridLength][gridWidth]
    // First dimension: x/y components of gradient vectors
    std::vector<std::vector<std::vector<double>>> gradients(2, 
        std::vector<std::vector<double>>(gridLength, 
            std::vector<double>(gridWidth)));
    
    // Setup random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(-1.0, 1.0);
    
    // Generate random unit vectors
    for (int y = 0; y < gridLength; ++y) {
        for (int x = 0; x < gridWidth; ++x) {
            // Generate random x,y components
            double gx = dist(gen);
            double gy = dist(gen);
            
            // Normalize to unit vector
            double len = std::sqrt(gx*gx + gy*gy);
            if (len > 0.0) {  // Avoid division by zero
                gx /= len;
                gy /= len;
            }
            
            // Store the gradient components
            gradients[0][y][x] = gx;
            gradients[1][y][x] = gy;
        }
    }
    
    return gradients;
}

// Compute dot product between two 2D vectors
double noise::dotProduct(const std::vector<double>& g, const std::vector<double>& d) {
    return g[0] * d[0] + g[1] * d[1];
}

// Smoothstep function for smoother interpolation
double noise::fade(double t) {
    // Improved Perlin's fade function: 6t^5 - 15t^4 + 10t^3
    return t * t * t * (t * (t * 6 - 15) + 10);
}

// Linear interpolation
double noise::lerp(double a, double b, double t) {
    return a + t * (b - a);
}