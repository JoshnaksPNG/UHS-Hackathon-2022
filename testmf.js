const fs = require('fs');

const e = { 
    "currentanimal":
    {
        "attributes": [
            [
                "shiny",
                10
            ],
            [
                "shiny",
                10
            ]
        ],
        "chest": "rhino",
        "curfood": 14,
        "head": "rhino",
        "id": 0,
        "maxfood": 14,
        "name": "Fluffles"
    },
    "world":
    {
        "day": 43,
        "feedstore": 100,
        "petcount": 1
    }
};

fs.writeFileSync(__dirname + "/c2j.json", JSON.stringify(e));