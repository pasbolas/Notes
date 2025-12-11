# CMPU 2017 – Operating Systems 2  
**TU856 / TU858 – Year 2 – Semester 1 (2024/25)**  
**Exam Practice Solutions (Model Answers)**  
*(Based on the uploaded CMPU 2017 Operating Systems 2 paper.)*

---

> **Instructions (from paper)**  
> Answer Question 1 and **any two** other questions.  
> Question 1 carries **40 marks**, all others carry **30 marks** each.

---

## Question 1

### (a) What are the four conditions that are required for Deadlock to occur?  (4 marks)

**Answer:**  

The classic Coffman deadlock conditions are:

1. **Mutual Exclusion**  
   At least one resource must be held in a **non‑shareable** mode. Only one process at a time can use that resource.  
   - Example: A printer that can only print one job at a time.

2. **Hold and Wait**  
   A process is holding at least one resource and is **waiting** to acquire additional resources that are currently held by other processes.  
   - Example: Process P1 holds a printer and waits for a tape drive while still keeping the printer.

3. **No Pre‑emption**  
   Resources cannot be **forcibly removed** from a process; they must be released **voluntarily** by the process that holds them.  
   - Example: The OS does not interrupt and take the printer away from P1; P1 must finish and call `release(printer)`.

4. **Circular Wait**  
   There exists a set of processes `{P1, P2, …, Pn}` such that P1 is waiting for a resource held by P2, P2 is waiting for a resource held by P3, …, and Pn is waiting for a resource held by P1.  
   - Example: P1 waits for a tape drive held by P2; P2 waits for a disk held by P1 → cycle.

All **four** conditions must hold simultaneously for a deadlock to occur; if the operating system breaks any one of them, deadlock cannot arise.

---

### (b) Explain, using a suitable example, the steps required to push a node onto a stack.  (8 marks)

Assume we implement a stack as a **singly linked list**, with a pointer `top` that points to the **top node** of the stack. Each node has:

```c
struct Node {
    int data;
    struct Node *next;
};
struct Node *top = NULL;
```

To **push** (insert) a new value `x` onto the stack, we do:

1. **Allocate memory for the new node**  
   ```c
   struct Node *newNode = malloc(sizeof(struct Node));
   ```  
   If `malloc` returns `NULL`, we handle stack overflow / allocation failure.

2. **Store the data in the new node**  
   ```c
   newNode->data = x;
   ```

3. **Link the new node to the current stack top**  
   The new node’s `next` pointer should point to the current `top`.  
   ```c
   newNode->next = top;
   ```

4. **Update `top` to point to the new node**  
   ```c
   top = newNode;
   ```

5. **(Optional) Example**  
   - Suppose the stack currently is: `top -> [20] -> [10] -> NULL`  
   - We push `30`. After the operation:
     - New node `[30]` is created.
     - `newNode->next = top` (points to `[20]` node).
     - `top = newNode`.  
   - Final stack: `top -> [30] -> [20] -> [10] -> NULL`

This matches the LIFO semantics: the most recently pushed element (`30`) becomes the new top of the stack.

---

### (c) Explain, using suitable examples, the steps required to add a node to an ordered linked list.  (10 marks)

Consider a **sorted singly linked list** in **ascending order**, with head pointer `head`. Nodes are:

```c
struct Node {
    int data;
    struct Node *next;
};
struct Node *head = NULL;
```

To insert a value `x` while preserving order:

1. **Allocate and initialise the new node**  
   ```c
   struct Node *newNode = malloc(sizeof(struct Node));
   newNode->data = x;
   newNode->next = NULL;
   ```

2. **Case 1 – Insert at the beginning (empty list or smallest element)**  
   If the list is empty (`head == NULL`) **or** `x <= head->data`, then the new node becomes the new head:  
   ```c
   if (head == NULL || x <= head->data) {
       newNode->next = head;
       head = newNode;
       return;
   }
   ```  
   - Example: List is `10 -> 20 -> 40 -> NULL`.  
     - Insert `5` → new list: `5 -> 10 -> 20 -> 40 -> NULL`.

