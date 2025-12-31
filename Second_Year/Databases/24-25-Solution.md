

---

## **Question 1**

### **1.(a)**  
**Entity:**  
A real-world object or concept represented in the database.  
*Example:* `User` in the social media platform.

**Attribute:**  
A property or characteristic of an entity.  
*Example:* `Username` in the `User` table.

**Relationship:**  
An association between two or more entities.  
*Example:* A `User` *likes* a `Post`.

**Primary Key:**  
A unique identifier for each record in a table.  
*Example:* `UserID` in the `User` table.

**Foreign Key:**  
An attribute in one table that refers to the primary key in another table, establishing a link.  
*Example:* `AuthorID` in the `Post` table referencing `UserID` in `User`.

---

### **1.(b)**  
```sql
SELECT Post.Title, User.Username
FROM Post
JOIN User ON Post.AuthorID = User.UserID
WHERE Post.PostDate < '2023-01-01';
```

---

### **1.(c)**  
```sql
SELECT CONCAT(FirstName, ' ', LastName) AS FullName
FROM User
WHERE UserID NOT IN (SELECT DISTINCT AuthorID FROM Post);
```

---

### **1.(d)**  
```sql
SELECT Post.Title, AVG(Like.Count) AS AvgLikes
FROM Post
LEFT JOIN Like ON Post.PostID = Like.PostID
GROUP BY Post.PostID, Post.Title;
```

---

### **1.(e)**  
```sql
ALTER TABLE Post
ADD Shares INTEGER;
```

---

## **Question 2**

### **2.(a)**  
**Objectives of normalization:**  
- Reduce data redundancy  
- Improve data integrity  
- Simplify data maintenance  
- Avoid update anomalies  

**Three main normal forms:**  
- **1NF:** Each column contains atomic values, no repeating groups.  
- **2NF:** In 1NF, and all non-key attributes are fully dependent on the primary key.  
- **3NF:** In 2NF, and no transitive dependency exists (non-key attributes depend only on the primary key).

---

### **2.(b)**  
**Proposed new entity:** `Comment`  
**Attributes:**  
- CommentID (PK)  
- PostID (FK → Post)  
- UserID (FK → User)  
- CommentText  
- CommentDate  

**Relationships:**  
- A `User` can write many `Comment`s.  
- A `Post` can have many `Comment`s.

---

### **2.(c)**  
**Error identification:**  

1. **First query:**  
   - Likely missing required columns in `Post` table.  
   - Example: `PostID` might be missing or `AuthorID` might be expected as foreign key.

2. **Second query:**  
   - Column order mismatch: `Email` and `Username` values are swapped.  
   - Also, string values should use single quotes, not double quotes.

3. **Third query:**  
   - Too many values for the columns listed: only `UserID, Username, Email` are specified, but a fourth value is provided.

---

## **Question 3**

### **3.(a)**  
```sql
ALTER TABLE Post
ALTER COLUMN PostDate SET NOT NULL;
```

**Significance:**  
Ensures that every post has a date, preventing incomplete records and maintaining data consistency.

---

### **3.(b)**  
```sql
SELECT Title, 
       TO_CHAR(PostDate, 'DD Mon YYYY') AS FormattedDate
FROM Post;
```

---

### **3.(c)**  
**Referential integrity** ensures that relationships between tables remain consistent.  
It is maintained by foreign key constraints, which prevent actions that would leave orphaned records (e.g., deleting a user who has posts).  
This ensures that all references in the database are valid, preserving data consistency and reliability.

---

I have answered all questions as per the exam paper’s requirements, using SQL syntax appropriate for the provided syntax sheet.