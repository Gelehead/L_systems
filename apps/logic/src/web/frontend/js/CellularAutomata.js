import * as THREE from 'three';

export class CellularAutomataVisualizer {
    constructor(containerID, options = {}) {
        this.container = document.getElementById(containerID);
        
        // Set default options if not provided
        this.options = {
            CellSize: options.CellSize || 1.0,
            CellSpacing: options.CellSpacing || 0,
            CellStateColors: options.CellStateColors || {
                1: 0xed0c6e,
                2: 0xf55437,
                3: 0xff9a01,
                default: 0xaaaaaa
            },
            backgroundColor: options.backgroundColor || 0x000000,
            useMergeGeometry: options.useMergeGeometry !== undefined ? options.useMergeGeometry : true
        };

        this.cells = new Map();
        this.cellsGroup = new THREE.Group();
        this.gridData = null;
    }

    // Fixed method name to match what's called elsewhere
    renderGrid() {
        // Clear existing cells
        this.cells.clear();
        
        // Clear the group (fixed the clear method)
        while(this.cellsGroup.children.length > 0) {
            this.cellsGroup.remove(this.cellsGroup.children[0]);
        }

        if (!this.gridData || !this.gridData.cells) {
            console.error("No grid data loaded");
            return;
        }

        if (this.options.useMergeGeometry && this.gridData.cells.length > 1000) {
            this.renderWithInstanceMesh();
        } else {
            this.renderWithIndividualMesh();
        }
    }

    // Update a specific cell state
    updateCell(x, y, z, newState) {
        const key = `${x},${y},${z}`;
        
        if (this.options.useMergeGeometry) {
            // For instanced meshes, we need to re-render the entire grid
            // Consider batching updates and only re-rendering periodically for performance
            
            // Update the data
            let cellFound = false;
            for (const cell of this.gridData.cells) {
                if (cell.x === x && cell.y === y && cell.z === z) {
                    cell.state = newState;
                    cellFound = true;
                    break;
                }
            }
            
            if (!cellFound && newState !== 0) {
                this.gridData.cells.push({x, y, z, state: newState});
            } else if (cellFound && newState === 0) {
                // Remove the cell if its state is 0
                this.gridData.cells = this.gridData.cells.filter(
                    cell => !(cell.x === x && cell.y === y && cell.z === z)
                );
            }
            
            // Re-render entire grid
            this.renderGrid();
        } else {
            // For individual meshes, we can update just this cell
            if (this.cells.has(key)) {
                const cellInfo = this.cells.get(key);
                
                if (newState === 0) {
                    // Remove cell if state is 0
                    this.cellsGroup.remove(cellInfo.mesh);
                    this.cells.delete(key);
                    
                    // Also update the data
                    this.gridData.cells = this.gridData.cells.filter(
                        cell => !(cell.x === x && cell.y === y && cell.z === z)
                    );
                } else {
                    // Update existing cell
                    const color = this.options.CellStateColors[newState] || this.options.CellStateColors.default;
                    cellInfo.mesh.material.color.set(color);
                    cellInfo.state = newState;
                    
                    // Update the data
                    for (const cell of this.gridData.cells) {
                        if (cell.x === x && cell.y === y && cell.z === z) {
                            cell.state = newState;
                            break;
                        }
                    }
                }
            } else if (newState !== 0) {
                // Create new cell if it doesn't exist
                const geometry = new THREE.BoxGeometry(
                    this.options.CellSize, 
                    this.options.CellSize, 
                    this.options.CellSize
                );
                
                const color = this.options.CellStateColors[newState] || this.options.CellStateColors.default;
                const material = new THREE.MeshLambertMaterial({ color });
                
                const mesh = new THREE.Mesh(geometry, material);
                mesh.position.set(
                    x * (this.options.CellSize + this.options.CellSpacing),
                    y * (this.options.CellSize + this.options.CellSpacing),
                    z * (this.options.CellSize + this.options.CellSpacing)
                );
                
                this.cellsGroup.add(mesh);
                
                this.cells.set(key, {
                    mesh,
                    state: newState
                });
                
                // Update the data
                this.gridData.cells.push({x, y, z, state: newState});
            }
        }
    }

