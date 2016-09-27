#
# GLOBAL STUFF
#
CPPFLAGS = $(CMOH_CFLAGS)

#
# CORE INSTALLATION
#

# installation of the headers
#
# this is a bit cumbersome, since we cannot use nobase_ without having a
# Makefile.am in include/ --which we decided against.
cmoh_sql_includes =

cmoh_sqldir = $(includedir)/cmoh/sql
cmoh_sql_HEADERS = \
	include/cmoh/sql/row.hpp \
	include/cmoh/sql/utils.hpp
cmoh_sql_includes += $(cmoh_sql_HEADERS)

cmoh_sql_statementdir = $(cmoh_sqldir)/statement
cmoh_sql_statement_HEADERS = \
	include/cmoh/sql/statement/select.hpp
cmoh_sql_includes += $(cmoh_sql_statement_HEADERS)

# use the include directory for internal builds
AM_CPPFLAGS = -I$(top_srcdir)/include


#
# DEPENDENCY TESTS
#
cmoh_sql_smoke_test_files = $(addsuffix .smoke,$(cmoh_sql_includes))
check_PROGRAMS = test/smoke
test_smoke_SOURCES = test/smoke.cpp
test_smoke_DEPENDENCIES = $(cmoh_sql_smoke_test_files)

# hack to make the compiler look at each header file
$(cmoh_sql_smoke_test_files): %.smoke: %
	$(CXXCOMPILE) -c -o $@ -x c++ - < $<


#
# MISC
#

# cleaning
CLEANFILES = $(cmoh_sql_smoke_test_files)


# things to distribute in a source tarball
EXTRA_DIST = \
	LICENSE

