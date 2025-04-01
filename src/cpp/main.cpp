#include "grammar.h"
#include <iostream>
#include <fstream>

#define DEFAULT_OUTPUT_PATH "../../build/grammars/gram_gen.txt"
#define FIRST_LANGUAGE "../../grammars/first_language.txt"

// Forward declaration of VulkanApp
class VulkanApp {
public:
    void run();
};

int main(int argc, char** argv) {
    // Process grammar first
    grammar g = argc > 1 ? grammar::read_grammar(argv[1]) : grammar::read_grammar(FIRST_LANGUAGE);
    std::string outputPath = (argc > 3) ? argv[3] : DEFAULT_OUTPUT_PATH;

    std::cout << g << std::endl;
    
    std::ofstream out(outputPath);
    out << grammar::vec2string(g.generate(atoi(argv[2]), g.s));
    out.close();
    
    // Create and run the Vulkan application
    /* try {
        VulkanApp vulkanApp;
        vulkanApp.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS; */
}