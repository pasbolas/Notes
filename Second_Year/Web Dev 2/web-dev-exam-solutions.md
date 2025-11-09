# Web Development 2 Exam Solutions
**TU Dublin - CMPU 2022 - 2024/25**

---

## Exam Instructions
- Answer **Question 1** (40 marks) - **MANDATORY**
- Answer **any TWO** of Questions 2, 3, or 4 (30 marks each)
- Total: 100 marks
- Time: 2 hours

---

# Question 1 (Mandatory - 40 marks)

## Part (a): Multi-Tier Application Architecture (10 marks)

### Definition
**Multi-Tier Application Architecture** (also called n-tier architecture) is a software design pattern that separates an application into distinct layers, each with specific responsibilities. This promotes modularity, scalability, and maintainability.

### Common Tiers

1. **Presentation Tier (Client Layer)**
   - The user interface that displays information and captures user input
   - Technologies: HTML, CSS, JavaScript
   - Handles user interaction and display logic

2. **Application Tier (Business Logic Layer)**
   - Processes user requests and implements business rules
   - Coordinates application functionality
   - Technologies: PHP, Node.js, Java, Python
   - Manages data flow between presentation and data tiers

3. **Data Tier (Database Layer)**
   - Manages data storage, retrieval, and persistence
   - Technologies: MySQL, PostgreSQL, MongoDB, Oracle
   - Handles CRUD operations

### Example: E-Commerce Web Application

**Presentation Tier:**
- HTML forms for product browsing
- Shopping cart display using CSS/JavaScript
- User interface for checkout process

**Application Tier:**
- PHP scripts that validate user input
- Calculate totals and apply discounts
- Process orders and payments
- Handle user authentication and sessions

**Data Tier:**
- MySQL database storing:
  - Product information (name, price, stock)
  - Customer details (name, address, email)
  - Order history and transaction records

### Benefits
- **Separation of Concerns**: Each tier has distinct responsibilities
- **Maintainability**: Changes to one tier don't affect others
- **Scalability**: Each tier can be scaled independently
- **Reusability**: Business logic can be reused across different interfaces
- **Security**: Sensitive data logic is separated from presentation

---

## Part (b): Web Server Selection Criteria (10 marks)

### Six Selection Criteria

1. **Performance and Scalability**
   - Ability to handle concurrent requests
   - Load balancing capabilities
   - Resource efficiency (CPU, memory usage)
   - Caching mechanisms

2. **Security Features**
   - SSL/TLS support
   - Built-in security modules
   - Vulnerability protection (DDoS, injection attacks)
   - Regular security updates

3. **Platform Compatibility**
   - Operating system support (Windows, Linux, Unix, macOS)
   - Hardware requirements
   - Database compatibility
   - Programming language support

4. **Cost**
   - Licensing fees (free vs commercial)
   - Total cost of ownership
   - Support and maintenance costs
   - Open-source vs proprietary solutions

5. **Ease of Configuration**
   - Setup complexity
   - Documentation quality
   - Administrative tools and GUI
   - Configuration file structure

6. **Community Support and Documentation**
   - Active development community
   - Available resources and tutorials
   - Troubleshooting assistance
   - Plugin/module ecosystem

### Three Market Leading Web Servers

1. **Apache HTTP Server (Apache)**
   - Most widely used web server
   - Open-source and free
   - Extensive module support
   - Excellent documentation

2. **Nginx**
   - High performance and low resource usage
   - Excellent for serving static content
   - Reverse proxy capabilities
   - Event-driven architecture

3. **Microsoft Internet Information Services (IIS)**
   - Native Windows integration
   - Strong .NET support
   - Enterprise-level features
   - GUI-based management

---

## Part (c): PHP Code Output (4 marks)

### Code Analysis
```php
<?php
function multi($num)
{
    if ($num == 3)
        echo "I Wonder";
    if ($num == 7)
        echo "Which One";
    if ($num == 8)
        echo "Is The";
    if ($num == 19)
        echo "Correct Answer";
}
$can = stripos("I love php, I love php too!","PHP");
multi($can);
?>
```

### Step-by-Step Execution

