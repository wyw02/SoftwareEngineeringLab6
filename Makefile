CXX=g++
LDFLAGS = -g -L../gtest-1.7.0/lib/ 
LIBS = -lgtest -lgtest_main -lpthread
CXXFLAGS = -I../gtest-1.7.0/include
funcTest: funcTest.o
	$(CXX) -o funcTest funcTest.o $(LIBS)
funcTest.o: funcTest.cpp
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -c funcTest.cpp
clean:
	rm -rf *.o funcTest
