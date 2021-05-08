# Toast

Convert source code TO AST.

## Getting Started

Build:

```bash
$ gcc src/main.c src/peppapeg.c -o toast
```

Copy "toast" into your $PATH.

## Usage

Command `toast` has two arguments: lang and path. 

* Argument lang supports json. 
* Argument path is the path to the source file to parse.

```bash
$ toast
usage: toast <lang> <path>
```

Example:

```bash
$ cat ./tests/json/y_number_simple_int.json
[123]

$ toast json ./tests/json/y_number_simple_int.json
[{"slice":[0,5],"type":"array","children":[{"slice":[1,4],"type":"number"}]}]
```

The output tree is in json format. It has fields `slice`, `type` and optional
`children`.

* Slice indicates the start and end position in the file that the
tree node covers.
* Type indicates which rule applies to the tree node.
* If the tree node is a non-terminal, then it will have a list of children nodes.

In the above example, type:array slice:[0,5] means the root tree node is an array
and covers the full text. It has one single child - type:number slice:[1,4], e.g. 123.
