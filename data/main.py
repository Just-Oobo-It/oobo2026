# This script will generate a uniformized dataset composed of one map image per environmental factor

from PIL import Image
import importlib

MAP_WIDTH = 1920
MAP_HEIGHT = 1080

def draw_map(empty_map: Image, data_array: list[list[int]], map_name: str):
    pass

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
    "WATER"
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
    mod.get_data()
    pass

for x in modules:
    print(x)
    data = get_data(x["name"], x["module"])
    draw_map(data, x["name"])
