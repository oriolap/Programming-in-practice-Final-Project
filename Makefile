.PHONY: clean All

All:
	@echo "----------Building project:[ UOCVineyard - Debug ]----------"
	@cd "UOCVineyard" && "$(MAKE)" -f  "UOCVineyard.mk"
	@echo "----------Building project:[ UOC20232 - Debug ]----------"
	@"$(MAKE)" -f  "UOC20232.mk"
clean:
	@echo "----------Cleaning project:[ UOCVineyard - Debug ]----------"
	@cd "UOCVineyard" && "$(MAKE)" -f  "UOCVineyard.mk"  clean
	@echo "----------Cleaning project:[ UOC20232 - Debug ]----------"
	@"$(MAKE)" -f  "UOC20232.mk" clean