3. **Case 2 – Insert in the middle or at the end**  
   Traverse the list with two pointers: `prev` and `curr`:
   ```c
   struct Node *prev = head;
   struct Node *curr = head->next;

   while (curr != NULL && curr->data < x) {
       prev = curr;
       curr = curr->next;
   }
   ```

4. **Insert the new node between `prev` and `curr`**  
   ```c
   newNode->next = curr;
   prev->next = newNode;
   ```

5. **Examples**  
   - List: `10 -> 20 -> 40 -> 60 -> NULL`  
     - Insert `30`:  
       - Traversal stops when `curr->data` (40) ≥ 30.  
       - `prev` points to `20`, `curr` to `40`.  
       - Insert between them: `10 -> 20 -> 30 -> 40 -> 60 -> NULL`.
   - Insert `70`:  
       - Traversal goes to the end (`curr == NULL`).  
       - Insert after `60`: `10 -> 20 -> 40 -> 60 -> 70 -> NULL`.

This ensures the list remains sorted after each insertion.

---

### (d) Queue code using `add` and `printQueue`  (12 + 6 marks)

> The question refers to specific code for an `add` function and a `printQueue` function that are shown in the paper, and to the exact parameters passed to them in `main`. Those code snippets are not visible in the text version of the document I can see, so I cannot safely quote or trace them line‑by‑line.  
> I will therefore explain, in a general but exam‑style way, how to analyse such a question and what you should look for when deciding whether two nodes are added correctly and what `printQueue` would output.

#### (d)(i) Will the code add two nodes to a queue? (12 marks)

For a typical **linked queue** implementation, you have:

```c
struct Node {
    int data;
    struct Node *next;
};

struct Node *front = NULL;
struct Node *rear  = NULL;
```

A **correct** `add` (enqueue) function usually has a signature like:

```c
void add(struct Node **front, struct Node **rear, int value);
```

Key logic:

1. **Allocate node**
   ```c
   struct Node *newNode = malloc(sizeof(struct Node));
   newNode->data = value;
   newNode->next = NULL;
   ```

2. **If queue is empty** (`*front == NULL` and `*rear == NULL`)  
   - New node becomes both `front` and `rear`:
     ```c
     *front = newNode;
     *rear  = newNode;
     ```

3. **Else (non‑empty queue)**  
   - Link current `rear` to new node and update `rear`:
     ```c
     (*rear)->next = newNode;
     *rear = newNode;
     ```

The exam code often tries to trick you with **parameter passing**:

- If the function is declared as  
  `void add(struct Node *front, struct Node *rear, int value)`  
  and `main` calls `add(front, rear, value);`  
  then **only copies** of `front` and `rear` are modified. The caller’s `front` and `rear` stay unchanged, so effectively **no nodes are added** to the real queue.
- If the function uses **pointers to pointers**, i.e.  
  `add(&front, &rear, value);`  
  then modifications inside `add` affect the queue in `main`, and nodes are correctly added.

So, to answer the question “will the code add two nodes to a queue”, you need to check:

1. Are `front` and `rear` passed by **address** (`&front`, `&rear`) or by value?  
2. In the `add` function, are `*front` and `*rear` updated correctly in both empty and non‑empty cases?  
3. Are the `next` pointers set properly so the list remains a valid queue?

- If it uses `struct Node **front, **rear` and is logically correct → **Yes**, it will add two nodes.
- If it uses `struct Node *front, *rear` only and updates those local copies → the visible queue in `main` will still be **empty**, so effectively **no nodes** are added.

#### (d)(ii) Expected output of `printQueue` (6 marks)

A typical `printQueue` implementation looks like:

```c
void printQueue(struct Node *front) {
    struct Node *temp = front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
```

Given a correct `add` implementation and two calls such as:

```c
add(&front, &rear, 10);
add(&front, &rear, 20);
printQueue(front);
```

The expected output would be the values in **FIFO order**:

```text
10 20
```

If instead the `add` function is incorrect (front/rear passed by value and not updated in `main`), then `front` remains `NULL` and `printQueue(front)` prints **nothing** (possibly just a newline).

In an exam setting, once you have the **actual** argument values from the question (e.g. `add(&front, &rear, 3); add(&front, &rear, 5);`), you would:

1. Draw the queue after each call, showing `front`, `rear`, and `next` links.
2. Then trace `printQueue` from `front` and list the `data` values visited, in order.

