APPNAME = appjit

include $(ISISROOT)/make/isismake.tsts

commands:
	$(CP) $(INPUT)/PSP_007556_2010_RED4.balance.cropped.cub $(OUTPUT);
	$(CP) $(INPUT)/PSP_007556_2010_RED5.balance.cropped.cub $(OUTPUT);
	$(LS) -1 $(OUTPUT)/*.balance.cropped.cub > from.lis;
	$(APPNAME) from=from.lis \
	master=$(OUTPUT)/PSP_007556_2010_RED5.balance.cropped.cub \
	jitter=$(INPUT)/PSP_007556_2010.txt \
	degree=2 pitchrate=0.00003084333 yaw=-0.001517547 > $(OUTPUT)/appjit.pvl;
	tabledump from=$(OUTPUT)/PSP_007556_2010_RED4.balance.cropped.cub \
	to=$(OUTPUT)/red4.instrumentPointing.csv \
	name=InstrumentPointing > /dev/null;
	tabledump from=$(OUTPUT)/PSP_007556_2010_RED5.balance.cropped.cub \
	name=InstrumentPointing \
	to=$(OUTPUT)/red5.instrumentPointing.csv > /dev/null;
	catlab from=$(OUTPUT)/PSP_007556_2010_RED5.balance.cropped.cub to=$(OUTPUT)/red5.pvl > /dev/null;
	$(RM) $(OUTPUT)/PSP_007556_2010_RED4.balance.cropped.cub $(OUTPUT)/PSP_007556_2010_RED5.balance.cropped.cub from.lis print.prt > /dev/null;
