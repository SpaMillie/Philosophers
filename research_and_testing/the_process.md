# Research done for Philosophers

## First steps:
- finding out what threads, multithreading, and mutex(mutual exclusion) are
- find out about concurrency issues
- creating a pseudocode of sorts, outlining the program structure
- man-ing all the allowed functions from the subject

**Resources:**
- Wikipedia
	- [Thread (computing)](https://en.wikipedia.org/wiki/Thread_(computing))
	- [Multithreading (computer architecture)](https://en.wikipedia.org/wiki/Multithreading_(computer_architecture))
	- [Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

**Insights:**
- Threads
	- Threads are similar to processes in a sense. They exist within a program, but unlike processes, they don't copy the resources of the program exactly. Both could be said to be 'units of execution' but a thread would usually be a smaller unit compared to a process. While processes have their own memory space, threads share the memory space within the program/process. Processes are separate from each other so if one fails, the others can continue running. Threads can but don't have to run independently. Since they can, though, this means they can run at the same time, i.e. concurrently (cf. concurrent programming).
	- Why is a process more secure than a thread? Corrupting one process doesn't mean all processes get corrupted, unlike with the threads.
	- Another con of using threads is that it requires synchronisation. This means synchronisation-related issues need to be handled too. See race conditions, deadlocks, concurrency problems.
	- "In computing, a context switch is the process of storing the state of a process or thread, so that it can be restored and resume execution at a later point, and then restoring a different, previously saved, state." Context switching is different for threads and processes > processes are less efficient when it comes to CPU usage since the CPU must save and load (access?) the memory state of each process, while with threads this doesn't happen since they share the same memory space and resources
	- Since threads share the same address space, this makes resource exchanges run easier. But data shared between threads is prone to race conditions, i.e. the behaviour becomes dependent on how and until when other events take place, potentially resulting in inconsistencies and, as a consequence, bugs. Race conditions can be prevented by using mutexes.
	- fun fact: mutex is a so-called synchronisation primitive
	- Examples: for processes > opening two applications at the same time; for threads > sending or handling mutliple user requests in a web server)
	- Analogy: a factory (process) with its staff (thread(s))

- Multithreading
	- this has more to do with what the CPU or the core can do; running multiple threads at the same time basically
	- "Multithreading is a widespread programming and execution model that allows multiple threads to exist within the context of one process. These threads share the process's resources, but are able to execute independently."
	- "Multithreading libraries tend to provide a function call to create a new thread, which takes a function as a parameter. A concurrent thread is then created which starts running the passed function and ends when the function returns. The thread libraries also offer data synchronization functions."
	- Piggybacking on the previous point, the pthread functions might have a fixed order of calling to some extent. Testing of the functions and their functioning (pun intended) to be carried out.
	- fun fact: with multithreading the CPU fills in idle time, engages all the cores, stays active, allows for a more efficient use of its capabilities
	- a deadlock is a situation when a thread can't proceed because it is waiting for another thread (or itself?) to release a lock (in this mutlithreading scenario; can apply to other contexts in computing)

**Remember:**
- (multiple) threads of execution 
- context switching
- memory state
- concurrency problems
- deadlocks
- race conditons
- synchronisation primitive

## Allowed functions

| Function | Header | Prototype | Description | Return Value |
| --- | --- | --- | --- | --- |
| memset | string.h | void *memset(void *s, int c, size_t n); | fills the first n bytes of the memory area pointed to by s with the constant byte c | a pointer to the memory area s |
| printf | ... | ... | ... | the number of characters printed (excluding the null byte used to end output to strings) |
| malloc | ... | ... | ... | ... |
| free | ... | ... | ... | ... |
| write | ... | ... | ... | ... | 
| usleep | unistd.h | int usleep(useconds_t usec); | suspends  execution  of  the  calling thread for (at least) usec microseconds | 0 on success, -1 on error and errno set | 
| gettimeofday | sys/time.h | int gettimeofday(struct timeval *tv, struct timezone *tz); | gets the time + timezone | 0 on success, -1 on error and errno set |
| pthread_create | pthread.h | int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg); | starts a new thread in the calling process | on success returns 0; on error, it returns an error number, and the contents of *thread are undefined |
| pthread_detach | ... | int pthread_detach(pthread_t thread); | marks the thread as detached and returns its resources automatically back into the system | 0 on success, errno on error | 
| pthread_join | ... | int pthread_join(pthread_t thread, void **retval); | functions like wait() for processes, only this is for threads | 0 on success, errno on error |
| pthread_mutex_init* | ... | int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr); | initialise a mutex | 0 on success, errno on error | 
| pthread_mutex_destroy | ... | int pthread_mutex_destroy(pthread_mutex_t *mutex); | the mutex object becomes, in effect, uninitialized; destroy only unlocked, initialised mutexes | 0 on success, errno on error |
| pthread_mutex_lock | ... | int pthread_mutex_lock(pthread_mutex_t *mutex); |locks a mutex | 0 on success, errno on error | 
| pthread_mutex_unlock | ... | int pthread_mutex_unlock(pthread_mutex_t *mutex); | unlocks a mutex | 0 on success, errno on error | 

*If  attr  is NULL,  the  default mutex attributes are used; the effect shall be the same as passing the address of a default mutex attributes object. Upon successful initialization, the state of the mutex becomes initialized and unlocked.

**Things I'll definitely need:**
error handling for too many or too few arguments
an ft_usleep instead of just using usleep
timestamps need to be in order
everything norminetted
separate functions handling eating, sleeping, thinking
a monitoring mechanism (checking whether the philosopher has died or not)
checking if there are forks available
starting odd- or even-numbered philosophers a ms ahead(?)

**Notes:**
gettimeofday might need two variables - one set at the beginning of the process and another one to subtract the first one from to get the time elapsed in-between the executions

## Pseudocode

**struct**
number_of_philosophers
time_to_die
time_to_eat
time_to_sleep
(number_of_times_each_philosopher_must_eat)
int *mutex_id
int *philo_id
int start_time
int cur_time
int argc

**struct philo**
time_to_die
time_to_eat
time_to_sleep
(how_many_times_should_eat)

__main__
if argc == 4 || == 5
	start
else
	error (invalid arguments)

__start__
atoi args and save in a struct
if any arg > INT_MAX
	return (invalid args)
create_threads
init_mutex
run_simulation
destroy_mutex
detach_threads
cleanup?

__create_threads__
while philo_num > i
	check = pthread_create
	if (check != 0)
		error

init_mutex
//are atr NULL or specified?
while philo_num > i
	check = pthread_create
	if (check != 0)
		error
//maybe can go into create_threads?

__run_simulation__
if num_philo == 1
	ft_die
	return