1. `stripos("I love php, I love php too!", "PHP")` searches for "PHP" (case-insensitive)
2. The string is: "I love php, I love php too!"
   - Position 0: I
   - Position 1: (space)
   - Position 2: l
   - Position 3: o
   - Position 4: v
   - Position 5: e
   - Position 6: (space)
   - Position 7: **p** ← First occurrence of "php"
3. `$can = 7`
4. Function `multi(7)` is called
5. The condition `$num == 7` is true
6. Output: "Which One"

### Answer
**iv. Which One** ✓

---

## Part (d): AerAirways Destinations PHP Script (16 marks)

### Complete Solution

```php
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Flight Destinations</title>
</head>
<body>
    <h1>Available Destinations</h1>
    
<?php
// Database connection parameters
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "aerairways";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Get user input from GET parameter
$going_from = $_GET['going_from'];

// SQL query with JOIN to get countries and flight numbers
$sql = "SELECT Airport.country, Flight.flightNum 
        FROM Flight 
        INNER JOIN Airport ON Flight.goingTo = Airport.airport 
        WHERE Flight.goingFrom = ? 
        ORDER BY Airport.country, Flight.flightNum";

// Prepare statement for security
$stmt = $conn->prepare($sql);
$stmt->bind_param("s", $going_from);
$stmt->execute();
$result = $stmt->get_result();

// Organize data by country
$destinations = array();
while($row = $result->fetch_assoc()) {
    $country = $row['country'];
    $flightNum = $row['flightNum'];
    
    // Create array for country if it doesn't exist
    if (!isset($destinations[$country])) {
        $destinations[$country] = array();
    }
    
    // Add flight number to country's array
    $destinations[$country][] = $flightNum;
}

// Display as nested unordered list
if (count($destinations) > 0) {
    echo "<ul>";
    
    foreach ($destinations as $country => $flights) {
        // Country as main list item
        echo "<li>" . htmlspecialchars($country);
        
        // Nested list for flight numbers
        echo "<ul>";
        foreach ($flights as $flight) {
            echo "<li>" . htmlspecialchars($flight) . "</li>";
        }
        echo "</ul>";
        
        echo "</li>";
    }
    
    echo "</ul>";
} else {
    echo "<p>No destinations found from airport: " . htmlspecialchars($going_from) . "</p>";
}

// Close connections
$stmt->close();
$conn->close();
?>

</body>
</html>
```

### Example Output
For input "DUB", the browser displays:
- England
  - ea101
- France
  - ea104
- Scotland
  - ea102
  - ea103

### Key Features
- Uses prepared statements for SQL injection prevention
- `htmlspecialchars()` for XSS protection
- Proper JOIN between Flight and Airport tables
- Organized data structure for nested lists
- Error handling for database connection
- Sorted by country and flight number

---

# Question 2 (30 marks)

## Part (a): XML vs JSON Differences (6 marks)

### Comparison Table

| Feature | XML | JSON |
|---------|-----|------|
| **Syntax** | Uses tags with opening/closing elements | Uses key-value pairs with curly braces |
| **Data Types** | Everything is text | Supports strings, numbers, booleans, arrays, objects, null |
| **Parsing** | Requires XML parser, slower | Native JavaScript support, faster |
| **File Size** | Verbose with closing tags | More compact, less overhead |
| **Metadata** | Supports attributes and namespaces | No attribute concept |
| **Readability** | Can be cluttered | Generally more readable |

### Detailed Differences

1. **Syntax Structure**
   - **XML**: `<tag attribute="value">content</tag>`
   - **JSON**: `{"key": "value"}`

2. **Data Type Support**
   - **XML**: All values are strings; requires parsing
   - **JSON**: Native data types (numbers, booleans, null)

3. **Performance**
   - **XML**: Slower parsing, more processing overhead
   - **JSON**: Faster parsing, especially in web applications

4. **Verbosity**
   - **XML**: Requires closing tags, more characters
   - **JSON**: Minimal syntax, smaller file sizes

5. **Comments**
   - **XML**: Supports comments `<!-- comment -->`
   - **JSON**: No comment support

6. **Use Cases**
   - **XML**: Document markup, configuration files, SOAP APIs
   - **JSON**: RESTful APIs, web services, data interchange

---

## Part (b): PHP Function Definition (4 marks)

