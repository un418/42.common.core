#!/usr/bin/env python3

class Generator:
    ...

class Grid:
    def __init__(self, x_max:int, y_max: int) -> None:
        self.x_max = x
        self.y_max = y
        self.matrix = [][]
        self.border = False


class Case:
    def __init__(self, x:int, y: int) -> None:
        self.x = x
        self.y = y
        self.border = False
        self.logo = False
        self.solution = False # part of 

        #self.visited = False #for maze solving


