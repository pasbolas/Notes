
# **Constraints Syntax Only (Without Table Creation)**

## **1. PRIMARY KEY Constraint**
```sql
-- Add
ADD PRIMARY KEY (column_name)

-- Composite primary key
ADD PRIMARY KEY (col1, col2, col3)

-- Drop
DROP PRIMARY KEY
-- OR
DROP CONSTRAINT constraint_name
```

---

## **2. FOREIGN KEY Constraint**
```sql
-- Add
ADD FOREIGN KEY (column) REFERENCES other_table(other_column)

-- Add with name and actions
ADD CONSTRAINT fk_name 
FOREIGN KEY (column) REFERENCES other_table(other_column)
ON DELETE action
ON UPDATE action

-- Actions: CASCADE, SET NULL, SET DEFAULT, RESTRICT, NO ACTION
```

---

## **3. UNIQUE Constraint**
```sql
-- Add single column
ADD UNIQUE (column_name)

-- Add with name
ADD CONSTRAINT unique_name UNIQUE (column_name)

-- Composite unique
ADD CONSTRAINT unique_combo UNIQUE (col1, col2)

-- Drop
DROP CONSTRAINT constraint_name
```

---

## **4. CHECK Constraint**
```sql
-- Add basic
ADD CHECK (condition)

-- Add with name
ADD CONSTRAINT check_name CHECK (condition)

-- Examples of conditions:
CHECK (age >= 18)
CHECK (salary > 0)
CHECK (email LIKE '%@%')
CHECK (status IN ('Active', 'Inactive', 'Pending'))
CHECK (end_date > start_date)

-- Drop
DROP CONSTRAINT constraint_name
```

---

## **5. NOT NULL Constraint**
```sql
-- Add
ALTER COLUMN column_name SET NOT NULL

-- Remove
ALTER COLUMN column_name DROP NOT NULL
```

---

## **6. DEFAULT Constraint**
```sql
-- Add/Set
ALTER COLUMN column_name SET DEFAULT default_value

-- Remove
ALTER COLUMN column_name DROP DEFAULT

-- Examples:
SET DEFAULT 0
SET DEFAULT 'Pending'
SET DEFAULT CURRENT_DATE
SET DEFAULT CURRENT_TIMESTAMP
```

---

## **7. ALL CONSTRAINTS IN ONE ALTER TABLE**
```sql
-- Multiple constraints in one statement
ADD PRIMARY KEY (id),
ADD CONSTRAINT fk_user FOREIGN KEY (user_id) REFERENCES users(id),
ADD CONSTRAINT chk_age CHECK (age >= 0),
ADD CONSTRAINT uniq_email UNIQUE (email),
ALTER COLUMN name SET NOT NULL,
ALTER COLUMN created_at SET DEFAULT CURRENT_TIMESTAMP;
```

---

## **8. DROP CONSTRAINTS**
```sql
-- Drop primary key
DROP PRIMARY KEY

-- Drop foreign key
DROP CONSTRAINT fk_name

-- Drop unique
DROP CONSTRAINT unique_name

-- Drop check
DROP CONSTRAINT check_name

-- Drop default (different syntax)
ALTER COLUMN column_name DROP DEFAULT
```

---

## **9. EXAMPLES WITH ACTUAL VALUES**

### **Check constraint examples:**
```sql
CHECK (age BETWEEN 0 AND 120)
CHECK (quantity >= 0 AND quantity <= 1000)
CHECK (phone_number ~ '^[0-9]{10}$')
CHECK (discount >= 0 AND discount <= 100)
CHECK (created_at <= CURRENT_TIMESTAMP)
CHECK (UPPER(gender) IN ('M', 'F', 'O'))
```

### **Foreign key with actions:**
```sql
FOREIGN KEY (dept_id) REFERENCES departments(id) ON DELETE CASCADE
FOREIGN KEY (manager_id) REFERENCES employees(id) ON DELETE SET NULL
FOREIGN KEY (order_id) REFERENCES orders(id) ON DELETE RESTRICT
FOREIGN KEY (user_id) REFERENCES users(id) ON UPDATE CASCADE
```

### **Composite constraints:**
```sql
PRIMARY KEY (student_id, course_id, semester)
UNIQUE (product_id, warehouse_id, batch_no)
CHECK (start_time < end_time AND end_time <= '23:59:59')
```
