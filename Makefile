CC := gcc
INC_DIRS := -I. -Itests
CFLAGS := -std=c99 $(INC_DIRS)
# -Werror
LIBRARY := libembroidery.so
TEST_EXEC := test_libembroidery
BUILD_DIR := build
LIB_FLAGS := -shared
LDFLAGS := -lm
LIB_SOURCES := \
	compound-file.c \
	compound-file-difat.c \
	compound-file-directory.c \
	compound-file-fat.c \
	compound-file-header.c \
	emb-arc.c \
	emb-circle.c \
	emb-color.c \
	emb-compress.c \
	emb-ellipse.c \
	emb-file.c \
	emb-flag.c \
	emb-format.c \
	emb-hash.c \
	emb-hoop.c \
	emb-layer.c \
	emb-line.c \
	emb-logging.c \
	emb-path.c \
	emb-pattern.c \
	emb-point.c \
	emb-polygon.c \
	emb-polyline.c \
	emb-reader-writer.c \
	emb-rect.c \
	emb-satin-line.c \
	emb-settings.c \
	emb-spline.c \
	emb-stitch.c \
	emb-thread.c \
	emb-time.c \
	emb-vector.c \
	format-100.c \
	format-10o.c \
	format-art.c \
	format-bmc.c \
	format-bro.c \
	format-cnd.c \
	format-col.c \
	format-csd.c \
	format-csv.c \
	format-dat.c \
	format-dem.c \
	format-dsb.c \
	format-dst.c \
	format-dsz.c \
	format-dxf.c \
	format-edr.c \
	format-emd.c \
	format-exp.c \
	format-exy.c \
	format-eys.c \
	format-fxy.c \
	format-gc.c \
	format-gnc.c \
	format-gt.c \
	format-hus.c \
	format-inb.c \
	format-inf.c \
	format-jef.c \
	format-ksm.c \
	format-max.c \
	format-mit.c \
	format-new.c \
	format-ofm.c \
	format-pcd.c \
	format-pcm.c \
	format-pcq.c \
	format-pcs.c \
	format-pec.c \
	format-pel.c \
	format-pem.c \
	format-pes.c \
	format-phb.c \
	format-phc.c \
	format-plt.c \
	format-rgb.c \
	format-sew.c \
	format-shv.c \
	format-sst.c \
	format-stx.c \
	format-svg.c \
	format-t01.c \
	format-t09.c \
	format-tap.c \
	format-thr.c \
	format-txt.c \
	format-u00.c \
	format-u01.c \
	format-vip.c \
	format-vp3.c \
	format-xxx.c \
	format-zsk.c \
	geom-arc.c \
	geom-circle.c \
	geom-line.c \
	hashtable.c \
	helpers-binary.c \
	helpers-misc.c \
	thread-color.c

#	emb-outline.c \

TEST_SOURCES := $(LIB_SOURCES) \
        tests/arc.c \
        tests/binary.c \
        tests/circle.c \
        tests/color.c \
        tests/compound.c \
        tests/compress.c \
        tests/ellipse.c \
        tests/flag.c \
        tests/formats.c \
        tests/hoop.c \
        tests/layer.c \
        tests/line.c \
        tests/logging.c \
        tests/main.c \
        tests/outline.c \
        tests/path.c \
        tests/pattern.c \
        tests/point.c \
        tests/polygon.c \
        tests/polyline.c \
        tests/rect.c \
        tests/satin-line.c \
        tests/spline.c \
        tests/stitch.c \
        tests/tests.c \
        tests/thread.c \
        tests/time.c \
        tests/vector.c

LIB_OBJECTS := $(LIB_SOURCES:%=$(BUILD_DIR)/%.o)
TEST_OBJECTS := $(TEST_SOURCES:%=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR)/$(LIBRARY) $(BUILD_DIR)/$(TEST_EXEC)

$(BUILD_DIR)/$(LIBRARY): $(LIB_OBJECTS)
	$(CC) $(LIB_FLAGS) $(LIB_OBJECTS) -o $@

$(BUILD_DIR)/$(TEST_EXEC): $(TEST_OBJECTS)
	$(CC) $(TEST_OBJECTS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

install:
	mv $(BUILD_DIR)/$(TEST_EXEC) /usr/bin
	mv $(BUILD_DIR)/$(LIBRARY) /usr/bin/x86_64-linux-gnu

check: $(BUILD_DIR)/$(TEST_EXEC)
	./$(BUILD_DIR)/$(TEST_EXEC)

.PHONY: clean
clean:
	rm -fr $(BUILD_DIR)

