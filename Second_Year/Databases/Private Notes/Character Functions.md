## Case Manipulation

#### Upper / Lower

```sql
select Title, Upper(Title) as "Upper Title"
from research;
```

#### Concatenate
```sql
CONCAT('hello', ' ', 'world)
```

##### Another Way :
      'a' || NULL --> NULL
       Concat('a', NULL) --> 'a'

#### Substring
``` sql
SUBSTR('Hello World', 1 , 5) <----- Hello
```

#### Position
```sql
POSITION('W' in 'Hello World')
```

#### Left Pad
```sql
LPAD('tech', 8, '0')
```

#### Replace
```sql
REPLACE('Jack', 'J', 'Bl')
```

#### Trim
```sql
TRIM('H' from 'Hello World')
```

