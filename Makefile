SRC_DIR = src/
TEST_DIR = test/

all : src_files test_files
.PHONY : all

src_files:
	cd $(SRC_DIR) && $(MAKE)

test_files:
	cd $(TEST_DIR) && $(MAKE)

clean:
	cd $(SRC_DIR) && ($(MAKE) clean)
	cd $(TEST_DIR) && ($(MAKE) clean)