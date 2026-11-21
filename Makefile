CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude

TARGET = binary_search_tree

SRCDIR = src
INCDIR = include
BUILDDIR = build

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

ifeq ($(OS),Windows_NT)
    BIN = $(TARGET).exe
    MKDIR = if not exist "$(BUILDDIR)" mkdir "$(BUILDDIR)"
    RM = del /Q /F
    RMDIR = if exist "$(BUILDDIR)" rmdir /S /Q "$(BUILDDIR)"
    RUN_CMD = $(BIN)
else
    BIN = $(TARGET)
    MKDIR = mkdir -p $(BUILDDIR)
    RM = rm -f
    RMDIR = rm -rf $(BUILDDIR)
    RUN_CMD = ./$(BIN)
endif

all: $(BIN)

$(BUILDDIR):
	@$(MKDIR)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

run: all
	$(RUN_CMD)

clean:
ifeq ($(OS),Windows_NT)
	-@if exist "$(subst /,\,$(BUILDDIR))\*.o" del /Q /F "$(subst /,\,$(BUILDDIR))\*.o" 2>nul || ver >nul
	-@if exist "$(BIN)" del /Q /F "$(BIN)" 2>nul || ver >nul
	-@if exist "$(BUILDDIR)" rmdir /S /Q "$(BUILDDIR)" 2>nul || ver >nul
else
	@rm -rf $(BUILDDIR) $(BIN)
endif

.PHONY: all run clean
