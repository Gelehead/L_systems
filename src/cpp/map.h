#include <iostream>
#include <vector>
#include <array>
#include <memory>
#include <string>

// Base Tile class that can be used in any dimension map
class Tile {
protected:
    bool walkable = true;
    int tileType = 0;
    std::string name = "Empty";

public:
    Tile() = default;
    Tile(bool isWalkable, int type, const std::string& tileName) 
        : walkable(isWalkable), tileType(type), name(tileName) {}
    
    virtual ~Tile() = default;
    
    bool isWalkable() const { return walkable; }
    void setWalkable(bool canWalk) { walkable = canWalk; }
    
    int getType() const { return tileType; }
    void setType(int type) { tileType = type; }
    
    const std::string& getName() const { return name; }
    void setName(const std::string& tileName) { name = tileName; }
    
    virtual std::string getDescription() const {
        return "Tile: " + name + " (Type: " + std::to_string(tileType) + 
               ", Walkable: " + (walkable ? "Yes" : "No") + ")";
    }
};
// Base MapClass using CRTP for maps of any dimension
template<typename Derived, size_t Dims>
class MapClass {
public:
    static constexpr size_t dimensions = Dims;
    using coordinate_type = std::array<int, dimensions>;
    
protected:
    bool initialized = false;

public:
    virtual ~MapClass() = default;
    
    // Common map operations
    void initialize() {
        static_cast<Derived*>(this)->initializeMap();
        initialized = true;
    }
    
    void displayInfo() const {
        const Derived* derived = static_cast<const Derived*>(this);
        std::cout << "Map type: " << derived->getMapType() << std::endl;
        std::cout << "Dimensions: " << dimensions << std::endl;
        derived->displayAdditionalInfo();
    }
    
    // Common tile operations
    bool isPointValid(const coordinate_type& point) const {
        return static_cast<const Derived*>(this)->isPointValidImpl(point);
    }
    
    Tile* getTileAt(const coordinate_type& point) {
        if (isPointValid(point)) {
            return static_cast<Derived*>(this)->getTileAtImpl(point);
        }
        return nullptr;
    }
    
    const Tile* getTileAt(const coordinate_type& point) const {
        if (isPointValid(point)) {
            return static_cast<const Derived*>(this)->getTileAtImpl(point);
        }
        return nullptr;
    }
    
    void setTileAt(const coordinate_type& point, std::unique_ptr<Tile> tile) {
        if (isPointValid(point)) {
            static_cast<Derived*>(this)->setTileAtImpl(point, std::move(tile));
        }
    }
};

// 2D Map implementation with Tiles
class Map2D : public MapClass<Map2D, 2> {
private:
    std::vector<std::vector<std::unique_ptr<Tile>>> grid;
    size_t width = 0;
    size_t height = 0;
    
public:
    Map2D(size_t w, size_t h) : width(w), height(h) {}
    
    void initializeMap() {
        grid.resize(height);
        for (auto& row : grid) {
            row.resize(width);
            for (auto& tile : row) {
                tile = std::make_unique<Tile>();
            }
        }
        std::cout << "2D tile map initialized with size " << width << "x" << height << std::endl;
    }
    
    std::string getMapType() const {
        return "2D Tile Grid";
    }
    
    void displayAdditionalInfo() const {
        std::cout << "Grid size: " << width << "x" << height << std::endl;
        
        // Display a small sample of tiles if available
        if (!grid.empty() && !grid[0].empty()) {
            size_t sampleSize = std::min(width, static_cast<size_t>(3));
            std::cout << "Sample tiles:" << std::endl;
            for (size_t i = 0; i < sampleSize; ++i) {
                if (grid[0][i]) {
                    std::cout << "  - Position [0," << i << "]: " 
                              << grid[0][i]->getDescription() << std::endl;
                }
            }
        }
    }
    
    bool isPointValidImpl(const coordinate_type& point) const {
        return point[0] >= 0 && point[0] < static_cast<int>(width) && 
               point[1] >= 0 && point[1] < static_cast<int>(height);
    }
    
    Tile* getTileAtImpl(const coordinate_type& point) {
        return grid[point[1]][point[0]].get();
    }
    
    const Tile* getTileAtImpl(const coordinate_type& point) const {
        return grid[point[1]][point[0]].get();
    }
    
    void setTileAtImpl(const coordinate_type& point, std::unique_ptr<Tile> tile) {
        grid[point[1]][point[0]] = std::move(tile);
    }
    
    // Utility method to get dimensions
    std::pair<size_t, size_t> getDimensions() const {
        return {width, height};
    }
};

// 3D Map implementation with Tiles
class Map3D : public MapClass<Map3D, 3> {
private:
    std::vector<std::vector<std::vector<std::unique_ptr<Tile>>>> volume;
    size_t width = 0;
    size_t height = 0;
    size_t depth = 0;
    
public:
    Map3D(size_t w, size_t h, size_t d) : width(w), height(h), depth(d) {}
    
    void initializeMap() {
        volume.resize(depth);
        for (auto& layer : volume) {
            layer.resize(height);
            for (auto& row : layer) {
                row.resize(width);
                for (auto& tile : row) {
                    tile = std::make_unique<Tile>();
                }
            }
        }
        std::cout << "3D tile map initialized with size " << width << "x" 
                  << height << "x" << depth << std::endl;
    }
    
    std::string getMapType() const {
        return "3D Tile Volume";
    }
    
    void displayAdditionalInfo() const {
        std::cout << "Volume size: " << width << "x" << height << "x" << depth << std::endl;
        
        // Display a small sample of tiles if available
        if (!volume.empty() && !volume[0].empty() && !volume[0][0].empty()) {
            std::cout << "Sample tiles:" << std::endl;
            for (size_t z = 0; z < std::min(depth, static_cast<size_t>(2)); ++z) {
                for (size_t x = 0; x < std::min(width, static_cast<size_t>(2)); ++x) {
                    if (volume[z][0][x]) {
                        std::cout << "  - Position [" << x << ",0," << z << "]: " 
                                  << volume[z][0][x]->getDescription() << std::endl;
                    }
                }
            }
        }
    }
    
    bool isPointValidImpl(const coordinate_type& point) const {
        return point[0] >= 0 && point[0] < static_cast<int>(width) && 
               point[1] >= 0 && point[1] < static_cast<int>(height) &&
               point[2] >= 0 && point[2] < static_cast<int>(depth);
    }
    
    Tile* getTileAtImpl(const coordinate_type& point) {
        return volume[point[2]][point[1]][point[0]].get();
    }
    
    const Tile* getTileAtImpl(const coordinate_type& point) const {
        return volume[point[2]][point[1]][point[0]].get();
    }
    
    void setTileAtImpl(const coordinate_type& point, std::unique_ptr<Tile> tile) {
        volume[point[2]][point[1]][point[0]] = std::move(tile);
    }
    
    // Utility method to get dimensions
    std::tuple<size_t, size_t, size_t> getDimensions() const {
        return {width, height, depth};
    }
};