### Options Analysis

i. `functionName(parameters) {function body}` ❌
   - Missing the `function` keyword

ii. `function {function body}` ❌
   - Missing function name and parameters

iii. `function functionName(parameters) {function body}` ✓
   - **CORRECT SYNTAX**

iv. `data type functionName(parameters) {function body}` ❌
   - PHP doesn't require data type declaration before function name (in traditional syntax)

### Answer
**iii. function functionName(parameters) {function body}** ✓

### Example
```php
function calculateSum($a, $b) {
    return $a + $b;
}
```

---

## Part (c): PHP Echo Statement (4 marks)

### Options Analysis

```php
i.  echo "\$x";   // Outputs: $x (backslash escapes $)
ii. echo "$$x";   // Outputs: value of variable whose name is in $x
iii. echo "/$x";  // Outputs: /[value of $x]
iv. echo "$x;";   // Outputs: [value of $x];
```

### Detailed Explanation

- **Option i**: `echo "\$x";`
  - The backslash `\` escapes the dollar sign
  - Treats `$` as a literal character
  - Output: `$x` (literal text)

- **Option ii**: `echo "$$x";`
  - Variable variables syntax
  - If `$x = "name"` and `$name = "John"`, outputs: `John`

- **Option iii**: `echo "/$x";`
  - Forward slash followed by variable
  - If `$x = "value"`, outputs: `/value`

- **Option iv**: `echo "$x;";`
  - Variable followed by semicolon inside quotes
  - If `$x = "value"`, outputs: `value;`

### Answer
**i. echo "\$x";** ✓

---

## Part (d): XML and JSON Document (16 marks)

### Well-Formed XML Document

```xml
<?xml version="1.0" encoding="UTF-8"?>
<serviceBill>
    <customer>
        <name>Steven Murphy</name>
    </customer>
    <services>
        <service>
            <dateOfService>20/05/2024</dateOfService>
            <description>Kitchen Flooring</description>
            <serviceID>122837</serviceID>
            <price currency="EUR">800</price>
        </service>
        <service>
            <dateOfService>21/05/2024</dateOfService>
            <description>Install Kitchen</description>
            <serviceID>129281</serviceID>
            <price currency="EUR">2000</price>
        </service>
    </services>
    <summary>
        <totalCharge currency="EUR">2800</totalCharge>
    </summary>
