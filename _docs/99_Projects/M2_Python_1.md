## Class 

A class is a user-defined **template** for creating objects.
It bundles data and functions together, making it easier to manage and use them. 
When we create a new class, we define a new type of object. 
We can then **create multiple instances** of this object type.

- https://docs.python.org/3/tutorial/classes.html
- https://www.geeksforgeeks.org/python/python-classes-and-objects/
- https://www.geeksforgeeks.org/python/__init__-in-python/

## Object

An object is a specific **instance** of a class. 
It holds its own set of data (instance variables) and can invoke methods defined by its class. Multiple objects can be created from same class, each with its own unique attributes.

## Initiate Object with __init__()

[__init__()](https://www.geeksforgeeks.org/python/__init__-in-python/) method acts as a constructor and is automatically executed when an object is created. 
It is used to initialize the attributes of the object with the values provided at the time of object creation.

```python
class Dog:
    species = "Canine"  # Class attribute

    def __init__(self, name, age):
        self.name = name  # Instance attribute
        self.age = age  # Instance attribute

# Creating an object of the Dog class
dog1 = Dog("Buddy", 3)

print(dog1.name)  
print(dog1.species)

```

## Increment / Decrement in Python

- https://www.geeksforgeeks.org/python/g-fact-21-increment-and-decrement-operators-in-python/

```python
#increment
i+=1
i=i+1
#decrement
i-=1
i=i-1
```


# ToDo

- [ ] ex1 & ex2 : Try to use \_\_str\_\_() instead of show()
- [ ] Redo the [quizz](https://www.geeksforgeeks.org/python/python-classes-and-objects/) 