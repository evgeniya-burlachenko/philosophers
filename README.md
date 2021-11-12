![philos](https://user-images.githubusercontent.com/63720882/139644206-60210874-2101-4ee5-837a-2b613d272555.png)
# philosophers
Five silent philosophers sit at a round table with bowls of spaghetti. Forks are placed between each pair of adjacent philosophers. Each philosopher must alternately think and eat. However, a philosopher can only eat spaghetti when they have both left and right forks. Each fork can be held by only one philosopher and so a philosopher can use the fork only if it is not being used by another philosopher. After an individual philosopher finishes eating, they need to put down both forks so that the forks become available to others. A philosopher can only take the fork on their right or the one on their left as they become available and they cannot start eating before getting both forks. Eating is not limited by the remaining amounts of spaghetti or stomach space; an infinite supply and an infinite demand are assumed.

# Dining philosophers problem

This project has a goal to get knowledge about multhithreding and multiprocessing and related problems with data manipulation.


>Philo - multithreading and mutex;

>Philo_bonus - multiprocessing and semaphore.

# Parameters

`./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]`

`./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]`

1. number_of_philosophers: is the number of philosophers and also the number of forks
2. time_to_die: is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’ milliseconds after starting his last meal or the beginning of the       simulation, it dies
3. time_to_eat: is in milliseconds and is the time it takes for a philosopher to eat. During that time he will need to keep the two forks
4. time_to_sleep: is in milliseconds and is the time the philosopher will spend sleeping
5. number_of_times_each_philosopher_must_eat: argument is optional, if all philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.

# Source

* https://youtu.be/6j4lwImwyT8 - Лекция по проекту Philosofers (school 21) ч.1
* https://youtu.be/2sv8LB0_uKg - Лекция по проекту Philosofers (school 21) ч.2
* https://learnc.info/c/pthreads_mutex_introduction.html - Введение в мьютексы
* https://learnc.info/c/pthreads_deadlock.html - Deadlock
* https://learnc.info/c/pthreads_semaphores.html - Семафоры
* https://learnc.info/c/pthreads_create_and_join.html - Создание и ожидание выполнения потоков
* https://nafuka11.github.io/philosophers-visualizer/ - визуализатор
