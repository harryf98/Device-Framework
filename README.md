# Device Framework for Arduino

## Introduction & Purpose

Standardizing communication and integration across different device architectures is hard because there are so many Internet of Things (IoT) devices. The Device Framework is a new way to solve this problem that was created as part of a bachelor's thesis at the University of Vienna. It aims to make interactions between devices simpler and ensure that different IoT devices work the same way.

At the core of this framework is an abstraction mechanism that standardizes device data, command handling, and serial communication. Inspired by the Web of Things Thing Description (WoT TD), the framework provides a centralized means of device representation—including properties, actions, and relevant information data. This eliminates the need for custom coding and paves the way for more seamless IoT setups.

## Web of Things (WoT) Thing Description (TD)

The Web of Things Thing Description (WoT TD) serves as a cornerstone for the `Device Framework`. It provides a standardized representation of IoT devices, encapsulating their properties, actions, and events. By leveraging the principles of WoT TD, the framework ensures a consistent and unified approach to device interactions, making it easier for developers and users to integrate and communicate with a wide range of IoT devices.

## Features

-   **Device Representation**: Define devices with unique properties and actions.
-   **Structured Interaction**: Interact with devices using a consistent and structured approach.
-   **Extensibility**: Easily extend the framework to accommodate various device types.

## Usage

### Integration

To integrate the `Device Framework` into your Arduino project, start by including the main header file:

```cpp
#include <Device.hpp>
```

### Define Your Device

Define your device by specifying its information, properties, and actions:

1. **Device Information**:

    ```cpp
    Information(Id, Name, Model, Manufacturer, Description)
    ```

2. **Device Properties**:

    ```cpp
    Property(Name, Description, Type, PointerFunction)
    ```

3. **Device Actions**:

    ```cpp
    Action(Name, Description, PointerFunction)
    ```

4. **Create the Device Object**:
    ```cpp
    Device<DeviceClass> myDevice(info, properties, actions);
    ```

### Interact via Serial Commands

Once your device is defined, you can send commands through the Serial interface. The framework processes these commands based on their structure:

-   **Device WoT TD (JSON)**:

    ```
    start
    ```

-   **Device Details (STRING)**:

    ```
    id
    name
    ```

-   **Query Properties (STRING)**:

    ```
    property/<PropertyName>
    ```

-   **Initiate Actions (VOID)**:
    ```
    action/<ActionName>
    ```

For a comprehensive understanding and advanced configurations, refer to the provided examples and documentation within the repository.

## Contribution

Contributions to the `Device Framework` are warmly welcomed. Whether it's bug fixes, feature enhancements, documentation improvements, or any other changes, your input is valued. Please ensure to fork the repository, create a feature branch, and submit a pull request for review.

## License

This project is licensed under the Apache License 2.0. For more details, see the [LICENSE](LICENSE) file.

## Acknowledgments

This framework was developed as part of a bachelor thesis at the University of Vienna. Gratitude is extended to all mentors, peers, and participants who provided insights, feedback, and support throughout the project's journey.
