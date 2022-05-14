//Include Modules
const fs = require('fs');
const path = require('path');
const Math = require('math.js');
const express = require("express");
const bodyParser = require("body-parser");

//App Variables
const app = express();
const port = process.env.PORT || "8000";

//App Configuration
app.use(express.static("express"));
app.use(bodyParser.json());

//Routes Definitions
app.get("/", (req, res) =>
{
    //res.status(200).send("IOjBUFHLAF. :)");
    res.sendFile(__dirname +'/express/index.html');
});

app.post("/request", (req, res) =>
{
    console.log(req.body);
    //console.log(res.body);
});

//Server Activation
app.listen(port, () =>
{
    console.log(`Listening to requests on http://localhost:${port}`);
});