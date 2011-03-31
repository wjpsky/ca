default:
	@echo "--- Normal compilation ----------------------------------"
	@echo "make calc     produces binary in src/"
	@echo " "
	@echo "--- Cleaning up -----------------------------------------"
	@echo "make clean    recursively clean up subdirs"
	@echo " "
	@echo "--- Verification and debugging --------------------------"
	@echo "make unit      run unit tests"

calc:
	cd src && $(MAKE) calc

clean:
	cd src && $(MAKE) clean
	cd tests/unit && $(MAKE) clean

unit:
	cd src && $(MAKE) testobjs
	cd tests/unit && $(MAKE) unit
