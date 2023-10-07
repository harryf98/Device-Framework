#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <list>
#include <ArduinoJson.h>

#include "Information.hpp"
#include "Property.hpp"
#include "Action.hpp"

template <typename T>
class Device
{
private:
    Information info;
    std::list<Property<T>> properties;
    std::list<Action<T>> actions;

public:
    Device(const Information &i, const std::list<Property<T>> &p, const std::list<Action<T>> &a) : info(i), properties(p), actions(a) {}

    Device(const int id, const String name, const String model, const String manufacturer, const String desc) : info(id, name, model, manufacturer, desc) {}

    Device();

    int getId() { return info.getId(); }
    String getName() { return info.getName(); }
    String getModel() { return info.getModel(); }
    String getManufacturer() { return info.getManufacturer(); }
    String getDescription() { return info.getDescription(); }

    void addProperty(Property<T> property) { properties.push_back(property); }
    std::list<Property<T>> getProperties() const { return properties; }

    void addAction(Action<T> action) { actions.push_back(action); }
    std::list<Action<T>> getActions() const { return actions; }

    String getTDJson()
    {
        StaticJsonDocument<2048> jsonDoc;
        JsonObject root = jsonDoc.to<JsonObject>();

        root["id"] = getId();
        root["name"] = getName();
        root["model"] = getModel();
        root["manufacturer"] = getManufacturer();
        root["description"] = getDescription();

        JsonArray propertiesArray = root.createNestedArray("properties");
        for (Property<T> &property : properties)
        {
            JsonObject prop = propertiesArray.createNestedObject();
            prop["name"] = property.getName();
            prop["description"] = property.getDescription();
            prop["type"] = property.getType();
        }

        JsonArray actionsArray = root.createNestedArray("actions");
        for (Action<T> &action : actions)
        {
            JsonObject act = actionsArray.createNestedObject();
            act["title"] = action.getTitle();
            act["description"] = action.getDescription();
        }

        String jsonString;
        serializeJson(root, jsonString);
        return jsonString;
    }

    String formatString(String value)
    {
        value.trim();            // Strip leading and trailing whitespace
        value.toLowerCase();     // Convert to lowercase
        value.replace(" ", "_"); // Replace spaces with underscores
        return value;
    }

    void printDeviceDetails(String command)
    {
        if (command == "start")
        {
            Serial.println(getTDJson());
        }
        else if (command == "id")
        {
            Serial.println(getId());
        }
        else if (command == "name")
        {
            Serial.println(getName());
        }
        else
        {
            Serial.println("Error: Unknown command." + command);
        }
    }

    void processPropertyCommand(String command, T &obj)
    {
        if (command == "property")
        {
            for (Property<T> &property : properties)
            {
                Serial.println(property.getName() + ": " + property.getValue(obj));
            }
        }
        else if (command.startsWith("property/"))
        {
            String propertyName = command.substring(9); // 9 is the length of "property/"
            for (Property<T> &property : properties)
            {
                if (formatString(property.getName()) == propertyName)
                {
                    Serial.println(property.getValue(obj));
                    return;
                }
            }
            Serial.println("Error: Property not found.");
        }
        else
        {
            Serial.println("Error: Unknown command." + command);
        }
    }

    void processActionCommand(String command, T &obj)
    {
        if (command.startsWith("action/"))
        {
            String actionName = command.substring(7); // 7 is the length of "action/"
            bool actionFound = false;
            for (Action<T> &action : actions)
            {
                if (formatString(action.getTitle()) == actionName)
                {
                    action.doAction(obj);
                    Serial.println("Success");
                    actionFound = true;
                    break;
                }
            }
            if (!actionFound)
            {
                Serial.println("Error: Action not found.");
            }
        }
        else
        {
            Serial.println("Error: Unknown command." + command);
        }
    }

    void processIncomingCommand(String command, T &obj)
    {
        command.trim(); // Remove whitespace

        if (command == "start" || command == "id" || command == "name")
        {
            printDeviceDetails(command);
        }
        else if (command.startsWith("property"))
        {
            processPropertyCommand(command, obj);
        }
        else if (command.startsWith("action"))
        {
            processActionCommand(command, obj);
        }
        else
        {
            Serial.println("Error: Unknown command." + command);
        }
    }
};

#endif /* DEVICE_HPP */
