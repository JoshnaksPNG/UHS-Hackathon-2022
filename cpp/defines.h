#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <stdexcept>
#include <thread>

typedef struct attribute
{
    std::string name;
    int value;
} attribute;

typedef struct pet
{
    std::string name = "";
    std::vector<attribute> qualities;
    int max_food;
    int cur_food;
    int food_per_int;
    int id;
    std::string head;
    std::string chest;
} pet;

typedef struct animal_type
{
    std::string name;
    int rarity;
} animal_type;