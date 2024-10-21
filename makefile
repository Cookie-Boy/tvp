CFLAGS = -g -O0
CC = g++
EXEDIR = exec
DEPDIR = deps
OBJDIR = obj
SRC = $(wildcard *.cpp)
EXECS = $(OBJ:.o=.exe)
DEPS = $(OBJ:.o=.d)
OBJ = $(SRC:.cpp=.o)

all: $(EXEDIR) $(DEPDIR) $(OBJDIR) $(EXEDIR)/$(EXECS)
	@powershell -Command "Write-Host 'Compilation ended successfully'"

$(EXEDIR): 
	@powershell -Command "Write-Host 'ERROR no' -ForegroundColor Red -NoNewLine; Write-Host ' $(EXEDIR)' -ForegroundColor Cyan -NoNewLine; Write-Host ' directory' -ForegroundColor Red"
	@powershell -Command "Write-Host 'trying creation directory' -ForegroundColor Yellow -NoNewLine; Write-Host '...'
	@mkdir $(EXEDIR) || exit 0
	@powershell -Command "Write-Host 'succeed! :)' -ForegroundColor Green

$(DEPDIR): 
	@powershell -Command "Write-Host 'ERROR no' -ForegroundColor Red -NoNewLine; Write-Host ' $(DEPDIR)' -ForegroundColor Cyan -NoNewLine; Write-Host ' directory' -ForegroundColor Red"
	@powershell -Command "Write-Host 'trying creation directory' -ForegroundColor Yellow -NoNewLine; Write-Host '...'
	@mkdir $(DEPDIR) || exit 0
	@powershell -Command "Write-Host 'succeed! :)' -ForegroundColor Green

$(OBJDIR): 
	@powershell -Command "Write-Host 'ERROR no' -ForegroundColor Red -NoNewLine; Write-Host ' $(OBJDIR)' -ForegroundColor Cyan -NoNewLine; Write-Host ' directory' -ForegroundColor Red"
	@powershell -Command "Write-Host 'trying creation directory' -ForegroundColor Yellow -NoNewLine; Write-Host '...'
	@mkdir $(OBJDIR) || exit 0
	@powershell -Command "Write-Host 'succeed! :)' -ForegroundColor Green

$(OBJDIR)/%.o: %.cpp


%.exe: $(OBJDIR)/%.o
	@powershell -Command "Write-Host 'compiling ' -NoNewLine; Write-Host '$< ' -ForegroundColor Cyan -NoNewLine; Write-Host " in " -NoNewLine; Write-Host ' $@' -ForegroundColor Green -NoNewLine; Write-Host '...'" 
	$(CC) $(CFLAGS) $< -o $(EXEDIR)/$@
	$(CC) -MM $< > $(DEPDIR)/$*.d
	@powershell -Command "Write-Host 'successfully compiled!' -ForegroundColor Green

-include $(DEPS)

clean:
	del /Q $(EXEDIR)\*.exe