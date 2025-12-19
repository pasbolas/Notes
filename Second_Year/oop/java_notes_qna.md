# Java Notes - Q&A Format

## 1. Effect of `static` keyword

**Q:** What is the effect of `static` when applied to a variable?

**A:** A `static` variable belongs to the **class**, not the object. There is only **one copy shared by all objects**. Updating it in one object affects all other instances.

```java
private static int multiplierFactor = 100;
```
- Shared by all instances.
- Can be accessed without creating an object (within the class if `private`).

**Q:** What is the effect of `static` when applied to a method?

**A:** A `static` method belongs to the **class** and can be called **without creating an object**. It cannot access non-static instance variables directly.

```java
public static void calcTax(int month) {
    // method body
}
```

---

## 2. Static vs local variables in methods

**Q:** If a local variable is declared inside a static method, is it shared across calls?

**A:** No. Local variables are **created fresh every method call** and destroyed after the method finishes. Only static fields are shared across instances.

```java
public static void tax(int month) {
    int x = 0;
    int income = x * month; // local variable, new copy each call
}
```
- Using `this` inside a static method causes a **compile-time error**.

**Q:** If the class was non-static, would a local variable like `income` survive?

**A:** No. **Local variables always exist only during the method call**, regardless of whether the method or class is static or not.

---

## 3. Static vs Non-static nested classes

**Q:** What is the difference between static and non-static nested classes?

**A:**
- **Non-static inner class:** tied to an **instance of the outer class**, can access instance members.
- **Static nested class:** belongs to the **class itself**, cannot access instance members.

**Example:**
```java
class Outer {
    int x = 10;
    static int y = 20;

    class Inner {
        void print() {
            System.out.println(x); // can access instance member
        }
    }

    static class Nested {
        void print() {
            System.out.println(y); // can access static member only
        }
    }
}
```

**Usage:**
```java
Outer o = new Outer();
Outer.Inner i = o.new Inner();
i.print();

Outer.Nested n = new Outer.Nested();
n.print();
```

**Rule of thumb:**
- Independent state → `static` nested class
- Dependent on outer instance → non-static inner class

---

## 4. Compile-time vs Runtime errors

**Q:** When do compile-time errors occur?

**A:** Detected **before running the program**. Compilation fails. Examples:
- Syntax errors
- Type mismatches
- Illegal use of `this` in static methods

```java
int x = "hello"; // compile-time error
```

**Q:** When do runtime errors occur?

**A:** Detected **during execution**. Compilation succeeds but execution fails. Examples:
- Division by zero
- Null pointer
- Array index out of bounds

```java
int a = 10 / 0; // runtime error
```

**Rule:**
- Compiler can **prove the error without running** → compile-time
- Error depends on **actual data or environment** → runtime

---

## 5. Exception Handling (`throw`, `try`, `catch`, `finally`, `throws`)

**Q:** What is `throw`?

**A:** Used to **manually trigger an exception**.

```java
if (age < 18) {
    throw new IllegalArgumentException("Age must be 18+");
}
```

**Q:** What is `try` and `catch`?

**A:** `try` encloses code that might throw an exception. `catch` handles the exception.

```java
try {
    int result = 10 / 0;
} catch (ArithmeticException e) {
    System.out.println("Cannot divide by zero!");
}
```

**Q:** What is `finally`?

**A:** Optional block that **always executes**, used for cleanup.

```java
finally {
    System.out.println("Cleanup done");
}
```

**Q:** What is `throws`?

**A:** Declares exceptions a method can propagate to the caller (checked exceptions must be handled).

```java
void readFile() throws IOException {
    FileReader fr = new FileReader("data.txt");
}
```

**Mental Map:**
- `throw` → create/trigger an exception
- `try` → monitor risky code
- `catch` → handle exceptions
- `finally` → always run
- `throws` → declare exception propagation

---

**End of Notes**

