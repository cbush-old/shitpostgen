#include <unistd.h>
#include <array>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <random>
#include <sstream>

#include "json.h"

#include <Magick++.h>

using namespace Magick;

// top_image_base64.cpp
extern const char * const TOP_IMAGE_BASE64;

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> d;

    Blob top_image_blob;
    top_image_blob.base64(TOP_IMAGE_BASE64);
    Image result(top_image_blob);

    result.fillColor(Color("white"));
    result.font("./Arial Bold.ttf");
    result.fontPointsize(32);
    result.fontWeight(900);
    result.strokeColor(Color("black"));
    result.strokeWidth(1);
    result.textKerning(-1);
    result.textGravity(NorthGravity);

    std::stringstream ss;
    ss << d(gen);
    auto n = ss.str();
    result.draw(DrawableText(0, result.rows() / 2 - 60, "SIMPSON, YOU'VE GOT A " + n));

    result.fontPointsize(72);
    result.strokeWidth(2);
    result.draw(DrawableText(90, result.rows() / 2 + 180, n));

    Blob blob;
    result.magick("JPEG");
    result.write(&blob);

    std::cout << blob.base64();
    return 0;
}

