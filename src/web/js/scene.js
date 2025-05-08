import * as THREE from 'three';

// Optional separate file for scene creation and management
export class SceneManager {
    constructor() {
        this.objects = {};
    }
    
    createScene() {
        const scene = new THREE.Scene();
        return scene;
    }
    
    createLights(scene) {
        // Add ambient light
        const ambientLight = new THREE.AmbientLight(0x404040);
        scene.add(ambientLight);
        
        // Add directional light
        const directionalLight = new THREE.DirectionalLight(0xffffff, 1);
        directionalLight.position.set(1, 1, 1);
        scene.add(directionalLight);
    }
    
    createGrid(scene, size = 20, divisions = 20) {
        const gridHelper = new THREE.GridHelper(size, divisions);
        scene.add(gridHelper);
    }
    
    createCube(scene, options = {}) {
        const {
            size = 2,
            color = 0x3350f0,
            position = { x: -5, y: 1, z: 0 }
        } = options;
        
        const geometry = new THREE.BoxGeometry(size, size, size);
        const material = new THREE.MeshPhongMaterial({ color });
        const cube = new THREE.Mesh(geometry, material);
        cube.position.set(position.x, position.y, position.z);
        scene.add(cube);
        
        // Store for external reference
        this.objects.cube = cube;
        return cube;
    }
    
    createSphere(scene, options = {}) {
        const {
            radius = 1.5,
            segments = 32,
            color = 0xff4040,
            position = { x: 5, y: 1.5, z: 0 }
        } = options;
        
        const geometry = new THREE.SphereGeometry(radius, segments, segments);
        const material = new THREE.MeshPhongMaterial({ color });
        const sphere = new THREE.Mesh(geometry, material);
        sphere.position.set(position.x, position.y, position.z);
        scene.add(sphere);
        
        // Store for external reference
        this.objects.sphere = sphere;
        return sphere;
    }
    
    // Additional methods for creating other objects...
    
    getObject(name) {
        return this.objects[name];
    }
    
    getAllObjects() {
        return this.objects;
    }
}