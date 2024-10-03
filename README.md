# C-Like-Compiler

C-like compiler using Flex scanner, Bison parser, and C++ for generating and pretty-printing the Abstract Syntax Tree (AST). Language is based on the unambiguous grammar shown below.

## Instructions to Run (Linux)
1.	From the root directory, execute the makefile by running this command: `make`
2.	Now, you should have an `ast` file
2.	Run test programs like so: `./ast test-max`

## Unambiguous Grammar

### Grammar Rules

- `<application>` → `<declarationList>`
- `<declarationList>` → `<declaration><declarationList>` | `<declaration>`
- `<declaration>` → `<varDeclaration>` | `<funcDeclaration>`

#### Variable Declarations:
- `<varDeclaration>` → `<type> id;` | `<type> id <arrayDim>;`
- `<arrayDim>` → `[integerConst]` | `[integerConst] <arrayDim>`
- `<assign>` → `id = <exp>;` | `id [integerConst] = <exp>;`

#### Expressions:
- `<exp>` → `<mathExp>` | `<stringExp>` | `<booleanExp>`
- `<mathExp>` → `<mathExp> <addSub> <mult>` | `<mult>`
- `<mult>` → `<mult> <multDivMod> <prim>` | `<prim>`
- `<prim>` → `(<mathExp>)` | `id` | `constant`
- `<stringExp>` → `stringLiteral` | `id + <stringExp>` | `id`

#### Boolean Expressions:
- `<booleanExp>` → `<booleanExp> || <booleanAnd>` | `<booleanAnd>`
- `<booleanAnd>` → `<booleanAnd> && <booleanNegation>` | `<booleanNegation>`
- `<booleanNegation>` → `!<booleanNegation>` | `<booleanRelational>`
- `<booleanRelational>` → `<mathExp> <relationalOperator> <mathExp>` | `<stringExp> <relationalOperator> <stringExp>`
- `<relationalOperator>` → `<` | `>` | `≤` | `≥` | `==` | `!=`

#### Function Declarations:
- `<funcDeclaration>` → `<type> id (<parameterList>) { <stmtList> }`
- `<parameterList>` → `<parameter>, <parameterList>` | `<parameter>`
- `<parameter>` → `<type> id` | `<type>[] id` | `ε`
- `<invokeFunction>` → `id(<argsList>);`
- `<argsList>` → `<exp>, <argsList>` | `<exp>` | `ε`

#### Statements:
- `<stmtList>` → `<stmt><stmtList>` | `<stmt>`
- `<stmt>` → `<varDeclaration>` | `<assign>` | `<returnStmt>` | `<conditional>` | `<whileLoop>` | `<doWhileLoop>` | `<invokeFunction>`
- `<returnStmt>` → `return <exp>;`
- `<conditional>` → `if <booleanExp> then <balanced> else <stmt>` | `if <booleanExp> then <stmt>`
- `<balanced>` → `<assign>` | `if <booleanExp> then <balanced> else <balanced>`
- `<whileLoop>` → `while <booleanExp> <stmtList>`
- `<doWhileLoop>` → `do <stmtList> while <booleanExp>`

#### Types and Operators:
- `<type>` → `int` | `float` | `char` | `boolean` | `string`
- `<addSub>` → `+` | `-`
- `<multDivMod>` → `*` | `÷` | `%`
