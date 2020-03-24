# cc = g++
# proj = test
# obj = test_mat.o mat_opt.o complex.o

# $(proj) : $(obj)
# 	g++ -o $(proj) $(obj)
# test_mat.o : test_mat.cpp complex.h mat_opt.h
# 	g++ -c -g test_mat.cpp
# mat_opt.o : mat_opt.cpp complex.h mat_opt.h
# 	g++ -c -g mat_opt.cpp
# complex.o : complex.cpp complex.h
# 	g++ -c -g complex.cpp

# clean:
# 	rm $(proj) $(obj)
cc = g++
target = test
obj = demo.o function.o mat_complex.o mat_float.o mat_uint8.o complex.o
Linked = -L/nvme/lizishi/anaconda3/envs/pytorch/lib -ltiff -lpng
rpath = -Wl,-rpath /nvme/lizishi/anaconda3/envs/pytorch/lib
Include = -I/nvme/lizishi/anaconda3/envs/pytorch/include/

$(target): $(obj)
	$(cc) $(obj) ${Include} $(Linked) $(rpath) -o $(target)

demo.o: demo.cpp
	$(cc) -c demo.cpp ${Include}

function.o: function.cpp function.h mat_complex.h mat_float.h mat_uint8.h complex.h
	$(cc) -c function.cpp ${Include}

mat_complex.o: mat_complex.cpp mat_complex.h
	$(cc) -c mat_complex.cpp

mat_float.o: mat_float.cpp mat_float.h
	$(cc) -c mat_float.cpp

mat_uint8.o: mat_uint8.cpp mat_uint8.h
	$(cc) -c mat_uint8.cpp

complex.o: complex.h
	$(cc) -c complex.cpp

.PHONY:clean
clean:
	rm $(target) $(obj)
