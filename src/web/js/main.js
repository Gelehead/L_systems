import * as THREE from 'three';
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';
import { SceneManager } from './scene.js';

// Scene, camera, renderer
let scene, camera, renderer, controls;
let sceneManager;

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
    sceneManager.createGrid(scene);
    
    // Create objects
    sceneManager.createCube(scene);
    sceneManager.createSphere(scene);
    
    // Create additional objects manually if needed
    createAdditionalObjects();
    
    // Add event listeners
    window.addEventListener('resize', onWindowResize);
}

// Setup orbit controls configuration
function setupControls() {
    controls.enableDamping = true;
    controls.dampingFactor = 0.05;
    controls.minDistance = 5;
    controls.maxDistance = 50;
    controls.maxPolarAngle = Math.PI / 2; // Limit to not go below the ground
}

// Create additional objects not covered by the SceneManager
function createAdditionalObjects() {
    // Green cone
    const coneGeometry = new THREE.ConeGeometry(1, 3, 32);
    const coneMaterial = new THREE.MeshPhongMaterial({ color: 0x40ff40 }); // Green
    const cone = new THREE.Mesh(coneGeometry, coneMaterial);
    cone.position.set(0, 1.5, 5);
    scene.add(cone);
    
    // Yellow torus
    const torusGeometry = new THREE.TorusGeometry(1, 0.4, 16, 100);
    const torusMaterial = new THREE.MeshPhongMaterial({ color: 0xffff40 }); // Yellow
    const torus = new THREE.Mesh(torusGeometry, torusMaterial);
    torus.position.set(0, 1.5, -5);
    torus.rotation.x = Math.PI / 2;
    scene.add(torus);
    
    // Store in scene manager for reference
    sceneManager.objects.cone = cone;
    sceneManager.objects.torus = torus;
}

// Handle window resize
function onWindowResize() {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
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