#ifndef INFORMATION_HPP
#define INFORMATION_HPP

struct Information
{
private:
    int id;
    String name;
    String model;
    String manufacturer;
    String description;

public:
    Information(int i, const String &name, const String &model, const String &manufacturer, const String &description) : id(i), name(name), model(model), manufacturer(manufacturer), description(description) {}

    int getId() { return id; }
    String getName() { return name; }
    String getModel() { return model; }
    String getManufacturer() { return manufacturer; }
    String getDescription() { return description; }
};

#endif /* INFORMATION_H */
