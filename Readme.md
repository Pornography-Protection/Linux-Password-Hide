+### Password-hide
+Access sudo password only on specific days and times

### How to build:
g++ gen_pass.cpp

'''
g++ key_gen.cpp -o key -O3
'''

# See:
https://reverseengineering.stackexchange.com/questions/47/can-i-create-an-object-file-using-gcc-that-cannot-be-reverse-engineered#comment4705_47
https://unix.stackexchange.com/questions/229802/convert-executable-back-to-c-source-code/229948#229948

# Timed:

### Password-hide
Access sudo password only on specific days and times

### Ignored days:
`cat /etc/password_days`

```
# Day waiting_time
20230101 60
20230713
20230714

20230715 30
20230716
20230717
    20240310 2
```

### Default waiting duration in minutes (360m = 6h):
`cat /etc/password_sleep_duration`

```
360
```

### Rules:
1. Empty lines and spaces will be ignored.
2. Dated lines, e.g. `20230101` will print password after x minutes (read from `/etc/password_sleep_duration`).
3. If the date is followed by a number, e.g. `20230101 60`, on that day you can print the password after waiting 60 minutes.

# TODO:
Inside [password_allowance_dates] add ranges of dates; add * for all days
