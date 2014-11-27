all:
	$(MAKE) -C src $(MAKEFLAGS) release
%:
	$(MAKE) -C src $(MAKEFLAGS) $(MAKECMDGOALS)
.PHONY: all

