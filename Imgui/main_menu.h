#pragma once
#include <vector>
#include <map>
#include <string>
#include <functional>
#include "base_control.h"

class Main_menu : public Base_control
{
public:
    Main_menu();
    void Render() override;
    float Get_height();
    template<class T> void AddMenu(const std::string& name, const std::string& item, T* const object = nullptr, void(T::* const func)(const std::string&) = nullptr)
    {
        menus[name].insert(menus[name].end(), item);
        if (object) {
            callbacks[item] = std::bind(func, object, std::placeholders::_1);
        }
    }
protected:
    std::map<std::string, std::vector<std::string>> menus;
    std::map<std::string, std::function<void(const std::string&)>> callbacks;
    void On_click_item(const std::string& item);
};