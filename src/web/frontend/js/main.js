import * as THREE from 'three';
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';
import { SceneManager } from './scene.js';
import { CellularAutomataVisualizer } from './CellularAutomata.js';


// Scene, camera, renderer
let scene, camera, renderer, controls;
let sceneManager;
let cellularAutomata; 
let gramFile, jsonSetupFile;

// Initialize the scene
function init() {
    // Create renderer
    renderer = new THREE.WebGLRenderer({ antialias: true });
    renderer.setSize(window.innerWidth, window.innerHeight);
    renderer.setPixelRatio(window.devicePixelRatio);
    renderer.setClearColor(0x222222); // Dark background
    document.getElementById('canvas-container').appendChild(renderer.domElement);
    
    // Create camera
    camera = new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight, 0.1, 1000);
    camera.position.set(0, 5, 15);
    
    // Create orbit controls
    controls = new OrbitControls(camera, renderer.domElement);
    setupControls();
    
    // Initialize scene manager
    sceneManager = new SceneManager();
    
    // Create scene
    scene = sceneManager.createScene();
    
    // Add lights
    sceneManager.createLights(scene);
    
    // Create grid
    // sceneManager.createGrid(scene);
    
    // Create bounding square 
    sceneManager.createEmptyCube(scene);

    // Create objects
    /* sceneManager.createCube(scene);
    sceneManager.createSphere(scene); */
    
    // Initialize and integrate cellular automata
    initCellularAutomata();
    
    // Add UI controls for cellular automata
    createCellularAutomataUI();
}

// Setup orbit controls configuration
function setupControls() {
    controls.enableDamping = true;
    controls.dampingFactor = 0.05;
    controls.minDistance = 5;
    controls.maxDistance = 1000;
    controls.maxPolarAngle = Math.PI ;
}

// Initialize and integrate cellular automata
function initCellularAutomata() {
    // Create a container for the cellular automata visualizer
    const container = document.createElement('div');
    container.id = 'cellular-automata-container';
    container.style.display = 'none'; // Hidden, as we're not using its renderer
    document.body.appendChild(container);
    
    // Initialize the visualizer
    cellularAutomata = new CellularAutomataVisualizer('cellular-automata-container', {
        CellSize: 0.5,
        CellSpacing: 0,
        CellStateColors: {
            1: 0xed0c6e, // Pink
            2: 0xf55437, // Orange-red
            3: 0xff9a01, // Orange
            default: 0xaaaaaa // Light gray
        },
        backgroundColor: 0x000000,
        useMergeGeometry: true
    });
    
    // Create a demo pattern for the cellular automata
    createDemoPattern();
    
    // Add the cellular automata group to the scene
    const cellGroup = cellularAutomata.cellsGroup;
    cellGroup.position.set(0, 0, 0);
    scene.add(cellGroup);
    
    // Store in scene manager for reference
    sceneManager.objects.cellularAutomata = cellularAutomata;
}

