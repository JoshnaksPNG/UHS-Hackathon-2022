#include "defines.h"
#include "json.hpp"

#define ATTR_FILE_LOC "/Users/moose/UHS-Hackathon-2022/back_end_data/attributes.json"
#define TYPES_FILE_LOC "/Users/moose/UHS-Hackathon-2022/back_end_data/pet_types.json"

int food_store = 100;
std::vector<pet> pets;
std::vector<attribute> attribute_library;
std::vector<animal_type> animal_library;

using json = nlohmann::json;

int main ()
{
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


    //TODO ADD THE INIT BACKEND FOR NODE RUN

    //YEES ADD IT IN HERE


    srand(TIME_UTC);
    int ran = rand() % animal_library.size();
    pet starter;
    starter.name = "penis";
    starter.max_food = 10;
    starter.cur_food = 10;
    return 0;
}