---

## Question 2

### (a) Briefly describe the elements of a process control block (PCB).  (4 marks)

A **Process Control Block (PCB)** is a kernel data structure that stores all information the OS needs to manage a process. Typical elements include:

1. **Process Identification Information**  
   - Process ID (PID)  
   - Parent process ID  
   - User ID / group ID

2. **Processor State Information**  
   - **CPU registers** (general‑purpose registers, PC, SP, flags) saved when the process is switched out.  
   - **Program Counter (PC)**: address of next instruction to execute.  
   - **Process State**: e.g. new, ready, running, waiting/blocked, terminated.

3. **CPU Scheduling Information**  
   - Process priority  
   - Pointers to scheduling queues  
   - Other scheduling parameters (e.g. time slice, nice value in Unix/Linux).

4. **Memory Management Information**  
   - Base and limit registers, or page tables / segment tables.  
   - Information about the process’s address space: code, data, stack regions.

5. **Accounting Information**  
   - CPU time used, real time elapsed, time limits.  
   - Job or process number, user and system time, etc.

6. **I/O Status Information**  
   - List of open files and corresponding file descriptors.  
   - I/O devices allocated to the process.  
   - Pending I/O operations.

Together these fields allow the OS to **suspend and resume** a process, schedule it, and manage its resources correctly.

---

### (b) Use of `fork()` and `wait()` to produce a child process.  (9 marks)

The question refers to a specific code snippet, but the general behaviour of `fork()` and `wait()` in Linux is as follows.

#### `fork()`

- `pid_t pid = fork();`  
- `fork()` **duplicates** the calling process:
  - The **child** gets a return value of `0`.
  - The **parent** gets the **PID of the child** (a positive integer).
  - On error, `fork()` returns `-1` in the parent and no child is created.

Example structure:

```c
pid_t pid = fork();

if (pid < 0) {
    // Error handling
    perror("fork failed");
    exit(1);
}
else if (pid == 0) {
    // Child process code
    printf("Child: my PID is %d, parent PID is %d\n", getpid(), getppid());
    // Possibly call exec*() here
    exit(0);
}
else {
    // Parent process code
    printf("Parent: created child with PID %d\n", pid);
    // Typically calls wait() here
}
```

After `fork()`, **both** processes run **concurrently**, starting from the instruction **after** the `fork()` call, but they take different branches based on the return value.

#### `wait()`

- Prototype: `pid_t wait(int *status);`  
- The parent calls `wait()` to **block** until a child process terminates.
- `wait()` returns the PID of the child that finished. If `status` is not `NULL`, it stores the child’s exit status there.

Typical usage with `fork()`:

```c
pid_t pid = fork();

if (pid == 0) {
    // Child
    // Do some work
    exit(42);
}
else {
    int status;
    pid_t childPid = wait(&status);
    printf("Parent: child %d finished with status %d\n",
           childPid, WEXITSTATUS(status));
}
```

In the exam code, you should identify:

- The **child branch** (`pid == 0`): usually the place where work is done or `exec()` is called.
- The **parent branch** (`pid > 0`): typically calls `wait()` to synchronise, ensuring the child finishes before the parent continues (e.g. before printing a message or exiting).

---

### (c) Purpose of command line arguments `1000` and `10000` in `./fork 1000 10000`  (5 marks)

In a typical `fork` example with command line arguments, `argc` and `argv` are used like this:

```c
int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    // Use n and m for loop limits, ranges, etc.
}
```

Given the command line:

```bash
./fork 1000 10000
```

- `argv[0] = "./fork"`  → program name.  
- `argv[1] = "1000"`    → first numeric argument.  
- `argv[2] = "10000"`   → second numeric argument.

The numbers `1000` and `10000` are **parameters** used by the program, commonly to:

- Control **loop counts** (e.g. child loops 1000 times, parent 10000 times).  
- Define **ranges** of computation (e.g. child works on 1..1000, parent on 1001..10000).  
- Act as **delays** (e.g. passed to `usleep()` or a busy‑wait loop to simulate work).

In other words, they allow the same compiled program to be reused with different workload sizes without recompiling; they are read with `atoi()` or `strtol()` inside the code.

---

