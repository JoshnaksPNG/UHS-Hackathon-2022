#include "defines.h"
#include "json.hpp"

#define ATTR_FILE_LOC "/Users/moose/UHS-Hackathon-2022/back_end_data/attributes.json"
#define TYPES_FILE_LOC "/Users/moose/UHS-Hackathon-2022/back_end_data/pet_types.json"
#define TRANSP_FIL_LOC "/Users/moose/UHS-Hackathon-2022/c2j.json"
#define READ_FILE_LOC "/Users/moose/UHS-Hackathon-2022/j2c.json"

int food_store = 100;
int topId = 0;
int maxRarity = 15;
int maxCom = 5;
int day = 0;
std::vector<pet> pets;
std::vector<attribute> attribute_library;
std::vector<animal_type> animal_library;
std::vector<std::string> names_list = {"Williams", "Charles", "Conklin", "Joseph", "Moose", "Josh", "Juliana Joy",
"Griffalililith", "Mike", "Gregory", "John", "Jeffery", "Smith", "Cicero", "Denver", "Daryyll", "Luna", "Bella", "Lily", "Lucy", "Nala", "Kitty", "Chloe", "Stella", "Zoe", "Lola"};

using json = nlohmann::json;


pet getrandpet(int maxID, int maxFood, int qcount);
std::string getrandpart();
void runnode();
void runloop();
json getstate(pet* primary);
state readstate();

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
    std::cout << "initilizing frontend...\n";
    pet first = getrandpet(topId, 10, (rand() % 5 + 1));
    pets.push_back(first);
    runloop();
    std::cout << "Program done!";
    return 0;
}

pet getrandpet(int maxID, int maxFood, int qcount)
{
    pet starter;
    
    starter.head = getrandpart();
    starter.chest = getrandpart();
    starter.name = names_list[rand() % names_list.size()];
    starter.age = 0;
    starter.max_food = rand() % maxFood + 5;
    starter.cur_food = starter.max_food;
    starter.id = maxID;
    topId++;
    starter.food_per_int = rand() % maxCom + 1;
    for (int i = 0; i < qcount; ++i)
    {
        attribute r = attribute_library[(rand() % attribute_library.size())];
        starter.qualities.push_back(r);
    }
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
    std::cout << "generating handshake...\n";
    pet first = pets[0];
    json shake = getstate(&first);
    std::ofstream o(TRANSP_FIL_LOC, std::ofstream::trunc);
    o << std::setw(4) << shake << std::endl;
    o.close();
    std::cout << "running main loop...\n";

    std::thread node(runnode);

    std::cout << "node launched...\n";
    bool shouldexit = false;
    int laststamp = 0;
    int mainindex = 0;
    int wait = 0;
    while (!shouldexit)
    {
        wait++;
        if (pets.size() == 0)
        {
            break;
        }
        state action = readstate();
        if (first.id != action.id)
        {
            for (int i = 0; i < pets.size(); ++i)
            {
                if (pets[i].id == action.id)
                {
                    first = pets[i];
                    mainindex = first.id;
                }
            }
        }
        if (action.stamp != laststamp)
        {
            if (action.name == "kill")
            {
                for (int i = 0; i < pets.size(); ++i)
                {
                    if (pets[i].id == action.id)
                    {
                        pets.erase(pets.begin() + i);
                        if (pets.size() == 0)
                        {
                            shouldexit = true;
                        }
                        if ((i-1) > 0)
                        {
                            mainindex = i-1;
                        }
                        else
                        {
                            mainindex = i+1;
                        }
                    }
                }

                //todo improve food quality 
                int accumulator = 0;
                for (int i = 0; i < first.qualities.size(); ++i)
                {
                    accumulator += first.qualities[i].value;
                }
                food_store += accumulator + first.age;
            }
            else if (action.name == "new")
            {
                //todo FIX THIS BAD BOY
                pet npet = getrandpet(topId, 20, (rand() % 5 + 1));
                pets.push_back(npet);
                mainindex = (pets.size() - 1);
            }
            else if (action.name == "exit")
            {
                shouldexit = true;
            }
            else if (action.name == "moveleft")
            {
                if ((pets.size() - 1) < 0)
                {
                    mainindex = pets.size();
                }
                else
                {
                    mainindex = (mainindex - 1);
                }
                first = pets[mainindex];
            }
            else if (action.name == "moveright")
            {
                if ((pets.size() + 1) > pets.size())
                {
                    mainindex = 0;
                }
                else
                {
                    mainindex = (mainindex + 1);
                }
                first = pets[mainindex];
            }

            
        }
        laststamp = action.stamp;

        //do the daily handling
        if (wait > 1000)
        {
            wait = 0;
            day += 1;
            for (pet p : pets)
            {
                p.cur_food -= p.food_per_int;
                if (p.cur_food <= 0)
                {
                    for (int i = 0; i < pets.size(); ++i)
                    {
                        if (pets[i].id == action.id)
                        {
                            pets.erase(pets.begin() + i);
                            if (pets.size() == 0)
                            {
                                shouldexit = true;
                            }
                            if ((i-1) > 0)
                            {
                                mainindex = i-1;
                            }
                            else
                            {
                                mainindex = i+1;
                            }
                        }
                    }
                }
                p.age += 1;
            }
        }

        //push the new state
        json shake = getstate(&first);
        std::ofstream o(TRANSP_FIL_LOC, std::ofstream::trunc);
        o << std::setw(4) << shake << std::endl;
        o.close();
    }

    node.join();
}

json getstate(pet* primary)
{
    json attr;
    for (attribute i : primary->qualities)
    {
        attr.push_back({i.name, i.value});
    }
    json shake = {
        {"currentanimal",
        {
                {"name", primary->name},
                {"head", primary->head},
                {"chest", primary->chest},
                {"maxfood", primary->max_food},
                {"curfood", primary->cur_food},
                {"id", primary->id},
                {"attributes", attr}
        }},
        {"world",
        {
            {"petcount", pets.size()},
            {"feedstore", food_store},
            {"day", day}
        }}
    };
    return shake;
}

state readstate()
{
    std::ifstream lib;
    lib.open(READ_FILE_LOC, std::ios::in);
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
    state out;
    auto j = json::parse(lib_content.c_str());
    out.id = j["currentAnimal"];
    out.name = j["currentAction"];
    out.stamp = j["stamp"];
    return out;
}