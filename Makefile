all:
	$(MAKE) -C src release
%:
	$(MAKE) -C src $(MAKECMDGOALS)
.PHONY: all

