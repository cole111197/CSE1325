CXXFLAGS += --std=c++17

all: train

debug: CXXFLAGS += -g
debug: train

rebuild: clean train

train: main.o train.o stock.o coach.o locomotive.o autocoach.o cattlecar.o boxcar.o
	$(CXX) $(CXXFLAGS) -o train main.o train.o stock.o coach.o locomotive.o autocoach.o cattlecar.o boxcar.o

main.o: main.cpp *.h
	$(CXX) $(CXXFLAGS) -c main.cpp
train.o: train.cpp *.h
	$(CXX) $(CXXFLAGS) -c train.cpp
stock.o: stock.cpp *.h
	$(CXX) $(CXXFLAGS) -c stock.cpp
coach.o: coach.cpp *.h
	$(CXX) $(CXXFLAGS) -c coach.cpp
locomotive.o: locomotive.cpp *.h
	$(CXX) $(CXXFLAGS) -c locomotive.cpp
autocoach.o: autocoach.cpp *.h
	$(CXX) $(CXXFLAGS) -c autocoach.cpp
cattlecar.o: cattlecar.cpp *.h
	$(CXX) $(CXXFLAGS) -c cattlecar.cpp
boxcar.o: boxcar.cpp *.h
	$(CXX) $(CXXFLAGS) -c boxcar.cpp

clean:
	rm -f *.o *.gch *~ train
