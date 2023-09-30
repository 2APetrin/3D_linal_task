DEBUG_FLAGS = -std=c++20 -D DEBUG -O0 -g3 -Wall -Wextra -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr -lgtest -lgmock -pthread

TRIAG_FILES   = geometry/point/point.cpp geometry/vector/vector.cpp geometry/line/line.cpp geometry/plane/plane.cpp geometry/segment/segment.cpp geometry/triangle/triangle.cpp include/double_operations/double_operations.cpp
TRIAG_HEADERS = geometry/point/point.hpp geometry/vector/vector.hpp geometry/line/line.hpp geometry/plane/plane.hpp geometry/segment/segment.hpp geometry/triangle/triangle.hpp include/double_operations/double_operations.hpp include/custom_assert.hpp

main: $(TRIAG_FILES) $(TRIAG_HEADERS) main.cpp
	g++ $(DEBUG_FLAGS) $(TRIAG_FILES) main.cpp

tests: $(TRIAG_FILES) $(TRIAG_HEADERS) tests/test.cpp
	g++ $(DEBUG_FLAGS) $(TRIAG_FILES) tests/test.cpp -o test -lgtest -lgmock -pthread