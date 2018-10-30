# Copyright 2014-present Facebook. All Rights Reserved.
#
# This program file is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation; version 2 of the License.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program in a file named COPYING; if not, write to the
# Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor,
# Boston, MA 02110-1301 USA

binary: httpd_test.o 
	$(CC) -o httpd_test.cgi httpd_test.o  

httpd_test.o: httpd_test.c
	$(CC) -c -I /home/tohas/fbook_openbmc/openBMC_rev2/openbmc/common/recipes-core/rikcgi/files httpd_test.c

clean:
	rm -f *.o binary
