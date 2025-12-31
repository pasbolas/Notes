
---

## Question 1

### 1(a) ERD Concepts (10 marks)

**Entity**  
An entity represents a real-world object or concept about which data is stored in the database. In an ERD, an entity usually corresponds to a table.

_Example:_  
`Movie` is an entity that stores information about films.

---

**Attribute**  
An attribute is a property or characteristic of an entity. Attributes become columns in a table.

_Example:_  
For the `Movie` entity, attributes include `MovieID`, `Title`, and `ReleaseYear`.

---

**Relationship**  
A relationship defines how two or more entities are connected to each other.

_Example:_  
A `Movie` _has_ a `Genre`, representing a relationship between the `Movie` and `Genre` entities.

---

**Primary Key**  
A primary key is an attribute that uniquely identifies each record in an entity. It must be unique and not null.

_Example:_  
`MovieID` is the primary key of the `Movie` table.

---

**Foreign Key**  
A foreign key is an attribute in one table that references the primary key of another table, establishing a relationship between entities.

_Example:_  
`GenreID` in the `Movie` table is a foreign key referencing `GenreID` in the `Genre` table.

---

### 1(b) Movies released before 2020 with their genres (8 marks)

```sql
SELECT m.Title, g.Name
FROM Movie m
INNER JOIN Genre g ON m.GenreID = g.GenreID
WHERE m.ReleaseYear < 2020;
```

---

### 1(c) Actors who have never been in any movies (8 marks)

```sql
SELECT a.FirstName, a.LastName
FROM Actor a
LEFT JOIN MovieActor ma ON a.ActorID = ma.ActorID
WHERE ma.MovieID IS NULL;
```

---

### 1(d) Average rating for each movie (8 marks)

```sql
SELECT m.Title, AVG(r.Rating) AS AverageRating
FROM Movie m
INNER JOIN Review r ON m.MovieID = r.MovieID
GROUP BY m.Title;
```

---

### 1(e) Add Budget column to Movie table (6 marks)

```sql
ALTER TABLE Movie
ADD Budget DECIMAL(10,2);
```

---

## Question 2

### 2(a) Database Normalisation (10 marks)

**Primary objectives of normalisation:**

- Reduce data redundancy
    
- Avoid data inconsistency
    
- Improve data integrity
    
- Simplify database maintenance
    

**Normal Forms:**

**First Normal Form (1NF):**

- All attributes contain atomic (indivisible) values
    
- No repeating groups
    

**Second Normal Form (2NF):**

- Table is in 1NF
    
- All non-key attributes depend on the whole primary key
    

**Third Normal Form (3NF):**

- Table is in 2NF
    
- No transitive dependencies (non-key attributes depend only on the primary key)
    

---

### 2(b) Proposed new entity (10 marks)

**New Entity:** `Director`

**Attributes:**

- `DirectorID` (Primary Key)
    
- `FirstName`
    
- `LastName`
    
- `DateOfBirth`
    

**Relationships:**

- One `Director` can direct many `Movie` records
    
- `DirectorID` would be added as a foreign key in the `Movie` table
    

This improves database structure by avoiding repeated director information in the Movie table.

---

### 2(c) Errors in SQL INSERT statements (10 marks)

**Query 1:**

```sql
INSERT INTO Movie
VALUES (102, 'The Shawshank Redemption', 1994, 'Frank Darabont');
```

**Error:**  
Number of values does not match the number of columns in the `Movie` table, and no column list is specified.

---

**Query 2:**

```sql
INSERT INTO Actor (ActorID, FirstName, LastName)
VALUES (201, Tom, Hanks);
```

**Error:**  
String values (`Tom`, `Hanks`) must be enclosed in single quotes.

---

**Query 3:**

```sql
INSERT INTO Movie (MovieID, Title, ReleaseYear, GenreID, Director)
VALUES (101, 'Inception', 2010, 1, 'Christopher Nolan', 'christopher.nolan@gmail.com');
```

**Error:**  
More values are provided than columns listed.

---

## Question 3

### 3(a) Adding value constraints using ALTER (12 marks)

```sql
ALTER TABLE Movie
ADD CONSTRAINT chk_movieid
CHECK (SUBSTR(MovieID, 1, 1) IN ('P', 'L', 'D', 'A'));

ALTER TABLE Genre
ADD CONSTRAINT chk_genreid
CHECK (SUBSTR(GenreID, 1, 1) BETWEEN 'A' AND 'Z');

ALTER TABLE Genre
ADD CONSTRAINT chk_genrename
CHECK (Name IN ('adventure', 'action', 'comedy', 'drama'));
```

---

### 3(b) NOT NULL constraint on ReleaseYear (8 marks)

```sql
ALTER TABLE Movie
ALTER COLUMN ReleaseYear SET NOT NULL;
```

**Explanation:**  
This ensures that every movie record must have a release year. It improves data integrity by preventing incomplete or invalid records.

---

### 3(c) Referential Integrity (10 marks)

Referential integrity ensures that relationships between tables remain consistent. It prevents invalid foreign key values that do not correspond to existing primary key values.

For example, a `GenreID` in the `Movie` table must already exist in the `Genre` table. Referential integrity is enforced using **foreign key constraints**, which prevent deletion or modification of referenced records if dependent records exist.

---
