# lwa-hot-corners

Pretty simple hot corners implementation for X server written in modern C++.

## Config file

When you run the program you need to pass path to your config file. Config file can contain information about command to execute for corners and hold duration(in ms) before command is executed. 


Example file:

```
top_left_command=geany
top_right_command=twm-session-logout
bottom_left_command=firefox
bottom_right_command=orage
hold_duration=500
```