# Decorator Design Pattern

## Definition
The **Decorator Design Pattern** is a **structural design pattern** that:

- **Adds new functionality** to objects dynamically without altering their structure
- **Wraps objects** with additional behavior using composition instead of inheritance
- Follows the **"is-a" and "has-a"** relationship principle
- Allows **stacking multiple decorators** for layered functionality

> **In short:** Wrap objects to add features dynamically, like adding toppings to a pizza.

---

## Why Use Decorator Pattern
We use the **Decorator Pattern** when we need:

1. **Runtime Enhancement** – Add features to objects at runtime
2. **Avoid Class Explosion** – Prevent creating numerous subclasses for every combination
3. **Single Responsibility** – Each decorator handles one specific enhancement
4. **Flexible Combinations** – Mix and match decorators as needed

> Example: **Mario Power-ups** – Start with basic Mario, add height, gun, star power in any combination.

---

## Implementation in C++

### 1. Component Interface
Defines the **common interface** for both concrete components and decorators.

```cpp
class Character {
public:
    virtual string getAbilities() const = 0;
    virtual ~Character() {}  // Virtual destructor
};
```

### 2. Concrete Component
The **base object** that can be decorated with additional functionality.

```cpp
class Mario : public Character {
public:
    string getAbilities() const override {
        return "Mario";
    }
};
```

### 3. Abstract Decorator
**Base decorator class** that maintains a reference to the wrapped component.

```cpp
class CharacterDecorator : public Character {
protected:
    Character* character;  // Wrapped component
public:
    CharacterDecorator(Character* c) : character(c) {}
    virtual ~CharacterDecorator() {}
};
```

### 4. Concrete Decorators
**Specific decorators** that add individual features to the wrapped component.

```cpp
// Height-Increasing Power-Up
class HeightUp : public CharacterDecorator {
public:
    HeightUp(Character* c) : CharacterDecorator(c) {}
    
    string getAbilities() const override {
        return character->getAbilities() + " with HeightUp";
    }
};

// Gun Shooting Power-Up
class GunPowerUp : public CharacterDecorator {
public:
    GunPowerUp(Character* c) : CharacterDecorator(c) {}
    
    string getAbilities() const override {
        return character->getAbilities() + " with Gun";
    }
};

// Star Power-Up (temporary ability)
class StarPowerUp : public CharacterDecorator {
public:
    StarPowerUp(Character* c) : CharacterDecorator(c) {}
    
    string getAbilities() const override {
        return character->getAbilities() + " with Star Power (Limited Time)";
    }
    
    ~StarPowerUp() {
        cout << "Destroying StarPowerUp Decorator" << endl;
    }
};
```

---

## Usage Example

```cpp
int main() {
    // Create a basic Mario character
    Character* mario = new Mario();
    cout << "Basic Character: " << mario->getAbilities() << endl;
    
    // Decorate Mario with a HeightUp power-up
    mario = new HeightUp(mario);
    cout << "After HeightUp: " << mario->getAbilities() << endl;
    
    // Decorate Mario further with a GunPowerUp
    mario = new GunPowerUp(mario);
    cout << "After GunPowerUp: " << mario->getAbilities() << endl;
    
    // Finally, add a StarPowerUp decoration
    mario = new StarPowerUp(mario);
    cout << "After StarPowerUp: " << mario->getAbilities() << endl;
    
    delete mario;
    return 0;
}
```

**Output:**
```
Basic Character: Mario
After HeightUp: Mario with HeightUp
After GunPowerUp: Mario with HeightUp with Gun
After StarPowerUp: Mario with HeightUp with Gun with Star Power (Limited Time)
Destroying StarPowerUp Decorator
```

---

## Key Benefits

1. **Flexibility** – Add/remove features at runtime
2. **Composition over Inheritance** – Avoid deep inheritance hierarchies
3. **Single Responsibility** – Each decorator has one job
4. **Open/Closed Principle** – Open for extension, closed for modification

---

## Real-World Applications

- **GUI Components** – Adding borders, scrollbars, shadows to windows
- **I/O Streams** – BufferedReader, GZIPInputStream wrapping FileInputStream
- **Coffee Shop** – Adding milk, sugar, whipped cream to base coffee
- **Game Development** – Power-ups, weapon attachments, character enhancements

---

## Structure Diagram

```
Component Interface (Character)
    ↑
    ├── Concrete Component (Mario)
    └── Abstract Decorator (CharacterDecorator)
            ↑
            ├── HeightUp
            ├── GunPowerUp
            └── StarPowerUp
```

The Decorator pattern provides a flexible alternative to subclassing for extending functionality, making it perfect for scenarios where you need to add responsibilities to objects dynamically and transparently.