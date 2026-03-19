CXX := g++
CXXFLAGS := -std=c++17 -Wall -I. -IFOS -I "C:/mingw64/include"

CC := gcc
CFLAGS := -std=c11 -Wall -I. -IFOS -I "C:/mingw64/include"

BUILD := build

obj := \
	$(BUILD)/Block.o \
	$(BUILD)/Diff.o \
	$(BUILD)/Juxtapose.o \
	$(BUILD)/TreeDiff.o 


all: $(BUILD) $(obj)


$(BUILD):
	mkdir -p $(BUILD)


$(BUILD)/Block.o: Block.cpp Block.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD)/Diff.o: Diff.cpp Diff.h Block.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD)/Juxtapose.o: Juxtapose.cpp Juxtapose.h Block.h Diff.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD)/TreeDiff.o: TreeDiff.cpp TreeDiff.h ../GardenNavigation/Navigation.h ../FOS/FOS_metadata.h Diff.h Juxtapose.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