</serviceBill>
```

### JSON Object

```json
{
  "serviceBill": {
    "customer": {
      "name": "Steven Murphy"
    },
    "services": [
      {
        "dateOfService": "20/05/2024",
        "description": "Kitchen Flooring",
        "serviceID": "122837",
        "price": {
          "amount": 800,
          "currency": "EUR"
        }
      },
      {
        "dateOfService": "21/05/2024",
        "description": "Install Kitchen",
        "serviceID": "129281",
        "price": {
          "amount": 2000,
          "currency": "EUR"
        }
      }
    ],
    "summary": {
      "totalCharge": {
        "amount": 2800,
        "currency": "EUR"
      }
    }
  }
}
```

### Alternative Simpler JSON

```json
{
  "customer": "Steven Murphy",
  "services": [
    {
      "date": "20/05/2024",
      "service": "Kitchen Flooring",
      "id": "122837",
      "price": 800
    },
    {
      "date": "21/05/2024",
      "service": "Install Kitchen",
      "id": "129281",
      "price": 2000
    }
  ],
  "totalCharge": 2800,
  "currency": "EUR"
}
```

---

# Question 3 (30 marks)

## Part (a): Dynamic vs Static Web Applications (6 marks)

### Static Web Applications

**Definition:**
Content is fixed and pre-written in HTML files. The same content is displayed to all users regardless of who accesses the page or when.

**Characteristics:**
- Files are created once and served as-is
- No server-side processing required
- Fast loading times
- Simple to host and deploy
- Content changes require manual file editing

**Example:**
- **Portfolio Website**: A photographer's portfolio with fixed images and text
- **Company Brochure Site**: Static pages about company history, services
- **Documentation Pages**: Technical manuals with unchanging content
- **Landing Pages**: Simple promotional pages

### Dynamic Web Applications

**Definition:**
Content is generated in real-time based on user input, database queries, or other conditions. Different users may see different content based on their interactions, preferences, or data.

**Characteristics:**
- Content generated on-the-fly by server
- Uses server-side languages (PHP, Python, Node.js)
- Interacts with databases
- Personalized user experience
- Content updates without changing code files

**Example:**
- **Social Media Platforms** (Facebook, Twitter): User-specific feeds, real-time updates
- **E-commerce Sites** (Amazon, eBay): Product searches, personalized recommendations
- **Online Banking**: Account-specific information, transaction history
- **News Websites**: Regularly updated articles, user comments

### Comparison Table

| Aspect | Static | Dynamic |
|--------|--------|---------|
| Content | Fixed | Generated |
| User Experience | Same for all | Personalized |
| Speed | Very fast | Depends on processing |
| Complexity | Simple | Complex |
| Database | Not required | Usually required |
| Cost | Low | Higher |

---

## Part (b): PHP pos() Function Output (4 marks)

### Code Analysis

```php
<?php
$php = array("Array", "Function", "Strings", "File");
echo pos($php);
?>
```

### Explanation

1. **Array Creation**: 
   ```php
   $php = array("Array", "Function", "Strings", "File");
   ```
   - Index 0: "Array"
   - Index 1: "Function"
   - Index 2: "Strings"
   - Index 3: "File"

2. **pos() Function**:
   - `pos()` is an alias of `current()`
   - Returns the current element in an array
   - Array pointer starts at the first element (index 0)

3. **Output**:
   - Current element is at index 0
   - Value: "Array"

### Answer
**iv. Array** ✓

---

## Part (c): PHP Constants and Variables (4 marks)

### Code Analysis

```php
<?php
define("VAR_NAME","test"); 
${VAR_NAME} = "value"; 
echo VAR_NAME;
echo ${VAR_NAME};
?>
```

### Step-by-Step Execution

1. **Line 1**: `define("VAR_NAME","test");`
   - Creates a constant named `VAR_NAME` with value `"test"`

2. **Line 2**: `${VAR_NAME} = "value";`
   - Variable variables syntax
   - `VAR_NAME` constant equals `"test"`
   - Creates variable `$test = "value"`

3. **Line 3**: `echo VAR_NAME;`
   - Outputs the constant value
   - Output: `test`

4. **Line 4**: `echo ${VAR_NAME};`
   - `VAR_NAME` equals `"test"`
   - Outputs the variable `$test`
   - Output: `value`

### Combined Output
`testvalue`

### Answer
**ii. testvalue** ✓

### Important Concept
- Constants are NOT being changed
- We're creating a new variable whose name is the value of the constant
- This is called "variable variables"

---

## Part (d): Student Query PHP Script (16 marks)

### Complete Solution

```php
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>High Performing Students</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 20px;
            background-color: #f5f5f5;
        }
        h1 {
            text-align: center;
            color: #333;
        }
        table {
            border-collapse: collapse;
            width: 90%;
            margin: 20px auto;
            background-color: white;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
        }
        th {
            background-color: #4CAF50;
            color: white;
            padding: 12px;
            text-align: left;
            font-weight: bold;
        }
        td {
            border: 1px solid #ddd;
            padding: 10px;
        }
        tr:nth-child(even) {
            background-color: #f2f2f2;
        }
        tr:hover {
            background-color: #e8f5e9;
        }
        .summary {
            text-align: center;
            margin-top: 20px;
            font-weight: bold;
        }
    </style>
</head>
<body>
    <h1>Students with Exam Results Over 70%</h1>
    
<?php
// Database connection parameters
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "university";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// SQL query with multiple JOINs
$sql = "SELECT 
            Student.StudentID, 
            Student.StudentName, 
            Course.Course, 
            Study.ExamResult 
        FROM Study 
        INNER JOIN Student ON Study.StudentID = Student.StudentID 
        INNER JOIN Course ON Study.CourseID = Course.CourseID 
        WHERE Study.ExamResult > 70 
        ORDER BY Student.StudentName, Course.Course";

// Execute query
$result = $conn->query($sql);

