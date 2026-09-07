# Wanikani_reviews_icon<img src="https://jfcameron.github.io/jfc-wanikani_reviews_icon/img/wanikani-32.png">

Linux system tray icon that notifies the user of new reviews on their wanikani account.

## Features:
- Icon graphic indicates: no reviews<img src="https://jfcameron.github.io/jfc-wanikani_reviews_icon/img/wanikani-32-no-reviews.png">, reviews available<img src="https://jfcameron.github.io/jfc-wanikani_reviews_icon/img/wanikani-32-reviews.png">, connection issue<img src="https://jfcameron.github.io/jfc-wanikani_reviews_icon/img/wanikani-32-no-connection.png">. 
- The # of reviews available is drawn onto the icon itself, so it is visible at a glance. Counts above 99 are shown as `99+` because that is what fits; hovering the cursor over the icon always gives the exact figure.
- When the # of reviews changes, a notification appears indicating the new count.
- Clicking the icon will load the wanikani website in your browser.

## Build

```
cmake --preset linux-gcc
cmake --build --preset linux-gcc
ctest --preset linux-gcc
```

Needs gtk3, an appindicator library (`libayatana-appindicator3-dev`, or Canonical's
`libappindicator3-dev`) and libcurl. `cmake --list-presets` shows the rest, including
`linux-clang-asan-ubsan`.

## Config

run the program to generate a config file in `~/.config/wanikani_reviews_icon/conf.json`, then enter your API key in that file.

You can also modify the config file to change what browser is opened when clicking the icon. By default it uses xdg-open to determine which browser to use, but you could change it to directly open "firefox" or whatever you like.

Once you've added your API key, configuration is complete.

## Install

```
cmake --install <build directory> --prefix ~/.local
```

This installs the program, a desktop entry and its icon.

