all: default_data_Types default_data2_Types sample_main sample_main2 

clean depend generated realclean check-syntax $(CUSTOM_TARGETS):
	@$(MAKE) -f Makefile.default_data_Types $(@)
	@$(MAKE) -f Makefile.default_data2_Types $(@)
	@$(MAKE) -f Makefile.sample_main $(@)
	@$(MAKE) -f Makefile.sample_main2 $(@)
	

.PHONY: default_data_Types
default_data_Types:
	@$(MAKE) -f Makefile.default_data_Types all

.PHONY: default_data2_Types
default_data2_Types: default_data2_Types
	@$(MAKE) -f Makefile.default_data2_Types all

.PHONY: sample_main
sample_main: sample_main
	@$(MAKE) -f Makefile.sample_main all

.PHONY: sample_main2
sample_main2: sample_main2
	@$(MAKE) -f Makefile.sample_main2 all




project_name_list:
	@echo default_data_Types
	@echo default_data2_Types
	@echo sample_main
	@echo sample_main2
	
