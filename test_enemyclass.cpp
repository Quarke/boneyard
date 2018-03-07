#include "json.cpp"
#include "enemy.h"

void GameState::createEnemyMap(){
   std::ifstream ifs("enemy.json");

    // Reader is deprecated, we are supposed to use a CharReaderBuilder and streams instead
    // Which is newer better practice, but it works so fuck it
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj); // reader can also read strings

    // Create an empty unordered_map and
    Enemy e;
    for(Json::Value::iterator i = obj.begin(); i !=obj.end(); ++i){
        Json::Value key = i.key();
        Json::Value value = (*i);

        e.name = value["name"].asString();
        e.health_current = value["health_current`"];
        e.health_max = value["health_max"];
        e.damage_person = value["damage_person"];
        e.damage_self = value["damage_self"];

        for(auto itr : value["object"]){
            e.objects.push_back(itr.asString());
        }

        std::string stringKey = key.asString();
        enemyMap[stringKey] = e;
    }
}
