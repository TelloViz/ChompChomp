#pragma once
#include <string>

class NamedEntity
{
public:
    virtual std::string Name() const = 0;
    virtual ~NamedEntity() {}
};