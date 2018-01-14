const fs = require('fs'),
    path = require('path'),
    csv = require('csvtojson'),
    rootDirPath = path.join(__dirname, 'csvPath'),
    jsonOutPath = path.join(__dirname, 'outputPath')

function readPath(dirPath) {
    let relativePath = path.relative(rootDirPath, dirPath);
    let targetPath = path.resolve(jsonOutPath, relativePath);
    console.log('relative path : ' + relativePath + '   target path ' + targetPath);
    if(!fs.existsSync(targetPath)){
        fs.mkdirSync(targetPath);
    }
    let files = fs.readdirSync(dirPath);
    for (let i = 0; i < files.length; i++) {
        let fileName = files[i];
        let curPath = path.join(dirPath, fileName);
        let stat = fs.statSync(curPath);
        if (stat.isFile()) {
            if (fileName.split('.')[1] == 'csv') {
                readFile(curPath, fileName);
            }
        } else if (stat.isDirectory()) {
            readPath(curPath);
        }
    }
}

function readFile(filePath, fileName) {
    console.log('source file : ' + filePath);
    let data = fs.readFileSync(filePath, { encoding: 'utf-8' });
    let buffer = [];
    let outFilePath = path.join(jsonOutPath, fileName.split('.')[0] + '.json');
    console.log('out file : ' + outFilePath);
    csv().fromString(data).on('json', (jsonObj) => {
        buffer.push(jsonObj)
    }).on('done', () => {
        fs.writeFileSync(outFilePath, JSON.stringify(buffer))
    }).on('error', (error) => {
        console.log(`doh! there was an error: ${error}`)
    })
}

readPath(rootDirPath);



// fs.readFile(filePath, { encoding: 'utf-8' }, function (error, data) {


// });
