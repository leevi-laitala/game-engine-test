//#ifndef SYSTEMMANAGER_HPP
//#define SYSTEMMANAGER_HPP
//
//#include <memory>
//#include <unordered_map>
//#include <typeinfo>
//
//#include "entity.hpp"
//#include "system.hpp"
//
//#include "engine.hpp"
//
//class SystemManager
//{
//public:
//    template<class T>
//    std::shared_ptr<T> registerSystem(Engine *engine)
//    {
//        const char* name = typeid(T).name();
//
//        auto system = std::make_shared<T>(engine);
//        m_mapSystems.insert({name, system});
//        return system;
//    }
//
//    template<class T>
//    void setSignature(const Signature& s)
//    {
//        const char* name = typeid(T).name();
//        m_mapSignatures.insert({name, s});
//    }
//
//    // Update systems with new signature
//    void updateSignature(const Entity& entity, Signature signature)
//    {
//        for (auto const& item : m_mapSystems)
//        {
//            if ((signature & m_mapSignatures[item.first]) == m_mapSignatures[item.first])
//            {
//                item.second->m_setEntities.insert(entity);
//            } else
//            {
//                item.second->m_setEntities.erase(entity);
//            }
//        }
//    }
//
//    // Remove entity from systems
//    void purgeEntity(const Entity& entity)
//    {
//        for (auto const& item : m_mapSystems)
//        {
//            item.second->m_setEntities.erase(entity);
//        }
//    }
//
//private:
//    std::unordered_map<const char*, std::shared_ptr<System>> m_mapSystems{};
//    std::unordered_map<const char*, Signature> m_mapSignatures{};
//};
//
//#endif // SYSTEMMANAGER_HPP