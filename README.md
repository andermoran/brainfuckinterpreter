# Brainfuck interpreter for macOS

Installation

	- Place bfc in /usr/local/bin
	- OR
	- Compile with

```sh
gcc -o /usr/local/bin/bfc bfc.c
```
# Features

	- VERY basic debugger
	- Support for Brainfuck++ (a language I'm working on)

# Overview
First off I want to say I did not make this interpreter all by myself. To translate Brainfuck to C, I didn't reinvent the wheel instead I modified [Cory Burgett's code] to suit my needs.
What this interpreter does is translates the Brainfuck code to C which is then compiled using gcc and then executed. I have begun extending the Brainfuck language to give it a few needed features. I'll refer to it as Brainfuck++. So far I've added two extra characters which are * and %. These symbols deal with i/o and their use it shown in the source code (bfc.c). Also your Brainfuck code needs to be flawless as my debugger is in it's fetus stage (like only 2 weeks pregnant young) so it's not going to help too much. I've never done anything like this before so this is a learning experience for me.

# Contact
@andermorandev
andermorandeveloper@gmail.com


License
----

MIT

[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)


	 [cory burgett's code]: <https://gist.github.com/Ricket/939687>
