# Notification System Design Patterns

## Overview
This C++ implementation demonstrates a **comprehensive notification system** that combines multiple design patterns to create a flexible, extensible, and maintainable architecture:

- **Decorator Pattern** – Dynamically adds features to notifications (timestamps, signatures)
- **Observer Pattern** – Automatically notifies multiple observers when notifications arrive
- **Singleton Pattern** – Ensures single instance of notification service
- **Strategy Pattern** – Supports multiple notification delivery methods (Email, SMS, Popup)

> **In short:** A robust notification system where you can create rich notifications and deliver them through multiple channels automatically.

---

## Why This Architecture?

This design solves common notification system challenges:

1. **Dynamic Enhancement** – Add timestamps, signatures, or other metadata without modifying core notification logic
2. **Multiple Recipients** – Automatically notify loggers, engines, and other components
3. **Flexible Delivery** – Support email, SMS, popup, and future delivery methods
4. **Centralized Management** – Single service manages all notifications
5. **Loose Coupling** – Components don't directly depend on each other

> Example: **Slack/Discord-like System** – Messages can have reactions, threads, formatting, and be delivered to multiple channels simultaneously.

---

## Pattern Implementations

### 1. Decorator Pattern - Notification Enhancement

#### Component Interface
Defines the **common interface** for all notifications.

```cpp
class INotification {
public:
    virtual string getContent() const = 0;
    virtual ~INotification() {}
};
```

#### Concrete Component
The **base notification** that can be enhanced with decorators.

```cpp
class SimpleNotification : public INotification {
private:
    string text;
public:
    SimpleNotification(const string& msg) : text(msg) {}
    
    string getContent() const override {
        return text;
    }
};
```

#### Abstract Decorator
**Base decorator class** that wraps notification objects.

```cpp
class INotificationDecorator : public INotification {
protected:
    INotification* notification;
public:
    INotificationDecorator(INotification* n) : notification(n) {}
    virtual ~INotificationDecorator() { delete notification; }
};
```

#### Concrete Decorators
**Specific enhancers** that add individual features.

```cpp
// Adds timestamp to notifications
class TimestampDecorator : public INotificationDecorator {
public:
    TimestampDecorator(INotification* n) : INotificationDecorator(n) {}
    
    string getContent() const override {
        return "[2025-04-13 14:22:00] " + notification->getContent();
    }
};

// Adds signature to notifications
class SignatureDecorator : public INotificationDecorator {
private:
    string signature;
public:
    SignatureDecorator(INotification* n, const string& sig) 
        : INotificationDecorator(n), signature(sig) {}
    
    string getContent() const override {
        return notification->getContent() + "\n-- " + signature + "\n\n";
    }
};
```

---

### 2. Observer Pattern - Automatic Notification

#### Observer Interface
Defines **update mechanism** for all observers.

```cpp
class IObserver {
public:
    virtual void update() = 0;
    virtual ~IObserver() {}
};
```

#### Observable Interface & Implementation
Manages **observer list** and triggers updates.

```cpp
class NotificationObservable : public IObservable {
private:
    vector<IObserver*> observers;
    INotification* currentNotification;
    
public:
    void addObserver(IObserver* obs) override {
        observers.push_back(obs);
    }
    
    void notifyObservers() override {
        for (auto observer : observers) {
            observer->update();
        }
    }
    
    void setNotification(INotification* notification) {
        if (currentNotification != nullptr) {
            delete currentNotification;
        }
        currentNotification = notification;
        notifyObservers();  // Automatic notification
    }
};
```

---

### 3. Singleton Pattern - Service Management

#### Notification Service
**Single instance** manages entire notification system.

```cpp
class NotificationService {
private:
    static NotificationService* instance;
    NotificationObservable* observable;
    vector<INotification*> notifications;
    
    NotificationService() {  // Private constructor
        observable = new NotificationObservable();
    }
    
public:
    static NotificationService* getInstance() {
        if(instance == nullptr) {
            instance = new NotificationService();
        }
        return instance;
    }
    
    void sendNotification(INotification* notification) {
        notifications.push_back(notification);
        observable->setNotification(notification);  // Triggers observers
    }
};
```

---

### 4. Strategy Pattern - Delivery Methods

#### Strategy Interface
Defines **delivery contract** for all notification methods.

```cpp
class INotificationStrategy {
public:    
    virtual void sendNotification(string content) = 0;
};
```

#### Concrete Strategies
**Specific delivery methods** for different channels.

```cpp
// Email delivery strategy
class EmailStrategy : public INotificationStrategy {
private:
    string emailId;
public:
    EmailStrategy(string emailId) : emailId(emailId) {}
    
    void sendNotification(string content) override {
        cout << "Sending email to: " << emailId << "\n" << content;
    }
};

// SMS delivery strategy
class SMSStrategy : public INotificationStrategy {
private:
    string mobileNumber;
public:
    SMSStrategy(string number) : mobileNumber(number) {}
    
    void sendNotification(string content) override {
        cout << "Sending SMS to: " << mobileNumber << "\n" << content;
    }
};

// Popup delivery strategy
class PopUpStrategy : public INotificationStrategy {
public:
    void sendNotification(string content) override {
        cout << "Showing popup: \n" << content;
    }
};
```

