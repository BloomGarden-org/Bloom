# Paths
root := ./app
build := $(root)/build
bin := main.exe
lib := libgarden.a

# Compiler
CXX := g++
CXXFLAGS := -Wall -std=c++17 "-IC:/mingw64/include" 
LDFLAGS := -L"C:/mingw64/lib/MT" -lssl -lcrypto 

CC := gcc
CFLAGS := -Wall -std=c11

obj_POD := FOS_metadata.o FOS_metadata_c_api.o
obj_GardenManipulation := FileWriter.o FileBuilder.o Navigation.o
obj_paths := GardenPath.o

obj_filesystem := \
	$(root)/fileSystemManagement/build/Index.o \
	$(root)/fileSystemManagement/build/GardenTag.o \
	$(root)/fileSystemManagement/build/GardenProtocol.o \
	$(root)/fileSystemManagement/build/HashTree.o \
	$(root)/fileSystemManagement/build/HashNode.o \
	$(root)/fileSystemManagement/build/Index_c_api.o \
	$(root)/fileSystemManagement/build/GardenTag_c_api.o \
	$(root)/fileSystemManagement/build/Hashing.o \
	$(root)/fileSystemManagement/build/HashVector.o \
	$(root)/fileSystemManagement/build/StaticPath.o

obj_diff := \
	$(root)/DiffEngine/build/Block.o \
	$(root)/DiffEngine/build/Diff.o \
	$(root)/DiffEngine/build/Juxtapose.o \
	$(root)/DiffEngine/build/TreeDiff.o 

# Submodules
SUBDIRS := app/fileSystemManagement app/DiffEngine

.PHONY: all $(SUBDIRS) clean

all: $(SUBDIRS) $(lib) $(bin)

$(SUBDIRS):
	$(MAKE) -C $@

# Build the library
$(lib): $(obj_filesystem) $(obj_diff) $(addprefix $(build)/, $(obj_GardenManipulation) $(obj_paths) $(obj_POD))
	ar rcs $@ $^

# Build the final executable
$(bin): $(addprefix $(build)/, main.o) $(lib)
	@echo Detected OS: $(detected_OS)
	$(CXX) $^ -o $@ $(LDFLAGS)


# TODO: delete if not used
#	$(build)/filebuilder/FileBuilder.o  
$(build)/FOS_metadata.o: $(root)/FOS/FOS_metadata.cpp $(root)/FOS/FOS_metadata.h $(root)/FOS/FOS_metadata_struct.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(build)/FOS_metadata_c_api.o: $(root)/FOS/FOS_metadata_c_api.c $(root)/FOS/FOS_metadata_struct.h
	$(CC) $(CFLAGS) -c $< -o $@
	
##===============================================================================
##			                   GardenManipulation
##===============================================================================
$(build)/FileWriter.o: $(root)/fileSystemWriter/FileWriter.cpp
	@echo "making $@..."
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
$(build)/FileBuilder.o: $(root)/fileSystemBuilder/fileBuilder.cpp
	@echo "making $@..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(build)/Navigation.o: $(root)/GardenNavigation/Navigation.cpp
	@echo "making $@..."
	$(CXX) $(CXXFLAGS) -c $< -o $@


##===============================================================================
##			                   path
##===============================================================================
$(build)/GardenPath.o: $(root)/paths/GardenPath.cpp
	@echo "making $@..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(build)/main.o: $(root)/main.cpp
	@echo "Compiling main.cpp..."
	$(CXX) $(CXXFLAGS) -c $< -o $@


run: all
	./main.exe
# Clean build directory
