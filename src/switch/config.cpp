#include "config.h"

#include <stdio.h>

Config::Config(const std::string& filename)
    : filename_(filename)
{
}

void Config::load()
{
    for (auto serialiseable : serialiseables_) {
        serialiseable->io(*this);
    }
}

void Config::save()
{
}

long Config::io(const std::string& section, const std::string& key, long defaultValue)
{
    return std::get<long>(getValue(section, key, defaultValue));
}

std::string Config::io(const std::string& section, const std::string& key, const std::string& defaultValue)
{
    return std::get<std::string>(getValue(section, key, defaultValue));
}

std::variant<std::string, long>& Config::getValue(const std::string& section, const std::string& key,
    const std::variant<std::string, long>& defaultValue)
{
    auto& sectionRef = sections_[section];

    if (!sectionRef.values_.count(key))
        sectionRef.values_[key] = defaultValue;

    return sectionRef.values_[key];
}