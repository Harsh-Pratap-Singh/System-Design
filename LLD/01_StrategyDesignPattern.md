#  Strategy Design Pattern — 

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

## UML Diagram 
![Google Docs UML Diagram](UML/01_StrategyDesignPattern.drawio.svg)
