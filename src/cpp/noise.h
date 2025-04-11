#include <vector>

class noise {
    public :
        int width, length;
        
        std::vector<std::vector<int>> perlin(int featureSize){
            // get grid dimension depending on feature size 
            // TODO : implement multiple 
            int grid_width = width / featureSize;
            int grid_length = length / featureSize;

            // initialize final noise grid
            std::vector<int> noise_rows(width);
            std::vector<std::vector<int>> noise_grid(width, noise_rows);

            // initialize gradient grid
            // stores random vectors gradients? inside a vec of vec
            // so values[x][y][x/y/z]
            // with the last xyz being the vector gradient associated
            std::vector<int> rows(grid_width);
            std::vector<std::vector<int>> grid(grid_length, rows);
            // every element should be assigned a random vector
            std::vector<std::vector<std::vector<int>>> values(3, grid);
        
            for (auto& row : values){
                for (auto& column : row ){
                    for ( auto& value : column ){
                        // smh generate the gradient or like the vector
                    }
                }
            }

            
        
        }

};