### (d) `execvp` – what it does and how `prog` / `argv` are filled for `cp file.c file2.c`  (4 marks)

Prototype:

```c
int execvp(char *prog, char **argv);
```

- `prog`: the **program name** to search for in the system’s `PATH`.  
- `argv`: a **NULL‑terminated array of strings**, representing the command line arguments; by convention `argv[0]` is the program name.

For the shell command:

```bash
cp file.c file2.c
```

If the program uses `execvp()` to execute that command, the typical call is:

```c
char *prog = "cp";
char *argv[] = { "cp", "file.c", "file2.c", NULL };

execvp(prog, argv);
perror("execvp failed");  // Only reached on error
```

- `prog` contains:  
  - `"cp"` – the name of the program to run.
- `argv` contains:  
  - `argv[0] = "cp"`  
  - `argv[1] = "file.c"`  
  - `argv[2] = "file2.c"`  
  - `argv[3] = NULL` (terminator)

What `execvp` does:

- It **replaces** the **current process image** with the new program (`cp` in this case).
- If successful, the current process **never returns** to the next line; it becomes the `cp` program.
- If it fails (e.g. command not found), it returns `-1` and `errno` is set.

Result (for this example): the file `file.c` is copied to `file2.c` by the `cp` command, in the context of the calling process.

---

### (e) Code using `fork()`, `wait()`, and `exec()` with `mv file1.c file2.c`  (8 marks)

The question refers to a specific code snippet that calls one of the `exec*` functions (likely `execvp` or `execlp`) after a `fork()`. Even without the exact code, the **standard pattern** for such a question is:

```c
int main(int argc, char *argv[]) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) {
        // Child process: execute mv
        execvp(argv[0], argv);
        perror("execvp failed");
        exit(1);
    }
    else {
        // Parent process
        wait(NULL);
        printf("Parent: mv finished\n");
    }
}
```

If the command line arguments (`argv`) correspond to:

```bash
mv file1.c file2.c
```

i.e.

- `argv[0] = "mv"`  
- `argv[1] = "file1.c"`  
- `argv[2] = "file2.c"`  
- `argv[3] = NULL`

then the behaviour is:

1. **Parent process** calls `fork()`:
   - A child process is created.

2. In the **child** branch (`pid == 0`):
   - `execvp("mv", argv)` (or equivalent) is called.  
   - The child process image is replaced by the `mv` program.
   - `mv` renames `file1.c` to `file2.c` (if `file1.c` exists and permissions allow).

3. In the **parent** branch (`pid > 0`):
   - The parent calls `wait()` (or `waitpid(pid, ...)`) and **blocks** until the child finishes running `mv`.
   - After `mv` completes, the parent resumes and may print a status message or exit.

Net effect:

- On successful execution, `file1.c` is **renamed** to `file2.c`.  
- The parent process only continues after the rename is complete, ensuring sequential behaviour.

---

## Question 3

### (a) Distinguish between single‑threaded and multi‑threaded processes.  (4 marks)

**Single‑threaded process:**

- Has **one** thread of control (one sequence of execution).  
- At any instant, it can be executing only **one** instruction.  
- State is simpler: one program counter, one stack, one set of registers.  
- Example: a simple command line tool that performs one task at a time with no internal concurrency.

**Multi‑threaded process:**

- Contains **multiple threads** within the same process.  
- Threads **share the same address space** (code, global data, heap, open files), but each has its own **program counter, registers and stack**.  
- Allows **concurrency** within a process:
  - One thread may handle I/O; another may process data; another may handle user interaction.
- More complex to manage (synchronisation, race conditions) but can improve **responsiveness** and **performance**, especially on multi‑core CPUs.

---

### (b) Explain the arguments to `pthread_create`.  (8 marks)

Prototype (simplified):

```c
int pthread_create(pthread_t *tidp,
                   pthread_attr_t *attr,
                   void *(*start_rtn)(void *),
                   void *arg);
```

1. **`pthread_t *tidp`**  
   - Output parameter where the **thread ID** is stored.  
   - The caller passes the **address** of a `pthread_t` variable.  
   - After a successful call, `*tidp` uniquely identifies the new thread and can be used in `pthread_join`, `pthread_cancel`, etc.

