# Compila programas do curso de OpenGL no ambiente Linux
# Substitua nome_do_programa pelo nome do programa ...
# ...que se est� trabalhando
#
# Antes das linhas que cont�m "gcc...", n�o pode haver espa�o em
# branco e sim uma marca de tabula��o
#
# Prof. Marco Antonio
#

# Variables
MESA = /softs/Mesa-6.0
INCPATH = -I$(MESA)/include
LIBPATH = -L$(MESA)/lib -L$(FEPIC_DIR)/Fepic/slibs
LIBS        = -lglut -lGLU -lGL -lm -lfepic
CFLAGS  = $(INCPATH) -g $(FEPIC_DIR)
LFLAGS  = $(LIBPATH) $(LIBS)

CPPSOURCES = $(wildcard *.cpp)

all: $(CPPSOURCES:.cpp=.exe)

%.o: %.cpp
	g++ -c $< $(CFLAGS) -o $@
	
%.exe: %.o
	$(CXX) $^ -o $@ $(LFLAGS)

# Clean up
clean:
	rm -f *.o *~ *.exe

msh2vtk: msh2vtk.cpp
	g++ msh2vtk.cpp -o msh2vtk -L$(FEPIC_DIR)/Fepic/slibs -lfepic


