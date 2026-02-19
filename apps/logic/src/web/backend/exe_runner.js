const express = require('express');
const multer = require('multer');
const { execFile } = require('child_process');
const path = require('path');
const fs = require('fs');

const PORT = 3000;

const app = express();
const uploads = multer({ dest: "uploads/"});

app.post('/run', uploads.fields([{name: 'exe'}, {name: 'json'}]), (req, res) => {
    const exepath = req.files.exe[0].path;
    const jsonpath = req.files.json[0].path;
    const generations = req.body.generations;

    execPath(exepath, [generations, jsonpath], (err, stdout, stderr) => {
        if ( err ) {
            console.log(`couldnt execute ${exepath} ${generations} times using ${jsonpath}`);
            console.error("error ", err);
            return res.status(500).send(stderr || "Execution failed");
        }
        res.send(stdout);
    });
});

app.listen(PORT, ()=> console.log(`backend server listening to port ${PORT}`));