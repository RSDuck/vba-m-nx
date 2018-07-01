#pragma once

#include <map>
#include <string>
#include <variant>
#include <vector>

class Serialiseable;

struct ConfigSection {
    std::map<std::string, std::variant<std::string, long>> values_;
};

class Config {
public:
    Config(const std::string& filename);

    long io(const std::string& section, const std::string& key, long defaultValue);
    std::string io(const std::string& section, const std::string& key, const std::string& defaultValue);

    void load();
    void save();

    inline void addSerialiseable(Serialiseable* serialiseable) { serialiseables_.push_back(serialiseable); }

private:
    std::variant<std::string, long>& getValue(const std::string& section, const std::string& key,
        const std::variant<std::string, long>& defaultValue);

    std::map<std::string, ConfigSection> sections_;
    std::vector<Serialiseable*> serialiseables_;

    std::string filename_;
};

class Serialiseable {
public:
    virtual void io(Config& cfg) = 0;
};
