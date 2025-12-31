
##  Character Functions

### Nullif(x,y) 

Return NULL if both parameters are equal.
```sql
Select sponsor, nullif(sponsor, 'SFI')
from grant_funding;
```

### Coalesce()

Returns the value if the value is not null.

```sql
SELECT 
    FirstName || ' ' || COALESCE(MiddleName || ' ', '') || LastName AS FullName
FROM Employees;
```

If first param is null, the second one is returned.

#### Greatest (a, b) 
Returns the greatest among them.

#### Least (a,b)
Returns the least among them.


## Number Functions

#### Round(11.1, 1) -> rounds off 11.1 to 11
#### Trunc(13.928, 2)  -->  returns 13.92

#### Mod (15, 2) --> returns 1

#### Absolute Function : abs( a - b)
returns the modulus of the difference


## Date Functions

### to_char

Can be used to display date in certain format.

```sql
select 
	birth_date, 
	to_char(birth_date, 'DD/MM/YYYY') 
from 
	Scientist
```

#### To get current time

```sql
Select now();
Select current_date();
```

#### Age gets the age of the date passed
```sql
SELECT age(birth_date) from scientist;
```

#### Cast()

```sql
Select 
	cast(begin_date as TEXT) 
from 
	research;
```

or as shortcut 

```sql
Select 
	amount::text
from 
	grant_funding; 
```

