ll:
	( cd SRC           ; make )
	( cd EXTERNAL      ; make )
	( cd TESTS/MM      ; mkdir -p OUT  ; make all)
	( cd TESTS/Lap     ; mkdir -p OUT  ; make all)
	( cd TESTS/Gen_Lap ; mkdir -p OUT  ; make all)
	( cd TESTS/Gen_MM_KPM ; mkdir -p OUT  ; make all)
	( cd TESTS/Gen_MM_Landos ; mkdir -p OUT  ; make all)
	( cd TESTS/Landos  ; mkdir -p OUT  ; make)
	( cd TESTS/Fortran ; make all)
clean:
	( cd SRC           ; make clean)
	( cd EXTERNAL      ; make clean)
	( cd TESTS/Gen_Lap ; make cleanall)
	( cd TESTS/Gen_MM_KPM ; make cleanall)	
	( cd TESTS/Gen_MM_Landos ; make cleanall)	
	( cd TESTS/MM      ; make cleanall)
	( cd TESTS/Lap     ; make cleanall)
	( cd TESTS/Landos  ; make cleanall)
	( cd TESTS/Fortran ; make clean)

docs:
	 ( doxygen Documentation/Doxyfile 2> Documentation/Doxygen-Errors.txt )
cleandocs:
	( cd Documentation; make  clean)

tests:
	+ ( cd TESTS/Gen_MM_Landos; make test_all)
	+ ( cd TESTS/Landos; make test_all)
	( echo "Passed tests" )