    renderWithIndividualMesh() {
        console.log("Rendering with individual meshing");

        const boxGeometry = new THREE.BoxGeometry(
            this.options.CellSize,
            this.options.CellSize,
            this.options.CellSize
        );

        // Fixed for...in to for...of
        for (const cell of this.gridData.cells) {
            const x = cell.x * (this.options.CellSize + this.options.CellSpacing);
            const y = cell.y * (this.options.CellSize + this.options.CellSpacing);
            const z = cell.z * (this.options.CellSize + this.options.CellSpacing);
            
            const color = this.options.CellStateColors[cell.state] || this.options.CellStateColors.default;
            const material = new THREE.MeshLambertMaterial({ color });

            const mesh = new THREE.Mesh(boxGeometry, material);
            mesh.position.set(x, y, z);

            this.cellsGroup.add(mesh);
        
            // Store reference to this cell for easy updates
            const key = `${cell.x},${cell.y},${cell.z}`;
            this.cells.set(key, {
                mesh,
                state: cell.state
            });
        }
    }

    renderWithInstanceMesh() {
        console.log("Using instance mesh for rendering");

        const cellsByState = new Map();

        // Fixed iteration over gridData.cells
        for (const cell of this.gridData.cells) {
            if (!cellsByState.has(cell.state)) {
                cellsByState.set(cell.state, []);
            }
            cellsByState.get(cell.state).push(cell);
        }

        const geometry = new THREE.BoxGeometry(
            this.options.CellSize,
            this.options.CellSize,
            this.options.CellSize
        );

        for (const [state, cells] of cellsByState.entries()) {
            const color = this.options.CellStateColors[state] || this.options.CellStateColors.default;
            const material = new THREE.MeshLambertMaterial({ color });

            const instancedMesh = new THREE.InstancedMesh(
                geometry,
                material,
                cells.length
            );

            const matrix = new THREE.Matrix4();

            cells.forEach((cell, index) => {
                const x = cell.x * (this.options.CellSize + this.options.CellSpacing);
                const y = cell.y * (this.options.CellSize + this.options.CellSpacing);
                const z = cell.z * (this.options.CellSize + this.options.CellSpacing);
            
                matrix.setPosition(x, y, z);
                instancedMesh.setMatrixAt(index, matrix);
            });

            instancedMesh.instanceMatrix.needsUpdate = true;
            this.cellsGroup.add(instancedMesh);
        }
    }

    // Set an entire frame of data
    setFrame(cellsData) {
        if (this.gridData) {
            this.gridData.cells = cellsData;
        } else {
            this.gridData = {
                cells: cellsData
            };
        }
        this.renderGrid();
    }

    async loadFromJson(url) {
        try {
            const response = await fetch(url);
            this.gridData = await response.json();

            this.renderGrid();

            return true;
        } catch (error) {
            console.error("Error loading grid data:", error);
            return false;
        }
    }

    // Additional helper methods for integration
    
    // Create a demo pattern
    createDemoPattern() {
        // Create a sample pattern 
        const demoData = {
            format_version: "1.0",
            grid_size_x: 10,
            grid_size_y: 10,
            grid_size_z: 10,
            cells: [
                // Glider pattern on z=0 plane
                {x: 3, y: 0, z: 0, state: 1},
                {x: 2, y: 1, z: 0, state: 1},
                {x: 0, y: 2, z: 0, state: 1},
                {x: 1, y: 2, z: 0, state: 1},
                {x: 2, y: 2, z: 0, state: 1},
                
                // Some cells on z=1 plane
                {x: 1, y: 0, z: 1, state: 2},
                {x: 2, y: 1, z: 1, state: 2},
                {x: 0, y: 2, z: 1, state: 2},
                
                // Some cells on z=2 plane
                {x: 1, y: 1, z: 2, state: 3},
                {x: 2, y: 1, z: 2, state: 3},
                {x: 3, y: 1, z: 2, state: 3}
            ]
        };
        
        this.gridData = demoData;
        this.renderGrid();
    }

    // Toggle visibility
    toggleVisibility(visible) {
        this.cellsGroup.visible = visible;
    }

    // Set position
    setPosition(x, y, z) {
        this.cellsGroup.position.set(x, y, z);
    }
}