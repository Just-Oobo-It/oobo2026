def get_data(MAP_WIDTH: int, MAP_HEIGHT: int) -> list[list[int]]:
    print(f"{__name__} loaded")
    res = list()
    for y in range(0, MAP_HEIGHT):
        res.append(list())
        for x in range(0, MAP_WIDTH):
            res[y].append((y + x) % 255)
    return res