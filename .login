# @(#)local.login 1.2     92/08/28 SMI
stty -istrip 
# setenv TERM `tset -Q -`

#
# if possible, start the windows system.  Give user a chance to bail out
#
limit core 0
if ( `tty` == "/dev/console" && $TERM == "sun" ) then

	if ( ${?OPENWINHOME} == 0 ) then	 
		setenv OPENWINHOME /usr/openwin
	endif			    

	echo ""
	echo -n "Starting OpenWindows in 5 seconds (type Control-C to interrupt)"
	sleep 5
	echo ""
	$OPENWINHOME/bin/openwin
	clear		# get rid of annoying cursor rectangle
	logout		# logout after leaving windows system

endif

