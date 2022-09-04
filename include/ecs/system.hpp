#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <set>
#include <unordered_map>
#include "entity.hpp" // for Entity type

class Engine;

struct System
{
    Engine *engine;
    std::set<Entity> m_setEntities;
    std::unordered_map<const char*, std::set<Entity>> m_mapEntities;
};

#endif // SYSTEM_HPP