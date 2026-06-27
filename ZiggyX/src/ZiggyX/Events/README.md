# Event System

## Summary
Each system requires specific event types. For the MVP, these are the systems and their required events:

| System | Events |
| ------ | ------ |
| User Input | Keyboard Handling, Mouse Handling |
| Physics | Movement Events *More Required* |

# Key Features for Input Handling

## Pollers
A poller will query the input devices or different sytems to check on their state. The poller will need to compare the current state with the previous state
and also developer the proper handlers to execute something on state changes. We can utilize ```GLFW``` to do this for us.

## Events
A handler such as ```Event``` base, ```KeyEvent``` which inherits from ```Event```. Our ```Event``` class will be the single event
that will have a specific event type and have the getters to determine what type of event it is. The ```KeyEvent``` will be the specific
key event that will have a series of key codes for detecting user input. ```GLFW``` will be used to read input.

## Event Buffer
We need an event buffer to place events into a queue rather than just executing events as they come in. This causes threads to be blocked.