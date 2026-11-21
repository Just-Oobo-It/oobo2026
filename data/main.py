# This script will generate a uniformized dataset composed of one map image per environmental factor

from PIL import Image
import importlib
import os

MAP_WIDTH = 1920
MAP_HEIGHT = 1080

def draw_map(data_array: list[list[int]], map_name: str):
    print(f"Drawing map for '{map_name}'")
    img = Image.new(mode="L", size=(MAP_WIDTH, MAP_HEIGHT))
    for y in range(0, MAP_HEIGHT):
        for x in range(0, MAP_WIDTH):
            img.putpixel((x, y), data_array[y][x])
    try:
        os.mkdir("./assets")
    except Exception:
        pass
    img.save(f"./assets/{map_name}.png", "png")


fields = [
    "TEMPERATURE",
    "SUNSHINE",
    "HUMIDITY",
    "CLOUDS",
    "WIND_FORCE",
    "RAIN",
    "SOIL_FERTILITY",
    "FOREST",
    "SEISMIC_ACTIVITY",
    "WATER",
    "MOCKED",
]

# Load modules
modules = list()
for x in fields:
    try:
        modules.append({
            "name": x,
            "module": importlib.import_module(f"mods.{x}")
        })
    except ModuleNotFoundError:
        print(f"Module '{x}' can't be found in mods folder.")
    except Exception:
        print(f"Error : {Exception}")

def get_data(name: str, mod) -> list[list[int]]:    
    print(f"Getting data from {name}")
    return mod.get_data(MAP_WIDTH, MAP_HEIGHT)

for x in modules:
    data = get_data(x["name"], x["module"])
    if (data and len(data)):
        draw_map(data, x["name"])
