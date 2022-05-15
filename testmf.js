const fs = require('fs');

const e = {e: "70998"};

fs.writeFileSync(__dirname + "/c2j.json", JSON.stringify(e));