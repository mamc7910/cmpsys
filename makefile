CXX	=g++
CXXFLAGS= -O3 

goals: judge
	echo "Done"

filter: FilterMain.cpp Filter.cpp cs1300bmp.cc
	$(CXX) $(CXXFLAGS) -o filter FilterMain.cpp Filter.cpp cs1300bmp.cc

##
## Parameters for the test run
##
FILTERS = gauss.filter vline.filter hline.filter emboss.filter
IMAGES = boats.bmp blocks-small.bmp
TRIALS = 1 2 3 4

judge: filter
	-./Judge -p ./filter -i boats.bmp 
	-./Judge -p ./filter -i blocks-small.bmp 
  
test:
	@find filtered*bmp | xargs -I @@ bash -c 'cmp --silent @@ tests/@@ && echo @@ looks correct. || echo INCORRECT: @@ does not match the reference image tests/@@.'

clean:
	-rm filter
	-rm filtered-*.bmp
    