---

### 5. Observer Implementations

#### Logger Observer
**Logs all notifications** for audit and debugging.

```cpp
class Logger : public IObserver {
private:
    NotificationObservable* notificationObservable;
public:
    Logger() {
        notificationObservable = NotificationService::getInstance()->getObservable();
        notificationObservable->addObserver(this);
    }
    
    void update() {
        cout << "Logging New Notification: \n" 
             << notificationObservable->getNotificationContent();
    }
};
```

#### Notification Engine Observer
**Delivers notifications** using multiple strategies simultaneously.

```cpp
class NotificationEngine : public IObserver {
private:
    NotificationObservable* notificationObservable;
    vector<INotificationStrategy*> notificationStrategies;
    
public:
    NotificationEngine() {
        notificationObservable = NotificationService::getInstance()->getObservable();
        notificationObservable->addObserver(this);
    }
    
    void addNotificationStrategy(INotificationStrategy* strategy) {
        notificationStrategies.push_back(strategy);
    }
    
    void update() {
        string content = notificationObservable->getNotificationContent();
        for(const auto strategy : notificationStrategies) {
            strategy->sendNotification(content);  // Multi-channel delivery
        }
    }
};
```

---

## Complete Usage Example

```cpp
int main() {
    // 1. Get notification service (Singleton)
    NotificationService* service = NotificationService::getInstance();
   
    // 2. Create observers
    Logger* logger = new Logger();  // Auto-registers with service
    NotificationEngine* engine = new NotificationEngine();
    
    // 3. Configure delivery strategies
    engine->addNotificationStrategy(new EmailStrategy("user@gmail.com"));
    engine->addNotificationStrategy(new SMSStrategy("+91 9876543210"));
    engine->addNotificationStrategy(new PopUpStrategy());

    // 4. Create enhanced notification (Decorator pattern)
    INotification* notification = new SimpleNotification("Your order has been shipped!");
    notification = new TimestampDecorator(notification);
    notification = new SignatureDecorator(notification, "Customer Care");
    
    // 5. Send notification (triggers all observers automatically)
    service->sendNotification(notification);

    delete logger;
    delete engine;
    return 0;
}
```

**Output:**
```
Logging New Notification : 
[2025-04-13 14:22:00] Your order has been shipped!
-- Customer Care

Sending email to: user@gmail.com
[2025-04-13 14:22:00] Your order has been shipped!
-- Customer Care

Sending SMS to: +91 9876543210
[2025-04-13 14:22:00] Your order has been shipped!
-- Customer Care

Showing popup: 
[2025-04-13 14:22:00] Your order has been shipped!
-- Customer Care
```

---

## Architecture Benefits

### **Flexibility**
- Add new notification types without changing existing code
- Mix and match decorators for different enhancement combinations
- Support new delivery strategies easily

### **Maintainability** 
- Each pattern handles specific responsibility
- Changes in one component don't affect others
- Easy to debug and test individual components

### **Scalability**
- Add unlimited observers for new notification processors
- Support any number of delivery strategies
- Centralized service manages complexity

### **Reliability**
- Single service instance prevents conflicts
- Automatic notification ensures no missed updates
- Clear separation of concerns

---

## Real-World Applications

- **Email Platforms** – Gmail, Outlook with formatting, signatures, auto-replies
- **Chat Applications** – Slack, Discord, WhatsApp with message enhancements
- **E-commerce** – Order updates, shipping notifications, promotional messages
- **Banking Systems** – Transaction alerts, account notifications, security warnings
- **Gaming Platforms** – Achievement notifications, friend requests, game updates

---

## System Architecture Diagram

```
┌─────────────────────────────────────────────────────────────────┐
│                    NotificationService (Singleton)              │
│  ┌─────────────────────────────────────────────────────────────┐│
│  │              NotificationObservable                        ││
│  │                                                            ││
│  │    ┌─────────────┐    ┌─────────────────────────────────┐  ││
│  │    │   Logger    │    │     NotificationEngine         │  ││
│  │    │ (Observer)  │    │       (Observer)               │  ││
│  │    └─────────────┘    │  ┌─────────────────────────────┐│  ││
│  │                       │  │     EmailStrategy           ││  ││
│  │                       │  │     SMSStrategy             ││  ││
│  │                       │  │     PopUpStrategy           ││  ││
│  │                       │  └─────────────────────────────┘│  ││
│  │                       └─────────────────────────────────┘  ││
│  └─────────────────────────────────────────────────────────────┘│
└─────────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────────┐
│                    Notification Decorators                      │
│  ┌─────────────────┐  ┌─────────────────┐  ┌─────────────────┐  │
│  │SimpleNotification│  │TimestampDecorator│  │SignatureDecorator│ │
│  └─────────────────┘  └─────────────────┘  └─────────────────┘  │
└─────────────────────────────────────────────────────────────────┘
```

This notification system demonstrates how multiple design patterns can work together to create a robust, extensible, and maintainable solution for complex software requirements.