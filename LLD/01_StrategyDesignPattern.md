# Strategy Design Pattern —

## **Definition**
The **Strategy Design Pattern** is a behavioral design pattern that:
- Defines a **family of algorithms or behaviors**.
- Encapsulates each behavior in its own **Strategy class**.
- Makes behaviors **interchangeable** without altering the class that uses them.

> In short: Instead of hardcoding a behavior, we "inject" it so it can be swapped at runtime.

---

## **Why This Approach (Composition over Inheritance)**

We prefer **composition** over **inheritance** because:

1. **Flexibility** – Change an object's behavior at runtime by swapping out strategies.
2. **Reusability** – The same strategy class can be reused with multiple objects.
3. **Loose Coupling** – The context (main class) depends only on the interface, not the concrete implementation.
4. **Avoid Pitfalls of Inheritance** – Prevents rigid and deep class hierarchies that are hard to maintain.

> _Think of it like Lego blocks: plug in the behaviors you need instead of locking them in at compile time._

---

## **How This Approach Works**

1. **Define Strategy Interfaces**
   
   Each capability (e.g., Walk, Talk, Fly) has its own interface with a method signature.
   
   Example:
   - `Walkable` → `walk()`
   - `Talkable` → `talk()`

2. **Create Concrete Strategies**
   
   Multiple implementations for each interface.
   
   Example:
   - `NormalWalk` / `NoWalk`
   - `NormalTalk` / `NoTalk`

3. **Create a Context Class**
   
   The **Context** (e.g., `Robot`) holds references to strategy objects.
   It delegates work to them instead of implementing behavior itself.

4. **Client Chooses the Behavior**
   
   When creating a context object, the client decides which strategy to use.
   This can also be changed at runtime.

---

## **Code Example**

```cpp
// See: 01_StrategyDesignPattern.cpp
class Walkable {
public:
    virtual void walk() = 0;
    virtual ~Walkable() = default;
};

class NormalWalk : public Walkable {
public:
    void walk() override {
        std::cout << "Walking normally" << std::endl;
    }
};

class Robot {
private:
    std::unique_ptr<Walkable> walkBehavior;
    std::unique_ptr<Talkable> talkBehavior;
    
public:
    Robot(std::unique_ptr<Walkable> walk, std::unique_ptr<Talkable> talk)
        : walkBehavior(std::move(walk)), talkBehavior(std::move(talk)) {}
    
    void performWalk() { walkBehavior->walk(); }
    void performTalk() { talkBehavior->talk(); }
    
    // Runtime behavior change
    void setWalkBehavior(std::unique_ptr<Walkable> newWalk) {
        walkBehavior = std::move(newWalk);
    }
};
```

---

## **When to Use Strategy Pattern**

✅ **Multiple Algorithms**: When you have multiple ways to perform the same task  
✅ **Runtime Selection**: When you need to choose algorithms at runtime  
✅ **Avoid Conditionals**: When you want to eliminate large if-else or switch statements  
✅ **Open/Closed Principle**: When you want to add new behaviors without modifying existing code  
✅ **Testing**: When you need to easily swap behaviors for testing purposes  

---

## **Benefits**

✅ **Runtime Flexibility** – Change behavior dynamically without recompilation  
✅ **Code Reusability** – Same strategies can be used across different contexts  
✅ **Easy Extension** – Add new strategies without touching existing code  
✅ **Separation of Concerns** – Each strategy handles one specific algorithm  
✅ **Testability** – Easy to test individual strategies and mock behaviors  
✅ **Eliminates Conditionals** – No more complex if-else chains for behavior selection  

---

## **Drawbacks**

❌ **Increased Complexity** – More classes and interfaces to manage  
❌ **Client Awareness** – Clients must know about different strategy options  
❌ **Object Overhead** – Additional objects created for each strategy  
❌ **Communication Overhead** – Context and strategy must communicate through interface  

---

## **Strategy vs Other Patterns**

| Pattern | Purpose | Key Difference |
|---------|---------|----------------|
| **Strategy** | Choose algorithm at runtime | Focuses on interchangeable algorithms |
| **State** | Change behavior based on internal state | Behavior changes automatically with state |
| **Command** | Encapsulate requests as objects | Focuses on action execution and undo/redo |
| **Template Method** | Define algorithm skeleton in base class | Uses inheritance, not composition |

---

## **Real-World Examples**

- **Payment Processing**: Different payment methods (Credit Card, PayPal, Bitcoin)
- **Sorting Algorithms**: QuickSort, MergeSort, BubbleSort based on data size
- **Compression**: ZIP, RAR, 7Z compression strategies
- **Game AI**: Different AI behaviors for NPCs (Aggressive, Defensive, Neutral)
- **Validation**: Different validation rules for forms or data input
- **Navigation**: Different route calculation algorithms (Fastest, Shortest, Scenic)

---

## **Implementation Variations**

### **1. Interface-Based (Recommended)**
```cpp
class Strategy {
public:
    virtual void execute() = 0;
    virtual ~Strategy() = default;
};
```

### **2. Function Object Based**
```cpp
class Context {
    std::function<void()> strategy;
public:
    void setStrategy(std::function<void()> s) { strategy = s; }
    void executeStrategy() { strategy(); }
};
```

### **3. Template-Based**
```cpp
template<typename StrategyType>
class Context {
    StrategyType strategy;
public:
    void execute() { strategy.execute(); }
};
```

---

## UML Diagram

![Strategy Design Pattern UML](UML/01_StrategyDesignPattern.drawio.svg)

---

## **Related Patterns**

- **State Pattern**: Similar structure but focuses on state-dependent behavior
- **Command Pattern**: Can use Strategy pattern for different command execution strategies  
- **Factory Pattern**: Often used together to create appropriate strategies
- **Decorator Pattern**: Both use composition, but Decorator adds responsibilities