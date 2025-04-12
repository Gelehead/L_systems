#include <vector>

class Tile {
    private :
        std::vector<int> position;
    
    public :
        Tile(std::vector<int> pos) {
            position = pos;
        }
};