#!/bin/bash

echo ""
echo "___________ FT_PRINTF TESTER___________"
echo ""

echo "##### Test : printf return (counter) #####"
cat tester.log | grep -a "#-#"
echo ""

echo "##### Test : printf output #####"
cat tester.log | grep -a --regexp="^ft_printf" | cut -d":" --fields=2,3 > difftest_ft_printf.txt
cat tester.log | grep -a --regexp="^printf" | cut -d":" --fields=2,3 > difftest_printf.txt

diff  -au0 difftest_ft_printf.txt difftest_printf.txt \
	&& echo "SUCCESS - NO DIFF" || echo "FAILURE - STDOUT DIFF between ft_printf() and printf()"
echo ""