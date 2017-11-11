all:
	clang++ \
		-std=c++14 \
		-Wall -Werror -Wunused -Wno-gnu-case-range \
		`Magick++-config --cppflags --cxxflags --ldflags --libs` \
		make_image.cpp \
		json.cpp \
		-o make_image
