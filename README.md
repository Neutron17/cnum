# CNum

number playground

see numbers in different counting systems and manipulate them

## Usage

the commands are declared in
```funcs.c```
 as
```c
const char *commands[CMD_SZ] = { ... };
```
you can run the program with a number like
```
cnum <num>
```
 by default it will choose a random number

the print style can be changed with the
```
conf
```
 command (grid or single line)

There are 4 print styles:

 - decimal(10):
 ```
 dec
 ```
 or
 ```
 p/prnt/print/ptr
 ```
 (this is the default)
 - hexadecimal(16):
 ```
 hex
 ```
 - binary(2):
 ```
 bin
 ```
 (looks cool in grid mode)
 - octal(8):
 ```
 oct
 ```

You can

 - increment the number ```inc```
 - decrement the number ```dcr```
 - binary shift left(```shl```)/right(```shr```)
 - ```set``` or create a ```new``` number
 - edit the ```conf```igs
 - get a random number (```r```/```rand```/```rnd```/```random```)

## Installation

```
sudo make install
```

