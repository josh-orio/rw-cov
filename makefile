BUILD_DIR := build
EXECUTABLE := $(BUILD_DIR)/rw-cov

.PHONY: all build clean run

all: build run

build:
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake .. && $(MAKE)

clean:
	@rm -rf $(BUILD_DIR)

run:
	@$(EXECUTABLE)
