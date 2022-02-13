# dbj-dll&trade;

&copy; by dbj@dbj.org

## DBJ DLL Component

Simple (kind-of-a) Component architecture, design and implementation.  Using the [DLL concept and mechanism as implemented in Windows](https://en.wikipedia.org/wiki/Dynamic-link_library).

> Linux shared objects are on the roadmap.

Component is a software building block.

## But, what is the component?

- one component is one executable
- one component has one interface
- interface is a collection of functions and types 

All that seems very OO. That is because it is. Those are the foundations of OO.
Concept of "information hiding". Architected, designed and implemented following the "Encapsulation and Decoupling" principle. Without the unfortunate cruft piled up through history of misunderstanding the OO.

[That link above](https://en.wikipedia.org/wiki/Dynamic-link_library), leads to a good text on DLL's and concept and benefits included. Please read it.

## Operational requirements

- Windows is the OS
- C is the language used
- One C struct is the interface on one DBJ DLL Component
- function pointers on that struct are interface functions.

## Wot? Is that all?!

Basically that is all that matters. Use DBJ DLL Components ubiquitously and the benefits will be clear. You will develop and deliver resilient applications made of nicely isolated, ABI safe, extremely simple components. Without the modern C++, COM, IDL and all that paraphernalia from the development horror basement. Especially if you stick to [standard C](http://www.open-std.org/jtc1/sc22/wg14/).

## Nothing is better that seeing the code.

Simple headers in here are extensively documented. Two are important:

- `dbj-dllimp.h`
  - to be used inside the dbj dll component implementation
- `dbj-dlluser.h`
  - to be used by dbj dll component client code

Simple and effective usage examples are coming soon.

There are few pretty useful DBJ DLL Components elsewhere, to which links will be inserted here. 

---------------------------------------------------------------------  

[![dbj();](https://dbj.org/wp-content/uploads/2015/12/cropped-dbj-icon-e1486129719897.jpg)](http://www.dbj.org "dbj")  
