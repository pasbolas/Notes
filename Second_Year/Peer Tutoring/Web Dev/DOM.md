
The **Document Object Model (DOM)** is a tree-structured representation of an HTML document that allows JavaScript to access, modify, add, or remove elements, attributes, and content dynamically after the page has loaded.



**1.(d) `document.getElementById()` vs `document.getElementsByClass()`**

- **`document.getElementById(id)`**
    - Returns **one single element**
        
    - IDs are **unique**
        
    - Fast and direct
        
    - Use when you need **one specific element**
        
- **`document.getElementsByClassName(className)`**
    
    - Returns an **HTMLCollection (multiple elements)**
        
    - Elements share the same class
        
    - Accessed using index (e.g. `[0]`)
        
    - Use when you need to **work with a group of elements**




### Question Code :

```js
let message = "Hello, World!";

function greet() {
  let message = "Hi there!";
  console.log(message);
}

greet();
console.log(message);

```