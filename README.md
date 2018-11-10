## Synopsis

MOD is a simple 16 bit, 32 bit (IA-32) disassembler library written in C, that can either work as a standalone disassembler or a part of a larger project (e.g. debugger).

It consists of two engines.
* Zombies ADE -- Advanced Disassembler Engine, cuts input to instructions and their parts
* Takes ADEs output and returns formatted strings in Intel syntax

## Usage Example

Initialize ADE

Load the code to disassemble into memory with `pindex` pointing to the start. Initialize ADE.

```
struct ade32_struct s = {4,4};  // prepare to disasm 32-bit code
int     length;                 // instruction length

length = ade32_disasm(pindex, &s);
```

If length is larger than 0, pass it to MOD and convert it to strings

```
instr_decode (&s, &name, index + length);
```

Where `name` is MODs internal structure for storing strings and `index + length` is the value of EIP register.

Then just print the content of the `name` structure.

File `sample.c` contains a simple instance of a disassembler.

## Motivation

A friend of mine was working on a debugger and needed a disassembler and I was bored at work … 

## Installation

You will need a `gcc` compiler and the `make` tool.

Then a simple `make` will do the job.

## Warning

Since it’s using zombies ADE, some antiviruses might detect your binaries as viruses or hacking tools.

The project has been written in 2004 and since then it has not been updated. There is no support for new instructions nor for IA-64.

Also the contact address in the `version.h` is outdated, please, contact me here, on github.

## Tests

The output od MOD was checked agains the Netwide Assembler `nasm`.

## Contributors

Zombie with his engine, Benny(29A) with bug fixes.

## License

Zombies ADE is freeware. My part is GNU GPL3.

