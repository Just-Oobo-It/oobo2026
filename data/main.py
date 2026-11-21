# This script will generate a uniformized dataset composed of one map image per environmental factor

from PIL import Image

MAP_WIDTH = 1920
MAP_HEIGHT = 1080

def create_empty_map():
    pass

def draw_map(empty_map: Image, data_array: int[MAP_HEIGHT][MAP_WIDTH], map_name: str):
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

modules = dict()
for x in fields:
    modules[x] = __import__(f"mods/{x}.py")

def get_data(name: str, mod: function) -> int[MAP_HEIGHT][MAP_WIDTH]:    
    print(f"Getting data from {name}")
    mod.get_data()
    pass

for k, m in modules:
    data = get_data(k, m)
    draw_map(create_empty_map(), data, "temperature")