2. **`pthread_attr_t *attr`**  
   - Pointer to a structure specifying **thread attributes** (stack size, scheduling policy, detach state, etc.).  
   - If `attr` is `NULL`, the thread is created with **default attributes**.

3. **`void *(*start_rtn)(void *)`**  
   - Pointer to the **thread start routine** (function) that will be executed by the new thread.  
   - The function must match the signature:
     ```c
     void *threadFunc(void *arg);
     ```
   - When the thread starts, it runs this function.

4. **`void *arg`**  
   - A **single argument** passed to the start routine.  
   - It is a `void *` so you can pass a pointer to **any type** (e.g. pointer to int, struct, array).  
   - Inside `threadFunc`, you cast it back to the appropriate type.

Return value:

- `0` on success; non‑zero error code on failure.

Example:

```c
void *worker(void *arg) {
    int id = *(int *)arg;
    printf("Thread %d running\n", id);
    return NULL;
}

int main(void) {
    pthread_t tid;
    int id = 1;
    pthread_create(&tid, NULL, worker, &id);
    pthread_join(tid, NULL);
    return 0;
}
```

---

### (c), (d), (e) – Thread code and outputs

The exam refers to a **specific thread program** (“Explain the following code”, “What would be the output for ./thread, ./thread 3 7 7, ./thread 3 7 5”, and “What happens if `pthread_join` is removed?”). Those source code lines are embedded in the Word document in a way that is not visible in the text representation I can access, so I cannot see variable names, condition checks, or exact print statements.

Because of that, I **cannot reliably compute the exact outputs line‑by‑line**. However, I will outline how you should approach these sub‑questions in the exam, as a model answer.

#### (c) Explaining the code (10 marks)

Typical structure of such a question:

- `main` parses command line arguments (`argc`, `argv`).  
- It may check that a certain number of arguments is supplied; if not, it prints a usage message.  
- It creates one or more threads with `pthread_create`, passing arguments (often integers from `argv`) via a struct or via casted pointers.  
- Each thread function performs some computation (e.g. sums numbers, checks equality / inequalities, prints messages) and possibly returns a value via `pthread_exit` or by writing through a shared data structure protected by a mutex.

To score high marks:

- Clearly describe:
  - How command line arguments are read (`argc`, `argv`).  
  - How they are converted (`atoi`) to integers.  
  - How those integers are passed to the thread function.  
  - What the thread function does with them (e.g. compares, loops, prints).  
  - Where `pthread_join` is called and why it is needed (to wait for the thread and possibly retrieve its return value).

#### (d) Outputs for different command lines (6 marks)

For each command:

1. `./thread`  
   - Usually, `argc == 1`.  
   - Program likely detects missing arguments and prints an error or usage message such as:  
     `"Usage: ./thread a b c"` or similar.

2. `./thread 3 7 7`  
   - `argc == 4`.  
   - `argv[1] = "3"`, `argv[2] = "7"`, `argv[3] = "7"`.  
   - Code may, for example:
     - Check if the last two arguments are equal (7, 7) → print one type of message.  
     - Or compute some function f(3,7,7) and print the result.

3. `./thread 3 7 5`  
   - Similar reasoning as above, but with different relationships between the numbers; e.g. condition fails (`7 != 5`) so a different branch of the code executes.

To fully answer in an exam, you would trace:

- The exact conditions in the thread function.  
- The prints in each branch.  
- The order in which the main thread and worker thread messages appear (taking into account `pthread_join`).

#### (e) Removing `pthread_join` and running `./thread 6 5 7`  (2 marks)

Even without exact code, general consequences of **removing `pthread_join`** are:

1. **The main thread may terminate before the worker thread finishes**.  
   - If `main` returns from `main()` without joining or detaching the thread, the process can exit, and any unfinished threads are terminated.  
   - So the worker thread’s output **may not appear at all**, or may be cut off.

2. **Output becomes non‑deterministic / race‑like**.  
   - Sometimes the worker thread may finish quickly and print everything before `main` exits.  
   - Other times `main` may exit first, killing the thread prematurely.  
   - Hence, two practical outcomes:
     - You see the expected output from the thread.  
     - You see **no output** (or partial output) from the thread because the process terminated first.

