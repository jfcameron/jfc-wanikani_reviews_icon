[![Build Status](https://travis-ci.org/jfcameron/jfc-wanikani_reviews_icon.svg?branch=master)](https://travis-ci.org/jfcameron/jfc-wanikani_reviews_icon)

## Wanikani_reviews_icon

Linux tray icon that notifies the user of new reviews on their wanikani account.

### Features:
- Icon graphic indicates: no reviews, reviews available, connection issue.
- Icon tooltip prints the # of reviews available.
- When the # of reviews changes, a notification appears indicating the new count.
- Clicking the icon will load the wanikani website in your browser.

### Build

refer to `.travis.yml` file

### Config

run the program to generate a config file in `~/.config/wanikani_reviews_icon/conf.json`, then enter your API key in that file.

You can also modify the config file to change what browser is opened when clicking the icon. By default it uses xdg-open to determine which browser to use, but you could change it to directly open "firefox" or whatever you like.

Once you've added your API key, configuration is complete. Set up the program to run in the background when you log into your computer.
