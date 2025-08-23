# Factory Design Pattern —

## **Definition**
The **Factory Design Pattern** is a creational design pattern that:
- Provides an **interface for creating objects** without specifying their exact classes.
- Encapsulates object creation logic in **factory classes or methods**.
- Makes object creation **flexible and extensible** without modifying existing code.

> In short: Instead of using `new` directly, we delegate object creation to factory methods that decide which class to instantiate.

---

## **Why This Approach (Abstraction over Direct Instantiation)**

We prefer **factory patterns** over direct object creation because:

1. **Flexibility** – Easy to add new product types without changing existing client code.
2. **Decoupling** – Client code doesn't depend on concrete classes, only interfaces.
3. **Centralized Logic** – Object creation logic is centralized and can be easily modified.
4. **Polymorphism** – Factory can return different implementations based on parameters or conditions.

> _Think of it like a vending machine: you press a button (provide parameters) and get the right product without knowing how it's made._

---

## **Types of Factory Patterns**

### 1. **Simple Factory**
- A single factory class with a method that creates objects based on input parameters.
- Not technically a "pattern" but a common programming idiom.

### 2. **Factory Method Pattern**
- Defines an interface for creating objects, but lets subclasses decide which class to instantiate.
- Each factory subclass is responsible for creating a specific type of product.

### 3. **Abstract Factory Pattern**
- Provides an interface for creating families of related or dependent objects.
- Creates multiple types of products that work together.

---

## **How This Approach Works**

### **Simple Factory:**
1. **Create Product Interface** – Define common interface for all products.
2. **Implement Concrete Products** – Create specific product classes.
3. **Create Factory Class** – Single class with creation method.
4. **Client Uses Factory** – Client calls factory method instead of `new`.

### **Factory Method:**
1. **Define Creator Interface** – Abstract creator with factory method.
2. **Implement Concrete Creators** – Each creates specific products.
3. **Define Product Hierarchy** – Product interface and implementations.
4. **Client Works with Creators** – Uses factory method to get products.

### **Abstract Factory:**
1. **Define Abstract Factory** – Interface for creating product families.
2. **Create Concrete Factories** – Each factory creates a family of products.
3. **Define Product Families** – Related products that work together.
4. **Client Uses Factory Interface** – Creates families without knowing specifics.

---

## **Code Examples**

### Simple Factory
```cpp
// See: 02_simpleFactoryDesignPattern.cpp
class ShapeFactory {
public:
    static std::unique_ptr<Shape> createShape(const std::string& type);
};
```

### Factory Method
```cpp
// See: 02_FactoryMethodDesignPattern.cpp
class VehicleFactory {
public:
    virtual std::unique_ptr<Vehicle> createVehicle() = 0;
};

class CarFactory : public VehicleFactory {
public:
    std::unique_ptr<Vehicle> createVehicle() override;
};
```

### Abstract Factory
```cpp
// See: 02_AbstractFactoryMethodDesignPattern.cpp
class GUIFactory {
public:
    virtual std::unique_ptr<Button> createButton() = 0;
    virtual std::unique_ptr<Checkbox> createCheckbox() = 0;
};

class WindowsFactory : public GUIFactory {
    // Creates Windows-style components
};

class MacFactory : public GUIFactory {
    // Creates Mac-style components
};
```

---

## **When to Use Each Pattern**

- **Simple Factory**: When you need to create objects of different types based on simple parameters, and the creation logic is straightforward.

- **Factory Method**: When you want to delegate object creation to subclasses, allowing for easy extension without modifying existing code.

- **Abstract Factory**: When you need to create families of related objects that must be used together (e.g., UI components for different operating systems).

---

## **Benefits**

✅ **Loose Coupling** – Client code doesn't depend on concrete classes  
✅ **Easy Extension** – Add new products without changing existing code  
✅ **Centralized Creation** – Object creation logic is in one place  
✅ **Polymorphism** – Work with objects through interfaces  
✅ **Testability** – Easy to mock factories for testing  

---

## **Drawbacks**

❌ **Complexity** – Can make code more complex for simple scenarios  
❌ **More Classes** – Introduces additional factory classes  
❌ **Indirection** – Extra layer between client and product creation  

---


## **Real-World Examples**

- **Database Connections**: Factory creates appropriate connection based on database type
- **UI Components**: Different factories for different operating systems or themes
- **Game Objects**: Factory creates different types of enemies, weapons, or items
- **File Parsers**: Factory returns appropriate parser based on file extension
- **HTTP Clients**: Factory creates client configured for different protocols or services

---

## **Related Patterns**

- **Builder Pattern**: Both create objects, but Builder focuses on step-by-step construction
- **Prototype Pattern**: Alternative creational pattern using cloning instead of factories
- **Singleton Pattern**: Often used together - factory itself might be a singleton