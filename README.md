# Shortest Vector Problem Solver

I built this project as a C implementation of a Shortest Vector Problem (SVP) solver, using lattice basis reduction to make the problem more tractable. Given a square lattice basis from the command line, the program applies the LLL algorithm, searches the reduced basis for the shortest Euclidean norm, and writes the result to `result.txt`.

The project was completed as part of my Durham University summative work, but I have kept the repository focused on the engineering challenge: translating a mathematically dense problem into a working, testable systems program.

## What It Does

- Parses an arbitrary square lattice basis from command-line vector input.
- Validates bracket structure and vector dimensions before computation.
- Applies Gram-Schmidt orthogonalisation as part of LLL basis reduction.
- Uses the Lovasz condition and size reduction steps to produce a reduced basis.
- Calculates the shortest vector norm found in the reduced basis.
- Includes a small known-basis test harness for checking expected SVP behaviour.

## Why This Project Matters

I chose SVP because it sits at the intersection of algorithms, number theory, and real-world cryptography. Lattice problems are important because they underpin areas of modern cryptographic research, including post-quantum cryptography, but they are also difficult enough to force careful implementation decisions.

For me, this project mattered because it turned an abstract mathematical topic into something I could build, debug, and reason about in C. I had to understand not only the theory behind lattice reduction, but also how memory management, input validation, floating-point arithmetic, and modular program structure affect whether that theory survives contact with real code.

## Skills I Used

- **C programming:** dynamic memory allocation, pointer-based matrix structures, header/source separation, and file output.
- **Algorithm implementation:** Gram-Schmidt orthogonalisation, LLL reduction, Lovasz condition checks, vector projection, dot products, and Euclidean norms.
- **Command-line tooling:** parsing structured vector input and returning repeatable output through a generated result file.
- **Testing and validation:** building a separate known-case test executable to compare the implementation against an expected shortest vector norm.
- **Technical communication:** writing up the design, implementation decisions, and mathematical background in the accompanying report.

## What I Learnt

This project taught me that implementing mathematical algorithms is as much about careful engineering as it is about understanding the equations. Small mistakes in memory handling, vector indexing, or input assumptions can change the behaviour of the whole solver.

I also learnt how valuable it is to separate concerns in a C project. Splitting the implementation into input parsing, vector operations, LLL reduction, and testing made the code easier to reason about and gave me clearer places to debug when the output was wrong.

## Repository Structure

| File | Purpose |
| --- | --- |
| `main.c` | Main CLI flow: input parsing, SVP execution, and result output. |
| `command_line.c` / `command_line.h` | Helpers for validating and measuring command-line input. |
| `svp_structs.c` / `svp_structs.h` | Vector and matrix operations used by the solver. |
| `lll.c` / `lll.h` | Gram-Schmidt and LLL basis reduction implementation. |
| `known_svp_test.c` / `known_svp_test.h` | Known-basis test harness. |
| `Makefile` | Build targets for the solver and test executable. |
| `svp-solution-report.pdf` | Written report explaining the project background, approach, and solution. |

## Build And Run

Build the main executable:

```sh
make
```

Run the solver with a square lattice basis:

```sh
./runme "[1 0 0]" "[0 1 0]" "[0 0 1]"
```

The program writes the shortest Euclidean norm it finds to:

```txt
result.txt
```

Run the known-basis test:

```sh
make test
```

Clean generated executables:

```sh
make clean
```

## Notes

This implementation focuses on demonstrating the core SVP and LLL workflow clearly in C. LLL reduction is commonly used as a practical approximation step for lattice problems, so this project should be read as an educational implementation rather than a production cryptographic library.
