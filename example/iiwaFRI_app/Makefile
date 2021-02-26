BASE_DIR	= ../..
include $(BASE_DIR)/build/GNUMake/paths.mak
include $(BASE_DIR)/build/GNUMake/$(TOOLS_MAK)

SOURCES 		= main.cpp appClient.cpp
TARGET 		= main

CXXFLAGS 	+=
LDFLAGS 		+= -lpthread -lboost_thread -lboost_system $(LIB_DIR)/libFRIClient.a 

include $(BASE_DIR)/build/GNUMake/rules_examples.mak
