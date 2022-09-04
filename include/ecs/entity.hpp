#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <bitset>

const uint32_t MAX_COMPONENTS = 8;
const uint32_t MAX_ENTITIES = 8;

using Entity = uint32_t;
using Signature = std::bitset<MAX_COMPONENTS>;

#endif // ENTITY_HPP