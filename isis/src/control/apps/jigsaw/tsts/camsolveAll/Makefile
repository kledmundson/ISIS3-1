APPNAME = jigsaw
# Adapted originally from observation_mode_cholmod test.
#
# This test exercises the bundle adjustment of images from the HiRISE camera onboard MRO.
# sparse method with observation mode; solving for angles (3rd degree polynomial, using 
# camsolve=all).
#
# NOTE: This test can be removed if another test tests the CAMSOLVE=ALL option.
#
# 2014-07-23 Jeannie Backer - Commented out references to bundleout_images.csv.
#                Removed default parameters.
# 2016-08-20 Ian Humphrey - Removed analogous case01 test and renamed this test from
#                observation_mode_cholmod to camsolveAll. References #4122.
include $(ISISROOT)/make/isismake.tsts

commands:
	$(CP) $(INPUT)/*.cub $(OUTPUT) > /dev/null;
	$(LS) -1 $(OUTPUT)/*.cub > $(OUTPUT)/cube.lis;
	$(APPNAME) fromlist=$(OUTPUT)/cube.lis \
	  cnet=$(INPUT)/redPntreg.net \
	  onet=$(OUTPUT)/obsmode_cholmod_out.net \
	  observations=yes \
	  update=yes \
	  cksolvedegree=3 \
	  camsolve=all \
	  twist=no > /dev/null;
	$(CAT) bundleout.txt  | grep -v "Run Time:" | grep -v "Elapsed Time:" \
	       | perl -pe 's/(^|,|: )([^,:]+\/)([^,\/:]*\.)(net|cub)/\1\3\4/g' 2>/dev/null \
	       | $(SED) 's/\([0-9][0-9]*\.[0-9][0-9][0-9][0-9][0-9]\)\([0-9][0-9]*\)/\1/g' \
	       | $(SED) s/`date +%Y-%m-%dT`\[0-2\]\[0-9\]:\[0-5\]\[0-9\]:\[0-5\]\[0-9\]/date/ \
	       | $(SED) 's/\(Iterations:\).*/\1/' \
	       > $(OUTPUT)/obsmode_cholmod_bundleout.txt
	# The above command uses sed to do the following (in order):
	# 1. remove cube filename paths
	# 2. remove net filename paths
	# 3. remove digits beyond the fifth decimal place of decimal numbers
	# 4. remove date and time
	# 5. remove number of iterations
	$(CAT) residuals.csv | $(SED) 's/,[^,]*\/\([^,\/]*\.cub\)/,\1/g'\
	       > $(OUTPUT)/obsmode_cholmod_residuals.csv
	$(CAT) bundleout_images.csv | $(SED) 's/\/[^,]*\/\([^,\/]*\.cub\)/\1/g' \
	       > $(OUTPUT)/obsmode_cholmod_bundleout_images.csv
	$(RM) bundleout_images.csv > /dev/null;
	$(RM) residuals.csv > /dev/null;
	$(MV) bundleout_points.csv $(OUTPUT)/obsmode_cholmod_bundleout_points.csv > /dev/null;
	$(RM) $(OUTPUT)/cube.lis > /dev/null;
	$(RM) bundleout.txt > /dev/null;
	cathist from=$(OUTPUT)/PSP_002733_1880_RED4.crop.cub > $(OUTPUT)/PSP4.pvl;
	cathist from=$(OUTPUT)/PSP_002733_1880_RED5.crop.cub > $(OUTPUT)/PSP5.pvl;
