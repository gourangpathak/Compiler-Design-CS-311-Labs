Dont put spaces in the regular expressions wantedly..

When defining the Macros in `.l` file.

```
letter_or_digit {digit}|{letter}|[_]      --> Correct
letter_or_digit {digit} | {letter} | [_]  --> Wrong  
```

- The relative ordering of rules matters.