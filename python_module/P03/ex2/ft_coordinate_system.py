#!/usr/bin/env python3

import math


def get_player_pos() -> tuple[float, float, float] | None:

    def split_coordinates(raw: str) -> list[str]:
        fields = raw.split(",")
        if len(fields) != 3:
            raise ValueError("Invalid syntax")
        return fields

    def parse_coordinates(point: list[str]) -> list[float]:
        parsed_point: list[float] = []
        for coordinate in point:
            try:
                parsed_point.append(float(coordinate))
            except ValueError as e:
                raise ValueError(f"Error on parameter '{coordinate}': {e}")
        return parsed_point

    while True:
        try:
            raw = input("Enter new coordinates as floats in format 'x,y,z': ")
            fields = split_coordinates(raw)
            coordinates = parse_coordinates(fields)
            x, y, z = coordinates
            return (x, y, z)
        except ValueError as e:
            print(e)
        except (KeyboardInterrupt, EOFError):
            print("\nExit: Program terminated by user")
            return None


def calculate_distance(p1: tuple[float, float, float],
                       p2: tuple[float, float, float]) -> float:
    return math.sqrt((p2[0]-p1[0])**2 +
                     (p2[1]-p1[1])**2 +
                     (p2[2]-p1[2])**2)


def main() -> None:
    print("=== Game Coordinate System ===")

    print("\nGet a first set of coordinates")
    pos1 = get_player_pos()
    if pos1 is None:
        return
    center = (0.0, 0.0, 0.0)
    dist_to_center = calculate_distance(center, pos1)
    print(f"Got a first tuple: {pos1}")
    print(f"It includes: X={pos1[0]}, Y={pos1[1]}, Z={pos1[2]}")
    print(f"Distance to center: {dist_to_center:.4f}")

    print("\nGet a second set of coordinates")
    pos2 = get_player_pos()
    if pos2 is None:
        return
    dist_btw_point = calculate_distance(pos1, pos2)
    print(f"Distance between the 2 sets of coordinates: {dist_btw_point:.4f}")


if __name__ == "__main__":
    main()
