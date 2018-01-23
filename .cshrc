# @(#)cshrc 1.11 89/11/29 SMI
umask 077
set path=(      /sbin \
		/usr/sbin \
		/bin            \
                /usr/local/bin  \
                /usr/local/gnu/bin\
                /usr/openwin/bin\
                /usr/local/X11R6/bin\
                /usr/ccs/bin    \
                /usr/bin        \
                /usr/ucb        \
                /etc \
		/usr/local/java/bin \
		$path )
if ( $?prompt ) then
        set history=32
endif

setenv MAIL /usr/spool/mail/`whoami`
limit core 0
