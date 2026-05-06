#!/bin/bash

TEST_DIR=test


echo ""
echo "___________ FT_PRINTF TESTER___________"
echo ""

echo "##### Test : printf return (counter) #####"
cat $TEST_DIR/difftester.log | grep -a "#-#"
echo ""

echo "##### Test : printf output #####"
cat $TEST_DIR/difftester.log | grep -a --regexp="^ft_printf" | cut -d":" --fields=2,3 > test/difftest_ft_printf.txt
cat $TEST_DIR/difftester.log | grep -a --regexp="^printf" | cut -d":" --fields=2,3 > test/difftest_printf.txt

diff  -au0 $TEST_DIR/difftest_ft_printf.txt $TEST_DIR/difftest_printf.txt \
	&& echo "SUCCESS - NO DIFF" || echo "FAILURE - STDOUT DIFF between ft_printf() and printf()"
echo ""
