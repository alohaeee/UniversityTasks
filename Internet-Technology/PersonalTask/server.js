const http = require('http');
const fs = require('fs');
const port = 3000;

var htmlFile = fs.readFileSync('index.html','utf-8');
var cssFile = fs.readFileSync("style.css", 'utf-8');
var scriptFile = fs.readFileSync("script.js", 'utf-8');
var dataFile = fs.readFileSync("data.txt", 'utf-8');
var requestFile = fs.readFileSync("request.json", 'utf-8');


var server = http.createServer((request, response) =>
{
    switch (request.url) 
    {
        case "/style.css" :
            response.writeHead(200, {"Content-Type": "text/css"});
            response.write(cssFile);
            break;
        case "/script.js" :
            response.writeHead(200, {"Content-Type": "text/javascript"});
            response.write(scriptFile);
            break;
        case "/data.txt":
            response.writeHead(200, {"Content-Type": "text/plain"});
            response.write(dataFile);
            break;
        case "/request.json":
            response.writeHead(200, {"Content-Type": "text/json"});
            response.write(requestFile);
            break;
        default :    
            response.writeHead(200, {"Content-Type": "text/html"});
            response.write(htmlFile);
    }
    response.end();
});
    
server.listen(port, (err) => {
    if (err) {
        return console.log('something bad happened', err)
    }
    console.log(`server is listening on ${port}`)
})