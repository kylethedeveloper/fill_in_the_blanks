# Fill in the Blanks

This is a C++ project for my Analysis of Algorithms class. It is aimed to build a system that fills the blanks, in a given statements file, using the input text.

**Boyer-Moore-Horspool** algorithm is used to search through text and find the searched pattern. *Running time* is calculated at each run.

>**NOTE THAT** this code **does not** give 100% correct results. It lacks some implementations , which I do not tend to fix. (Maybe someday if I am so so much bored.)

## Boyer-Moore-Horspool Algorithm :books:

A *brute-force* algorithm would search the given pattern for every character in the text as shown in below:

![](https://i.imgur.com/IwygU0f.png "Brute Force Algorithm")

This means, if the text has **N** characters and the pattern has **M** characters, running time of brute-force algorithm would be `O(N * M)`.

***

A Boyer-Moore-Horspool algorithm *(also known as bad character heuristic)* would search the
given pattern (word) from **right to left** instead of left to right. Also pattern is shifted many times while
searching which prevents unnecessary checks and increases the running time.

Let’s assume text has N characters and the pattern has M characters. If the bad character *(the
text symbol that causes a mismatch)* occurs somewhere in the pattern, pattern is shifted so it is
aligned with the symbol. If there are no bad characters and symbols does not match with the
pattern, pattern is shifted by M characters. An example can be seen in below:

![](https://i.imgur.com/iV2BZhY.png "Boyer-Moore-Horspool Algorithm")

## Usage

Code and the text files must be in the same directory in order them to be run.

Main text file must be a *one lined* text. Meaning that there can not be line breaks which my code does not detect. It is specifically designed for *one lined* texts. You can examine the  exemplary main text file which is used in the code [over here](./the_truman_show_script.txt). You can edit [this line](./main.cpp#L137) to put your own text file.

Each statement should have line breaks between them in the statements file. To indicate the blanks that needs to be filled, use **three underscore symbols** (`___`) . You can examine the  exemplary statement files which are used in the code: [statements](./statements.txt), [statements_2](./statements_2.txt), [statements_3](./statements_3.txt). You can edit [this line](./main.cpp#L144) to put your own statements file.

> When the blanks are at the end or at the beginning, it mostly can not find the result.
