//Include Modules
const fs = require('fs');
const path = require('path');
const Math = require('math.js');
const express = require("express");

//App Variables
const app = express();
const port = process.env.PORT || "8000";

//App Configuration
app.use(express.static("express"));

//Routes Definitions
app.get("/", (req, res) =>
{
    //res.status(200).send("IOjBUFHLAF. :)");
    res.sendFile(__dirname +'/express/index.html');
});

//Server Activation
app.listen(port, () =>
{
    console.log(`Listening to requests on http://localhost:${port}`);
});