// Check if results exist
if ($result->num_rows > 0) {
    echo "<table>";
    echo "<tr>
            <th>Student ID</th>
            <th>Student Name</th>
            <th>Course</th>
            <th>Exam Result (%)</th>
          </tr>";
    
    // Output data for each row
    while($row = $result->fetch_assoc()) {
        echo "<tr>";
        echo "<td>" . htmlspecialchars($row['StudentID']) . "</td>";
        echo "<td>" . htmlspecialchars($row['StudentName']) . "</td>";
        echo "<td>" . htmlspecialchars($row['Course']) . "</td>";
        echo "<td>" . htmlspecialchars($row['ExamResult']) . "%</td>";
        echo "</tr>";
    }
    
    echo "</table>";
    
    // Display summary
    echo "<p class='summary'>Total Records Found: " . $result->num_rows . "</p>";
} else {
    echo "<p class='summary'>No students found with exam results over 70%.</p>";
}

// Close connection
$conn->close();
?>

</body>
</html>
```

### SQL Query Explanation

```sql
SELECT 
    Student.StudentID, 
    Student.StudentName, 
    Course.Course, 
    Study.ExamResult 
FROM Study 
INNER JOIN Student ON Study.StudentID = Student.StudentID 
INNER JOIN Course ON Study.CourseID = Course.CourseID 
WHERE Study.ExamResult > 70 
ORDER BY Student.StudentName, Course.Course
```

**Query Breakdown:**
1. **FROM Study**: Start with the Study table (contains exam results)
2. **INNER JOIN Student**: Connect to Student table using StudentID
3. **INNER JOIN Course**: Connect to Course table using CourseID
4. **WHERE Study.ExamResult > 70**: Filter for results over 70%
5. **ORDER BY**: Sort by student name, then course name

### Key Features
- Multiple INNER JOINs between three tables
- XSS protection using `htmlspecialchars()`
- Proper error handling
- Styled HTML table for better presentation
- Result count display
- Sorted output for readability

---

# Question 4 (30 marks)

## Part (a): Client vs Server Validation (6 marks)

### User Registration Page

**Recommendation: Both Client-Side AND Server-Side Validation**

#### Client-Side Validation (JavaScript)
**Reasons:**
- **Immediate Feedback**: Users get instant error messages without page reload
- **Better UX**: Validates email format, password strength, required fields in real-time
- **Reduced Server Load**: Catches obvious errors before submission
- **Faster Response**: No network round-trip needed

**Example Validations:**
- Email format check using regex
- Password length and complexity
- Required field checks
- Matching password confirmation

#### Server-Side Validation (PHP)
**Reasons:**
- **Security**: Client validation can be bypassed by disabling JavaScript
- **Data Integrity**: Final verification before database insertion
- **Prevents Malicious Input**: SQL injection, XSS attacks
- **Business Logic**: Complex validation rules
- **Cannot be circumvented**: Only validation you can truly trust

**Example Validations:**
- Duplicate email/username check in database
- Password hashing before storage
- Input sanitization
- Database constraint verification

### Search Screen

**Recommendation: Both, with Emphasis on Client-Side**

#### Client-Side Validation
**Reasons:**
- **Immediate Search Feedback**: Validates search parameters before request
- **Prevents Empty Searches**: Checks for valid input
- **Better UX**: No unnecessary server requests
- **Format Validation**: Date ranges, numeric values

#### Server-Side Validation
**Reasons:**
- **SQL Injection Prevention**: Sanitizes search queries
- **Parameter Validation**: Ensures allowed search parameters
- **Database Protection**: Prevents malicious queries
- **Rate Limiting**: Prevents automated attacks

### Summary Table

| Page Type | Client-Side | Server-Side | Priority |
|-----------|-------------|-------------|----------|
| Registration | ✓ Required | ✓ Essential | Both equal |
| Search | ✓ Preferred | ✓ Required | Client emphasis |

---

## Part (b): PHP GLOBALS Output (4 marks)

### Code Analysis

```php
<?php
$x = 5;
$y = 10;
function fun()
{
    $y = $GLOBALS['x'] + $GLOBALS['y'];
} 
fun();
echo $y;
?>
```

### Step-by-Step Execution

1. **Line 2**: `$x = 5;` - Global variable `$x` = 5
2. **Line 3**: `$y = 10;` - Global variable `$y` = 10
3. **Lines 4-7**: Function definition
4. **Line 8**: `fun();` - Function is called
5. **Inside function**:
   - `$y = $GLOBALS['x'] + $GLOBALS['y'];`
   - This creates a **LOCAL** variable `$y` inside the function
   - Local `$y` = 5 + 10 = 15
   - **IMPORTANT**: This does NOT modify the global `$y`
6. **Line 9**: `echo $y;` - Outputs the global `$y`
7. **Output**: 10

### Why 10 and not 15?

- The function creates a **new local variable** `$y`
- To modify the global `$y`, we would need:
  ```php
  $GLOBALS['y'] = $GLOBALS['x'] + $GLOBALS['y'];
  ```

### Answer
**ii. 10** ✓

---

## Part (c): PHP While Loop Output (4 marks)

### Code Analysis

```php
<?php
$i = 5;
while (--$i > 0 && ++$i)
{
    print $i;
}
?>
```

### Step-by-Step Execution

#### First Iteration:
1. `--$i`: Pre-decrement, `$i` becomes 4
2. `4 > 0`: TRUE
3. `++$i`: Pre-increment, `$i` becomes 5
4. `5` is truthy: TRUE
5. Both conditions TRUE: enter loop
6. `print $i`: Outputs **5**

#### Second Iteration:
1. `--$i`: Pre-decrement, `$i` becomes 4
2. `4 > 0`: TRUE
3. `++$i`: Pre-increment, `$i` becomes 5
4. `5` is truthy: TRUE
5. Both conditions TRUE: enter loop
6. `print $i`: Outputs **5**

#### Pattern:
- `$i` always decrements to 4, then increments back to 5
- Condition always evaluates to TRUE
- **Infinite loop**: prints "5" forever

### Output
```
555555555555555555...
```

### Answer
**i. 555555555…infinitely** ✓

---

## Part (d): Bike Order Form and PHP (16 marks)

### HTML Form (order_form.html)

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Bike Order Form</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            max-width: 900px;
            margin: 30px auto;
            padding: 30px;
            border: 2px solid #333;
            background-color: #f9f9f9;
        }
        h2 {
            text-align: center;
            color: #333;
        }
        .form-section {
            margin: 20px 0;
            padding: 15px;
            background-color: white;
            border-radius: 5px;
        }
        .form-section strong {
            display: block;
            margin-bottom: 10px;
            color: #555;
        }
        .form-group {
            margin: 10px 0;
        }
        label {
            display: inline-block;
            width: 180px;
            font-weight: normal;
        }
        input[type="text"] {
            padding: 8px;
            width: 250px;
            border: 1px solid #ddd;
            border-radius: 4px;
        }
        textarea {
            padding: 8px;
            width: 500px;
            height: 100px;
            border: 1px solid #ddd;
            border-radius: 4px;
            font-family: Arial, sans-serif;
        }
        select {
            padding: 8px;
            width: 200px;
            border: 1px solid #ddd;
            border-radius: 4px;
        }
        button {
            margin: 20px 10px 0 0;
            padding: 12px 30px;
            font-size: 16px;
            cursor: pointer;
            border: none;
            border-radius: 5px;
        }
        button[type="submit"] {
            background-color: #4CAF50;
            color: white;
        }
        button[type="submit"]:hover {
            background-color: #45a049;
        }
        button[type="reset"] {
            background-color: #f44336;
            color: white;
        }
        button[type="reset"]:hover {
            background-color: #da190b;
        }
        .button-group {
            text-align: center;
        }
    </style>
</head>
<body>
    <h2>A bike order form</h2>
    
    <form action="process_order.php" method="post">
        
        <!-- Bike Type Selection -->
        <div class="form-section">
            <strong>What type of bike do you want to purchase?</strong>
            <div class="form-group">
                <input type="radio" id="street" name="bike_type" value="Street bike" checked>
                <label for="street" style="width: auto;">Street bike</label>
                
                <input type="radio" id="mountain" name="bike_type" value="Mountain bike">
                <label for="mountain" style="width: auto;">Mountain bike</label>
                
                <input type="radio" id="dirt" name="bike_type" value="Dirt bike">
                <label for="dirt" style="width: auto;">Dirt bike</label>
            </div>
        </div>
        
        <!-- Accessories Selection -->
        <div class="form-section">
            <strong>What accessories do you need?</strong>
            <div class="form-group">
                <input type="checkbox" id="gloves" name="accessories[]" value="Gloves">
                <label for="gloves" style="width: auto;">Gloves</label>
                
                <input type="checkbox" id="helmet" name="accessories[]" value="Helmet">
                <label for="helmet" style="width: auto;">Helmet</label>
                
                <input type="checkbox" id="waterbag" name="accessories[]" value="Camel water bag">
                <label for="waterbag" style="width: auto;">Camel water bag</label>
            </div>
        </div>
        
        <!-- Biking Location -->
        <div class="form-section">
            <strong>Where do you go biking?</strong>
            <div class="form-group">
                <select name="biking_location">
                    <option value="Parks">Parks</option>
                    <option value="Bike routes">Bike routes</option>
                    <option value="Mountains">Mountains</option>
                    <option value="Trails">Trails</option>
                </select>
            </div>
        </div>
        
        <!-- Shipping Information -->
        <div class="form-section">
            <strong>Shipping information</strong>
            <div class="form-group">
                <label>First Name</label>
                <input type="text" name="first_name" required>
            </div>
            <div class="form-group">
                <label>Last Name</label>
                <input type="text" name="last_name" required>
            </div>
            <div class="form-group">
                <label>Address</label>
                <input type="text" name="address">
            </div>
            <div class="form-group">
                <label>City</label>
                <input type="text" name="city">
            </div>
            <div class="form-group">
                <label>State</label>
                <input type="text" name="state">
            </div>
            <div class="form-group">
                <label>Zip code</label>
                <input type="text" name="zip_code">
            </div>
        </div>
        
        <!-- Special Delivery Instructions -->
        <div class="form-section">
            <strong>Special delivery instructions</strong>
            <div class="form-group">
                <textarea name="delivery_instructions" placeholder="Enter any special instructions here..."></textarea>
            </div>
        </div>
        
        <!-- Payment Information -->
        <div class="form-section">
            <strong>Payment information</strong>
            <div class="form-group">
                <label>Credit card number</label>
                <input type="text" name="card_number">
            </div>
            <div class="form-group">
                <label>Expires</label>
                <input type="text" name="expiry" placeholder="12/10">
            </div>
        </div>
        
        <!-- Form Buttons -->
        <div class="button-group">
            <button type="submit">Send Order</button>
            <button type="reset">Start Over</button>
        </div>
        
    </form>
</body>
</html>
```

