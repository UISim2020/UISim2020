cc = g++
prom1 = release/OnlineTest
prom2 = release/SelectHubs
prom3 = release/Online
prom4 = release/Online_sp
prom5 = release/Online_ap
para = -std=c++11 -O3 -fmessage-length=0 -I include/
deps = calc.h
obj1 = OnlineTest.o Config.o Graph.o QueryProcessor2.o Node.o PrimeSim.o DataWriter.o DataReader.o TextReader.o TextWriter.o IndexManager.o
obj2 = SelectHubs.o Config.o Graph.o Node.o TextReader.o TextWriter.o IndexManager.o PrimeSim.o DataWriter.o DataReader.o HubSelection.o InDegHub.o RandomHub.o
obj3 = Online.o Config.o Graph.o QueryProcessor2.o Node.o PrimeSim.o DataWriter.o DataReader.o TextReader.o TextWriter.o IndexManager.o
obj4 = Online_sp.o Config.o Graph.o QueryProcessor3.o Node.o PrimeSim.o DataWriter.o DataReader.o TextReader.o TextWriter.o IndexManager.o
obj5 = Online_ap.o Config.o Graph.o QueryProcessor1.o Node.o PrimeSim.o DataWriter.o DataReader.o TextReader.o TextWriter.o IndexManager.o
all :$(prom1) $(prom2) $(prom3) $(prom4) $(prom5)
.PHONY : all

$(prom1): $(obj1)
	$(cc) ${para} -o $(prom1) $(obj1)

$(prom2): $(obj2)
	$(cc) ${para} -o $(prom2) $(obj2)

$(prom3): $(obj3)
	$(cc) ${para} -o $(prom3) $(obj3)

$(prom4): $(obj4)
	$(cc) ${para} -o $(prom4) $(obj4)

$(prom5): $(obj5)
	$(cc) ${para} -o $(prom5) $(obj5)

OnlineTest.o: OnlineTest.cpp
	$(cc) ${para} -c OnlineTest.cpp
	
SelectHubs.o: SelectHubs.cpp
	$(cc) ${para} -c SelectHubs.cpp

Online.o: Online.cpp
	$(cc) ${para} -c Online.cpp

Online_sp.o: Online_sp.cpp
	$(cc) ${para} -c Online_sp.cpp

Online_ap.o: Online_ap.cpp
	$(cc) ${para} -c Online_ap.cpp

Config.o: src/Config.cpp
	$(cc) ${para} -c src/Config.cpp

Graph.o: src/Graph.cpp include/NodeHash.h include/Trim.h
	$(cc) ${para} -c src/Graph.cpp

PrimeSim.o: src/PrimeSim.cpp
	$(cc) ${para} -c src/PrimeSim.cpp

Node.o: src/Node.cpp
	$(cc) ${para} -c src/Node.cpp

QueryProcessor1.o: src/QueryProcessor1.cpp
	$(cc) ${para} -c src/QueryProcessor1.cpp

QueryProcessor2.o: src/QueryProcessor2.cpp
	$(cc) ${para} -c src/QueryProcessor2.cpp

QueryProcessor3.o: src/QueryProcessor3.cpp
	$(cc) ${para} -c src/QueryProcessor3.cpp

IndexManager.o: src/IndexManager.cpp include/Trim.h
	$(cc) ${para} -c src/IndexManager.cpp

DataWriter.o: src/DataWriter.cpp
	$(cc) ${para} -c src/DataWriter.cpp

DataReader.o: src/DataReader.cpp
	$(cc) ${para} -c src/DataReader.cpp

TextWriter.o: src/TextWriter.cpp
	$(cc) ${para} -c src/TextWriter.cpp

HubSelection.o: src/HubSelection.cpp
	$(cc) ${para} -c src/HubSelection.cpp

RandomHub.o: src/RandomHub.cpp
	$(cc) ${para} -c src/RandomHub.cpp

InDegHub.o: src/InDegHub.cpp
	$(cc) ${para} -c src/InDegHub.cpp

TextReader.o: src/TextReader.cpp include/Trim.h
	$(cc) ${para} -c src/TextReader.cpp
clean:
	rm -rf $(obj1) $(prom1) $(obj2) $(prom2) $(obj3) $(prom3) $(obj4) $(prom4) $(obj5) $(prom5)