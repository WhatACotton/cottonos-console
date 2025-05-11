VIVADO = vivado
XSCT = xsct
DESIGN_TCL = ./tcl/flow.tcl
XSA_FILE = ./dist/design_1_wrapper.xsa

$(XSA_FILE): $(DESIGN_TCL)
	@echo "Checking if $(XSA_FILE) needs to be rebuilt..."
	@if [ ! -f $(XSA_FILE) ] || [ $(DESIGN_TCL) -nt $(XSA_FILE) ]; then \
		echo "Generating $(XSA_FILE) from $(DESIGN_TCL)..."; \
		$(VIVADO) -mode batch -source $(DESIGN_TCL) -nolog -nojournal; \
	else \
		echo "$(XSA_FILE) is up to date. Skipping build."; \
	fi

setup: $(XSA_FILE)
	@echo "Setting up the environment...";\
	${XSCT} ./tcl/setup.tcl;\
	cp -r ./vitis/src ./workspace/cottonos_console


all: $(XSA_FILE)

build:
	@echo "Building the design...";\
	${XSCT} ./tcl/build.tcl;\

run: $(XSA_FILE)
	@echo "Running the design...";\
	${XSCT} ./tcl/run.tcl
clean:
	rm -rf .gen .srcs .Xil workspace dist synth_tmp $(XSA_FILE)