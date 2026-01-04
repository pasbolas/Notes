
---

### 1. **Add a Column with a Default Value**
```sql
ALTER TABLE users
ADD COLUMN is_active BOOLEAN DEFAULT TRUE;
```

---

### 2. **Drop a Column**
```sql
ALTER TABLE post
DROP COLUMN shares;
```

---

### 3. **Modify a Column's Data Type**
#### PostgreSQL:
```sql
ALTER TABLE users
ALTER COLUMN username TYPE VARCHAR(100);
```
#### MySQL:
```sql
ALTER TABLE users
MODIFY COLUMN username VARCHAR(100);
```

---

### 4. **Rename a Column**
```sql
ALTER TABLE post
RENAME COLUMN postdate TO published_date;
```

---

### 5. **Add a NOT NULL Constraint**
```sql
ALTER TABLE users
ALTER COLUMN email SET NOT NULL;
```

---

### 6. **Drop a NOT NULL Constraint**
```sql
ALTER TABLE users
ALTER COLUMN email DROP NOT NULL;
```

---

### 7. **Add a Primary Key**
```sql
ALTER TABLE post
ADD PRIMARY KEY (postid);
```

---

### 8. **Drop a Primary Key**
```sql
ALTER TABLE post
DROP CONSTRAINT post_pkey;  -- Replace with actual constraint name
```

---

### 9. **Add a Foreign Key**
```sql
ALTER TABLE post
ADD FOREIGN KEY (userid) REFERENCES users(userid);
```

---

### 10. **Add a Unique Constraint**
```sql
ALTER TABLE users
ADD CONSTRAINT unique_email UNIQUE (email);
```

---

### 11. **Drop a Constraint**
```sql
ALTER TABLE users
DROP CONSTRAINT unique_email;
```

---

### 12. **Rename a Table**
```sql
ALTER TABLE post
RENAME TO articles;
```

---

### 13. **Add a CHECK Constraint**
```sql
ALTER TABLE post
ADD CONSTRAINT check_likes CHECK (likescount >= 0);
```

---

### 14. **Set a Default Value for Existing Column**
```sql
ALTER TABLE post
ALTER COLUMN shares SET DEFAULT 0;
```

---

### 15. **Drop a Default Value**
```sql
ALTER TABLE post
ALTER COLUMN shares DROP DEFAULT;
```

---

### 16. **Add Multiple Columns at Once**
```sql
ALTER TABLE post
ADD COLUMN tags TEXT,
ADD COLUMN views INT DEFAULT 0;
```

---

### 17. **Change Column Order (MySQL only)**
```sql
ALTER TABLE post
MODIFY COLUMN postdate TIMESTAMP AFTER title;
```

---

### 18. **Add an Index**
```sql
ALTER TABLE users
ADD INDEX idx_email (email);
```

---