### PHP Processing Script (process_order.php)

```php
<?php
// Database connection parameters
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "bike_shop";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Get form data with validation
$first_name = isset($_POST['first_name']) ? trim($_POST['first_name']) : '';
$last_name = isset($_POST['last_name']) ? trim($_POST['last_name']) : '';
$delivery_instructions = isset($_POST['delivery_instructions']) ? trim($_POST['delivery_instructions']) : '';

// Basic validation
if (empty($first_name) || empty($last_name)) {
    die("Error: First Name and Last Name are required fields.");
}

// Prepare SQL statement to prevent SQL injection
$sql = "INSERT INTO orders (first_name, last_name, delivery_instructions, order_date) 
        VALUES (?, ?, ?, NOW())";

$stmt = $conn->prepare($sql);

if ($stmt === false) {
    die("Error preparing statement: " . $conn->error);
}

// Bind parameters (s = string)
$stmt->bind_param("sss", $first_name, $last_name, $delivery_instructions);

// Execute and check result
if ($stmt->execute()) {
    $order_id = $stmt->insert_id;
    
    // Display success page
    ?>
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <title>Order Confirmation</title>
        <style>
            body {
                font-family: Arial, sans-serif;
                max-width: 800px;
                margin: 50px auto;
                padding: 30px;
                text-align: center;
                background-color: #f0f8f0;
                border: 2px solid #4CAF50;
                border-radius: 10px;
            }
            h1 {
                color: #4CAF50;
            }
            .success-icon {
                font-size: 60px;
                color: #4CAF50;
                margin: 20px 0;
            }
            .order-details {
                background-color: white;
                padding: 20px;
                margin: 20px 0;
                border-radius: 5px;
                text-align: left;
            }
            .detail-row {
                margin: 10px 0;
                padding: 10px;
                border-bottom: 1px solid #eee;
            }
            .detail-label {
                font-weight: bold;
                color: #555;
            }
            a {
                display: inline-block;
                margin-top: 20px;
                padding: 12px 30px;
                background-color: #4CAF50;
                color: white;
                text-decoration: none;
                border-radius: 5px;
            }
            a:hover {
                background-color: #45a049;
            }
        </style>
    </head>
    <body>
        <div class="success-icon">✓</div>
        <h1>Order Submitted Successfully!</h1>
        
        <div class="order-details">
            <h2>Order Confirmation</h2>
            <div class="detail-row">
                <span class="detail-label">Order ID:</span> 
                #<?php echo htmlspecialchars($order_id); ?>
            </div>
            <div class="detail-row">
                <span class="detail-label">Customer Name:</span> 
                <?php echo htmlspecialchars($first_name . " " . $last_name); ?>
            </div>
            <?php if (!empty($delivery_instructions)): ?>
            <div class="detail-row">
                <span class="detail-label">Delivery Instructions:</span><br>
                <?php echo nl2br(htmlspecialchars($delivery_instructions)); ?>
            </div>
            <?php endif; ?>
            <div class="detail-row">
                <span class="detail-label">Order Date:</span> 
                <?php echo date('F j, Y, g:i a'); ?>
            </div>
        </div>
        
        <p>Thank you for your order! We will process it shortly.</p>
        
        <a href="order_form.html">Place Another Order</a>
    </body>
    </html>
    <?php
} else {
    echo "<!DOCTYPE html>";
    echo "<html><head><title>Error</title></head><body>";
    echo "<h2>Error Submitting Order</h2>";
    echo "<p>There was an error processing your order: " . $stmt->error . "</p>";
    echo "<a href='order_form.html'>Go Back</a>";
    echo "</body></html>";
}

// Close connections
$stmt->close();
$conn->close();
?>
```

