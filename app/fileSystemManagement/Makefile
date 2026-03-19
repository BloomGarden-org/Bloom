# Makefile for filesystemManagement

CXX := g++
CC := gcc
CXXFLAGS := -std=c++17 -Wall -I. -Igarden_tags -Iindex -Iutilz -Iseed -I "C:/mingw64/include"
CFLAGS := -std=c11 -Wall -I. -Igarden_tags -Iindex -Iutilz -Iseed -I "C:/mingw64/include"

BUILD := build

obj := \
  $(BUILD)/StaticPath.o \
  $(BUILD)/GardenTag.o \
  $(BUILD)/GardenTag_c_api.o \
  $(BUILD)/Index.o \
  $(BUILD)/Index_c_api.o \
  $(BUILD)/HashNode.o \
  $(BUILD)/HashTree.o \
  $(BUILD)/GardenProtocol.o \
  $(BUILD)/Hashing.o \
  $(BUILD)/HashVector.o 
all: $(BUILD) $(obj)

$(BUILD):
	mkdir -p $(BUILD)


#garden_tags
$(BUILD)/GardenTag.o: garden_tags/GardenTag.cpp garden_tags/GardenTag.h garden_tags/GardenTag_struct.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD)/GardenTag_c_api.o: garden_tags/GardenTag_c_api.c garden_tags/GardenTag_struct.h
	$(CC) $(CFLAGS) -c $< -o $@


#index
$(BUILD)/Index.o: index/Index.cpp index/Index.h index/Index_struct.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD)/Index_c_api.o: index/Index_c_api.c index/Index_struct.h
	$(CC) $(CFLAGS) -c $< -o $@


#seed
$(BUILD)/HashNode.o: seed/HashNode.cpp seed/HashNode.h seed/HashNode_struct.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD)/HashTree.o: seed/HashTree.cpp seed/HashTree.h garden_tags/GardenTag_struct.h
	$(CXX) $(CXXFLAGS) -c $< -o $@


#utilz
$(BUILD)/GardenProtocol.o: utilz/GardenProtocol/GardenProtocol.cpp utilz/GardenProtocol/GardenProtocol.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD)/StaticPath.o: utilz/PathManagement/StaticPath.cpp utilz/PathManagement/StaticPath.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD)/Hashing.o: utilz/processes/Hashing.cpp utilz/processes/Hashing.h utilz/processes/Hashing.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD)/HashVector.o: utilz/processes/HashVector.cpp utilz/processes/HashVector.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD)