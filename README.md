# Shitpost Generator

A simple shitpost generator that pastes a random frame from Frinkiac to that "guys only want one thing" tweet.

![alt text](https://i.imgur.com/qWgxdkZ.jpg "Brilliant.")

See it in action [here](http://gash.ca/guys/).


## Motivation

Do I really need to explain? It's a shitpost generator.


## Dependencies

- Magick++ (`$ brew install imagemagick`, `$ sudo pacman -S imagemagick`, etc.)
- curl (the cli)

## Compiling the generator

`$ make`

## What ./make_image does

- Uses popen() to run shell commands (curl) because I was lazy
- Fetches a random frame from Frinkiac using curl
- Uses ImageMagick to paste the frame below the top image. The top image is stored in top_image_base64.cpp as base64-encoded string.
- The top image is resized a bit to match the bottom image. Frinkiac tends to have black vertical bars on both sides of the frame, hence the pixel offset when pasting the bottom image.
- Outputs the Image as base64-encoded jpeg.

## Replacing the top image

```$ echo "extern const char * const TOP_IMAGE_BASE64 = \"`base64 -w 0 < NEW_IMAGE`\";" > top_image_base64.cpp```

where `NEW_IMAGE` is the path to your new image in any format supported by ImageMagick.

Then recompile.


## Web frontend layout

The frontend is a simple php script that executes `make_image` and puts the base64-encoded image data directly into the html.

I have the server laid out so that the http root is at a `public/` directory, but scripts are below the public directory. The frontend just contains symlinks to the scripts. So for example:

    public/
    public/shitpostgen/index.php -> ../../shitpostgen/index.php
    shitpostgen/
    shitpostgen/index.php
    shitpostgen/make_image
    shitpostgen/...<etc>...


