#!/usr/bin/env python3

class Generator:
    ...


class Matrix:
    def __init__(self, width: int, height: int) -> None:
        self.width: int = width
        self.height: int = height
        self.matrix: list[list[Cell]] = [
            [None for x in range(width)] for y in range(height)]

    def gen_constraint(self) -> None:
        """Add metadata to cell in the matrix before generating the wall"""
        for y in range(self.height):
            for x in range(self.width):
                if (x == 0 or
                        y == 0 or
                        x == self.width - 1 or
                        y == self.height - 1):
                    self.matrix[y][x].border = True

    def print_matrix(self) -> None:
        ...


class Cell:
    def __init__(self, x: int, y: int, border: bool = False) -> None:
        self.x = x
        self.y = y
        self.border = border
        self.logo = False
        self.wall: int | None = None

        # self.solution = False # part of maze solution
        # self.visited = False #for maze solving


if __name__ == "__main__":
    pass
