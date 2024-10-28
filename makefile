# gui3
LIB = libgui3.a
SRCS = button.cc edit.cc GUI.cc image.cc list.cc scroll.cc text.cc window.cc mesh.cc gameobject.cc
HEADERS = button.h context.h edit.h GUI.h image.h list.h mytypes.h scroll.h text.h window.h mesh.h gameobject.h gameobjects.h
OBJS = $(addprefix obj/,$(SRCS:.cc=.o))
CC = g++
CFLAGS = -g `pkg-config --cflags gtk+-3.0` -std=c++11
LDFLAGS = `pkg-config --libs gtk+-3.0` # -fsanitize=leak

# examples
EXAMPLES = browse calc clock draw myprog quad view test asteroids

ASTEROIDS_SRCS = digit7.cc asteroids.cc mesh.cc gameobject.cc
ASTEROIDS_OBJS = $(addprefix obj/,$(ASTEROIDS_SRCS:.cc=.o))

BROWSE_SRCS = browse.cc
BROWSE_OBJS = $(addprefix obj/,$(BROWSE_SRCS:.cc=.o))

CALC_SRCS = calc.cc
CALC_OBJS = $(addprefix obj/,$(CALC_SRCS:.cc=.o))

CLOCK_SRCS = digit7.cc clock.cc
CLOCK_OBJS = $(addprefix obj/,$(CLOCK_SRCS:.cc=.o))

DRAW_SRCS = draw.cc
DRAW_OBJS = $(addprefix obj/,$(DRAW_SRCS:.cc=.o))

MYPROG_SRCS = myprog.cc
MYPROG_OBJS = $(addprefix obj/,$(MYPROG_SRCS:.cc=.o))

QUAD_SRCS = quad.cc
QUAD_OBJS = $(addprefix obj/,$(QUAD_SRCS:.cc=.o))

VIEW_SRCS = view.cc
VIEW_OBJS = $(addprefix obj/,$(VIEW_SRCS:.cc=.o))

TEST_SRCS = test.cc
TEST_OBJS = $(addprefix obj/,$(TEST_SRCS:.cc=.o))

all: $(LIB) $(EXAMPLES)

$(LIB): $(OBJS)
	ar -r -s $(LIB) $(OBJS)

obj/%.o: source/%.cc $(addprefix source/,$(HEADERS))
	$(CC) $(CFLAGS) -c $< -o $@

asteroids: $(LIB) $(ASTEROIDS_OBJS)
	$(CC) $(ASTEROIDS_OBJS) $(LIB) -o asteroids $(LDFLAGS)

browse: $(LIB) $(BROWSE_OBJS)
	$(CC) $(BROWSE_OBJS) $(LIB) -o browse $(LDFLAGS)

calc: $(LIB) $(CALC_OBJS)
	$(CC) $(CALC_OBJS) $(LIB) -o calc $(LDFLAGS)

$(CLOCK_OBJS): source/digit7.h
clock: $(LIB) $(CLOCK_OBJS)
	$(CC) $(CLOCK_OBJS) $(LIB) -o clock $(LDFLAGS)

draw: $(LIB) $(DRAW_OBJS)
	$(CC) $(DRAW_OBJS) $(LIB) -o draw $(LDFLAGS)

$(MYPROG_OBJS): source/myprog.h
myprog: $(LIB) $(MYPROG_OBJS)
	$(CC) $(MYPROG_OBJS) $(LIB) -o myprog $(LDFLAGS)

quad: $(LIB) $(QUAD_OBJS)
	$(CC) $(QUAD_OBJS) $(LIB) -o quad  $(LDFLAGS)

view: $(LIB) $(VIEW_OBJS)
	$(CC) $(VIEW_OBJS) $(LIB) -o view $(LDFLAGS)

test: $(LIB) $(TEST_OBJS)
	$(CC) $(TEST_OBJS) $(LIB) -o test $(LDFLAGS)

clean:
	rm $(LIB) $(EXAMPLES) obj/*
