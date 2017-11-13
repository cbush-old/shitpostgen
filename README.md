# Shitpost Generator

A simple shitpost generator that pastes a random frame from Frinkiac to that "guys only want one thing" tweet.

## Dependencies

Magick++ (`$ brew install imagemagick`, `$ sudo pacman -S imagemagick`, etc.)
curl (the cli)

## Compiling the generator

`$ make`

## What ./make_image does

- Uses popen() to run shell commands (curl) because I was lazy
- Fetches a random frame from Frinkiac using curl
- Uses ImageMagick to paste the frame below the top image. The top image is stored in top_image_base64.cpp as base64-encoded string.
- Outputs the Image as base64-encoded jpeg.

## Web frontend layout

The frontend is a simple php script that executes `make_image` and puts the base64-encoded image data directly into the html.

I have the server laid out so that the http root is at a `public/` directory, but scripts are below the public directory. The frontend just contains symlinks to the scripts. So for example:

    public/
    public/shitpostgen/index.php -> ../../shitpostgen/index.php
    shitpostgen/
    shitpostgen/index.php
    shitpostgen/make_image
    shitpostgen/...<etc>...


