# Singleton Design Pattern —

## **Definition**
The **Singleton Design Pattern** is a creational design pattern that:
- **Ensures only one instance** of a class exists throughout the application lifecycle
- **Provides global access** to that single instance
- **Controls instantiation** by making constructor private

> In short: One class, one instance, global access point.

---

## **Why Use Singleton Pattern**

We use **Singleton** when we need:

1. **Single Point of Control** – Database connections, logging, configuration settings
2. **Resource Management** – Expensive objects that should be created only once
3. **Global State** – Shared data across the entire application
4. **Thread Pool Management** – Single thread pool manager for the application

> _Think of it like a government: there's only one president at a time, and everyone knows how to reach them._

---

## **Implementation Approaches**

### **1. Simple Lazy Initialization**
```cpp
// File: 03_simpleSingletonDesignPattern.cpp
class Singleton {
private:
    static Singleton* instance;
    Singleton() {
        cout << "Singleton Constructor called" << endl;
    }
public:
    static Singleton* getInstance() {
        if(instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }
};
```

**How it works:**
- Constructor is private (prevents direct instantiation)
- Static `getInstance()` method checks if instance exists
- Creates instance only on first call (lazy initialization)
- Returns same instance on subsequent calls

**Drawbacks:**
❌ **Not Thread-Safe** – Multiple threads can create multiple instances  
❌ **Race Conditions** – Two threads might check `instance == nullptr` simultaneously  
❌ **Memory Leak** – Instance is never deleted (minor issue for singletons)  

---

### **2. Thread-Safe with Mutex (Always Lock)**
```cpp
// File: 03_ThreadSafeSingletonDesignPattern.cpp
class Singleton {
private:
    static Singleton* instance;
    static mutex mtx;
    
public:
    static Singleton* getInstance() {
        lock_guard<mutex> lock(mtx); // Lock for every access
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }
};
```

**How it works:**
- Uses mutex to ensure thread safety
- Locks on every `getInstance()` call
- Only one thread can access the method at a time

**Drawbacks:**
❌ **Performance Overhead** – Locks on every call, even after instance is created  
❌ **Serialization** – All threads must wait, reducing concurrency  
❌ **Unnecessary Locking** – Continues locking after singleton is already initialized  

---

### **3. Thread-Safe Double-Checked Locking**
```cpp
// File: 03_ThreadSafeDoubleLockingSingletonDesignPattern.cpp
class Singleton {
private:
    static Singleton* instance;
    static mutex mtx;
    
public:
    static Singleton* getInstance() {
        if (instance == nullptr) {          // First check (no locking)
            lock_guard<mutex> lock(mtx);     // Lock only if needed
            if (instance == nullptr) {       // Second check (after lock)
                instance = new Singleton();
            }
        }
        return instance;
    }
};
```

**How it works:**
- **First Check**: Quick check without locking (performance optimization)
- **Lock**: Only lock if instance doesn't exist
- **Second Check**: Verify instance is still null after acquiring lock
- **Create**: Create instance only if still needed

**Benefits:**
✅ **Thread-Safe** – Prevents race conditions  
✅ **Performance Optimized** – Minimal locking overhead  
✅ **Lazy Initialization** – Creates instance only when needed  

**Drawbacks:**
❌ **Complex Code** – More difficult to understand and maintain  
❌ **Compiler Optimization Issues** – May not work correctly with aggressive compiler optimizations  
❌ **Memory Ordering** – Requires careful consideration of memory barriers  

---

### **4. Thread-Safe Eager Initialization**
```cpp
// File: 03_ThreadSafeEagerSingletonDesignPattern.cpp
class Singleton {
private:
    static Singleton* instance;
    
public:
    static Singleton* getInstance() {
        return instance;
    }
};

// Initialize at program startup
Singleton* Singleton::instance = new Singleton();
```

**How it works:**
- Instance is created at program startup (before `main()`)
- Static initialization is thread-safe in C++
- `getInstance()` simply returns pre-created instance

**Benefits:**
✅ **Thread-Safe** – Static initialization guarantees thread safety  
✅ **Simple Code** – No complex locking logic  
✅ **Fast Access** – No checks or locks in `getInstance()`  

**Drawbacks:**
❌ **Eager Loading** – Creates instance even if never used  
❌ **Startup Time** – Increases program initialization time  
❌ **Static Initialization Order** – May cause issues if singleton depends on other static objects  

---

## **Comparison Table**

| Implementation | Thread Safety | Performance | Memory Usage | Complexity |
|---------------|---------------|-------------|--------------|------------|
| **Simple Lazy** | ❌ No | ⚡ Fast | 💾 Efficient | 😊 Simple |
| **Always Lock** | ✅ Yes | 🐌 Slow | 💾 Efficient | 😊 Simple |
| **Double-Check** | ✅ Yes | ⚡ Fast | 💾 Efficient | 😰 Complex |
| **Eager Init** | ✅ Yes | ⚡ Fastest | 💾 May waste | 😊 Simple |

---

## **When to Use Each Approach**

### **Simple Lazy Initialization**
- Single-threaded applications
- Prototypes or educational examples
- When thread safety is not a concern

### **Thread-Safe with Always Lock**
- Multi-threaded applications
- When `getInstance()` is called infrequently
- When simplicity is more important than performance

### **Double-Checked Locking**
- High-performance multi-threaded applications
- Frequent `getInstance()` calls
- When both thread safety and performance are critical

### **Eager Initialization**
- When singleton will definitely be used
- Simple multi-threaded applications
- When initialization cost is low

---

## **Real-World Examples**

- **Logger**: Single logging instance across the application
- **Database Connection Pool**: Manage connections centrally
- **Configuration Manager**: Global access to app settings
- **Cache Manager**: Single point for caching operations
- **Thread Pool**: Manage worker threads globally


---

## **Modern C++ Alternative (Recommended)**

```cpp
class Singleton {
public:
    static Singleton& getInstance() {
        static Singleton instance;  // Thread-safe since C++11
        return instance;
    }
    
private:
    Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};
```

**Benefits of Modern Approach:**
✅ **Thread-Safe** – C++11 guarantees thread-safe static initialization  
✅ **No Memory Leaks** – Automatic cleanup when program ends  
✅ **Simple** – No explicit mutex or double-checking needed  
✅ **Exception Safe** – Handles constructor exceptions properly  

---

## **Best Practices**

1. **Prefer Modern C++11 Approach** – Use static local variables
2. **Delete Copy Operations** – Prevent accidental copying
3. **Consider Dependency Injection** – Singletons can make testing difficult
4. **Be Careful with Global State** – Can lead to tight coupling
5. **Document Thread Safety** – Clearly specify which approach you're using

---

## **Anti-Patterns and Warnings**

⚠️ **Global State Issues** – Makes unit testing difficult  
⚠️ **Hidden Dependencies** – Classes using singleton have implicit dependencies  
⚠️ **Tight Coupling** – Hard to modify or extend  
⚠️ **Difficult Mocking** – Hard to create test doubles  

> Consider if you really need Singleton or if Dependency Injection would be better.

---