// Create a demo pattern for cellular automata
function createDemoPattern() {
    // Create a sample Game of Life glider pattern in 3D
    const demoData = {
        format_version: "1.0",
        grid_size_x: 10,
        grid_size_y: 10,
        grid_size_z: 10,
        cells: [
            // Glider pattern on z=0 plane
            {x: 1, y: 0, z: 0, state: 1},
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
    
    // Set the data and render
    cellularAutomata.gridData = demoData;
    cellularAutomata.renderGrid(); // Note: fixed the method name
}

// Create UI controls for cellular automata
function createCellularAutomataUI() {
    const uiContainer = document.createElement('div');
    uiContainer.style.position = 'absolute';
    uiContainer.style.top = '10px';
    uiContainer.style.left = '10px';
    uiContainer.style.backgroundColor = 'rgba(0, 0, 0, 0.7)';
    uiContainer.style.color = 'white';
    uiContainer.style.padding = '10px';
    uiContainer.style.borderRadius = '5px';
    uiContainer.style.fontFamily = 'Arial, sans-serif';
    
    uiContainer.innerHTML = `
        <div style="margin-bottom: 10px; font-weight: bold;">Cellular Automata Controls</div>
        <div>
            <button id="toggle-automata">Hide/Show</button>
            <button id="load-demo">Load Demo Pattern</button>
            <button id="load-file">Load From File</button>
            <button id="load-setup"> Load Setup </button>
        </div>
        <div style="margin-top: 10px;">
            <label for="position-x">X:</label>
            <input type="range" id="position-x" min="-20" max="20" value="0" style="width: 80px;">
            
            <label for="position-y">Y:</label>
            <input type="range" id="position-y" min="-20" max="20" value="0" style="width: 80px;">
            
            <label for="position-z">Z:</label>
            <input type="range" id="position-z" min="-20" max="20" value="0" style="width: 80px;">
        </div>
    `;
    
    document.body.appendChild(uiContainer);
    
    // Add event listeners
    document.getElementById('toggle-automata').addEventListener('click', () => {
        cellularAutomata.cellsGroup.visible = !cellularAutomata.cellsGroup.visible;
    });
    
    document.getElementById('load-demo').addEventListener('click', () => {
        createDemoPattern();
    });

    document.getElementById('load-setup').addEventListener('click', () => {
        const setupContainer = document.createElement('div');
        setupContainer.style.position = 'absolute';
        setupContainer.style.top = '120px';
        setupContainer.style.left = '10px';
        setupContainer.style.backgroundColor = 'rgba(0, 0, 0, 0.7)';
        setupContainer.style.color = 'white';
        setupContainer.style.padding = '10px';
        setupContainer.style.borderRadius = '5px';
        setupContainer.style.fontFamily = 'Arial, sans-serif';

        setupContainer.innerHTML = `
            <div>
                <div style="margin-bottom: 10px; font-weight: bold;">
                    <p> grammar file </p>
                    <input type="file" id="upload-gram" accept=".exe" />
                </div>
                <div style="margin-bottom: 10px; font-weight: bold;">
                    <p> JSON file </p>
                    <input type="file" id="upload-json-setup" accept=".JSON" />
                </div>
                <div style="margin-bottom: 10px; font-weight: bold;">
                    <p> number of generations </p>
                    <button id="run-1-gen"> run 1 generation </button>
                    <input type="number" id="n_gen" name="n_gen" min="1" max="100">
                    <button id="run-n-gen"> run n generations </button>
                </div>
            </div>
        `;

        document.body.appendChild(setupContainer);

        document.getElementById('upload-gram').addEventListener('change', (event) => {
            const file = event.target.files[0];
            if ( file ) {
                gramFile = file;
                console.log("loaded grammar => ", file.name);
            }
        });

        document.getElementById('upload-json-setup').addEventListener('change', (event) => {
            const file = event.target.files[0];
            if ( file ) {
                jsonSetupFile = file;
                console.log("loaded json => ", file.name);
            }
        });
        
        document.getElementById('run-1-gen').addEventListener('click', () => {
            // get next generation json
            const next_gen_json = query_exe_runner(gramFile, jsonSetupFile, 1);

            // update visuals
            cellularAutomata.gridData = next_gen_json;
            cellularAutomata.renderGrid();

            // update the current json file
            jsonSetupFile = next_gen_json;
        });

        /** Basically saw that i would have more or less the same code twice with 'run-1-gen' and 'run-n-gen' so i made a function
         * DRY babyyyy
         * 
         * @param {*} grammar_file exe file that represents the Cellular Automata logic
         * @param {*} jsonFile JSON file containing the position and state of tiles at a given generation ( does not take past generations into account )
         * @param {*} n_gen number of generations we want
         * 
         * @return {*} JSON file of the next generation of tiles
         */
        async function query_exe_runner(grammar_file, json_file, n_gen) {
            // format data to give to backend
            const formData = new FormData();
            formData.append('exe', grammar_file);
            formData.append('json', json_file);
            formData.append('generations', n_gen);

            // send request
            try {
                fetch("http://localhost:3000/run", {
                method: "post",
                body: formData,
                });
                const response = await res.json;
                console.log(`response : ${response}`);
                return output;
            } catch (err) {
                console.error(`error : ${err}`);
                return null;
            }
        };

        async function delay(ms) {
            return new Promise( resolve => setTimeout(resolve, ms));
        }
        
        document.getElementById('run-n-gen').addEventListener('click', async () => {
            for ( i = 0 ; i < document.getElementById(n_gen).value ; i ++){
                const next_gen_json = await query_exe_runner(gramFile, jsonSetupFile, 1);
                // executes the function then waits 0.2s
                if ( next_gen_json ) {
                    next_gen_json = query_exe_runner(gramFile, jsonSetupFile, 1);
                    
                    cellularAutomata.gridData = next_gen_json;
                    cellularAutomata.renderGrid();

                    jsonSetupFile = next_gen_json;
                }
                await delay(200);
            }
        });
    });
}

// Animation loop
function animate() {
    requestAnimationFrame(animate);
    
    // Get objects from scene manager
    const objects = sceneManager.getAllObjects();
    
    // Rotate objects
    if (objects.cube) {
        objects.cube.rotation.x += 0.01;
        objects.cube.rotation.y += 0.01;
    }
    
    if (objects.sphere) {
        objects.sphere.rotation.y += 0.01;
    }
    
    if (objects.cone) {
        objects.cone.rotation.y += 0.01;
    }
    
    if (objects.torus) {
        objects.torus.rotation.y += 0.01;
        objects.torus.rotation.z += 0.01;
    }
    
    // Update controls
    controls.update();
    
    // Render scene
    renderer.render(scene, camera);
}

// Initialize the scene and start the animation loop
init();
animate();

// Expose variables to window for debugging
window.scene = scene;
window.cellularAutomata = cellularAutomata;
window.sceneManager = sceneManager;