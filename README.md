# lwa-hot-corners

Pretty simple hot corners implementation for X server written in modern C++.


# build-instructions
Open terminal in repository folder
```build-instructions
make
sudo make install
```

## Config file

When you run the program you need to pass path to your config file. Config file can contain information about command to execute for corners, update interval(in ms) and hold duration(in ms) before command is executed. 
If you do not want to have command for corner just skip line in config.

Example file:

```
top_left_command=geany
top_right_command=twm-session-logout
bottom_left_command=firefox
bottom_right_command=orage
disable_on_fullscreen=false
hold_duration=500
update_interval=200
```
