# 🍴 philosophers
Who thought philosophy would be so deadly.

## 🧐 Description:
This project is all about the dining philosophers problem and the basics of threading a process. Threads, mutexes and whatnot.
One or more philosophers are sitting at a round table doing one of three things: eating, thinking, or sleeping.

The philosophers sit at a circular table with a big 'ol bowl of spaghetti in the center. There are the same number of forks on the table as there are philosophers. A philosopher needs two forks to eat. Whenever a philosopher is done eating, he will drop his forks and start sleeping. When a philosopher is done sleeping, he will start thinking. The simulation stops when a philosopher dies.

## 🔧 Usage:
1. Go into the root directory and run `make`.
```
cd philosophers
make
```
2. Run the executable created.
```
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] (*optional* [number_of_meals_each_philosopher_must_eat])
```
E.g:
```
./philo 5 800 200 200
```
