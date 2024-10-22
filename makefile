CFLAGS = -g -O0
CC = g++
EXEDIR = exec
DEPDIR = deps
OBJDIR = obj
SRC = $(wildcard *.cpp)
OBJ = $(SRC:%.cpp=$(OBJDIR)/%.o)
DEPS = $(SRC:%.cpp=$(DEPDIR)/%.d)
EXECS = $(SRC:%.cpp=$(EXEDIR)/%.exe)

all: $(EXECS)
	@powershell -Command "Write-Host 'Compilation ended successfully'"

$(EXEDIR):
	@powershell -Command "Write-Host 'ERROR no' -ForegroundColor Red -NoNewLine; Write-Host ' $(EXEDIR)' -ForegroundColor Cyan -NoNewLine; Write-Host ' directory' -ForegroundColor Red"
	@powershell -Command "Write-Host 'trying creation directory' -ForegroundColor Yellow -NoNewLine; Write-Host '...'"
	@mkdir $(EXEDIR) || exit 0
	@powershell -Command "Write-Host 'succeed! :)' -ForegroundColor Green"

$(DEPDIR):
	@powershell -Command "Write-Host 'ERROR no' -ForegroundColor Red -NoNewLine; Write-Host ' $(DEPDIR)' -ForegroundColor Cyan -NoNewLine; Write-Host ' directory' -ForegroundColor Red"
	@powershell -Command "Write-Host 'trying creation directory' -ForegroundColor Yellow -NoNewLine; Write-Host '...'"
	@mkdir $(DEPDIR) || exit 0
	@powershell -Command "Write-Host 'succeed! :)' -ForegroundColor Green"

$(OBJDIR):
	@powershell -Command "Write-Host 'ERROR no' -ForegroundColor Red -NoNewLine; Write-Host ' $(OBJDIR)' -ForegroundColor Cyan -NoNewLine; Write-Host ' directory' -ForegroundColor Red"
	@powershell -Command "Write-Host 'trying creation directory' -ForegroundColor Yellow -NoNewLine; Write-Host '...'"
	@mkdir $(OBJDIR) || exit 0
	@powershell -Command "Write-Host 'succeed! :)' -ForegroundColor Green"

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	@powershell -Command "Write-Host 'Compiling $< to $@' -ForegroundColor Cyan"
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEDIR)/%.exe: $(OBJDIR)/%.o | $(EXEDIR)
	@powershell -Command "Write-Host 'Linking $(EXEDIR)/$(@F)' -ForegroundColor Green"
	$(CC) $(CFLAGS) $< -o $@

$(DEPDIR)/%.d: %.cpp | $(DEPDIR)
	@$(CC) -MM $< > $@

-include $(DEPS)

clean:
	del /Q $(EXEDIR)\*.exe
	del /Q $(OBJDIR)\*.o
	del /Q $(DEPDIR)\*.d
