# dbj-dll&trade;

&copy by dbj@dbj.org

## DBJ DLL Component

Simple (kind-of-a) Component architecture, design and implementation.  Using the [DLL concept and mechanism as implemented in Windows](https://en.wikipedia.org/wiki/Dynamic-link_library).

> Linux shared objects are on the roadmap.

## But, what is the component?

- one component is one executable
- one component has one interface
- interface is a collection of functions and types 

All that seems very OO. That is because it is. That is the foundation of OO.
Concept of "information hiding". Architected, designed and implemented as "Encapsulation and Decoupling". Without the unfortunate cruft piled up through history of misunderstanding the OO.

[That link above](https://en.wikipedia.org/wiki/Dynamic-link_library), leads to a good text on DLL's and concept and benefits included. Please read it.

## Operational requirements

- Windows is the OS
- C is the language used
- One C struct is the interface on one DBJ DLL Component
- function pointers on that struct are interface functions.

## Wot? Is that all?!

Basically that is all. Use it ubiquitously and the benefits wil be clear. You will have nicely isolated, ABI safe, extremely simple components. Without the modern C++, COM, IDL and all that paraphernalia of development horror reality.

Especially if you stick to [standard C](http://www.open-std.org/jtc1/sc22/wg14/).

There are few pretty useful DBJ DLL Components elsewhere, to which link will be inserted here. 

Nothing is better that seeing the code.

Thus three simple headers in here are extensively documented. 

