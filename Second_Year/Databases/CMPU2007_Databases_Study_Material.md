
# CMPU2007 — Databases 1 (Full Study Material + Syntax Examples)

## 1. Entity Relationship Concepts

### Example ERD (Social Media Database)
```
USER (UserID, Username, FirstName, LastName, Email)
POST (PostID, Title, Content, PostDate, UserID)
LIKE (LikeID, UserID, PostID)
FRIENDSHIP (User1ID, User2ID)
```

**Relationships**
- User (1) → Post (M)
- User (M) ↔ User (M) via Friendship
- Post (1) → Like (M)

---

## 2. SQL Queries and Syntax Examples

### SELECT + JOIN Example
```sql
CREATE TABLE User (
  UserID INT PRIMARY KEY,
  Username VARCHAR(50),
  FirstName VARCHAR(50),
  LastName VARCHAR(50),
  Email VARCHAR(100)
);

CREATE TABLE Post (
  PostID INT PRIMARY KEY,
  Title VARCHAR(100),
  Content TEXT,
  PostDate DATE,
  UserID INT REFERENCES User(UserID)
);

INSERT INTO User VALUES (1, 'alice', 'Alice', 'Johnson', 'alice@email.com');
INSERT INTO User VALUES (2, 'bob', 'Bob', 'Smith', 'bob@email.com');
INSERT INTO Post VALUES (101, 'First Day', 'Hello World', '2022-12-01', 1);
INSERT INTO Post VALUES (102, 'Holiday', 'Travel pics', '2023-02-01', 2);

SELECT p.Title, u.Username
FROM Post p
JOIN User u ON p.UserID = u.UserID
WHERE p.PostDate < '2023-01-01';
```

### GROUP BY + Aggregate Example
```sql
CREATE TABLE Genre (
  GenreID CHAR(4) PRIMARY KEY,
  GenreName VARCHAR(50)
);

CREATE TABLE Movie (
  MovieID CHAR(4) PRIMARY KEY,
  Title VARCHAR(100),
  ReleaseYear INT,
  GenreID CHAR(4) REFERENCES Genre(GenreID)
);

INSERT INTO Genre VALUES ('A001', 'Action'), ('C001', 'Comedy');
INSERT INTO Movie VALUES ('M001', 'Inception', 2010, 'A001'), ('M002', 'Rush Hour', 1998, 'C001');

SELECT g.GenreName, COUNT(m.MovieID) AS TotalMovies
FROM Movie m
JOIN Genre g ON m.GenreID = g.GenreID
GROUP BY g.GenreName;
```

### LEFT JOIN + IS NULL Example
```sql
SELECT CONCAT(u.FirstName, ' ', u.LastName) AS FullName
FROM User u
LEFT JOIN Post p ON u.UserID = p.UserID
WHERE p.PostID IS NULL;
```

### Date Formatting
```sql
SELECT p.Title, TO_CHAR(p.PostDate, 'DD Mon YYYY') AS FormattedDate
FROM Post p;
```

### ALTER TABLE Examples
```sql
ALTER TABLE Post ADD Shares INTEGER;

ALTER TABLE Movie ADD Budget DECIMAL(10,2);

ALTER TABLE Post ALTER COLUMN PostDate SET NOT NULL;

ALTER TABLE Movie ADD CONSTRAINT chk_movieid CHECK (SUBSTR(MovieID,1,1) IN ('P','L','D','A'));
```

### NULL Handling
```sql
SELECT UserID, COALESCE(Email, 'Unknown') AS Email FROM User;
```

---

## 3. Normalisation Forms

| Normal Form | Rule                     | Example                                |
| ----------- | ------------------------ | -------------------------------------- |
| 1NF         | Atomic attributes only   | Split multivalued fields into new rows |
| 2NF         | No partial dependency    | Move attributes to new table           |
| 3NF         | No transitive dependency | Remove derived attributes              |

---

## 4. Integrity and Constraints Examples
```sql
ALTER TABLE Post
ADD CONSTRAINT fk_user FOREIGN KEY (UserID)
REFERENCES User(UserID);

ALTER TABLE Movie
ADD CONSTRAINT chk_year CHECK (ReleaseYear BETWEEN 1900 AND 2100);
```

---

## 5. INSERT Error Fixing Examples
| Error | Wrong | Fixed |
|-------|-------|-------|
| Missing Quotes | `INSERT INTO Movie VALUES (101, Inception, 2010);` | `INSERT INTO Movie VALUES ('M101', 'Inception', 2010);` |
| Wrong Count | `INSERT INTO User VALUES ('U01', 'John');` | `INSERT INTO User (UserID, Username, Email) VALUES ('U01', 'John', 'john@email.com');` |

---

## 6. New Entity Example
```sql
CREATE TABLE Comment (
  CommentID SERIAL PRIMARY KEY,
  UserID INT REFERENCES User(UserID),
  PostID INT REFERENCES Post(PostID),
  Content TEXT NOT NULL,
  CommentDate DATE DEFAULT CURRENT_DATE
);
```

---

## 7. Common SQL Functions
| Category | Function | Example |
|-----------|-----------|----------|
| String | CONCAT(), LOWER(), UPPER() | `SELECT UPPER(Username) FROM User;` |
| Aggregation | COUNT(), AVG(), SUM() | `SELECT COUNT(*) FROM Post;` |
| Date | TO_CHAR(), CURRENT_DATE | `SELECT TO_CHAR(CURRENT_DATE, 'DD Mon YYYY');` |
| NULL | NVL(), COALESCE() | `SELECT COALESCE(Email, 'N/A') FROM User;` |
