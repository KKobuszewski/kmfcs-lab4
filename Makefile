
CXX       = g++ -pipe -std=c++14
CXX_FLAGS = -mtune=native -march=native -m64 -O3 -fPIC -fopenmp
CXX_INC   = -I/usr/local/include -I.


all: graphene

graphene:
	$(CXX) -o graphene.exe graphene.cpp $(CXX_FLAGS) $(CXX_INC)



clean:
	@rm *.exe