#!/usr/bin/env bash

TITLE="Visualizer for task \"circuits\""
DIALOG="Do you want to select a file or directly copy-paste the output?"
A="Choose file"
B="Paste output"
WIDTH=300
VIS="visualizer.py"

ans=$(zenity --info --title "$TITLE" --text "$DIALOG" --ok-label "$A" --extra-button "$B" --width $WIDTH)
ret=$?

if [ "$ret" == "0" ] ; then
	f=$(zenity --file-selection)
	if [ $? -ne 1 ] ; then
		sed -i -e '$a\' $f

		tmpasy=$(mktemp /tmp/visXXXXXX.asy)
		$VIS < $f > $tmpasy

		cd /tmp
		tmpasy=$(basename $tmpasy)
		tmppdf=${tmpasy/.asy/.pdf}
		asy -f pdf $tmpasy

		evince $tmppdf
	fi
elif [ "$ans" != "" ] ; then
	text=$(yad --title "$TITLE" --form --field="Paste output:":TXT --width 500 --height 500 --center)
	if [ $? -ne 1 ] ; then
		tmpasy=$(mktemp /tmp/visXXXXXX.asy)
		# remove pipe character from end of string (added by yad)
		echo -e "${text%|}" | $VIS > $tmpasy

		cd /tmp
		tmpasy=$(basename $tmpasy)
		tmppdf=${tmpasy/.asy/.pdf}
		asy -f pdf $tmpasy

		evince $tmppdf
	fi
fi
