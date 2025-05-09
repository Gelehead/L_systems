class CellularAutomataVisualizer {
    constructor(containerID, options = {}) {
        this.containerID = document.getElementById(containerID);
        this.options = options != {} ? options :
        {
            CellSize : 1.0,
            CellStateColors: 
            {
                1: 0xed0c6e,
                2: 0xf55437,
                3: 0xff9a01,
                default: 0xaaaaaa
            }
        }

        this.cells = new Map;
    }

}