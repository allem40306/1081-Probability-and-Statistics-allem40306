@echo off

( for %%a in (500000) do (
	(for %%b in (100 500 1000) do (
			main %%a %%b > %%a_%%b.in
		))
	))