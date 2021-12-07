# Assignment 3

#### Deadlines: 

- Part 1: **Monday, Nov 29**. 
- Part 2: **Wednesday, Dec 8**.

## Introduction

The purpose of the assignment is to learn how a functional programming languages can be extended to an imperative programming language. 

- Part 1 introduces only a small amount of more convenient syntax: Better notation for lists, pattern matching, separate definitions. Nothing serious, so apart from getting used to the new syntax, you should be able to carry over everything you learned from Assignment 2.

- Part 2 will add sequential composition, assignment, while loops and pointers. 

## Instructions

You may form groups of up to 2 students. 

Each group submits their answer by sending me a link to their github repository via [email using this link](mailto:akurz@chapman.edu?subject=Assignment%203%20Part%20X).

Use the same private github repository as for Assignment 1 and 2. If you think that this is not possible/appropriate get in touch. 

Put a copy of [LambdaFun](https://github.com/alexhkurz/programming-languages-2021/tree/main/Lab2-Lambda-Calculus/LambdaFun) in your repository. The file structure should look as follows.

    Assignment1
    Assignment2
    Assignment3
        README.md -- name of students, critical appraisal
        LambdaFun -- copy of LambdaFun plus your solutions
            test/solutions.lc -- solution for Part 1
            test/round-robin.lc -- solution for Part 2

I will run `stack build` on my side, so do not commit any files that `stack build` generates on your side.

## Part 1

(3 points)


#### Instructions

- Start from [Lab2-Lambda-Calculus/LambdaFun](https://github.com/alexhkurz/programming-languages-2021/tree/master/Lab2-Lambda-Calculus/LambdaFun).

- Build the interpreter (can take a while) and start the REPL as explained in the [README.md](https://github.com/alexhkurz/programming-languages-2021/blob/master/Lab2-Lambda-Calculus/LambdaFun/README.md).

- Study the grammar at [README.md](https://github.com/alexhkurz/programming-languages-2021/blob/master/Lab2-Lambda-Calculus/LambdaFun/README.md). The syntax is slightly different and there are new features, most prominently, sequential composition, while loops, assignment. (You do not need the new features for Part 1).

- Study the example programs in [test/examples.lc](https://github.com/alexhkurz/programming-languages-2021/blob/master/Lab2-Lambda-Calculus/LambdaFun/test/examples.lc).

- Run in a terminal

        stack exec lamfun

    That should open the REPL. Run

        λ :help

    to get an overview of the available commands. There are some built in functions. Run (and, as always, predict the expected results before hitting return/enter):

        λ head [2,3];;
        λ tail [2,3];;
        λ head [];;
        λ tail [];;

    Beware of the difference between `,` and `:` and throw in some parentheses if you get unexpected results: 

        λ [1,[2,3]];;
        λ 1:[2,3];;
        λ head [1]:[2,3];;
        λ (head [1]):[2,3];;
        λ [head [1],[2,3]];;

    Run 

        λ :load test/examples.lc 

    to load the examples. You can now call the defined functions as in

        λ plusone 4;;
        λ member 2 [3,2,3] ;;


- Experiment with your own examples. 

- Looking at the grammar and the example programs side by side, note the following.

    - `let` and `let rec` are now replaced by a list of definitions introduced by keywords `val` and `rec`. The keyword `in` is not needed anymore.

    - There is now a syntax for pattern matching using `case`.

    - The notation for lists changed, for example, `#` is now `[]`.

- **(3 points)**: Write the programs of Assignment 2.

- Let me know if there are any problems, questions, etc

## Part 2 

If you want to have a look already how we will use the new features of the language, read the discussion on the [Memory Model](https://hackmd.io/@alexhkurz/HkEBbgGnS) and study the examples in [linked-list.lc](https://github.com/alexhkurz/programming-languages-2021/blob/master/Lab2-Lambda-Calculus/LambdaFun/test/linked-list.lc). 

This assignment is about a round robin algorithm that allocates CPU time to tasks held in a cyclic list. 

The assignment provides the round robin algorithm, but asks you to implement the library functions needed to run it.

This example is taken from operating systems, see [Round-robin scheduling](https://en.wikipedia.org/wiki/Round-robin_scheduling) for general background.

#### Instructions

Each group submits their answer by sending me a link to a github repository via [email using this link](mailto:akurz@chapman.edu?subject=Assignment%203%20Part%202).

To assess your work, I will run the code in the file [round-robin.lc](https://github.com/alexhkurz/programming-languages-2021/blob/master/Lab2-Lambda-Calculus/LambdaFun/round-robin/round-robin.lc), so make sure that the functions you implement all run as expected. 

**You need to include the tests of [round-robin-test.lc](https://github.com/alexhkurz/programming-languages-2021/blob/master/Lab2-Lambda-Calculus/LambdaFun/round-robin/round-robin-test.lc) in round_robin.lc.** In particular, upon loading `round-robin.lc`, the function `testAll` should be executed.

#### Specification

The library will consist of the following functions.[^types] 

    newCList :: elem -> cList
    next :: cList -> cList
    get :: cList -> elem
    update :: elem, cList -> cList
    insert :: elem, cList -> cList
    delete :: cList -> cList

---

`newClist` takes an element and returns (the address of) a circular list of length 1 containing the element. The data structure looks like this, namely we use a pair `[e,a]`, where `e` is the element stored in the list and `a` is an address which points back at the pair    

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="./pictures/newCList.svg" width=105px>

---

`next` takes (the address of) a circular list `a` and returns (the address of) the list after the current position. (This is similar to the tail of linked lists but it doesn't need a case for the empty list and it doesn't reduce the length of the list.)

---

**Remark:** In the following I drop the "(the address of)".

---

`get` takes a circular list `a` and returns the element at the current position. (This is similar to the head of linked lists.)

---

`update` takes an element `e` and a circular list `a` and replaces the element at the current position of `a` with `e`.

---

`insert` takes an element `e` and a circular list `a` and inserts `e` after the current element. 

|            Before                   |               After                 |
|:-----------------------------------:|:-----------------------------------:|
|<img src="./pictures/insert1.svg" width=180px>|<img src="./pictures/insert2.svg" width=180px>|

(One could make the case for `insert` to insert before the entry point. What would be involved in doing this?)

---

`delete` takes a circular list `a` and "deletes" the element after the current element of `a` (if it exists) by reassigning the pointer of `a` pointing to the successor. In particular, deleting from the one-element cyclic list does not change the list. 

|            Before                   |               After                 |
|:-----------------------------------:|:-----------------------------------:|
|<img src="./pictures/delete1.svg" width=248px>|<img src="./pictures/delete2.svg" width=248px>|

### Testing

The explanations below refer to the file [round-robin-test.lc](https://github.com/alexhkurz/programming-languages-2021/blob/master/Lab2-Lambda-Calculus/LambdaFun/round-robin/round-robin-test.lc).

#### Test the individual functions

The file [round-robin-test.lc](https://github.com/alexhkurz/programming-languages-2021/blob/master/Lab2-Lambda-Calculus/LambdaFun/round-robin/round-robin-test.lc) contains tests such as `testInsert1`. But feel free to write your own.

After you implemented all the functions and they test as expected you can turn to the round robin algorithm described next.

#### Test by running the round robin algorithm

One of the standard applications of cyclic lists is to collect tasks and work on them one by one going around the list until all tasks are completed. The following tests are based on this idea.

We provided a function `testRRobin` that you should use to test your library functions. Here is an example:

```
λ testRRobin [addTask 6];;
[6]
λ testRRobin [addTask 6,tick,tick];;
[4]
```

Adding a task of "size" 6 and then waiting for two "clock cycles" leaves us with a task of size 4.

```
λ testRRobin [addTask 6,tick,tick,addTask 5];;
[5, 4]
```

Adding another task, puts it in front of the cyclic list. Then waiting for one more clock cycle reduces the size of the next task by one:

```
λ testRRobin [addTask 6,tick,tick,addTask 5,tick];;
[3, 5]
```

Note that waiting for one clock cycle moves the last task in the cyclic list to the front.

**Exercise:** Predict the results of
```
λ testRRobin [addTask 6,tick,tick,addTask 5,tick,tick,tick];;
```

**Explanation:** The testing uses the following functions provided with `round_robin.lc`.
- The function `roundRobin` takes a list `ts` of tasks such as `[addTask 6,tick,tick,addTask 5,tick]`, or just `[6,0,0,5,0]` for short, and takes a cyclic list `a` and simulates a round robin algorithm that inserts the tasks into the cyclic list and, for each `tick`, reduces the current task by 1 and goes on to the next task.
- The function `testRRobin` takes a list of tasks, calls `roundRobin` with this list of tasks on the cyclic list containing 0, and then converts the resulting cyclic list into an ordinary list.

[^types]: `LambdaFun` has no built-in types. The types are listed only for documentation purposes. Also note that the type `clist` represents references (pointers, addresses) to circular lists. These are not mathematical functions transforming inputs to outputs. Rather they work by their side-effects on memory.
