# CMPU 1031 – Web Development 1  
_Student-style worked answers_

## Question 1

### 1(a) Separation of Concerns in Web Development (10 marks)
In web development, separation of concerns means splitting the page into different layers, each with its own responsibility:

- **HTML**: structure and content
- **CSS**: presentation and styling
- **JavaScript**: behaviour and interactivity

**Three benefits of separating HTML from CSS:**
1. Easier maintenance  
2. Reusability and consistent design  
3. Cleaner, more readable HTML  

---

### 1(b) Meta tags and search engines (5 marks)
A meta tag provides metadata about a webpage, placed inside `<head>`.  
Search engines use them to understand the page and sometimes display the description in search results.

Example:
```html
<meta name="description" content="Laptop store">
<meta name="keywords" content="laptop, accessories">
```

---

### 1(c) HTML5 semantic tags and accessibility (5 marks)
Semantic tags (`<header>`, `<nav>`, `<main>`, `<section>`, etc.) give structure.  
They help:
- Developers understand page layout  
- Search engines rank content better  
- Assistive technologies navigate easily  

---

### 1(d) Document Object Model (DOM) (8 marks)
The DOM represents the webpage as a tree of objects. JavaScript can change these nodes.

Example:
```html
<p id="msg">Hello</p>
<button onclick="change()">Click</button>

<script>
function change() {
  const p = document.getElementById("msg");
  p.textContent = "Button clicked!";
  p.style.color = "red";
}
</script>
```

---

### 1(e) CSS Box Model (12 marks)
Every HTML element is a box containing:
- **Content**
- **Padding**
- **Border**
- **Margin**

These control spacing and layout.

---

## Question 2

### 2(a) CSS button hover and white text (10 marks)
```css
.my-button {
  background-color: #333;
  color: white;
  padding: 10px 20px;
}

.my-button:hover {
  background-color: blue;
}
```

---

### 2(b) JavaScript multiply function (10 marks)
```javascript
function multiply(a, b) {
  return a * b;
}
```

---

### 2(c) Static vs absolute positioning (10 marks)
**Static**: default, element stays in normal flow.  
**Absolute**: removed from document flow and positioned using coordinates relative to nearest positioned ancestor.

---

## Question 3

### 3(a) Low‑fidelity vs high‑fidelity prototypes (10 marks)
- **Low‑fidelity**: rough sketches, simple wireframes, fast to modify.  
- **High‑fidelity**: detailed, polished, realistic mockups with colours and interactions.

---

### 3(b) Bootstrap and benefits (10 marks)
Bootstrap is a front‑end framework with ready-made CSS/JS components.

Benefits:
1. Faster development  
2. Built‑in responsive grid system  

---

### 3(c) Descendant selector in CSS (10 marks)
```css
.container p {
  color: red;
}
```
This affects all `<p>` inside elements with class `.container`.

---

## Question 4

### 4(a) Absolute vs relative paths (10 marks)
**Absolute path**: full location from root or URL.  
Example: `/images/penguin.jpg`

**Relative path**: based on current file’s location.  
Example: `images/penguin.jpg`

---

### 4(b) Media queries and responsive design (10 marks)
```css
@media (max-width: 600px) {
  body { font-size: 16px; }
}
```
Applies different CSS on small screens.

---

### 4(c) Image tag paths (6 marks)
Same folder:
```html
<img src="penguin.jpg" alt="Penguin">
```

Subfolder:
```html
<img src="images/penguin.jpg" alt="Penguin">
```

---

### 4(d) Ordered list (4 marks)
```html
<ol>
  <li>Apple</li>
  <li>Banana</li>
  <li>Cherry</li>
</ol>
```