The key exam point: `pthread_join` is required to **synchronise** with the worker thread and ensure it completes before `main` terminates.

---

## Question 4

### (a) Why careful control of concurrency is critical – the race problem.  (10 marks)

A **race condition** occurs when the result of a program depends on the **interleaving** of operations by concurrent processes/threads on a **shared resource** or variable.

#### Example – Shared Counter

Suppose two threads increment a global counter:

```c
int counter = 0;

void *threadFunc(void *arg) {
    for (int i = 0; i < 1000000; i++) {
        counter = counter + 1;
    }
    return NULL;
}
```

We create two threads, both running `threadFunc`, and then join them. The **logically correct** final value should be:

```text
counter = 2,000,000
```

But the increment operation

```c
counter = counter + 1;
```

is not atomic; it is composed of multiple steps:

1. Load `counter` from memory into a register.  
2. Add 1 to the register.  
3. Store the register back into `counter`.

If the threads interleave like this:

- Thread 1 loads `counter` (0) into a register.  
- Thread 2 loads `counter` (0) into a register.  
- Thread 1 adds 1 and stores 1 to `counter`.  
- Thread 2 adds 1 and stores 1 to `counter`.

Even though there have been **two increments**, the final value is **1**, not 2. This is a **lost update** caused by a race condition.

Because the scheduling/interleaving is non‑deterministic, repeated runs of the same program can produce **different results** (e.g. 1,950,000; 1,820,000; etc.), which is unacceptable in correct systems.

Therefore, access to shared data must be carefully controlled (e.g. by locks, semaphores, monitors, condition variables) to ensure mutual exclusion and correctness.

---

### (b) How Test‑and‑Set is used to prevent the race problem.  (6 marks)

**Test‑and‑Set** is an **atomic hardware instruction** used to implement mutex locks.

Let `lock` be a shared boolean variable (0 = unlocked, 1 = locked). A typical pseudo‑code for Test‑and‑Set is:

```c
boolean TestAndSet(boolean *target) {
    boolean old = *target;
    *target = true;
    return old;
}
```

Key property: The **read** and **write** of `target` happen as **one indivisible operation**; no other processor or core can see an intermediate state.

To implement a **spinlock** mutex:

```c
while (TestAndSet(&lock)) {
    // busy wait (spin) until lock becomes 0
}

// critical section

lock = false;  // release
```

Explanation:

1. A thread that wants to enter the critical section calls `TestAndSet(&lock)`:
   - If `lock` was `false` (0), `TestAndSet` sets it to `true` and returns `false`. The while condition fails, and the thread enters the critical section.  
   - If `lock` was already `true` (1), `TestAndSet` returns `true`, and the thread **spins** in the while loop until some other thread releases the lock.

2. When the thread leaves the critical section, it sets `lock = false`, allowing another waiting thread to acquire it.

Because the Test‑and‑Set operation is atomic, it ensures that **only one thread at a time** succeeds in acquiring the lock, thereby enforcing **mutual exclusion** and preventing race conditions on the protected shared data.

---

### (c) Condition variable code with `TCOUNT = 5`, `COUNT_LIMIT = 6`, `count = 0`  (14 marks)

The question refers to a particular condition‑variable example, very similar to the classic `condvar.c` program (with `count`, `count_mutex`, and `count_threshold_cv`, and two kinds of threads: one “watcher” thread and two “incrementing” threads). The precise source code is not visible here, but its structure is known from standard Pthreads examples.

Typical elements:

```c
#define NUM_THREADS  3
int count = 0;
pthread_mutex_t count_mutex;
pthread_cond_t  count_threshold_cv;

void *watch_count(void *id);
void *inc_count(void *id);
```

- `watch_count` waits until `count` reaches `COUNT_LIMIT`, then modifies `count`.  
- `inc_count` increments `count` inside a loop up to `TCOUNT` times and signals the condition variable when `count` reaches `COUNT_LIMIT`.

With:

```c
TCOUNT      = 5;
COUNT_LIMIT = 6;
count       = 0;
```

and `main()` creating one watcher and two incrementing threads, a high‑level explanation is:

#### 1. Initialisation

