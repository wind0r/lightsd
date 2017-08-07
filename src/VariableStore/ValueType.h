#pragma once

#include <ostream>
#include <functional>

class ValueType {
public:
    using CallbackType = std::function<void(ValueType *)>;
private:
    std::vector<CallbackType> callbacks;
public:
    enum class Type {
        FLOAT, INTEGER, UNKNOWN, BOOLEAN
    };

    virtual Type getType() const = 0;

    virtual bool getBool() const = 0;

    virtual void setBool(const bool) = 0;

    virtual float getFloat() const = 0;

    virtual int getInteger() const = 0;

    virtual void setFloat(const float) = 0;

    virtual void setInteger(const int) = 0;

    virtual void addOnChangeCallback(std::function<void(ValueType *)>);

    virtual void triggerCallbacks();
};

std::ostream &operator<<(std::ostream &os, const ValueType &obj);

std::ostream &operator<<(std::ostream &os, const ValueType::Type t);
