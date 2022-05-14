#include "defines.h"
#include "json.hpp"

#define ATTR_FILE_LOC "/Users/moose/UHS-Hackathon-2022/back_end_data/attributes.json"
#define TYPES_FILE_LOC "/Users/moose/UHS-Hackathon-2022/back_end_data/pet_types.json"

int food_store = 100;
int topId = 0;
int maxRarity = 15;
int maxCom = 5;
std::vector<pet> pets;
std::vector<attribute> attribute_library;
std::vector<animal_type> animal_library;

using json = nlohmann::json;


pet getrandpet(int maxID, int maxFood, std::string name);
std::string getrandpart();
void runnode();
void runloop();

int main ()
{
    //seed our randoms
    auto t = std::chrono::system_clock::now().time_since_epoch();
    srand(t.count());
    //get a file stream of the attributes
    std::ifstream lib;
    lib.open(ATTR_FILE_LOC, std::ios::in);
    if (lib.is_open() == false)
    {
        throw std::runtime_error("Couldnt open the attribute library!");
    }
    std::string lib_content;
    char byte = 0;
    while (lib.get(byte))
    {
        if (byte != '\n' && byte != '\t' && byte != ' ')
        {
            lib_content += byte;
        }
    }
    lib.close();
    //parse these attributes into a json file then read them into the proper std::vector
    auto j = json::parse(lib_content.c_str());
    int count = j["acount"];
    for (int i = 0; i < count; ++i)
    {
        std::string index = ("a" + std::to_string(i));
        json jattr = j[index];
        attribute newattr;
        newattr.name = jattr[0];
        newattr.value = jattr[1];
        attribute_library.push_back(newattr);
    }
    lib_content.clear();
    j.clear();
    std::cout << "loaded " << count << " attributes...\n";
    //change the file to read in the pet types with their assorted rarities
    lib.open(TYPES_FILE_LOC, std::ios::in);
    if (lib.is_open() == false)
    {
        throw std::runtime_error("Couldnt open the attribute library!");
    }
    byte = 0;
    while (lib.get(byte))
    {
        if (byte != '\n' && byte != '\t' && byte != ' ')
        {
            lib_content += byte;
        }
    }
    lib.close();
    //parse the animal types into the vectors
    auto j2 = json::parse(lib_content.c_str());
    count = j2["ecount"];
    for (int i = 0; i < count; ++i)
    {
        std::string index = ("e" + std::to_string(i));
        json jattr = j2[index];
        animal_type newtype;
        newtype.name = jattr[0];
        newtype.rarity = jattr[1];
        animal_library.push_back(newtype);
    }
    lib_content.clear();
    j2.clear();
    std::cout << "loaded " << count << " types...\n";
    std::cout << "Initilizing frontend\n";

    


    pet first = getrandpet(topId, 10, "Fluffles");
    pets.push_back(first);
    //runloop();
    std::cout << "Program done!";
    return 0;
}

pet getrandpet(int maxID, int maxFood, std::string name)
{
    pet starter;
    starter.head = getrandpart();
    starter.chest = getrandpart();
    starter.name = name;
    starter.max_food = rand() % maxFood + 5;
    starter.cur_food = starter.max_food;
    starter.id = maxID;
    starter.food_per_int = rand() % maxCom + 1;
    return starter;
}

std::string getrandpart()
{
    std::string out;
    while (true)
    {
        int ran = rand() % animal_library.size();
        int ran2 = rand() % maxRarity;
        if (animal_library[ran].rarity <= ran2)
        {
            out = animal_library[ran].name;
            break;
        }
    }
    return out;
}

void runnode()
{
    system("node .");
}

void runloop()
{
    std::cout << "Running main loop";
    std::thread node(runnode);
    std::cout << "Node Launched!";
    bool shouldexit = false;
    while (!shouldexit)
    {

    }
    node.join();
}