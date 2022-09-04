#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <unordered_map>
#include <string>
#include <iostream>
#include <memory>

template<typename Resource, typename ID>
class ResourceManager
{
public:
    void load(const std::string& fname, ID id)
    {
        // Load resource from disc to heap, and save it's pointer to map
        if (m_mapResources.find(id) == m_mapResources.end()) // Continue only if resource does not exist
        {
            std::shared_ptr<Resource> res = std::make_shared<Resource>();

            if (!res->loadFromFile(fname))
            {
                std::cout << "[RMgr] Could not load file " << fname << std::endl;
            } else
            {
                m_mapResources.insert({id, res});
            }

            std::cout << "[RMgr] Resource loaded. Current map size: " << m_mapResources.size() << std::endl;
        }
    }

    // Get pointer to resource
    std::shared_ptr<Resource> get(ID id)
    {
        if (m_mapResources.find(id) != m_mapResources.end()) // Check if resource exists
            return m_mapResources.at(id);

        return nullptr;
    }

    // Delete one resource
    void destroy(ID id)
    {
        if (m_mapResources.find(id) != m_mapResources.end()) // Check if resource exists
        {
            m_mapResources.erase(id);
        }

        std::cout << "[RMgr] Res deleted. Current map size: " << m_mapResources.size() << std::endl;
    }

private:
    std::unordered_map<ID, std::shared_ptr<Resource>> m_mapResources;
};

#endif // RESOURCEMANAGER_HPP