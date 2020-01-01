# Ex3
First milestone of Advanced Programming course project.

coding by Eldad Horvitz and Nizan Mandelblit
## Getting Statred

#### GitHub
GitHub link of the project:

* [GithHub Project](https://github.com/NizanMandelblit/ex3).
#### Contributors
* [Nizan Mandelblit](https://github.com/NizanMandelblit)
* [Eldad Horvitz](https://github.com/EldadHorvitz)

#### Prerequisites
in order to properly run the project, the follwoing will need to be provided by the user:
* fly.txt file.
* [FlightGear simulator](https://www.flightgear.org/) software.
#### Run Command
the expected command line is to be:
```
  g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
```

## Introduction
#### Goal

The goal of this project is to connect to the FlightGear simulator game, and to send/recieve data from and to the simulator.
we use the file fly.txt in order to use the commands and execute the instructions which are written in it.

#### Compoistion
we used commands pattern to run commands without knowing whicj command it is (polymorphism).

we used shunting yard algorithm to handle mathematical expression.

## Work Flow
we use a function "lexer" that devides the data in the file and put it in a vector.
the vector contanes the commands and the information seperated (for each line one for the command and the second for the infoamation)

we initialze the maps of the symbol table according to the symbol table file and initialize the commands we work with.
we use the function parser to execute all the commands in the vector (originally in the text).

at the begining we open server to get data from the simulator we update in the program the data that we recived from the simulator.
it works in a thread in order to repeat during the program and update the data from the simulator.

we open client in order to send data to the simulator.
we save the client socket number in the map in order to use it out of class.

we have while and if commands that check if a condition is true and then they execute whats written in them.

sleep commands makes the thread o the main sleep.

print commands prints string or value of a variable from the table.

define var command initlazing a new var and put it in the table with the information it recived about it.

assignmeant command is updating value of a variable in the table and send it to the simulator if it needs to.


we use interpreter in order to make an Expression out of a text.
we use calculate in order to to get the result of the Expression.
we implimented it by using shunting yard algorithm that was invented by Edsger Dijkstra.
we change an infix expression to postfix expression.
than it pushes numbers to the output queue and operators onto a stack.
than it calculates it by poping the operators from the operator stack onto the output queue,
it pops 2 numbers and an operator them it calculates them and push back the result.
we use it for arithmetical expressions.

at the end we delete what we saved on the heap and close the client socket.
