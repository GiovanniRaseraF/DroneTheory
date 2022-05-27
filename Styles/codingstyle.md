[Coding Style](https://github.com/multiwii/baseflight/wiki/CodingStyle)
# Guidelines

 1. **working code**
 2. **proper formatting**
 3. **useful**

Code not following these guidelines will not be accepted into the project no matter how great or useful it might appear to be. Sloppy and inconsistent formatting and indentation will not be tolerated.

# Coding style

Baseflight project would like to maintain code quality and readability, and thus have set strict rules on code formatting, indentation, variable naming, etc.

## Indentation and formatting

baseflight uses [K&R indent style](http://en.wikipedia.org/wiki/Indent_style#K.26R_style) with **4 space indent, NO hard tabs** (all tabs are replaced by spaces). As an example, output of "indent -kr -nut -l400" would format the code acceptable for this project. Eclipse can be used to re-format the code in the event of "indent" not being available.

You can also run your code through [astyle](http://astyle.sourceforge.net/) with the following options: 
```bash
    astyle --style=kr --indent=spaces=4 --pad-header --pad-oper --align-pointer=name --align-reference=none --convert-tabs --indent-switches  --min-conditional-indent=1 --preserve-date --suffix=none --mode=c src/*.*
```
 * Spaces between operators/parameters, but not between ()'s: 
```c
             int x = y * 2;
             call(a, 10);
             int foo(float *bar);
             y = 2 * (x - z);
```
If your code looks like
```c
             for(i=0;i<10;i++)crap(i);
```
it will be deleted immediately.

* New line will be inserted between variable declarations at top of scope and code following it:
```c
        void func(void)
        {
                int foo;
                
                for (foo = 0; ...
        }
```
* Curly brace on same line for everything except function definitions
* if/else/while/etc blocks all break to new line after condition. stuff like 
```c
             if (foo) bar(); 
```
will not be tolerated. sticking all code on one line doesn't make it faster.
* if/else blocks which only contain a single line body must not use opening/closing braces:
```c
             if (foo)
                 bar();
             else {
                 baz();
                 beep();
             }
```
* The above also applies to for/while loops:

```c
             for (i = 0; i < 10; i++)
                 printf("lol\n");
             while (i--)
                 blink();
             while (1) {
                 loop();
                 calculate();
             }
```
* inline commenting should use C++ "//" comment notation. Space must be inserted between "//" and comment text:
```c
             // this is a valid comment
```
Original C-style comments "/* */" are to be used when comment spans several lines. If possible, and when commenting on a block of code (example struct members), all the comment text must be left-aligned at some tab-multiple distance away from longest variable name.
* blank argument list in function definition or declaration is not allowed.
```c
             void foo(void);
```
is correct,
```c
             void foo();
```
is not. Obviously, it's ok when function is called: foo();
* There is space between type and pointer symbol but not after it: 
```c
             void foo(int *bar)
             {
                 int baz = *bar;
             }
```
Likewise, there is space between addressof operator but not after it:
```c
             int bar(12, &foo);
             void *bar = &foo;
```
* Typecasting - no space between typecast and variable:
```c
             (int)var;
```
## Variables

Generally, **lowerCamelCase is preferred** for function names, arguments, etc. For configuration variables that are user accessible via CLI or similar, all_lowercase with underscore is permitted: int gps_index;

structs are named with lowerCamelCase_t, adding the "_t" suffix. Named enums are generally UpperCamelCase without suffix.

Avoid global variables. Use structs to communicate between modules or threads.

While baseflight is built as C99, declaring variables in the middle of scope just because of laziness is not allowed. Do not do this:
```c
    void foo(void)
    {
        int bar;
        somecode();
        morecode();
        ...;
        int baz;
        code(&baz);
    }
```
## File naming

Device drivers must have drv_ prefix and avoid importing global variables from the rest of the project. pass all required data to a driver via driver-specific init struct.

File names should be short and to the point. ideally, filename would be a single word or two words separated by underscore, all in lower_case. Examples: 

     data.c 
     much_gps.c
Filenames must not be longer than 10 characters (not counting drv_ prefix, if applicable).


# Code quality
Crap code will not be tolerated. it has to work good AND look good. hacks, direct copypaste from other projects, large blocks of uncommented code are not allowed.

##Compiler options
Code which depends on a particular compiler/OS, will not be accepted.

## Unintentional use of doubles instead of floats

In general, using double precision floats is not necessary for this project.
Therefore, avoid implicit double conversions and only use float-argument functions. Check .map file to make sure no conversions sneak in, and use -Wdouble-promotion warning with gcc (armcc already has this warning enabled). Use sinf(), cosf(), etc instead of sin(), cos().
Constants should be defined as :
```c
     1.0f
     3.1415926f
```
With "**f**" suffix, otherwise double conversion might occur.