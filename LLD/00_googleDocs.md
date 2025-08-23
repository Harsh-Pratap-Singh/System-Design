# Google Documents —

## **Definition**
A **Document Editor System** that demonstrates multiple design patterns working together:
- **Composite Pattern** for document structure (elements hierarchy)
- **Strategy Pattern** for persistence mechanisms (file vs database storage)
- **Template Method Pattern** for rendering process

> A scalable document editor supporting text and images with extensible storage options.

---

## **System Requirements**

**Current Support:**
- ✅ Text elements
- ✅ Image elements (path-based)
- ✅ Formatting elements (newlines, tabs)
- ✅ File persistence

**Future Scalability:**
- 📋 Additional element types (tables, lists, headers)
- 📋 Multiple storage backends (database, cloud)
- 📋 Different rendering formats (HTML, PDF, Markdown)

---

## **Design Approach**

### **Bottom-Up Architecture**
1. **Base Abstraction** → `DocumentElement` interface
2. **Concrete Elements** → `TextElement`, `ImageElement`, `NewLineElement`
3. **Composite Structure** → `Document` holds collection of elements
4. **Service Layer** → `DocumentEditor` manages operations
5. **Persistence Layer** → `Persistence` abstraction with concrete implementations

### **Key Design Principles**

#### **1. Single Responsibility Principle (SRP)**
- `DocumentElement` → Only handles rendering
- `Document` → Only manages element collection
- `Persistence` → Only handles storage
- `DocumentEditor` → Only manages client interactions

#### **2. Open/Closed Principle (OCP)**
- ✅ **Open for extension**: Easy to add new element types
- ✅ **Closed for modification**: Existing code doesn't change when adding features

#### **3. Dependency Inversion Principle (DIP)**
- `DocumentEditor` depends on `Persistence` abstraction, not concrete implementations
- Easy to swap storage mechanisms without changing editor logic

#### **4. Composite Pattern Implementation**
```cpp
class Document {
    vector<DocumentElement*> documentElements;  // Treats all elements uniformly
    
    string render() {
        // Delegates rendering to each element
        for (auto element : documentElements) {
            result += element->render();
        }
    }
};
```

---

## **Core Components**

### **1. Document Elements (Composite Pattern)**
```cpp
// Base abstraction
class DocumentElement {
public:
    virtual string render() = 0;
};

// Leaf implementations
class TextElement : public DocumentElement { /* text rendering */ };
class ImageElement : public DocumentElement { /* image placeholder */ };
class NewLineElement : public DocumentElement { /* line breaks */ };
```

### **2. Persistence Layer (Strategy Pattern)**
```cpp
// Storage abstraction
class Persistence {
public:
    virtual void save(string data) = 0;
};

// Concrete strategies
class FileStorage : public Persistence { /* file system */ };
class DBStorage : public Persistence { /* database */ };
```

### **3. Document Manager**
```cpp
class Document {
    vector<DocumentElement*> documentElements;
public:
    void addElement(DocumentElement* element);
    string render();  // Composite rendering
};
```

### **4. Client Interface**
```cpp
class DocumentEditor {
    Document* document;
    Persistence* storage;
public:
    void addText(string text);
    void addImage(string imagePath);
    string renderDocument();
    void saveDocument();
};
```

---

## **Implementation Highlights**

### **Scalability Features**
- **Element Extensibility**: Add new element types by implementing `DocumentElement`
- **Storage Flexibility**: Swap persistence mechanisms via dependency injection
- **Rendering Optimization**: Cached rendering to avoid recomputation

### **Memory Management**
- Uses raw pointers (C++ style) - could be improved with smart pointers
- Document takes ownership of elements
- Clear separation between data and behavior

### **Error Handling**
- File I/O error checking in `FileStorage`
- Graceful degradation for storage failures

---

## **Usage Example**

```cpp
// Setup
Document* document = new Document();
Persistence* persistence = new FileStorage();
DocumentEditor* editor = new DocumentEditor(document, persistence);

// Content creation
editor->addText("Hello, world!");
editor->addNewLine();
editor->addTabSpace();
editor->addText("Indented text");
editor->addImage("picture.jpg");

// Operations
cout << editor->renderDocument();  // Display content
editor->saveDocument();            // Persist to storage
```

---

## **Design Patterns Used**

| Pattern | Implementation | Benefit |
|---------|---------------|---------|
| **Composite** | `DocumentElement` hierarchy | Uniform treatment of elements |
| **Strategy** | `Persistence` implementations | Swappable storage backends |
| **Template Method** | Rendering process | Consistent document processing |

---

## **Future Extensions**

### **Easy to Add:**
- **New Elements**: `TableElement`, `ListElement`, `HeaderElement`
- **Storage Types**: `CloudStorage`, `CacheStorage`, `CompressedStorage`
- **Export Formats**: `HTMLRenderer`, `PDFRenderer`, `MarkdownRenderer`

### **Modification Points:**
```cpp
// New element type
class TableElement : public DocumentElement {
    string render() override { /* table HTML/text */ }
};

// New storage backend  
class CloudStorage : public Persistence {
    void save(string data) override { /* cloud API */ }
};
```

---

## **Code Structure**
```
Cpp/
└── 00_googleDocs.cpp     // Complete implementation
```

> **Code**: [C++ Implementation](Cpp/00_googleDocs.cpp)

---

## UML Diagram

![Google Docs UML Diagram](UML/00_googleDocs.drawio.svg)

---

## **Key Takeaways**

✅ **Modular Design** → Each component has a single, clear responsibility  
✅ **Pattern Synergy** → Multiple patterns work together effectively  
✅ **Future-Proof** → Easy to extend without breaking existing code  
✅ **Practical Example** → Real-world application of design principles  

> This implementation showcases how proper abstraction and design patterns create maintainable, extensible systems.