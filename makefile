.PHONY: submodules_update
submodules_update:
	@git submodule foreach git pull origin master