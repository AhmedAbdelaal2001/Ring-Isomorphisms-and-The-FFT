## Polynomials "are" Discrete Signals?
Rings are a very interesting class of algebraic structures in mathematics; a Ring can be thought of as a set of mathematical objects that can be added, subtracted, and
multiplied (in more formal terms from abstract algebra, the set should be an Abelian group under addition, and should satisfy commutativity and distributivity under
multiplication). It is trivial to observe that real polynomials and real discrete signals are both rings (the operations for signals are addition and __convolution__).
The elegant part in this argument is as follows: there is a bijective mapping from real polynomials to real discrete signals that completely preserves the addition
and multiplication (convolution) operations, more formally known as a Ring Isomorphism. In simpler terms, polynomials and signals exactly identical in structure from
a purely algebraic perspective, despite how different they are in substance, and convolution between signals can be accurately mapped to polynomial multiplication!

## Fast Polynomial Multiplication Using The FFT
Given that we can draw an isomorphism between discrete signals and real polynomials, the Fast Fourier Transform (radix-2) was used in this repository to speed up
polynomial multiplication by viewing it as a convolution of discrete signals, accomplishing multiplication in O(log(n)) time. Potential future applications are in public
key cryptosystems involving ideal lattices.
