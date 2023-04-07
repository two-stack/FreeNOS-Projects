Project 3: Prioritize it

Names: Lorenzo Cabrera, Zhong Ooi

Contribution:
Lorenzo: Implementation of Prioritry, ps -l, and renice
Zhong: Worked with Lorenzo to create ML scheduling of the processes

Features:
- processes all have priority now, defaulting at priority level 3. Priority levels go between 1-5 with 1 being the lowest and 5 the highest.
- ps -l now prints priorities of the processes
- renice -n (priority) (PID) sets the Process with the given PID to the new priorirty
- Scheduling uses ML algorithm to schedule, there are 5 queues for each priority level

Branch:
priority branch contains all changes, includes wait command from Project 2

Comments:
We had issues debugging FreeNOS as there was no debugger client and we could not print in the kernel. As well as this, renice follows the structure of the ps applications as was stated in the instructions but if we were to reimplement it again, we would follow the structure of the sleep command and write a new syscall.

Link to video:

https://youtu.be/6-s3FkaRmSs

