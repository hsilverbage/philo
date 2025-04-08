# 🧠 Philosophers – 42 Project

This project is a simulation of the classic **Dining Philosophers Problem**, implemented in C using POSIX threads (pthreads).  
It’s part of the common core at École 42 and focuses on **multithreading**, **synchronization**, and preventing **race conditions** and **deadlocks**.

---

## 🧩 Project Goals

- Understand and use **threads** (via `pthreads`)
- Manage **shared resources** (forks) using **mutexes**
- Handle **concurrency issues** like deadlocks and starvation
- Simulate time, routines, and clean program termination

---

## 🍽️ The Dining Philosophers Problem

Five philosophers sit at a table, each alternating between **thinking**, **eating**, and **sleeping**.  
Each needs **two forks** (one on each side) to eat. But there are only five forks...

> The challenge: allow all philosophers to eat **without starving**, **deadlocking**, or **crashing** the program.

---

## 🛠 Implementation Details

- **Language**: C  
- **Concurrency**: POSIX Threads  
- **Synchronization**: Mutexes  
- **Precise timing**: `usleep`, `gettimeofday`, time diff calculation  
- **Input parsing & error handling**

---

## 📦 Program Structure

```
philo/
├── philo.c              # Main program logic
├── utils.c              # Time & printing helpers
├── init.c               # Initialization of threads, mutexes, and data
├── routine.c            # Philosopher behavior loop
├── philo.h              # Headers and data structures
├── Makefile             # Compilation rules
```

---

## 🧪 How to Compile & Run

### ✅ Compile:

```bash
make
```

### 🚀 Run:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### 🧾 Example:

```bash
./philo 5 800 200 200
```

This runs the simulation with:
- 5 philosophers  
- Each dies if they don’t eat within 800ms  
- Eating takes 200ms  
- Sleeping takes 200ms

---

## 🧠 Bonus (If applicable)

If you did the **philo_bonus** version:

- Uses **processes** and **semaphores** instead of threads/mutexes
- Shows mastery of **IPC (Interprocess Communication)**

---

## 🧯 Error Handling

Handles:
- Invalid argument count
- Non-numeric input
- Overflow/underflow
- System call failures

---

## 📚 Useful References

- [Dining Philosophers – Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)  
- [`man pthreads`](https://man7.org/linux/man-pages/man7/pthreads.7.html)  
- [42 Docs & peer reviews]

---

## 👤 Author

**Name**: _Your Full Name_  
**42 Login**: _your_login_  
**Contact**: _your_email or LinkedIn_

---

## 📝 License

This project was developed as part of the 42 School curriculum.  
For educational and personal use only.