### Database Schema (orders table)

```sql
CREATE TABLE orders (
    order_id INT AUTO_INCREMENT PRIMARY KEY,
    first_name VARCHAR(100) NOT NULL,
    last_name VARCHAR(100) NOT NULL,
    delivery_instructions TEXT,
    order_date DATETIME NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
```

### Key Features

1. **Form Features:**
   - Radio buttons for bike type (single selection)
   - Checkboxes for accessories (multiple selection)
   - Dropdown for biking location
   - Text inputs for shipping information
   - Textarea for delivery instructions
   - Required fields marked

2. **PHP Security:**
   - Prepared statements prevent SQL injection
   - `htmlspecialchars()` prevents XSS attacks
   - Input validation
   - Error handling

3. **User Experience:**
   - Styled form with clear sections
   - Visual confirmation page
   - Order ID generation
   - Link to place another order

---

## Study Tips

### For Question 1
- Understand multi-tier architecture thoroughly
- Know common web servers (Apache, Nginx, IIS)
- Practice PHP string functions
- Master database JOINs

### For Question 2
- Memorize XML vs JSON differences
- Know PHP function syntax
- Understand escape characters in strings
- Practice data format conversions

### For Question 3
- Understand static vs dynamic websites
- Know PHP array functions
- Study variable variables concept
- Practice complex SQL JOINs

### For Question 4
- Learn client vs server validation
- Understand PHP variable scope
- Study loop execution carefully
- Practice form handling and database insertion

---

## Quick Reference

### Common PHP Functions
- `stripos()` - Find position (case-insensitive)
- `pos()` / `current()` - Get current array element
- `htmlspecialchars()` - Escape HTML characters
- `trim()` - Remove whitespace
- `prepare()` - Prepare SQL statement
- `bind_param()` - Bind parameters to SQL

### MySQL Connection Pattern
```php
$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
// Your queries here
$conn->close();
```

### Prepared Statement Pattern
```php
$stmt = $conn->prepare("SELECT * FROM table WHERE id = ?");
$stmt->bind_param("i", $id);
$stmt->execute();
$result = $stmt->get_result();
$stmt->close();
```

---

**Good luck with your exam! 🍀**