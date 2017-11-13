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

std::string command_line(const char *command)
{
    FILE *pipe = popen(command, "r");
    assert(pipe);

    char buffer[1024];
    std::string result;

    while (auto count = std::fread(buffer, 1, sizeof(buffer), pipe))
    {
        result.insert(result.end(), buffer, buffer + count);
    }

    pclose(pipe);
    return result;
}

std::string command_line(const std::string &command)
{
    return command_line(command.c_str());
}

const std::string &get_host();

std::string fetch_frinkiac_random_json()
{
    return command_line(std::string("curl -s ") + get_host() + "/api/random");
}

struct Frame
{
    explicit Frame(const std::string &frame_json)
    {
        auto value = json::parse(frame_json).get_object();
        const auto &frame = value.at("Frame").get_object();
        const auto &episode = frame.at("Episode").get_string();
        const uint64_t timestamp = frame.at("Timestamp").get_number();
        std::stringstream ss;
        ss << get_host() << "/img/" << episode << '/' << timestamp << ".jpg";
        url = std::move(ss).str();
        ss = std::stringstream();
        ss << episode << '-' << timestamp;
        id = std::move(ss).str();
    }

    std::string id;
    std::string url;
};

Image download_and_open_image(Frame const &frame)
{
    auto data = command_line("curl -s " + frame.url);
    return Image(Blob(data.data(), data.size()));
}

// top_image_base64.cpp
extern const char * const TOP_IMAGE_BASE64;

int main()
{
    Blob top_image_blob;
    top_image_blob.base64(TOP_IMAGE_BASE64);
    Image top_image(top_image_blob);

    auto frame_json = fetch_frinkiac_random_json();
    assert(frame_json.size());

    Frame frame(frame_json);

    auto bottom_image = download_and_open_image(frame);

    Geometry new_size(bottom_image.columns(), 0);
    top_image.resize(new_size);

    new_size = Geometry(bottom_image.columns() + 20, 0);
    bottom_image.resize(new_size);

    Image result(Geometry(
        top_image.columns(),
        top_image.rows() + bottom_image.rows()
    ), "white");

    result.composite(top_image, 0, 0, OverCompositeOp);
    result.composite(bottom_image, -10, top_image.rows(), OverCompositeOp);

    new_size = Geometry(0, 800);
    result.resize(new_size);

    Blob blob;
    result.magick("JPEG");
    result.write(&blob);

    std::cout << blob.base64();
    return 0;
}

const std::string &get_host()
{
    static const std::string HOST = []
    {
        const std::array<std::string, 3> hosts
        {{
            "https://frinkiac.com",
            "https://morbotron.com",
            "https://masterofallscience.com",
        }};
        std::random_device rd;
        std::mt19937 gen(rd());
        std::discrete_distribution<> d({100, 1, 1});
        return hosts[d(gen)];
    }();
    return HOST;
}
