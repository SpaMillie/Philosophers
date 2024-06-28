# Research done for Philosophers

## First steps:
- finding out what threads, multithreading, and mutex(mutual exclusion) are
- find out about concurrency issues
- creating a pseudocode of sorts, outlining the program structure


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
	- Context switching is different for threads and processes > processes are less efficient when it comes to CPU usage since the CPU must save and load (access?) the memory state of each process, while with threads this doesn't happen since they share the same memory space and resources
	- fun fact: with multithreading the CPU fills in idle time, engages all the cores, stays active, allows 
	- Examples: for processes > openning two applications at the same time; for threads > sending or handling mutliple user requests in a web server)
	- Analogy: a factory (process) with its staff (thread(s))

- Multithreading
	- this has more to do with what the CPU or the core can do

Remember:
- (multiple) threads of execution 
- context switching
- memory state
- concurrency problems

Things I'll definitely need:
error handling for too many or too few arguments
an ft_usleep instead of just using usleep
timestamps need to be in order
everything norminetted
separate functions handling eating, sleeping, thinking
a monitoring mechanism (checking whether the philosopher has died or not)
checking if there are forks available
starting odd- or even-numbered philosophers a ms ahead(?)


