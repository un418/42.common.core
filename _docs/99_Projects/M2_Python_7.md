
> We will now use more advanced patterns: **abstract factories**, **extra capabilities** and **strategy patterns**.

- abstract factories
- extra capabilities
- strategy patterns

# Book Reading
## Effective Python
### Item 49: Prefer Polymorphism over `isinstance` checks

>Things to Remember
	✦ Instead of defining and instantiating classes, you can often simply use functions for simple interfaces between components in Python.
	✦ References to functions and methods in Python are first class meaning they can be used in expressions (like any other type).
	✦ The __call__ special method enables instances of a class to be called like plain Python functions and pass callable checks.
	✦ When you need a function to maintain state, consider defining a class that provides the \__call__

### Item 52: Use `@classmethod` Polymorphism to Construct Objects
>Things to Remember
	✦ Python only supports a single constructor per class: the __init__ method.
	✦ Use @classmethod to define alternative constructors for your classes.
	✦ Use class method polymorphism to provide generic ways to build and connect many concrete subclasses.

## Fluent Python

### Ch 13 -  Goose Typing

>**duck typing**
>ignoring an object’s actual type, focusing instead on ensuring that the object implements the  method names, signatures, and semantics required for its intended use.
>