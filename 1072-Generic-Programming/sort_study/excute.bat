@echo off
REM 1000 5000 10000 50000 100000 500000
REM 100 500 1000
( for %%a in (100000) do (
	(for %%b in (100 500 1000) do (
            echo %%a %%b
			Simple_main %%a %%b < %%a_%%b.in > Simple_%%a_%%b.out
		))
	))