- `count` is initialised to 0.  
- `count_mutex` (a mutex) and `count_threshold_cv` (a condition variable) are initialised.  
- Threads are created, e.g.:
  - Thread 0: `watch_count` (the “waiting” thread).  
  - Thread 1 and Thread 2: `inc_count` (the “incrementing” threads).

#### 2. Behaviour of the watcher thread

Pseudo‑code:

```c
void *watch_count(void *id) {
    pthread_mutex_lock(&count_mutex);

    while (count < COUNT_LIMIT) {
        pthread_cond_wait(&count_threshold_cv, &count_mutex);
        // when awakened, mutex is re‑acquired
        // typically prints and may adjust count
    }

    pthread_mutex_unlock(&count_mutex);
    pthread_exit(NULL);
}
```

- It locks `count_mutex`.  
- While `count` is less than `COUNT_LIMIT` (6), it calls `pthread_cond_wait`:
  - This **atomically** releases `count_mutex` and puts the thread to sleep.  
  - It will be woken up when some other thread calls `pthread_cond_signal` or `pthread_cond_broadcast` on `count_threshold_cv`.  
  - Upon wakeup, it re‑acquires `count_mutex` before returning from `pthread_cond_wait`.

#### 3. Behaviour of each incrementing thread

Pseudo‑code:

```c
void *inc_count(void *id) {
    for (int i = 0; i < TCOUNT; i++) {
        pthread_mutex_lock(&count_mutex);

        count++;
        // print or log current count and thread id

        if (count == COUNT_LIMIT) {
            pthread_cond_signal(&count_threshold_cv);
        }

        pthread_mutex_unlock(&count_mutex);
        // optional: sleep or yield to emphasise interleavings
    }
    pthread_exit(NULL);
}
```

- Each incrementing thread loops `TCOUNT` (= 5) times, so overall a maximum of `2 × 5 = 10` increments can occur.  
- On each iteration, it:
  1. Locks `count_mutex`.  
  2. Increments `count`.  
  3. If `count` equals `COUNT_LIMIT` (6), it signals the condition variable.  
  4. Unlocks the mutex.

#### 4. Timeline with given constants

- Initial `count = 0`.  
- Two incrementing threads run; due to scheduling, increments interleave, but eventually `count` will reach 6.  
- On the increment where `count` becomes 6:
  - The incrementing thread calls `pthread_cond_signal(&count_threshold_cv)`.  
  - This wakes the watcher thread (if it is waiting).

When the watcher wakes:

1. It re‑acquires `count_mutex`.  
2. It checks the loop condition `while (count < COUNT_LIMIT)` again:
   - Now `count == 6`, so the loop ends.  
3. It might modify `count` further (in many versions of the example, the watcher adds a constant amount to `count`, e.g. `count += 125;`).  
4. It prints the final value of `count` and unlocks the mutex.  
5. It exits via `pthread_exit`.

The incrementing threads may continue to run if they still have remaining loop iterations (because `TCOUNT = 5`, each does exactly five increments). Eventually:

- All increments finish (up to 10 increments total).  
- All threads terminate.  
- `main()` joins them and prints the final `count` value.

#### 5. What you should explain in an exam answer

To score well on this 14‑mark part, your answer should:

1. **Describe the role of `count_mutex`**:  
   - Ensures that only one thread at a time can read/modify `count`.  
   - Prevents race conditions on `count`.

2. **Describe the role of `count_threshold_cv`**:  
   - Used by incrementing threads to **signal** the watcher when `count` reaches `COUNT_LIMIT`.  
   - Used by the watcher to **wait** for that event.

3. **Trace the control flow**:  
   - Watcher locks mutex, sees `count < 6`, goes to `pthread_cond_wait`.  
   - Incrementers increment `count`; when they hit 6, they signal the condition variable.  
   - Watcher wakes, sees `count >= 6`, performs its post‑threshold logic, then terminates.

4. **Discuss the effect of `TCOUNT = 5` and `COUNT_LIMIT = 6`**:  
   - There are enough increments (10 possible) to ensure that `count` will reach 6, so the watcher will eventually be signalled and will complete.  
   - The exact interleaving between incrementer threads is non‑deterministic, but the use of mutex and condition variable guarantees correctness (no races on `count`, and the watcher will not miss the signal when using the loop and mutex correctly).

---

**End of model answers.**
