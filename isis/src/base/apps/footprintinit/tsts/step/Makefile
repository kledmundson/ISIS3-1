APPNAME = footprintinit

include $(ISISROOT)/make/isismake.tsts

# cp so I don't destroy the input cube
commands:
	$(CP) $(INPUT)/PSP_001365_2720_RED4_0.cub $(OUTPUT)/long.cub;
	$(APPNAME) from=$(OUTPUT)/long.cub \
	           linc=1500 \
	           >& /dev/null;
	$$ISISROOT/bin/blobdump from=$(OUTPUT)/long.cub \
	                        to=$(OUTPUT)/long.txt \
	                        name=footprint \
	                        type=Polygon \
	                        >& /dev/null;
	$(CAT) $(OUTPUT)/long.txt \
	       | $(SED) 's/\([0-9]\.[0-9]\{5\}\)\([0-9]*\)/\1/g' \
	       | $(SED) -e '$$G' \
	       >& $(OUTPUT)/long.trimmed.txt;
	$(RM) $(OUTPUT)/long.cub $(OUTPUT)/long.txt;

	$(CP) $(INPUT)/PSP_001365_2720_RED4_0.cub $(OUTPUT)/wide.cub;
	$(APPNAME) from=$(OUTPUT)/wide.cub \
	           sinc=1500 \
	           >& /dev/null;
	$$ISISROOT/bin/blobdump from=$(OUTPUT)/wide.cub \
	                        to=$(OUTPUT)/wide.txt \
	                        name=footprint \
	                        type=Polygon \
	                        >& /dev/null;
	$(CAT) $(OUTPUT)/wide.txt \
	       | $(SED) 's/\([0-9]\.[0-9]\{5\}\)\([0-9]*\)/\1/g' \
	       | $(SED) -e '$$G' \
	       >& $(OUTPUT)/wide.trimmed.txt;
	$(RM) $(OUTPUT)/wide.cub $(OUTPUT)/wide.txt;
