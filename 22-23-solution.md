

---

# **Question 1**

## **1(a) ERD concepts + ERD explanation (20 marks)**

### Entity

An **entity** represents a real-world object or concept that the database stores information about. Each entity is usually represented as a table.

**Example:**  
`game`, `platform`, `genre`, and `game_publisher` are entities in the video game database.

---

### Attribute

An **attribute** is a property or characteristic of an entity. Attributes correspond to columns in a table.

**Example:**  
In the `game` entity, attributes include `game_id`, `game_name`, `genre_id`, and `publisher_id`.

---

### Relationship

A **relationship** defines how two entities are connected.

**Example:**  
A `game` belongs to a `genre`, and a `game` is published by a `game_publisher`.  
The table `game_platform` represents a **many-to-many relationship** between `game` and `platform`.

---

### Primary Key

A **primary key** uniquely identifies each record in a table. It cannot contain NULL values and must be unique.

**Example:**  
`game_id` is the primary key of the `game` table.  
The combination `(platform_id, game_id)` is the primary key of `game_platform`.

---

### Foreign Key

A **foreign key** is an attribute that references the primary key of another table to enforce relationships.

**Example:**  
`genre_id` in the `game` table is a foreign key referencing `genre(genre_id)`.

---

## **1(b) Value constraints using ALTER (15 marks)**

```sql
ALTER TABLE game
ADD CONSTRAINT chk_gameid
CHECK (SUBSTR(game_id, 1, 1) IN ('P','L','D','A'));

ALTER TABLE game_publisher
ADD CONSTRAINT chk_email
CHECK (publisher_email LIKE '%@%.%');

ALTER TABLE platform
ADD CONSTRAINT chk_platformid
CHECK (SUBSTR(platform_id, -1) BETWEEN '1' AND '6');

ALTER TABLE genre
ADD CONSTRAINT chk_genreid
CHECK (SUBSTR(genre_id, 1, 1) BETWEEN 'A' AND 'Z');

ALTER TABLE genre
ADD CONSTRAINT chk_genrename
CHECK (genre_name IN ('adventure','RPG','simulation','puzzle'));
```

---

## **1(c) Errors in INSERT statements (5 marks)**

### Query 1

```sql
INSERT INTO game_publisher VALUES ('Pewter Games', 'pewter@email.com');
```

**Error:**  
Missing `publisher_id` and number of values does not match table structure.

---

### Query 2

```sql
INSERT INTO game VALUES ('1453', 5555, Super Mario, 1234);
```

**Errors:**

- `Super Mario` must be in single quotes
    
- Attribute order does not match table definition
    

---

### Query 3

```sql
INSERT INTO platform (platform_id, platform_name, developer_name)
VALUES (4321, 'Xbox’, ‘Brain Games Studio', 'Mabel Addis');
```

**Errors:**

- Mismatched quotes
    
- Too many values for listed columns
    

---

# **Question 2**

## **2(a) Games with publisher and sales info (12 marks)**

```sql
SELECT g.game_name, g.genre_id, p.publisher_name, s.number_of_sales
FROM game g
INNER JOIN game_publisher p ON g.publisher_id = p.publisher_id
INNER JOIN sale s ON p.publisher_id = s.publisher_id;
```

---

## **2(b) Modified output (10 marks)**

```sql
SELECT 
LOWER(g.game_name) AS "Game Title",
g.genre_id AS "Genre Identifier",
LOWER(p.publisher_name) AS "Name of the publisher",
s.number_of_sales AS "Sales"
FROM game g
INNER JOIN game_publisher p ON g.publisher_id = p.publisher_id
INNER JOIN sale s ON p.publisher_id = s.publisher_id;
```

---

## **2(c) Insert new publishers (8 marks)**

```sql
INSERT INTO game_publisher VALUES (5055, 'Blue Dragon', 'blue@email.com');
INSERT INTO game_publisher VALUES (4500, 'Major Galaxy', 'major@email.com');
INSERT INTO game_publisher VALUES (3245, 'Fabulous Magic', 'fabulous@email.com');
INSERT INTO game_publisher VALUES (4532, 'Super Studio', NULL);
```

---

# **Question 3**

## **3(a) Publisher details with formatting (8 marks)**

```sql
SELECT 
publisher_id,
UPPER(publisher_name) AS publisher_name,
NVL(publisher_email, 'Unknown') AS publisher_email
FROM game_publisher
ORDER BY publisher_id DESC;
```

---

## **3(b) Count simulation games (5 marks)**

```sql
SELECT 
'There are ' || COUNT(*) || ' simulation games on the database'
FROM game g
INNER JOIN genre ge ON g.genre_id = ge.genre_id
WHERE ge.genre_name = 'Simulation';
```

---

## **3(c) Number of games per genre (8 marks)**

```sql
SELECT 
ge.genre_name AS "Game genre",
COUNT(g.game_id) AS "Number of games"
FROM genre ge
LEFT JOIN game g ON ge.genre_id = g.genre_id
WHERE ge.genre_name IN ('Simulation','RPG','Adventure','Puzzle')
GROUP BY ge.genre_name
ORDER BY COUNT(g.game_id) DESC;
```

---

## **3(d) Integrity rules (9 marks)**

### Entity Integrity

Ensures each table has a primary key and no primary key value is NULL.

**Example:**  
`game_id` uniquely identifies each game.

---

### Domain Integrity

Ensures attribute values are valid and within defined domains.

**Example:**  
`genre_name` restricted to specific values using CHECK constraints.

---

### Referential Integrity

Ensures foreign keys correctly reference existing primary keys.

**Example:**  
`publisher_id` in `game` must exist in `game_publisher`.

---
