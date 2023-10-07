#ifndef ACTION_HPP
#define ACTION_HPP

template <typename T>
class Action
{
private:
    String title;
    String description;
    void (T::*function)();

public:
    Action(const String &t, const String &d, void (T::*function)()) : title(t), description(d), function(function) {}

    String getTitle() { return title; }
    String getDescription() { return description; }
    void doAction(T &obj)
    {
        (obj.*function)();
        Serial.println("Success");
    }
};

#endif /* ACTION_HPP */
