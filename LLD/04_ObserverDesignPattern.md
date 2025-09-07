# Observer Design Pattern

## Definition
The **Observer Design Pattern** is a **behavioral design pattern** that:

- Defines a **one-to-many dependency** between objects  
- When the **subject (observable)** changes state, **all its dependents (observers)** are notified automatically  
- Promotes **loose coupling** between subject and observers  

> **In short:** One subject, many observers, automatic updates.

---

## Why Use Observer Pattern
We use the **Observer Pattern** when we need:

1. **Publish–Subscribe Model** – Notifications to multiple listeners  
2. **Loose Coupling** – Subjects don’t need to know concrete observer details  
3. **Dynamic Subscription** – Observers can join/leave at runtime  
4. **Event-Driven Systems** – GUIs, messaging systems, real-time updates  

> Example: **YouTube** – One channel uploads a video, and all subscribers get notified.

---

## Implementation in C++

### 1. Subject (Observable) Interface
Defines methods to **attach, detach, and notify observers**.

```cpp
class IChannel {
public:
    virtual void subscribe(ISubscriber* subscriber) = 0;
    virtual void unsubscribe(ISubscriber* subscriber) = 0;
    virtual void notifySubscribers() = 0;
    virtual ~IChannel() {}
};
