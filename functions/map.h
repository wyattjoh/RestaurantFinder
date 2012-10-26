#ifndef _MAP_H
#define _MAP_H


// These constants are for the 2048 by 2048 map.
int16_t map_width = 2048;
int16_t map_height = 2048;
int32_t map_north = 5361858;  
int32_t map_west = -11368652;
int32_t map_south = 5340953; 
int32_t map_east = -11333496;

// These functions convert between x/y map position and lat/lon 
// (and vice versa.)
int32_t x_to_lon(int16_t x) {
    return map(x, 0, map_width, map_west, map_east);
}

int32_t y_to_lat(int16_t y) {
    return map(y, 0, map_height, map_north, map_south);
}

int16_t lon_to_x(int32_t lon) {
    return map(lon, map_west, map_east, 0, map_width);
}

int16_t lat_to_y(int32_t lat) {
    return map(lat, map_north, map_south, 0, map_height);
}

#endif