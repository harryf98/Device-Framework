#ifndef PROPERTY_HPP
#define PROPERTY_HPP

template <typename T>
class Property
{
private:
    String name;
    String description;
    String type;
    String value;
    String (T::*function)();

public:
    Property(String name, String description, String type, String (T::*function)()) : name(name), description(description), type(type), function(function) {}

    const String getName() { return name; }
    const String getDescription() { return description; }
    const String getType() { return type; }
    String getValue(T &obj)
    {
        value = (obj.*function)();
        return value;
    }
};

#endif /* PROPERTY_HPP */
